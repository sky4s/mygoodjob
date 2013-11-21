#ifndef ELM_H
#define ELM_H

//#include <GearELM327.h>

void printStatus(byte status){
  switch (status)
  {
  case ELM_TIMEOUT: 
    Serial.println("ELM_TIMEOUT");
    break;
  case ELM_SUCCESS:
    Serial.println("ELM_SUCCESS");
    break;
  case ELM_NO_RESPONSE:
    Serial.println("ELM_NO_RESPONSE");
    break;
  case ELM_BUFFER_OVERFLOW:
    Serial.println("ELM_BUFFER_OVERFLOW");
    break;
  case ELM_GARBAGE:
    Serial.println("ELM_GARBAGE");
    break;
  case ELM_UNABLE_TO_CONNECT:
    Serial.println("ELM_UNABLE_TO_CONNECT");
    break;
  case ELM_NO_DATA:
    Serial.println("ELM_NO_DATA");
    break;
  default:
    Serial.print("UNKNOWN: ");
    Serial.println(status);
  }
}
 
#endif
