  #include <Streaming.h>
  #include "RF24.h" //http://tmrh20.github.io/ this is a manitned fork, the original is now radiohead
  #include <SPI.h>
  RF24 radio(7, 8);
  typedef enum { role_xylo , role_hub } role_e;
  role_e role = role_hub;// The role of the current running sketch
  
  byte addresses[][6] = {"1Node","2Node"};


  int sns00;

void setup() {
    radio.begin();
   Serial.begin(115200);

   if ( role == role_hub ) {  // Start listening
   radio.openWritingPipe(addresses[1]);
   radio.openReadingPipe(1,addresses[0]);
   radio.startListening();
 }

  if ( role == role_xylo )  { //setup remote pins
   radio.openWritingPipe(addresses[0]);
   radio.openReadingPipe(1,addresses[1]);
   radio.stopListening(); 
 }

}

void loop() {
  if ( role == role_xylo)  {
    sns00=analogRead(0);
    bool ok = radio.write(&sns00, sizeof(int));
    delay(1000);
  }
  if ( role == role_hub )
   if ( radio.available() )
    {
      while(radio.available()){
        radio.read(&sns00, sizeof(int));
        Serial<<sns00<<endl;
      }
    }
}
