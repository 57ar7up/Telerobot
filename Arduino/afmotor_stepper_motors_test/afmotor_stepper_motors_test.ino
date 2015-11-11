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
int motor_speed = 300;      //Set maximum speed of motor. 0 (0V) - 255 (full voltage)

char direction_1; //Direction of 1st stepper motor
char direction_2; //Direction of 2nd stepper motor
int motors_move;

char last_symbol;
/* END OF CONFIG */

void setup(){
  //Setup motors
  motors_move = 1;
  Serial.begin(baud_rate); //Start SPI communication
  motor1.setSpeed(motor_speed);
  motor2.setSpeed(motor_speed);
}

void loop(){
    direction_1 = FORWARD;
    direction_2 = BACKWARD;
    run_2_stepper_motors();
}

void run_2_stepper_motors(){
    if(motors_move == 1){
      motor1.step(1, direction_1, DOUBLE);
      motor2.step(1, direction_2, DOUBLE);
    }
}
