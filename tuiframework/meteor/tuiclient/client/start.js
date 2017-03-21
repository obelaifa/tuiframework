import { Template } from 'meteor/templating';

Template.start.onCreated(function helloOnCreated() {
});



Template.start.helpers({
});


Template.start.events({
  'click #start-button'(event, instance) {
    console.log('====> start!');
    console.log(event, instance);
    console.log('==>', $('#cdb-server-url').val());
    console.log('==>', $('#cdb-user').val());
    console.log('==>', $('#cdb-password').val());

    Meteor.call('connectTUIServer', $('#tuiserver-url').val());
  },

});
