#include "SR04.h"
#define TRIG1_PIN 10
#define ECHO1_PIN 11
#define TRIG2_PIN 12
#define ECHO2_PIN 13
#define full_distance 10
SR04 sr_R = SR04(ECHO1_PIN,TRIG1_PIN);
SR04 sr_L = SR04(ECHO2_PIN,TRIG2_PIN);

char R_car_test(){//检测右侧车位，返回0或1
  long D;
  Serial.println("Start");
  delay(800); 
  char n=0;
  char i=0;
  while(i<15){//检测次数
   D=sr_R.Distance();//获取右侧模块的检测距离
   if(D<full_distance) ++n;//对有效距离的次数进行累计
   ++i;
   delay(20); 
  }  
  if(n>8) {//如果检测的有效距离次数达到一定数量
     return 1;
  }
  else{
     return 0;
  }
}

char L_car_test(){//检测左侧车位，返回0或1
  long D;
  Serial.println("Start");
  delay(800); 
  char n=0;
  char i=0;
  while(i<15){//检测次数
   D=sr_L.Distance();//获取左侧模块的检测距离
   if(D<full_distance) ++n;
   ++i;
   delay(20); 
  }  
  if(n>8) {
     return 1;
  }
  else{
     return 0;
  }
}
void setup() {
   Serial.begin(9600);
   Serial.println("Written by linguosen");
   delay(1000);
}

void loop() {
  if(R_car_test()) {
     Serial.println("Full");
  }
  else{
     Serial.println("Empty");
  }
  delay(5000); 
  }
