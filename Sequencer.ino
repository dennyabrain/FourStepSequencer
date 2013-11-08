/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.
  
    Demonstrates the use of Oscil to play a wavetable.
  
    Circuit: Audio output on digital pin 9 (on a Uno or similar), or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012.
    This example code is in the public domain.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/saw2048_int8.h> // sine table for oscillator
#include <EventDelay.h>
#include <LowPassFilter.h>


// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw4(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawAM(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFM1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFM2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFM3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFM4(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFMmod(SAW2048_DATA);

int seq=0;
int sawOneFreq, sawTwoFreq,sawThreeFreq,sawFourFreq=0,sawAMFreq=0;
int knobOne,knobTwo,knobThree,knobFour=0;
int pKnobOne,pKnobTwo,pKnobThree,pKnobFour=0;
boolean am=true,fm=false;
EventDelay stepRate(500);
int cutoff=0;
int mode=3;

LowPassFilter lpf;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please


void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  
  SawAM.setFreq(0);
  SawFMmod.setFreq(1000);
  stepRate.start();
  lpf.setResonance(200);
  //FM OSCs
  SawFM1.setFreq(440+(2000*SawFMmod.next()));
  SawFM2.setFreq(220+(2000*SawFMmod.next()));
  SawFM3.setFreq(500+(2000*SawFMmod.next()));
  SawFM4.setFreq(340+(2000*SawFMmod.next()));
  knobOne = mozziAnalogRead(0);
  knobOne = map(knobOne,0,1023,10,1000);
  knobTwo = mozziAnalogRead(1);
  knobTwo = map(knobTwo,0,1023,10,1000);
  knobThree = mozziAnalogRead(2);
  knobThree = map(knobThree,0,1023,10,1000);
  knobFour = mozziAnalogRead(3);
  knobFour = map(knobFour,0,1023,10,1000);
  Saw1.setFreq(knobOne);
  Saw2.setFreq(knobTwo);
  Saw3.setFreq(knobThree);
  Saw4.setFreq(knobFour);
}


void updateControl(){
  // put changing controls in here
  knobOne = mozziAnalogRead(0);
    knobOne = map(knobOne,0,1023,10,1000);
    knobTwo = mozziAnalogRead(1);
    knobTwo = map(knobTwo,0,1023,10,1000);
    knobThree = mozziAnalogRead(2);
    knobThree = map(knobThree,0,1023,10,1000);
    knobFour = mozziAnalogRead(3);
    knobFour = map(knobFour,0,1023,10,1000);
    Saw1.setFreq(knobOne);
    Saw2.setFreq(knobTwo);
    Saw3.setFreq(knobThree);
    Saw4.setFreq(knobFour);
  
  if(stepRate.ready())
  {
    stepRate.start();
    seq=(seq+1)%4;
    //cutoff=(cutoff+1)%2000;
  }

  if(mode==0){
    knobOne = mozziAnalogRead(0);
    knobOne = map(knobOne,0,1023,10,1000);
    knobTwo = mozziAnalogRead(1);
    knobTwo = map(knobTwo,0,1023,10,1000);
    knobThree = mozziAnalogRead(2);
    knobThree = map(knobThree,0,1023,10,1000);
    knobFour = mozziAnalogRead(3);
    knobFour = map(knobFour,0,1023,10,1000);
    Saw1.setFreq(knobOne);
    Saw2.setFreq(knobTwo);
    Saw3.setFreq(knobThree);
    Saw4.setFreq(knobFour);
  }
  
  else if(mode==3){
    sawAMFreq = mozziAnalogRead(3);
    sawAMFreq = map(sawAMFreq,0,1023,0,2000);
    SawAM.setFreq(sawAMFreq);    
  }

  lpf.setCutoffFreq(100);
  
  SawFM1.setFreq(1000+(20*SawFMmod.next()));
  SawFM2.setFreq(220+(20*SawFMmod.next()));
  SawFM3.setFreq(500+(20*SawFMmod.next()));
  SawFM4.setFreq(340+(20*SawFMmod.next()));
}


int updateAudio(){
  float osc;
  switch(seq){
    case 0:
      if(am){
      //return lpf.next((Saw1.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw1.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw1.next();
      }
      if(fm){
      return lpf.next((SawFM1.next()));
      }
      break;
    case 1:
      if(am){
      //return lpf.next((Saw2.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw2.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw2.next();
      }
      if(fm){
        return lpf.next((SawFM2.next()));
      }
      break;
    case 2:
      if(am){
      //return lpf.next((Saw3.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw3.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw3.next();
      }
      if(fm){
        return lpf.next((SawFM3.next()));
      }
      break;
    case 3:
      if(am){
      //return lpf.next((Saw4.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw4.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw4.next();
      }
      if(fm){
        return lpf.next((SawFM4.next()));
      }
      break;
  }
 
}


void loop(){
  audioHook(); // required here
}



