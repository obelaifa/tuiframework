import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';

import addon from 'tuiclient';


var TUIPortsHandler = require('./TUIPortsHandler');

var tuiPortsCollection = new Mongo.Collection('TUIPorts');


Meteor.methods({
  sendPortValue(tuiObjectName, portName, value) {
    console.log("addon.emitEvent('" + tuiObjectName + "', '" + portName + "', " + JSON.stringify(value) + ")");
    addon.emitEvent(tuiObjectName, portName, value);

    tuiPortsCollection.update({"tuiObject.name": tuiObjectName, "port.name": portName},
      {
        $set: {
          value: value
        }
      },
      (err) => {
        if (err) {
          console.log('MongoDB Error: Failed to update port value')
        }
      }
    );

  }
});


Meteor.startup(() => {

  tuiPortsCollection.remove({}, (err) => {
    if (err) {
      console.log('MongoDB Error: Failed to initialize an empty Collection.')
    }
  });

  let tuiPortsHandler = new TUIPortsHandler(tuiPortsCollection);
  var cb = (err, res) => {
    let attachedObjects = addon.getAttachedObjects();
    tuiPortsHandler.init(attachedObjects);
  };

  addon.tuiclient(cb);
  let func = Meteor.bindEnvironment(() => {
    addon.processEvents();
    setTimeout(func, 10);
  });

  setTimeout(func, 1000);
});
