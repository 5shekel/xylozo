    #include <Streaming.h>
    #include <SoftwareSerial.h>

    SoftwareSerial midiSerial(3,4 ); // RX, TX
    //midi lib http://arduinomidilib.fortyseveneffects.com/
    //but using http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/
    // beauce there some issues with software serial on the MIDI lib

#define DEBUG 1
 #define noteON 144//144 = 10010000 in binary, note on command
 #define noteOFF 128//128 = 10000000 in binary, note off command
 #define THRESH 50

 void setup() {
   midiSerial.begin(31250);
   Serial.begin(115200);
}

void loop() {

        int sns00 = analogRead(A0);
        int sns01 = analogRead(A1);
        int sns02 = analogRead(A2);
        int sns03 = analogRead(A3);
        int sns04 = analogRead(A4);
        int sns05 = analogRead(A5);
        int sns06 = analogRead(A6);
        int sns07 = analogRead(A7);
/*
    sendTrig(sns00, 50);
    sendTrig(sns01, 51);
    sendTrig(sns02, 52);
    sendTrig(sns03, 53);
    sendTrig(sns04, 54);
    sendTrig(sns05, 55);
    sendTrig(sns06, 56);
    sendTrig(sns07, 57);
*/
    if (DEBUG){
        Serial<< sns00 <<" "<<sns01 <<" "<<sns02 <<" "<<sns03 
        <<" "<<sns04 <<" "<<sns05 <<" "<<sns06 <<" "<<sns07 <<endl;
        delay(20);
    }
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
  midiSerial.write(command);//send note on or note off command 
  midiSerial.write(MIDInote);//send pitch data
  midiSerial.write(MIDIvelocity);//send velocity data
}
