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
boolean am=false,fm=true;
EventDelay stepRate(500);
int cutoff=0;

LowPassFilter lpf;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please


void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  Saw1.setFreq(440); // set the frequency
  Saw2.setFreq(220);
  Saw3.setFreq(500);
  Saw4.setFreq(340);
  SawAM.setFreq(1500);
  SawFMmod.setFreq(1000);
  stepRate.start();
  lpf.setResonance(200);
  //FM OSCs
  SawFM1.setFreq(440+(2000*SawFMmod.next()));
  SawFM2.setFreq(220+(2000*SawFMmod.next()));
  SawFM3.setFreq(500+(2000*SawFMmod.next()));
  SawFM4.setFreq(340+(2000*SawFMmod.next()));
}


void updateControl(){
  // put changing controls in here
  if(stepRate.ready())
  {
    stepRate.start();
    seq=(seq+1)%4;
    //cutoff=(cutoff+1)%2000;
  }

  lpf.setCutoffFreq(15000);
  
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
      return lpf.next((Saw1.next()*SawAM.next())>>8); // return an int signal centred around 0
      }
      if(fm){
      return lpf.next((SawFM1.next()));
      }
      break;
    case 1:
      if(am){
      return lpf.next((Saw2.next()*SawAM.next())>>8); // return an int signal centred around 0
      }
      if(fm){
        return lpf.next((SawFM2.next()));
      }
      break;
    case 2:
      if(am){
      return lpf.next((Saw3.next()*SawAM.next())>>8); // return an int signal centred around 0
      }
      if(fm){
        return lpf.next((SawFM3.next()));
      }
      break;
    case 3:
      if(am){
      return lpf.next((Saw4.next()*SawAM.next())>>8); // return an int signal centred around 0
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



