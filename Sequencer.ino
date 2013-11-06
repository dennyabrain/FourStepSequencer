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


// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw1(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw3(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> Saw4(SAW2048_DATA);

int seq=0;
EventDelay stepRate(500);

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // powers of 2 please


void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  Saw1.setFreq(440); // set the frequency
  Saw2.setFreq(220);
  Saw3.setFreq(500);
  Saw4.setFreq(340);
  stepRate.start();
}


void updateControl(){
  // put changing controls in here
  if(stepRate.ready())
  {
    stepRate.start();
    seq=(seq+1)%4;
  }
}


int updateAudio(){
  switch(seq){
    case 0:
      return Saw1.next(); // return an int signal centred around 0
      break;
    case 1:
      return Saw2.next(); // return an int signal centred around 0
      break;
    case 2:
      return Saw3.next(); // return an int signal centred around 0
      break;
    case 3:
      return Saw4.next(); // return an int signal centred around 0
      break;
  }
}


void loop(){
  audioHook(); // required here
}



