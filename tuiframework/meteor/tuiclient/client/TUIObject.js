

Template.TUIObject.onCreated(function helloOnCreated() {
  let instance = Template.instance();
  instance.tuiObjects = null;
});



Template.TUIObject.helpers({
  tuiObjectName() {
    let instance = Template.instance();
    return instance.data.name;
  },
  entryArray() {
    let instance = Template.instance();
    return collection.tuiPorts.find({"tuiObject.name":instance.data.name}).fetch()
  },
});
