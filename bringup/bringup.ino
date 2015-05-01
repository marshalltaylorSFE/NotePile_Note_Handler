//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  420, 2015
//
//  The sketch takes midi input data and saves it to a dynamic link list.
//  It's kind of like a stack, but with random access.  When the note off
//  data is detected, it seeks and destroys the note.
//
//  This example also converts poly input to mono giving priority to the
//  last pressed key.  It outputs midi of that key, with a poor algorithm
//  that potentially retriggers previously mutued keys when unmuting them.
//
//  Serial data comes out through the software serial port (you'll need
//  somthing that can read serial off the pins).  It reports the remaining
//  memory between the heap and the top of stack using Arduino freeRam().
//
//**********************************************************************//

//Includes
#include "NotePile.h"
#include <AltSoftSerial.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

//instantiates NotePile constructed to max depth of ( stackDepthVar inputDepth ) stored notes
NotePile myNotePile(5);//Starts empty, depth = 0;

AltSoftSerial altSerial;  

pNote myPNote;  //This is the main 
uint8_t actionpending = 0;  //flag

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Do whatever you want when a note is pressed.
  actionpending = 1; //flag for loop action
  //Build the note
  myPNote.noteValue = pitch;
  pNote oldPNote;
  myPNote.noteVelocity = velocity;
  if(myNotePile.seekNote( myPNote ) == -1)//If the note doesn't exist yet
  {
    //Turn off the last note
    
    oldPNote = myNotePile.peekNote();
    //oldPNote->notePlaying = 0;
    MIDI.sendNoteOff(oldPNote.noteValue, 0, 1);
    
    //Push the new note, and turn it on
    
    //myPNote.notePlaying = 1;
    myNotePile.pushNote( myPNote );
    MIDI.sendNoteOn(myPNote.noteValue, 127, 1);
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Do something when the note is released.
  // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
  actionpending = 1;
  myPNote.noteValue = pitch;
  int notePos = myNotePile.seekNote( myPNote );
  pNote oldPNote;
  if(notePos == 0)
  {
    MIDI.sendNoteOff(myPNote.noteValue, 0, 1);
    myNotePile.dropNote(notePos);
    if(myNotePile.stackDepth() > 0)
    {
      //Turn on previous note
      oldPNote = myNotePile.peekNote();
      MIDI.sendNoteOn(oldPNote.noteValue, 127, 1);
    }
  }
  else
  {  
    myNotePile.dropNote(notePos);
  }


  
}

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  altSerial.begin(57600);
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);

  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
}

void loop()
{

  MIDI.read();  
  if(actionpending)
  {
    actionpending = 0;
    //if(myNotePile.stackDepth() > 0)
    //{
    //  myPNote = myNotePile.peekNote();
    //  MIDI.sendNoteOn(myPNote.noteValue,127,1);
    //  myNotePile.pl
    //}
    myNotePile.printfNotePile();
    altSerial.println(freeRam());

  }
}



