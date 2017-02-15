

Template.DigitalChannel.onCreated(function DigitalChannelOnCreated() {
  console.log('DigitalChannelOnCreated')
  this.flowDirection = this.data.port.flowDirection;
});


Template.DigitalChannel.onRendered(() => {
  let instance = Template.instance();
  let disabled = false;

  if ((instance.flowDirection & 2) == 0) {
    disabled = true;
  }

  $("#" + instance.data.tuiObject.name + '-' + instance.data.port.name).buttonset();

  let a = $("input[name='radio-" + instance.data.tuiObject.name + '-' + instance.data.port.name + "']").attr('disabled', disabled);
  $("input[name='radio-" + instance.data.tuiObject.name + '-' + instance.data.port.name + "']").button('option', 'disabled', disabled);
  console.log(a);
});


Template.DigitalChannel.helpers({
  updater() {
    let instance = Template.instance();
    console.log('!!!!!')

    if (instance.buttonState !== this.value) {
      instance.buttonState = this.value;
      /*
      if (this.value) {
        $("#radio-1-" + instance.data.tuiObject.name + '-' + instance.data.port.name).prop("checked", true);
      } else {
        $("#radio-2-" + instance.data.tuiObject.name + '-' + instance.data.port.name).prop("checked", true);
      }
      */
      if (this.value) {
        $("label[for='radio-1-" + instance.data.tuiObject.name + '-' + instance.data.port.name).addClass('ui-state-active');
        $("label[for='radio-2-" + instance.data.tuiObject.name + '-' + instance.data.port.name).removeClass('ui-state-active');
      } else {
        $("label[for='radio-1-" + instance.data.tuiObject.name + '-' + instance.data.port.name).removeClass('ui-state-active');
        $("label[for='radio-2-" + instance.data.tuiObject.name + '-' + instance.data.port.name).addClass('ui-state-active');
      }
    }
  }
});


Template.DigitalChannel.events({
  'click label': function(event) {
    let instance = Template.instance();
    let radio1 = "radio-1-" + instance.data.tuiObject.name + '-' + instance.data.port.name;
    let radio2 = "radio-2-" + instance.data.tuiObject.name + '-' + instance.data.port.name;
    let id = event.currentTarget.control.id;
    if (id === radio1) {
      console.log('radio1');
      Meteor.call('sendPortValue', instance.data.tuiObject.name, instance.data.port.name, true);
    }
    if (id === radio2) {
      Meteor.call('sendPortValue', instance.data.tuiObject.name, instance.data.port.name, false);

    }
  }
});