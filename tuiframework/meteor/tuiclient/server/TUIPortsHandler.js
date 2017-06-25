import addon from 'tuiclient';

var Fiber = require('fibers');
var TUIEventHandler = require('./TUIEventHandler');

const tuiPortsCollectionName = 'TUIPorts';


class TUIPortsHandler {

  constructor() {
    this.tuiPortsCollection = new Mongo.Collection(tuiPortsCollectionName);
    this.clear();
  }


  init(attachedObjects) {
    console.log('attached Objects:');

    Fiber(() => {
      //console.log(JSON.stringify(attachedObjects, null, 2));
      for (let tuiObjectInstance of attachedObjects.tuiObjectInstanceArray) {
        console.log(tuiObjectInstance);
        let tuiObjectType = attachedObjects.tuiObjectTypeObjs[tuiObjectInstance.type];
        console.log(tuiObjectType);

        let keys = Object.keys(tuiObjectType.ports);
        console.log(keys);
        let id = 1;
        for (let key of keys) {
          let port = tuiObjectType.ports[key];
          let displayName = port.name;

          if (port.name.lastIndexOf('.') !== -1) {
            displayName = port.name.substring(port.name.lastIndexOf('.') + 1, port.name.length);
          }

          //console.log('===> ', key, tuiObjectType.ports[key]);
          let doc = {
            tuiObject: {
              name: tuiObjectInstance.name,
              type: tuiObjectInstance.type,
            },
            port: {
              name: port.name,
              displayName: displayName,
              id: id,
              type: port.type,
              flowDirection: port.flowDirection,
              description: port.description,
              parameterGroupSet: port.parameterGroupSet,
            },
            value: null
          }
          ++id;
          let curFiber = Fiber.current;
          this.tuiPortsCollection.insert(doc, (err) => {
            if (err) {
              console.log('MongoDB Error: Failed to insert a TUIObject-Port document.')
            }
            curFiber.run()
          });
          Fiber.yield();
          //console.log('===>', doc)
          // console.log(id, key);
          let eventHandler = new TUIEventHandler(this.tuiPortsCollection, tuiObjectInstance.name, port.name);
          if ((port.flowDirection & 1) && (port.type == 'AnalogChannel' || port.type == 'DigitalChannel')) {
            addon.registerEventCallback(tuiObjectInstance.name, port.name, eventHandler.update, eventHandler);
          }
        }
      }
    }).run();
  }


  updateValue(tuiObjectName, portName, value) {
    this.tuiPortsCollection.update({"tuiObject.name": tuiObjectName, "port.name": portName},
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

  clear() {
    this.tuiPortsCollection.remove({}, (err) => {
      if (err) {
        console.log('MongoDB Error: Failed to initialize an empty Collection.')
      }
    });
  }

};


module.exports = TUIPortsHandler;
