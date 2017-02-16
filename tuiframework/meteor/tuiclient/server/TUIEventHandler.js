

class TUIEventHandler {
  constructor(collection, tuiObjectName, tuiPortName) {
    this.collection = collection;
    this.tuiObjectName = tuiObjectName;
    this.tuiPortName = tuiPortName;
    //console.log('====> ', this.tuiObjectName, this.tuiPortName);
  }

  update(value) {
    console.log(this.tuiObjectName, this.tuiPortName, ": ", value);
    let query = {"tuiObject.name": this.tuiObjectName, "port.name": this.tuiPortName};
    this.collection.update({"tuiObject.name": this.tuiObjectName, "port.name": this.tuiPortName},
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
}

module.exports = TUIEventHandler;
