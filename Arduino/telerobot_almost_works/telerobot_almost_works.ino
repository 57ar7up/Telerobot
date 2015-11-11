// lineItems = loadStrings("http://YOURDOMAIN.COM/file.txt");
// comPort.write(lineItems[0]); //1 line
// delay(1000); //Wait 1 second

//#include <SoftwareSerial.h> //This is right way to work with SPI (I hope)
#include <AFMotor.h> //Motor library, communicates with motor shield by digital ports

/* CONFIG */
const int pin_RX = 0;    //Standard serial receive pin on Arduino is   0
const int pin_TX = 1;   //Standard serial transmit pin on Arduino is  1
const int pin_LED = 13;   //Standard integrated LED pin on Arduino is   13
AF_Stepper motor1(200, 1);
AF_Stepper motor2(200, 2);
long baud_rate = 57600; //Speed of Serial Peripheral Interface, 1 baud = 1 bps (bits per second) Can be 2000000. Arduino serial monitor limit is 115200
int motor_speed = 300;    //Set maximum speed of motor. 0 (0V) - 255 (full voltage)

char direction_1; //Direction of 1st stepper motor
char direction_2; //Direction of 2nd stepper motor
int motors_stop;

char last_symbol;
byte descript[2];

//SoftwareSerial Serial1(pin_RX, pin_TX); //Configuring serial connection with built-in library. Serial buffer is 64 bytes
/* END OF CONFIG */

void setup(){
  motors_move = 0;
  //delay(30000); //To avoid garbage on start
  Serial.begin(baud_rate); //Start SPI communication
  //motor_smoothness_test(Motor_l, maximum_speed); return; //Test how motors can run regular and smoothly
  //Serial1.begin(baud_rate); //Start SPI communication through SoftwareSerial
  //Setup motors
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
}

void loop(){
  if(Serial.available() > 1){
    //while(Serial.available() > 0){
      
      /*if(Serial.read()=='Y'){
        for(byte i=0; i < 3; i++){
          descript[i] = Serial.read();    
        }        
        if((descript[0] == 'E')){
          char current_symbol = descript[1];
          command_exec(current_symbol);
        }
      } else {
        for(byte i=0; i < 255; i++){
         Serial.read();    
        } 
      } */
        char current_symbol = Serial.read();
        if(last_symbol == 'Y'){
          command_exec(current_symbol);
        }
        last_symbol = current_symbol;
      //char current_symbol = Serial.read();
      //command_exec(current_symbol);
    //}
  }
  run_2_stepper_motors();
}

//Execution of command from SPI
int command_exec(char command){
  if(command == 'w'){
    direction_1 = FORWARD;
    direction_2 = FORWARD;
    motors_move = 0;
    Serial.println("FORWARD");
  } else if(command == 's'){
    direction_1 = BACKWARD;
    direction_2 = BACKWARD;
    motors_move = 0;
    Serial.println("BACK");
  } else if(command == 'a'){
    direction_1 = BACKWARD;
    direction_2 = FORWARD;
    motors_move = 0;
    Serial.println("TURN_LEFT");
  } else if(command == 'd'){
    direction_1 = FORWARD;
    direction_2 = BACKWARD;
    motors_move = 0;
    Serial.println("TURN_RIGHT");
  } else if(command == ' '){
    motors_move = 1;
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

