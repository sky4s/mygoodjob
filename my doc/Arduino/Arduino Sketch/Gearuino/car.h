#ifndef CAR_H
#define CAR_H

//============================================================================
// Car define
//============================================================================
//#define LANCER_FORTIS
#ifdef LANCER_FORTIS
static const float TireRound = 2.049575047;
static const float GearRatio[] ={
  10.71,
  14.37588,
  8.54964,
  6.57288,
  5.09184,
  3.86172,
  3.17016,
};
static const int MaxGear = 7;
#else
static const float TireRound = 1.8893538219;
static const float GearRatio[] ={
  15.265971,
  15.256715,
  9.460955,
  6.250908,
  4.444413,
  3.376965,
  2.73429
};
static const int MaxGear = 7;
#endif
#define AFR 14.7
//============================================================================

static float gearrpm[MaxGear];
byte getGearPosition(int rpm,byte speed) {
  for(int x=0;x<MaxGear;x++) {
    gearrpm[x] = speed*GearRatio[x]/TireRound*1000/60;
  }
  float minDelta = 3.4028235E+38;
  byte minIndex=0;
  for(byte x=1;x<MaxGear;x++) {
    float delta = abs( gearrpm[x] -rpm);
    if(delta<minDelta) {
      minDelta = delta;
      minIndex = x;
    }
  }
  //  Serial.println(String(rpm)+" "+String(speed));
  return minIndex;
}

float getKPL(byte vss,unsigned int maf) {
  return 302.15* vss / maf;
}

float getKPL(int rpm,byte map,int iat,float ve) {
  return 0;
}


#endif
