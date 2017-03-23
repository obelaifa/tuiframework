import { Meteor } from 'meteor/meteor';
import { Mongo } from 'meteor/mongo';

import addon from 'tuiclient';

const TUIPortsHandler = require('./TUIPortsHandler');
const TUIServerConnectionHandler = require('./TUIServerConnectionHandler');

const tuiPortsHandler = new TUIPortsHandler();
const tuiServerConnectionHandler = new TUIServerConnectionHandler(tuiPortsHandler);

Meteor.methods({
  connectTUIServer(ipAddressAndPort) {
    tuiServerConnectionHandler.connect(ipAddressAndPort);
  },
  disconnectTUIServer() {
    tuiServerConnectionHandler.disconnect();
  },
  sendPortValue(tuiObjectName, portName, value) {
    console.log("addon.emitEvent('" + tuiObjectName + "', '" + portName + "', " + JSON.stringify(value) + ")");
    addon.emitEvent(tuiObjectName, portName, value);
    tuiPortsHandler.updateValue(tuiObjectName, portName, value);
  },
});


Meteor.startup(() => {
});
