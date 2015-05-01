NotePile note handling class
========================================


Creates a sort of malleable stack for handling note on and off actions.

Repository Contents
-------------------

* **/bringup** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/unitTest** - Misc exercises.

Version History
---------------

* [V_1.0.0](https://github.com/marshalltaylorSFE/NotePile_Note_Handler/tree/V_1.0.0) - Initial release

Basic Operation
--------------
The pile starts empty
|myNotePile|
|---|
||
Key A4 is pressed
|myNotePile|
|---|
|Note A4|
Key C4 is pressed
|myNotePile|
|---|
|Note C4|
|Note A4|
Key E4 is pressed
|myNotePile|
|---|
|Note E4|
|Note C4|
|Note A4|
Key C4 is released.  The stack is searched and C4 destroyed.
|myNotePile|
|---|
|Note E4|
|Note A4|
Key A4 is released.  The stack is searched and A4 destroyed.
|myNotePile|
|---|
|Note E4|
Key E4 is released.  The stack is searched and E4 destroyed.
|myNotePile|
|---|
|Note A4|
The pile is empty again
|myNotePile|
|---|
||

Class Diagram
-------------------
The stackDepthVar is just a uint8_t

|typedef uint8_t stackDepthVar|
|---|

Note structure (can be extended with extra data)
|struct pNote|
|---|
|int8_t noteValue|
|int8_t noteVelocity|
|int8_t notePlaying|
|pNote * lowerPNote|

Class structure
|class NotePile|Comment|
|---|---|
|stackDepthVar maxDepth||
|stackDepthVar currentDepth||
|pNote * topPNote|A pointer to the upper most note|
|pNote nullNote|special null identification|
|NotePile( stackDepthVar )|Construct with passed max depth|
|NotePile( void )||
|void pushNote( pNote & )|Pass pNote|
|pNote popNote( void )|returns pNote|
|pNote peekNote( void )||
|pNote peekNote( stackDepthVar )||
|void dropNote( stackDepthVar )|Pass position, returns pNote|
|int8_t seekNote( pNote & )|pass pNote, returns position|
|stackDepthVar stackDepth( void )|returns depth of stack.|
|void printfNotePile( void )||

The Bringup Sketch
-------------------
This example converts poly input to mono giving priority to the
last pressed key.  It outputs midi of that key, with a poor algorithm
that potentially retriggers previously mutued keys when unmuting them.

Serial data comes out through the software serial port (you'll need
somthing that can read serial off the pins).  It reports the remaining
memory between the heap and the top of stack using Arduino freeRam().


License Information
-------------------

This product is _**open source**_! 

The **code** is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

\- Your friends at SparkFun.
