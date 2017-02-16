

Template.AnalogChannel.onCreated(function AnalogChannelOnCreated() {
  console.log('AnalogChannelOnCreated')
  this.updateSlider = true;

});


Template.AnalogChannel.onRendered(() => {
  let instance = Template.instance();

  Meteor.defer(() => {
    let min = 0;
    let max = 100;
    let step = (max - min)/100.0;
    let disabled = false;

    if ((instance.data.port.flowDirection & 2) == 0) {
      //disabled = true;
      disabled = false;
    }
    $("." + instance.data.tuiObject.name + '-' + instance.data.port.id).slider({
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
  })
});


Template.AnalogChannel.helpers({
  updater() {
    let instance = Template.instance();
    $("." + instance.data.tuiObject.name + '-' + instance.data.port.id).slider("option", "range", "min");
      if (instance.updateSlider) {
        let value = this.value;
        if (value === null) {
          value = 0;
        }
        $('.' + this.tuiObject.name + '-' + this.port.id).slider(
          {
            value: value
          }
        )
    }
  }
});