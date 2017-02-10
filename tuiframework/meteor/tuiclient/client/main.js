import { Template } from 'meteor/templating';
import { ReactiveVar } from 'meteor/reactive-var';



Template.hello.onCreated(function helloOnCreated() {
  // counter starts at 0
  this.counter = new ReactiveVar(0);
  let instance = Template.instance();
  instance.testCollection = new Mongo.Collection('TUIPorts');
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
      //console.log('===>', entry);
      return counter;
    }
    return 0;
  },
  entryArray() {
    let instance = Template.instance();
    //console.log('===========>', instance)
    //instance.localTemp = "myTest"

    return instance.testCollection.find().fetch()
  },
  tempName(param) {
   // let instance = Template.instance();
    //console.log('==> this: ', this);
    //console.log('==> instance: ', this);

    //console.log('====>', param, instance);

    //let a = "custom_" + this.port.name;
    //return a
    return param;
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

Template.myTest.helpers({
  testHelper() {
    console.log("myTest", this)
  },
});


console.log('==> Client')
Template.myTest.onRendered(function() {

  console.log('before slider');
  let a = $('.mytext').each(function(index, value) {
    console.log(value);
    $(value).slider({
      range: "min",
      min: 0,
      value: 50,
      slide: function( event, ui) {
        //console.log(this);
        //$(this).css('padding-left', '20px')
        //$(this).find('.ui-slider-range').css('border-right', '20px')
        //$(this).find('.ui-slider-range').css('border-left', '20px')

        /*
         var range = $('.ui-slider-horizontal .ui-slider-range-min');
         console.log('==> range: ', range.width());

         var handle = $( '.ui-slider-handle' ),
         handleWidth = handle.width(),
         position = handle.position(),
         marginLeft;



         handle.text(ui.value + ' years');
         if(ui.value == 4)
         marginLeft = -handleWidth/2-10;
         else if(ui.value == 5)
         marginLeft = -handleWidth-20;
         else
         marginLeft = 0;
         //handle.css('margin-left',marginLeft+'px');
         range.css('width', range.width() + 200 + 'px')
         */

      }
    })

  });


  console.log('after slider');
});