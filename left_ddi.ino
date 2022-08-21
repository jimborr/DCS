
#include <PCF857X.h>
#include <DcsBios.h>


 /* Instantiate a ProtocolParser object to parse the DCS-BIOS export stream */
DcsBios::ProtocolParser parser;
 /* Declare a Master Caution Reset button on pin 10 */

PCF857X Expander[4];

int lastState[4][8]; // Store the "old" state of the Input pins, (MCP)(Bank)(Pin)

void setup(){


Serial.begin(500000);
  Expander[1].begin(0x20);
  Expander[3].begin(0x21);
  Expander[0].begin(0x22);
  Expander[2].begin(0x23); // done

    for (int i = 0; i <= 3; i++) {
        Expander[i].pinMode(0, INPUT);
        Expander[i].pinMode(1, INPUT);
        Expander[i].pinMode(2, INPUT);
        Expander[i].pinMode(3, INPUT);
        Expander[i].pinMode(4, INPUT);
    }


}

void loop() {
  // feed incoming data to the parser
  while (Serial.available()) {
      parser.processChar(Serial.read());
  }
  
  // poll inputs
  DcsBios::PollingInput::pollInputs();
  
  //Switch2Pos ("UFC_MASTER_CAUTION","TOGGLE", 0, 0); // Here we define A 2 Position switch on Expander 0, Pin 0
  
  Switch2Pos ("LEFT_DDI_PB_01","",0,4);
  Switch2Pos ("LEFT_DDI_PB_02","",0,3);
  Switch2Pos ("LEFT_DDI_PB_03","",0,2);
  Switch2Pos ("LEFT_DDI_PB_04","",0,1);
  Switch2Pos ("LEFT_DDI_PB_05","",0,0);
  
  Switch2Pos ("LEFT_DDI_PB_06","",1,0);
  Switch2Pos ("LEFT_DDI_PB_07","",1,1);
  Switch2Pos ("LEFT_DDI_PB_08","",1,2);
  Switch2Pos ("LEFT_DDI_PB_09","",1,3);
  Switch2Pos ("LEFT_DDI_PB_10","",1,4);

  Switch2Pos ("LEFT_DDI_PB_11","",2,0);
  Switch2Pos ("LEFT_DDI_PB_12","",2,1);
  Switch2Pos ("LEFT_DDI_PB_13","",2,2);
  Switch2Pos ("LEFT_DDI_PB_14","",2,3);
  Switch2Pos ("LEFT_DDI_PB_15","",2,4);

  Switch2Pos ("LEFT_DDI_PB_16","",3,4);
  Switch2Pos ("LEFT_DDI_PB_17","",3,3);
  Switch2Pos ("LEFT_DDI_PB_18","",3,2);
  Switch2Pos ("LEFT_DDI_PB_19","",3,1);
  Switch2Pos ("LEFT_DDI_PB_20","",3,0);
  
  
}
 
void sendDcsBiosMessage(const char* msg, const char* arg) {
  Serial.write(msg);
  Serial.write(' ');
  Serial.write(arg);
  Serial.write('\n');
}
  
  
void onDcsBiosWrite(unsigned int address, unsigned int value) {
  
}

 // Define our I2C version of Switch2Pos (for pcf8574)
void Switch2Pos(char* msg, char* arg, int chip, int pin) {
 char state = Expander[chip].digitalRead(pin); // reads the Pin of the MCP
 if (state != lastState[chip][pin]) {
  //Serial.write(state);
  sendDcsBiosMessage(msg, state == 1 ? "0" : "1");
 }
 lastState[chip][pin] = state;
}
