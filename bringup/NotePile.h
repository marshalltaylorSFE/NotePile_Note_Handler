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
//**********************************************************************//
#ifndef NOTESTACK_H_INCLUDED
#define NOTESTACK_H_INCLUDED

#include "stdint.h"

//Depth into the stack variable
typedef uint8_t stackDepthVar;

#define NULLNOTE -1

//Note data type
struct pNote
{
  int8_t noteValue;
  int8_t noteVelocity;
  int8_t notePlaying;
  //A pointer to the lower note
  pNote * lowerPNote;

};


//Classes
class NotePile
{
    stackDepthVar maxDepth;
    stackDepthVar currentDepth;

    //A pointer to the upper most note
  public:
    pNote * topPNote;
    pNote nullNote;

  public:
    NotePile( stackDepthVar ); //Construct with passed max depth
    NotePile( void );
    void pushNote( pNote & ); //Pass pNote
    pNote popNote( void ); //returns pNote
    pNote peekNote( void );
    pNote peekNote( stackDepthVar );
    void dropNote( stackDepthVar ); //Pass position, returns pNote
    int8_t seekNote( pNote & ); //pass pNote, returns position
    stackDepthVar stackDepth( void ); //returns depth of stack.
    void printfNotePile( void );


};

#endif // FILE_H_INCLUDED

