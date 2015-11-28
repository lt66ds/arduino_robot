/*
  ROBOT
*/
#include "SR04.h"
/*LEFT_1 左电机前向口
 *LEFT_2 左电机后向口
 *RIGHT_1 右电机前向口
 *RIGHT_1 右电机后向口
*/

#define LEFT_1 6
#define LEFT_2 7
#define RIGHT_1 8
#define RIGHT_2 9  

/*L2PIN 左1光线传感器
 *L1PIN 左2光线传感器
 *R1PIN 右1光线传感器
 *R2PIN 右2光线传感器
*/

#define L2PIN 4
#define L1PIN 3
#define R1PIN 2
#define R2PIN 5

//单边检测到线就要触发检测?
//单边请设为true
//否则双边均检测到线才触发
bool oneSideDetectAsCross=true;

//检测车位阈值
int full_distance=3;

//检测车位计数器相关
#define MAXCROSS 10
int counter=0;
int carPos[]={};

unsigned long startTime=2000;
unsigned long stopTime=0;



#define TRIG1_PIN 10
#define ECHO1_PIN 11
#define TRIG2_PIN 12
#define ECHO2_PIN 13
#define full_distance 10
SR04 sr_R = SR04(ECHO1_PIN,TRIG1_PIN);
SR04 sr_L = SR04(ECHO2_PIN,TRIG2_PIN);







void findPath()
{
  int L1=digitalRead(L1PIN);
  int R1=digitalRead(R1PIN);
  motoStop();
  if (L1==HIGH && R1==HIGH)
  {
     forward();
  }
  else if (L1==HIGH)
  {
     rotateRight();
  }
  else if (R1==HIGH)
  {
    rotateLeft();
  }
  delay(10);  
}






char R_car_test(){//检测右侧车位，返回0或1
  long D;
  Serial.println("Start");
  //delay(800); 
  char n=0;
  char i=0;
  while(i<15){//检测次数
   D=sr_R.Distance();//获取右侧模块的检测距离
   if(D<full_distance) ++n;//对有效距离的次数进行累计
   ++i;
   findPath(); 
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
  //delay(800); 
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





/*************************
 *void sendMsg(int count,char info)
 *发送车位检测的消息
*************************/
void sendMsg(int count,char info)
{
  
}




/*************************
 *void leftFd()
 *小车左轮前进
*************************/
void leftFd()
{
  digitalWrite(LEFT_1,HIGH);
  digitalWrite(LEFT_2,LOW);
}

/*************************
 *void leftFd()
 *小车右轮前进
*************************/
void rightFd()
{
  digitalWrite(RIGHT_1,HIGH);
   digitalWrite(RIGHT_2,LOW);
}

/*************************
 *void leftFd()
 *小车左轮停止
*************************/
void leftStop()
{
  digitalWrite(LEFT_1,LOW);
  digitalWrite(LEFT_2,LOW);
}

/*************************
 *void leftFd()
 *小车右轮停止
*************************/
void rightStop()
{
  digitalWrite(RIGHT_1,LOW);
  digitalWrite(RIGHT_2,LOW);
}


/*************************
 *void leftFd()
 *小车左轮后退
*************************/
void leftBd()
{
  digitalWrite(LEFT_1,LOW);
  digitalWrite(LEFT_2,HIGH);
}

/*************************
 *void leftFd()
 *小车右轮后退
*************************/
void rightBd()
{
  digitalWrite(RIGHT_1,LOW);
  digitalWrite(RIGHT_2,HIGH);
}



/*************************
 *void setup()
 *IO口初始化输入/输出
*************************/
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(10,  OUTPUT);
  pinMode(11, INPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
}


/*************************
 *void forward()
 *小车前进
*************************/
void forward()
{
    leftFd();
    rightFd();
}


/*************************
 *void forward()
 *小车后退
*************************/
void backward()
{
    leftBd();
    rightBd();
}


/*************************
 *void rotateLeft()
 *小车左转
*************************/
void rotateLeft()
{
    leftStop();
    rightFd();
}


/*************************
 *void rotateRight()
 *小车右转
*************************/
void rotateRight()
{
    rightStop();
    leftFd();
    
}



/*************************
 *void motoStop()
 *小车停止
*************************/
void motoStop()
{
    leftStop();
    rightStop();
}




void turnLeft()
{
    motoStop();
//    int state=digitalRead(R1PIN);
//    while (state==LOW)
//    {
//      rotateRight();
//      state=digitalRead(R1PIN);
//      delay(10);
//    }
    rotateRight();
    delay(1000);
    motoStop();
    delay(100);
    
}

void turnRight()
{

}

bool isCarPos()
{
  int n=sizeof(carPos);
  bool res=false;
  for (int i=0;i<n;i++)
  {
    if ( counter==carPos[i] )
    {
        res=true;
        break;
    }
  }
  return res;
}



//从左到右四个传感器状态
int L2,L1,R1,R2;

// the loop function runs over and over again forever
void loop() {
  L2=digitalRead(L2PIN);
  L1=digitalRead(L1PIN);
  R1=digitalRead(R1PIN);
  R2=digitalRead(R2PIN);
  delay(10);  
  motoStop(); 
  

//  if ( flag && L1==HIGH && L2==HIGH  )
//  {
//    motoStop();
//  }
  if (L1==HIGH && L2==HIGH)
  {
    //仅左二传感器均探测到线，可前进
    turnLeft();
  }
  else if (R1==HIGH && R2==HIGH)
  {
    char r_car=R_car_test();
    if (r_car==1)
    {
      motoStop();
      delay(2000);
    } 
  }
  else if (L2==HIGH)
  {
    rotateRight();
  }
  else if (R2==HIGH)
  {
    rotateLeft();
  }
  else if (L1==HIGH && R1==HIGH)
  {
     //四个传感器均探测到线，在岔路口
     forward();
  }
  else if (L2==LOW && L1==HIGH && R1==LOW && R2==LOW)
  {
    rotateRight();
  }
  else if (L2==LOW && L1==LOW && R1==HIGH && R2==LOW)
  {
    rotateLeft();
  }
  else if (L2==LOW && L1==LOW && R1==LOW && R2==LOW)
  {
    rotateRight();
  }


  delay(10);              // 延时200ms
  
}
