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
//  The sketch outputs a series of operations on the pile to the serial
//  terminal.
//
//**********************************************************************//

//Includes
#include "NotePile.h"

//instantiates NotePile constructed to max depth of (n) stored notes
NotePile myNotePile(5);

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop()
{
  //This used to provide test note.  Can be controlled by midi
  pNote myPNote;
  Serial.println(freeRam());

  while (1)
  {
    myPNote.noteValue = 24;
    myPNote.noteVelocity = 64;
    Serial.print("Pushing note.\n");
    myNotePile.pushNote( myPNote );
    myNotePile.printfNotePile();

    myPNote.noteValue = 12;
    myPNote.noteVelocity = 32;
    Serial.print("Pushing note.\n");
    myNotePile.pushNote( myPNote );
    myNotePile.printfNotePile();

    Serial.print("Popping off the last note.\n");
    myNotePile.popNote();
    myNotePile.printfNotePile();

    myPNote.noteValue = 19;
    myPNote.noteVelocity = 40;
    Serial.print("Pushing note.\n");
    myNotePile.pushNote( myPNote );
    myNotePile.printfNotePile();

    Serial.println(freeRam());

    Serial.print("Pushing 10 notes.\n");
    for ( int i = 1; i < 10; i++)
    {
      myPNote.noteValue = i;
      myNotePile.pushNote( myPNote );
    }
    myNotePile.printfNotePile();

    Serial.print("Popping off the last note.\n");
    myNotePile.popNote();
    myNotePile.printfNotePile();

    Serial.print("Pushing 10 more notes.\n");
    for ( int i = 10; i < 20; i++)
    {
      myPNote.noteValue = i;
      myNotePile.pushNote( myPNote );
    }
    myNotePile.printfNotePile();

    Serial.println(freeRam());

    Serial.print("Seeking notevalue 19.\n");
    Serial.print("Depth: ");
    Serial.println(myNotePile.seekNote( myPNote ));
    myNotePile.printfNotePile();

    Serial.print("dropping 19.\n");
    myNotePile.dropNote(myNotePile.seekNote( myPNote ));
    myNotePile.printfNotePile();

    Serial.print("attempt to pop 10 off\n");
    for ( int i = 0; i < 10; i++ )
    {
      myNotePile.popNote();
    }
    myNotePile.printfNotePile();

    Serial.print("seeking notevalue 22\n");
    myPNote.noteValue = 22;
    Serial.print("Depth: ");
    Serial.println(myNotePile.seekNote( myPNote ));

    Serial.println(freeRam());

    delay(100);

  }

}



