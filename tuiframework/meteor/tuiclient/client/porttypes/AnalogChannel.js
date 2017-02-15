

Template.AnalogChannel.onCreated(function AnalogChannelOnCreated() {
  console.log('AnalogChannelOnCreated')
  this.updateSlider = true;
  this.flowDirection = this.data.port.flowDirection;
  //this.flowDirection = 2;
  this.flowDirection = 2;
});


Template.AnalogChannel.onRendered(() => {

  let instance = Template.instance();

  let min = 0;
  let max = 20;
  let step = (max - min)/100.0;
  let disabled = false;

  if ((instance.flowDirection & 2) == 0) {
    disabled = true;
  }

  $("." + instance.data.tuiObject.name + '-' + instance.data.port.name).slider({
    range: "min",
    min: min,
    max: max,
    step: step,
    start: (event, ui) => {
      console.log('start', event, ui);
      instance.updateSlider = false;
    },
    stop: (event, ui) => {
      console.log('stop', event, ui);
      console.log(ui.value);
      Meteor.call('sendPortValue', instance.data.tuiObject.name, instance.data.port.name, ui.value);
      instance.updateSlider = true;
    },
    disabled: disabled
  });
});


Template.AnalogChannel.helpers({
  updater() {
    let instance = Template.instance();
      if (instance.updateSlider) {
      $('.' + this.tuiObject.name + '-' + this.port.name).slider(
        {
          value: this.value
        }
      )
    }
  }
});