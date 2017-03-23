import { Template } from 'meteor/templating';

Template.start.onCreated(function helloOnCreated() {
});



Template.start.helpers({
  connectionState() {
    let doc = collection.connectionState.findOne();
    return doc == undefined ? 'disconnected' : doc.state;
  },
  isConnected() {
    let doc = collection.connectionState.findOne();
    let state = doc == undefined ? 'disconnected' : doc.state;
    return state == 'connected';
  },
  isDisconnected() {
    let doc = collection.connectionState.findOne();
    let state = doc == undefined ? 'disconnected' : doc.state;
    return state == 'disconnected';
  }
});


Template.start.events({
  'click #button-tuiserver-connect'(event, instance) {
    console.log(event, instance);
    console.log('==>', $('#cdb-server-url').val());
    console.log('==>', $('#cdb-user').val());
    console.log('==>', $('#cdb-password').val());

    Meteor.call('connectTUIServer', $('#tuiserver-url').val());
  },
  'click #button-tuiserver-disconnect'(event, instance) {
    Meteor.call('disconnectTUIServer');
  },
  'click #button-start'(event, instance) {
    Router.go('main');
  },
});
