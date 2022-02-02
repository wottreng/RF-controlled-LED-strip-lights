/*
my EEPROM lib
class to help with eeprom writing and reading strings
*/
#include <Arduino.h>
#include <string.h>
#include <EEPROM.h>

// custom lib
#include "myEEPROM.h"

#define max_data_length 20

//initialize eeprom
void EEPROM_tools_c::init(){
     EEPROM.begin(512);//eeprom is 512bytes in size
}

// EEPROM commands =====================================================
void EEPROM_tools_c::write_to_EEPROM(String data,int address){
  uint8_t dataLength = data.length();
  char charInput[dataLength + 1];
  // string to char array
  strcpy(charInput, data.c_str());
  // write to EEPROM
  EEPROM.write(address, dataLength);
  for (int i = 0; i < dataLength; i++) {
    EEPROM.write(address + 1 + i, charInput[i]);
  }
  EEPROM.commit();//flush, write content to eeprom
}



// read eeprom
String EEPROM_tools_c::read_eeprom(int address) {
  uint8_t dataLength = EEPROM.read(address);
  String data;
  uint8_t a;
    if(dataLength > max_data_length){
        return "---";
    } else {
        for (int i = 0; i < dataLength; i++) {
            a = EEPROM.read(address + 1 + i);
            data += char(a);
        }
    }
  return data;
  }
  
EEPROM_tools_c EEPROM_tools;