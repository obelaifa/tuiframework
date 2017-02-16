import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';

import addon from 'tuiclient';


var TUIPortsHandler = require('./TUIPortsHandler');

Meteor.methods({
  testMethod(checked) {
    console.log('====> Meteor testMethod, checked: ', checked);
    addon.emitEvent('MyTUIObjectInstance', 'LED', checked);
    return true;
  },
  sendPortValue(tuiObjectName, portName, value) {
    console.log("addon.emitEvent('" + tuiObjectName + "', '" + portName + "', " + JSON.stringify(value) + ")");
    addon.emitEvent(tuiObjectName, portName, value);
  }
});


Meteor.startup(() => {
  let tuiPortsHandler = new TUIPortsHandler('TUIPorts');
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
