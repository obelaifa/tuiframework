import { ReactiveVar } from 'meteor/reactive-var'


Template.TUIObject.onCreated(function helloOnCreated() {
  let instance = Template.instance();
  instance.tuiObjects = null;
  this.contentVisible = {};
  this.contentVisible.AnalogChannel = new ReactiveVar(false);
  this.contentVisible.DigitalChannel = new ReactiveVar(false);
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
    console.log("===> isContentVisible", portType, instance.contentVisible);
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
    return instance.contentVisible[portType].get();
  }
  },
);


Template.TUIObject.events({
  'click .AnalogChannelFilter'(event, instance) {
    instance.contentVisible.AnalogChannel.set(!instance.contentVisible.AnalogChannel.get());
    console.log('====> click tuiObject-Box')
  },
  'click .DigitalChannelFilter'(event, instance) {
    instance.contentVisible.DigitalChannel.set(!instance.contentVisible.DigitalChannel.get());
    console.log('====> click tuiObject-Box')
  },
});

