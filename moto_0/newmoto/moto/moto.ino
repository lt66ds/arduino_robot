/*
  ROBOT
*/

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
int counter=0;

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
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

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


/*************************
 *char L_car_test()
 *左侧车位检测
 *返回值： 1为有车，0为无车
*************************/
char L_car_test()
{
}

/*************************
 *char R_car_test()
 *右侧车位检测
 *返回值： 1为有车，0为无车
*************************/
char R_car_test()
{
//  //检测右侧车位，返回0或1
//  long D;
//  Serial.println("Start");
//  delay(800); 
//  char n=0;
//  char i=0;
//  while(i<15)
//  {
//    //检测次数
//    D=sr_R.Distance();//获取右侧模块的检测距离
//    if(D<full_distance) ++n;//对有效距离的次数进行累计
//    ++i;
//    delay(20); 
//  }  
//  if(n>8) 
//  {
//    //如果检测的有效距离次数达到一定数量
//     rerotate 1;
//  }
//  else
//  {
//     rerotate 0;
//  }
}

void turnLeft()
{
    motoStop();
    forward();
    delay(200);
    int state=digitalRead(L2PIN);
    while (state==LOW)
    {
      rotateRight();
      delay(50);
    }
    rotateRight();
    delay(50);
    
    
}

void turnRight()
{
    leftStop();
    rightFd();
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
  
//  else if (L2==LOW && R2==LOW)
//  {
//     //两端传感器均探测到线，很可能在岔路口
//     if (!oneSideDetectAsCross)
//     {
//        //两端传感器均探测到线，到达车位或岔路
//        counter++;
//        char r_car=R_car_test();
//        sendMsg(counter,r_car);
//     }
//     forward();
//  }
  if (L2==HIGH && R2==HIGH)
  {
     //L2 R2传感器均探测到线，在岔路口
     //TO DO 
     //ADD SUPERSONIC
     turnLeft();
     forward();
  }
  else if (L2==LOW && L1==LOW && R1==LOW && R2==LOW)
  {
     //四个传感器均探测到线，在岔路口
     forward();
  }
  else if (L2==HIGH && L1==HIGH && R1==HIGH && R2==HIGH)
  {
     //四个传感器均探测到线，在岔路口
     forward();
  }
  else if (L2==LOW && L1==HIGH && R1==HIGH && R2==LOW)
  {
     //四个传感器均探测到线，在岔路口
     forward();
  }
  else if (L2==HIGH && L1==LOW && R1==LOW && R2==LOW)
  {
    //仅右端传感器均探测到线，右转纠正
    if (oneSideDetectAsCross)
    {
        //一端传感器均探测到线，到达车位或岔路
        counter++;
        char r_car=R_car_test();
        sendMsg(counter,r_car);
    }
    rotateRight();
  }
  else if (L2==LOW && L1==HIGH && R1==LOW && R2==LOW)
  {
    //仅右端传感器均探测到线，右转纠正
    if (oneSideDetectAsCross)
    {
        //一端传感器均探测到线，到达车位或岔路
        counter++;
        char r_car=R_car_test();
        sendMsg(counter,r_car);
    }
    rotateRight();
  }
  else if (L2==LOW && L1==LOW && R1==LOW && R2==HIGH)
  {
    //仅右端传感器均探测到线，右转纠正
    if (oneSideDetectAsCross)
    {
        //一端传感器均探测到线，到达车位或岔路
        counter++;
        char r_car=R_car_test();
        sendMsg(counter,r_car);
    }
    rotateLeft();
  }
  else if (L2==LOW && L1==LOW && R1==HIGH && R2==LOW)
  {
    //仅左端传感器均探测到线，左转纠正
    if (oneSideDetectAsCross)
    {
        //一端传感器均探测到线，到达车位或岔路
        counter++;
        char r_car=R_car_test();
        sendMsg(counter,r_car);
    }
    rotateLeft();
  }
  else if (L1==HIGH)
  {
    //仅左二传感器均探测到线，可前进
    rotateRight();
  }
  else if (R1==HIGH)
  {
    //仅右二传感器均探测到线，可前进
    rotateLeft();
  }

  delay(10);              // 延时200ms
  
}
