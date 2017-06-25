import { ReactiveVar } from 'meteor/reactive-var'


Template.TUIObject.onCreated(function helloOnCreated() {
  this.contentVisible = {};
  this.contentVisible.AnalogChannel = new ReactiveVar(false);
  this.contentVisible.DigitalChannel = new ReactiveVar(false);
  console.log('========>', this)
});



Template.TUIObject.helpers({
  tuiObjectName() {
    let instance = Template.instance();
    return instance.data.name;
  },
  tuiObjectType() {
    let instance = Template.instance();
    return instance.data.type;
  },
  entryArray() {
    let instance = Template.instance();
    return collection.tuiPorts.find({"tuiObject.name":instance.data.name}).fetch()
  },
  isContentVisible(portType) {
    let instance = Template.instance();

    if (!portType) {
      const keyArray = Object.keys(instance.contentVisible);
      let result = false;
      for (const key of keyArray) {
        if (instance.contentVisible[key].get()) {
          result = true;
          break;
        }
      }
      return result;
    }
    if (instance.contentVisible[portType]) {
      return instance.contentVisible[portType].get();
    }
    return false;
  }
});


Template.TUIObject.events({
  'click .AnalogChannelFilter'(event, instance) {
    instance.contentVisible.AnalogChannel.set(!instance.contentVisible.AnalogChannel.get());
  },
  'click .DigitalChannelFilter'(event, instance) {
    instance.contentVisible.DigitalChannel.set(!instance.contentVisible.DigitalChannel.get());
  },
});

