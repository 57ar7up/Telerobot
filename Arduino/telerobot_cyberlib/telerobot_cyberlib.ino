#include <CyberLib.h>
#include <AFMotor.h> //Motor library, communicates with motor shield by digital ports

#define motors_init {D3_Out; D4_Out;} 
#define robot_go {D3_Low; D4_High;} 
#define robot_back {D3_High; D4_Low;}
#define robot_stop {D3_Low; D4_Low;} 
#define robot_rotation_left {D3_Low; D4_High;} 
#define robot_rotation_right {D3_High; D4_Low;}
uint8_t inByte;

AF_DCMotor Motor_l(4);   //Left motor M4
AF_DCMotor Motor_r(3);    //Right motor M3
int motor_speed = 150;    //Set maximum speed of motor. 0 (0V) - 255 (full voltage)

void setup(){ 
  UART_Init(57600);// Инициализация порта для связи с роутером
  wdt_enable (WDTO_250MS);    //Сторожевая собака 0,5сек.   
  Motor_l.setSpeed(motor_speed);
  Motor_r.setSpeed(motor_speed);
}  

void loop(){  
  if (UART_ReadByte(inByte)){ //если что то пришло
    switch (inByte)  //смотрим какая команда пришла
    {  
        case 'x':  //стор
          Motor_l.run(RELEASE);
          Motor_r.run(RELEASE);
        break; 
        
        case 'w':  //вперед
          
          Motor_l.run(FORWARD);
          Motor_r.run(FORWARD);
        break;  
        
        case 'd':  //лево
         Motor_l.run(BACKWARD);
          Motor_r.run(FORWARD);
        break;

        case 'a': //право
         Motor_l.run(FORWARD);
          Motor_r.run(BACKWARD);
        break; 
        
        case 's':  //назад
          Motor_l.run(BACKWARD);
          Motor_r.run(BACKWARD);
        break;      
    }          
  } 
 wdt_reset(); //покормить собаку 
}  
