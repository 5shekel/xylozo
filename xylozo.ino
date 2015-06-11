//xylo ttohw.tumblr.com

#include <Streaming.h>

#include "RF24.h" //http://tmrh20.github.io/ this is a manitned fork, the original is now radiohead
#include <SPI.h>
RF24 radio(7, 8);
typedef enum { role_xylo , role_hub } role_e;
role_e role = role_xylo;// The role of the current running sketch

byte addresses[][6] = {"1Node","2Node"};
int sns00;
uint8_t piezoVal[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.enableAckPayload();                         // We will be using the Ack Payload feature, so please enable it
  radio.enableDynamicPayloads();                    // Ack payloads are dynamic payloads

  if ( role == role_hub ) {  // Start listening
   radio.openWritingPipe(addresses[1]);
   radio.openReadingPipe(1,addresses[0]);
   radio.startListening();
    radio.printDetails();                             // Dump the configuration of the rf unit for debugging

  }else if ( role == role_xylo )  { //setup remote pins
   radio.openWritingPipe(addresses[0]);
   radio.openReadingPipe(1,addresses[1]);
   radio.stopListening(); 
 }

}

void loop() {
  if ( role == role_xylo)  {
    
    for(int iii=0; iii < sizeof(piezoVal) ;iii+=2){
      piezoVal[iii] = lowByte(analogRead(iii)); 
      piezoVal[iii+1] = highByte(analogRead(iii)); 
      }
  
    bool ok = radio.write(&piezoVal, sizeof(piezoVal));
    delay(20);


    }else if ( role == role_hub )
    if ( radio.available() )
    {
      while(radio.available()){
        radio.read(&piezoVal, sizeof(piezoVal));
       
        for(int iii=0; iii < sizeof(piezoVal); iii+=2)
          Serial<<word(piezoVal[iii+1], piezoVal[iii])<<" ";
         
         Serial.println();
        
      }
    }
  }
