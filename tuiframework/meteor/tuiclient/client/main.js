import { Template } from 'meteor/templating';
import { ReactiveVar } from 'meteor/reactive-var';


Template.main.onCreated(function helloOnCreated() {
  // counter starts at 0
  this.counter = new ReactiveVar(0);
  let instance = Template.instance();
  instance.tuiObjects = null;
  this.filter = new ReactiveVar("")
});


Template.main.helpers({
  counter() {
    //return Template.instance().counter.get();
    let entry = collection.tuiPorts.find().fetch()[0]
    if (entry !== undefined) {
      let counter = entry.value;
      //console.log('===>', entry);
      return counter;
    }
    return 0;
  },
  tuiObjectHeaderArray() {
    let instance = Template.instance();
    instance.tuiObjectNames = [];
    instance.tuiObjects = [];
    let entries = collection.tuiPorts.find().fetch();
    for (entry of entries) {
      if (instance.tuiObjectNames.indexOf(entry.tuiObject.name) === -1) {
        instance.tuiObjectNames.push(entry.tuiObject.name)
        instance.tuiObjects.push(entry.tuiObject);
      }
    }
    return instance.tuiObjects;
  },
  isTUIObjectVisible(name) {
    let instance = Template.instance();
    return instance.filter.get() == "" || name.indexOf(instance.filter.get()) !== -1;
  },
  entryArray(name) {
    return collection.tuiPorts.find({"tuiObject.name":name}).fetch()
  },
});


Template.main.events({
  'click #button-initial-settings'(event, instance) {
    Router.go('/');
  },
  'click .mylabel .mycheckbox'(event, template) {
    //console.log(template.$('.mylabel .mycheckbox').prop( "checked" ));
    console.log(event.target.checked);
    Meteor.call('testMethod', event.target.checked)
  },
  'keyup #tuiobject-search'(event, template) {
    let instance = Template.instance();
    instance.filter.set($('#tuiobject-search')[0].value);
  }
});
