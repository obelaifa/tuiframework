"use strict";

var addon = require('bindings')('tuiclient');


var cb = (err, res) => {
  console.log('===> callback: ', err, res);
  let attachedObjects = addon.getAttachedObjects();
  console.log('====> attachedObjects ', JSON.stringify(attachedObjects, null, 2));
  addon.registerEventCallback('MyTUIObjectInstance', 'Pressure', cb2);
}

var cb2 = (val) => {
  console.log('====> eventCallback: ', val);
}

addon.tuiclient(cb);

let func = () => {
  console.log('=====> after timeout')
  addon.processEvents();
  setTimeout(func, 500);
};

setTimeout(func, 1000);

console.log('=============================================>', {
  'Hallo Welten': 1
})




/*
addon.runCallback(cb);
console.log(addon.add(10, 11));

addon.testFunc({myValue: 'Test'});
addon.testFunc({myValue: 10.123});
addon.testFunc({myValue: true});
addon.testFunc({myValue: [3, 6, 8, 4, 5]});
addon.getAttachedObjects();

addon.tuiclient();

let func = () => {
  console.log('=====> after timeout')
  addon.processEvents();
  addon.getAttachedObjects();
  setTimeout(func, 500);
};

setTimeout(func, 1000);
  */