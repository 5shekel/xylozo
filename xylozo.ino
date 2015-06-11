    #include <Streaming.h>
    
    //midi lib http://arduinomidilib.fortyseveneffects.com/
    //but using http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/
    // beauce there some issues with software serial on the MIDI lib
#define DEBUG 0

 #define noteON 144//144 = 10010000 in binary, note on command
 #define noteOFF 128//128 = 10000000 in binary, note off command
 #define THRESH 50

 void setup() {
   //this broke on my nano clones
   // midiSerial.begin(31250);
   Serial.begin(31250);
}

void loop() {

    sendTrig(analogRead(A0), 50);
    sendTrig(analogRead(A1), 51);
/*
    sendTrig(analogRead(A2), 52);
    sendTrig(analogRead(A3), 53);
    sendTrig(analogRead(A5), 54);
    sendTrig(analogRead(A6), 55);
    sendTrig(analogRead(A7), 56);
*/
}

void sendTrig(int piezo, int note){
    if(piezo > THRESH){
            MIDImessage(noteON, note, piezo/4);//turn note on
            delay(2);//hold note
            MIDImessage(noteOFF, note, piezo/4);//turn note off  
    }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
