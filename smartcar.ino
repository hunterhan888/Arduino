#include <Servo.h> 
//作者hunter
//电机驱动板使用L293D
int L_IN_Positive=14;   //ARDUINO（A0）------ L293D（L+）  
int L_IN_Negative=15;   //ARDUINO（A1）------ L293D（L-）  
int R_IN_Positive=16;   //ARDUINO（A2）------ L293D（R+） 
int R_IN_Negative=17;   //ARDUINO（A3）------ L293D（R-）

//超声波
int inputPin = 9;  //ARDUINO（9）
int outputPin =8;  //ARDUINO（8）
const int SensorLeft = 2;     
const int SensorRight = 6;     
int SL;   
int SR;   

int front_distance = 0;
int left_distance = 0;  
int right_distance = 0;           
int directionn = 0;   
Servo myservo;        
int delay_time = 250; //舵机转向后的稳定时间
int Front_go = 8;         // 前进
int Right_go = 6;         // 右转
int Left_go = 4;          // 左转
int Back_go = 2;          // 后退

void setup()
{
     Serial.begin(9600);      
     pinMode(L_IN_Negative,OUTPUT); 
     pinMode(L_IN_Positive,OUTPUT); 
     pinMode(R_IN_Negative,OUTPUT);  
     pinMode(R_IN_Positive,OUTPUT);  
     pinMode(SensorLeft, INPUT);       
     pinMode(SensorRight, INPUT);   
     pinMode(inputPin, INPUT);    
     pinMode(outputPin, OUTPUT);   
     myservo.attach(10);                   
}

//前进
void front_run(int a)     
{            
     digitalWrite(L_IN_Positive,HIGH);  
     digitalWrite(L_IN_Negative,LOW);
     digitalWrite(R_IN_Positive,HIGH);  
     digitalWrite(R_IN_Negative,LOW);     
     delay(a * 100);     
}

//后退
void back(int g)          
{
     digitalWrite(L_IN_Positive,LOW);  
     digitalWrite(L_IN_Negative,HIGH);
     digitalWrite(R_IN_Positive,LOW);  
     digitalWrite(R_IN_Negative,HIGH);       
     delay(g * 100);     
}

//左转
void turn_left(int e)        
{
     digitalWrite(L_IN_Positive,LOW);   
     digitalWrite(L_IN_Negative,HIGH);
     analogWrite(L_IN_Positive,0);
     analogWrite(L_IN_Negative,200);
     digitalWrite(R_IN_Positive,HIGH);
     digitalWrite(R_IN_Negative,LOW);   
     analogWrite(R_IN_Positive,200);
     analogWrite(R_IN_Negative, 0);    
     delay(e * 100);
}    

//右转
void turn_right(int d)        
{
     digitalWrite(L_IN_Positive,HIGH);   
     digitalWrite(L_IN_Negative,LOW);
     analogWrite(L_IN_Positive,200);
     analogWrite(L_IN_Negative,0);
     digitalWrite(R_IN_Positive,LOW);
     digitalWrite(R_IN_Negative,HIGH);   
     analogWrite(R_IN_Positive,0);
     analogWrite(R_IN_Negative, 200);  
     delay(d * 100);
}

//停止
void stopp(int f)         
{
     digitalWrite(L_IN_Negative,LOW);
     digitalWrite(L_IN_Positive,LOW);
     digitalWrite(R_IN_Negative,LOW);
     digitalWrite(R_IN_Positive,LOW);
     delay(f * 100);
}
//超声波测量
void detection()        
{      
      int delay_time = 250;                     
      measure_front_distance();                 
      if(front_distance < 10)                  
      {
            stopp(1);                
            back(2);
      }     
      if(  front_distance < 25)                  
      {
            stopp(1);                
            measure_left_distance();             
            delay(delay_time);                 
            measure_right_distance();   
            delay(delay_time);                       
            
            if(left_distance > right_distance)    
            {
                 directionn = Left_go;                        }
            
            if(left_distance <= right_distance)   
            {
                 directionn = Right_go;           
            } 
            
            if (left_distance < 10 && right_distance < 10)   
            {
                 directionn = Back_go;                    
            }          
      }
      else                           
      {
            directionn = Front_go;                     
      }     
} 


void measure_front_distance()   
{
      myservo.write(90);
      digitalWrite(outputPin, LOW);               
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);              
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);               
      float Fdistance = pulseIn(inputPin, HIGH);  
      Fdistance= Fdistance/5.8/10;                
      Serial.print("F distance:");      
      Serial.println(Fdistance);         
      front_distance = Fdistance;                 
}


void measure_left_distance()   
{
      myservo.write(5);
      delay(delay_time);
      digitalWrite(outputPin, LOW);               
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);              
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);               
      float Ldistance = pulseIn(inputPin, HIGH);  
      Ldistance= Ldistance/5.8/10;                
      Serial.print("L distance:");       
      Serial.println(Ldistance);         
      left_distance = Ldistance;                  
}


void measure_right_distance()   
{
      myservo.write(177);
      delay(delay_time);
      digitalWrite(outputPin, LOW);               
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);              
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);               
      float Rdistance = pulseIn(inputPin, HIGH);  
      Rdistance= Rdistance/5.8/10;                
      Serial.print("R distance:");       
      Serial.println(Rdistance);         
      right_distance = Rdistance;                 
}  

    
void loop()
 {
       SL = digitalRead(SensorLeft);
       SR = digitalRead(SensorRight);
       if (SL == LOW)
       {
        delay(1);
        digitalWrite(R_IN_Positive,LOW);
        digitalWrite(R_IN_Negative,LOW);
        digitalWrite(L_IN_Positive,LOW);
        digitalWrite(L_IN_Negative,LOW);
       }
       
      myservo.write(90);                         
      detection();                                   
      if(directionn == Back_go)                              
      {
             back(8);                            
             turn_left(2);                       
             Serial.print(" Reverse ");       
      }
     if(directionn == Right_go)                     
     {
             back(1); 
             turn_right(6);                   
             Serial.print(" Right ");    
     }
     if(directionn == Left_go)                       
     {  
             back(1);      
             turn_left(6);                  
             Serial.print(" Left ");        
     }  
     if(directionn == Front_go)                   
     { 
            front_run(1);                   
            Serial.print(" front_run ");   
            Serial.print("   ");    
     }
 }


