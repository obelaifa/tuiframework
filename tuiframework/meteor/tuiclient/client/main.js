import { Template } from 'meteor/templating';
import { ReactiveVar } from 'meteor/reactive-var';



Template.hello.onCreated(function helloOnCreated() {
  // counter starts at 0
  this.counter = new ReactiveVar(0);
  let instance = Template.instance();
  instance.testCollection = new Mongo.Collection('test');
  console.log('==>', instance);
  console.log('==>', instance.testCollection);
});


Template.hello.helpers({
  counter() {
    //return Template.instance().counter.get();
    let instance = Template.instance();
    let entry = instance.testCollection.find().fetch()[0]
    if (entry !== undefined) {
      let counter = entry.value;
      console.log('===>', entry);
      return counter;
    }
    return 0;
  },
});


Template.hello.events({
  'click button'(event, instance) {
  },
  'click .mylabel .mycheckbox'(event, template) {
    //console.log(template.$('.mylabel .mycheckbox').prop( "checked" ));
    console.log(event.target.checked);
    Meteor.call('testMethod', event.target.checked)
  }

});
