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
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <EventDelay.h>
#include <LowPassFilter.h>


// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw4(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawAM(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFMmod(SAW2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinFMmod(SIN2048_DATA);

int seq=0;
int sawOneFreq, sawTwoFreq,sawThreeFreq,sawFourFreq=0,sawAMFreq=0,sinFMFreq=0;
int knobOne,knobTwo,knobThree,knobFour=0;
int pKnobOne,pKnobTwo,pKnobThree,pKnobFour=0;
boolean am=true,fm=false;
EventDelay stepRate(500);
EventDelay modeChange(5000);
int cutoff=0;
int mode=0;
int flag=0;

LowPassFilter lpf;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please


void setup(){
  //Serial.begin(9600);
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  
  SawAM.setFreq(0);
  SinFMmod.setFreq(0);
  stepRate.start();
  modeChange.start();
  lpf.setResonance(200);

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
  sawOneFreq = knobOne;
  sawTwoFreq = knobTwo;
  sawThreeFreq = knobThree;
  sawFourFreq = knobFour;
}


void updateControl(){
  /*knobOne = mozziAnalogRead(0);
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
  sawOneFreq = knobOne;
  sawTwoFreq = knobTwo;
  sawThreeFreq = knobThree;
  sawFourFreq = knobFour;*/
  /*
  Serial.println(sawOneFreq);
  Serial.println(sawTwoFreq);
  Serial.println(sawThreeFreq);
  Serial.println(sawFourFreq);
  Serial.println("-----");
  delay(50);*/
  // put changing controls in here
 /*   Saw1.setFreq(sawOneFreq);
    Saw2.setFreq(sawTwoFreq);
    Saw3.setFreq(sawThreeFreq);
    Saw4.setFreq(sawFourFreq);
  */
  
  
  /*Serial.println(sawOneFreq);
  Serial.println(sawTwoFreq);
  Serial.println(sawThreeFreq);
  Serial.println(sawFourFreq);
  Serial.println("-----");*/
  
  
  if(stepRate.ready())
  {
    stepRate.start();
    seq=(seq+1)%4;
    //cutoff=(cutoff+1)%2000;
  }
  
  if(modeChange.ready()){
    mode=3;
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
    sawOneFreq = knobOne;
    sawTwoFreq = knobTwo;
    sawThreeFreq = knobThree;
    sawFourFreq = knobFour;
    Saw1.setFreq(sawOneFreq);
    Saw2.setFreq(sawTwoFreq);
    Saw3.setFreq(sawThreeFreq);
    Saw4.setFreq(sawFourFreq);
  }
  
  if(mode==3){
    
    Saw1.setFreq(sawOneFreq);
    Saw2.setFreq(sawTwoFreq);
    Saw3.setFreq(sawThreeFreq);
    Saw4.setFreq(sawFourFreq);
    sawAMFreq = mozziAnalogRead(3);
    sawAMFreq = map(sawAMFreq,0,1023,0,2000);
    SawAM.setFreq(sawAMFreq);    
    
    sinFMFreq = mozziAnalogRead(2);
    sinFMFreq = map(sinFMFreq,0,1023,0,2000);
    SinFMmod.setFreq(sinFMFreq);     
  }

  //lpf.setCutoffFreq(100);
  
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
      //return lpf.next((SawFM1.next()));
      return Saw1.phMod(20*SinFMmod.next());
      }
      break;
    case 1:
      if(am){
      //return lpf.next((Saw2.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw2.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw2.next();
      }
      if(fm){
      //return lpf.next((SawFM2.next()));
      return Saw2.phMod(20*SinFMmod.next());
      }
      break;
    case 2:
      if(am){
      //return lpf.next((Saw3.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw3.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw3.next();
      }
      if(fm){
      //return lpf.next((SawFM3.next()));
      return Saw3.phMod(20*SinFMmod.next());
      }
      break;
    case 3:
      if(am){
      //return lpf.next((Saw4.next()*SawAM.next())>>8); // return an int signal centred around 0
      return ((Saw4.next()*SawAM.next())>>8); // return an int signal centred around 0
      //return Saw4.next();
      }
      if(fm){
      //return lpf.next((SawFM4.next()));
      return Saw4.phMod(20*SinFMmod.next());
      }
      break;
  }

}


void loop(){
  audioHook(); // required here
}



