//**********************************************************************//
//  BEERWARE LICENSE
//
//  This code is free for any use provided that if you meet the author
//  in person, you buy them a beer.
//
//  This license block is BeerWare itself.
//
//  Written by:  Marshall Taylor
//  Created:  March 21, 2015
//
//  depth 0 is 0 notes.  Shall point to null
//
//
//**********************************************************************//

//Includes
#include "NotePile.h"
#include "stdint.h"
#include "Arduino.h"
#include <AltSoftSerial.h>

extern AltSoftSerial altSerial;

//**********************************************************************//
//  NotePile Class
//
//  Creates link list
//
//  Construct with passed max depth or use default 4
//
NotePile::NotePile( stackDepthVar inputDepth )
{
  topPNote = &nullNote;  //start pointed to null note
  currentDepth = 0 ;  //Size 0
  maxDepth = inputDepth;  //set max size
  nullNote.noteValue = -1;  //define null note
  nullNote.noteVelocity = -1;  //define null note
}
NotePile::NotePile( void )
{
  topPNote = &nullNote;
  currentDepth = 0;
  maxDepth = 4;
  nullNote.noteValue = -1;
  nullNote.noteVelocity = -1;

}

//Pass pNote to be pushed to the stack (top)
void NotePile::pushNote( pNote & noteToPush )
{
  //This creates a new note object, but then forgets the name
  //and doesn't delete the note.
  //
  //If the stack size is too big, new notes won't be accepted
  if ( currentDepth < maxDepth )
  {
    //Make a new note to the heap
    pNote *newPNote = new pNote;
    //grow stack size
    currentDepth++;
    //Set the new note's params
    newPNote->noteValue = noteToPush.noteValue;
    newPNote->noteVelocity = noteToPush.noteVelocity;
    //Point the top of stack to the new note
    newPNote->lowerPNote = topPNote;
    topPNote = newPNote; //equals the address of the new note
  }

}

//returns pNote
pNote NotePile::popNote( void )
{
  //Target note variable
  pNote * noteToDestroy;

  if (currentDepth > 0) //If there are any notes on the stack,
  {
    noteToDestroy = topPNote;
    //move top pointer
    topPNote = noteToDestroy->lowerPNote;
    //destruct topPNote by topStack
    delete noteToDestroy;
    currentDepth--;

    //If depth now == 0, point top to null
    if (currentDepth == 0)
    {
      topPNote = &nullNote;
    }
  }

  return *topPNote;
}

//returns pNote
pNote NotePile::peekNote( void )
{
  pNote * noteToReturn;
  noteToReturn = topPNote;
  return *noteToReturn;
}

//returns pNote
pNote NotePile::peekNote( stackDepthVar inputDepth ) //position 0 = top
{
  pNote * noteToReturn;

  if (inputDepth < maxDepth) //Prevent out of range peeks
  {
    noteToReturn = topPNote;
    //Iterate to the depth
    for ( uint8_t i = 0; i < inputDepth; i++ )
    {
      noteToReturn = noteToReturn->lowerPNote;
    }
  }
  else
  {
    noteToReturn = &nullNote;
  }
  return *noteToReturn;
}

//Pass position, returns void
void NotePile::dropNote( stackDepthVar depthToDrop )
{
  //Check depth
  if ( depthToDrop == 0 )
  {
    //If depth is 0 and there is a note on top, pop it
    if (topPNote != &nullNote)
    {
      popNote();
    }

  }
  else if ( depthToDrop >= currentDepth )
  {
    //Too deep!  Do nothing.
  }
  else
  {
    //Ok, good to do it.

    //pointer for note above note to drop
    pNote * noteAbove = topPNote;
    //pointer for note to drop
    pNote * noteToDrop;
    //go to the depth above the one to drop
    for (uint8_t i = 0; i < (depthToDrop - 1); i++ )
    {
      noteAbove = noteAbove->lowerPNote;
    }
    //point the note to drop
    noteToDrop = noteAbove->lowerPNote;
    //Redirect the note above
    noteAbove->lowerPNote = noteToDrop->lowerPNote;//noteToDrop->lowerPNote;
    //Drop it like it's hot
    delete noteToDrop;
    currentDepth--;
  }

}

//pass pNote, returns position
int8_t NotePile::seekNote( pNote & noteToSeek )
{
  //Create temporary note to use for comparison
  pNote * noteVar;
  noteVar = topPNote;
  int8_t returnVar = -1;

  for (uint8_t i = 0; i < currentDepth; i++)
  {
    //For now, only use the notevalue
    if ( noteVar->noteValue == noteToSeek.noteValue )
    {
      returnVar = i;
    }
    //Walk down into the stack
    noteVar = noteVar->lowerPNote;
  }
  return returnVar;
}

//returns depth of stack.
stackDepthVar NotePile::stackDepth( void )
{
  return currentDepth;
}

//printfs the stack
void NotePile::printfNotePile( void )
{
  pNote * noteToPrint;
  long output;
  noteToPrint = topPNote;
  altSerial.println("\n Pos, value, address");
  altSerial.println(  "-------------------------");
  //Iterate to the depth
  for ( uint8_t i = 0; i < currentDepth; i++ )
  {
    altSerial.print(" ");
    altSerial.print(i);
    altSerial.print(", ");
    altSerial.print(noteToPrint->noteValue);
    altSerial.print(", ");
    output = (long)noteToPrint;
    altSerial.println(output, HEX);
    
    //move note
    noteToPrint = noteToPrint->lowerPNote;

  }
}

