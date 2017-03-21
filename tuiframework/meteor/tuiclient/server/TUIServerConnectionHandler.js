import { Mongo } from 'meteor/mongo';
import addon from 'tuiclient';

const senderPort = 8998;
const receiverPort = 8999;

const disconnected = 'disconnected';
const connecting = 'connecting';
const connected = 'connected';

const connectingTimeout = 5000;


class TUiServerConnectionHandler {

  constructor(tuiPortsHandler) {
    this.tuiPortsHandler = tuiPortsHandler;
    this.connectionStateCollection = new Mongo.Collection('ConnectionState');
    this.connectionStateCollection.remove({}, (err) => {
      if (err) {
        console.log('MongoDB Error: Failed to initialize an empty Collection.')
      }
    });

    this.setState(disconnected);
  }


  setState(newState) {
    console.log('===> StateChange: ', this.state, ' -> ', newState);
    this.state = newState;
  }


  isCurrentStateEqualTo(state2) {
    return this.state == state2;
  }


  connect(ipAddressAndPort) {
    if ( ! this.isCurrentStateEqualTo(disconnected)) {
      return;
    }
    this.setState(connecting);

    let timeoutCallback = () => {
      if (this.isCurrentStateEqualTo(connecting)) {
        this.disconnect();
      }
    }
    setTimeout(timeoutCallback, connectingTimeout);

    var connectedCallback = (err, res) => {
      if (this.isCurrentStateEqualTo(connecting)) {
        let attachedObjects = addon.getAttachedObjects();
        this.tuiPortsHandler.init(attachedObjects);
        this.setState(connected);
      } else {
        this.disconnect();
      }
    };
    addon.connect(senderPort, receiverPort, ipAddressAndPort, connectedCallback);

    let func = Meteor.bindEnvironment(() => {
      if (this.isCurrentStateEqualTo(connecting) || this.isCurrentStateEqualTo(connected)) {
        addon.processEvents();
      }
      setTimeout(func, 10);
    });
    setTimeout(func, 1000);
  }


  disconnect() {
    addon.disconnect();
    this.setState(disconnected);
  }

}


module.exports = TUiServerConnectionHandler;
