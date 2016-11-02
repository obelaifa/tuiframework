import { Meteor } from 'meteor/meteor';

import addon from 'tuiclient';
//const addon = require('tuiclient');


Meteor.methods({
  testMethod(checked) {
    console.log('====> Meteor testMethod, checked: ', checked);
    addon.emitEvent('MyTUIObjectInstance', 'LED', checked);
    return true;
  }
});


Meteor.startup(() => {

  let testCollection = new Mongo.Collection('test');

  var cb2 = Meteor.bindEnvironment((value) => {
    console.log('===> event: ', value);
    testCollection.remove({});
    testCollection.insert({value: value});
  });

  var cb = Meteor.bindEnvironment((err, res) => {
    console.log('===> callback: ', err, res);
    let attachedObjects = addon.getAttachedObjects();
    console.log('====> attachedObjects ', JSON.stringify(attachedObjects, null, 2));
    addon.registerEventCallback('MyTUIObjectInstance', 'Pressure', cb2);
  });

  addon.tuiclient(cb);

  let func = Meteor.bindEnvironment(() => {
    addon.processEvents();

    setTimeout(func, 0);
  });

  setTimeout(func, 1000);

});

/*
*
*
* TODO concept of TUIObjects how should they look like
* Create Test scenario
* Store the received data in mongodb, which should be available in mini mongo
*
* Start with Frontend logic
*
*
*
*/