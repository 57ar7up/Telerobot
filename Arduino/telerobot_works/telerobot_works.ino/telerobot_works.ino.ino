// lineItems = loadStrings("http://YOURDOMAIN.COM/file.txt");
// comPort.write(lineItems[0]); //1 line
// delay(1000); //Wait 1 second

#include <AFMotor.h> //Motor library, communicates with motor shield by digital ports

/* CONFIG */
const int pin_RX = 0;       //Standard serial receive pin on Arduino is   0
const int pin_TX = 1;       //Standard serial transmit pin on Arduino is  1
const int pin_LED = 13;     //Standard integrated LED pin on Arduino is   13
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);
long baud_rate = 57600;     //Speed of Serial Peripheral Interface, 1 baud = 1 bps (bits per second) Can be 2000000. Arduino serial monitor limit is 115200
int motor_speed = 500;      //Set maximum speed of motor. 0 (0V) - 255 (full voltage)
char null_byte = '\0';  //Or 0x00

char direction_1; //Direction of 1st stepper motor
char direction_2; //Direction of 2nd stepper motor
int motors_move;

byte descript[5];

/* END OF CONFIG */

void setup(){
  //motors_move = 1;
  //delay(30000); //To avoid garbage on start
  Serial.begin(baud_rate); //Start SPI communication
  //motor_smoothness_test(Motor_l, maximum_speed); return; //Test how motors can run regular and smoothly
  //Serial1.begin(baud_rate); //Start SPI communication through SoftwareSerial
  //Setup motors
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
}

void loop(){
  run_2_stepper_motors();
  if(Serial.available() > 4){
    if(Serial.read()=='Y'){ // проверяем первый символ, если это 'Y', то продолжаем принимать, если нет, то выходим из цикла чтения 
      for(byte i=0; i < 5; i++){
         descript[i] = Serial.read();    
      } 
      if((descript[0] =='+') && (descript[1] =='=') && (descript[2] =='Z')) {
        command_exec(descript[3]);
      }
    }
  }
}

//Execution of command from SPI
int command_exec(char command){
  if(command == 'w'){
    direction_1 = BACKWARD;
    direction_2 = FORWARD;
    motors_move = 1;
    Serial.println("FORWARD");
  } else if(command == 's'){
    direction_1 = FORWARD;
    direction_2 = BACKWARD;
    motors_move = 1;
    Serial.println("BACK");
  } else if(command == 'a'){
    direction_1 = BACKWARD;
    direction_2 = BACKWARD;
    motors_move = 1;
    Serial.println("TURN_LEFT");
  } else if(command == 'd'){
    direction_1 = FORWARD;
    direction_2 = FORWARD;
    motors_move = 1;
    Serial.println("TURN_RIGHT");
  } else if(command == ' '){
    motors_move = 0;
    Serial.println("STOP");
  } else {
    Serial.println("Unknown command: " + command);
  }
}

void run_2_stepper_motors(){
    if(motors_move == 1){
      motor1.step(1, direction_1, DOUBLE);
      motor2.step(1, direction_2, DOUBLE);
    }
}

