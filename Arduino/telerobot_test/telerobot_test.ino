// lineItems = loadStrings("http://YOURDOMAIN.COM/file.txt");
// comPort.write(lineItems[0]); //1 line
// delay(1000); //Wait 1 second

//#include <SoftwareSerial.h> //This is right way to work with SPI (I hope)
#include <AFMotor.h> //Motor library, communicates with motor shield by digital ports

/* CONFIG */
const int pin_RX = 0;		//Standard serial receive pin on Arduino is		0
const int pin_TX = 1;		//Standard serial transmit pin on Arduino is	1
const int pin_LED = 13;		//Standard integrated LED pin on Arduino is		13
AF_DCMotor Motor_l(4);		//Left motor M4
AF_DCMotor Motor_r(3);		//Right motor M3
long baud_rate = 57600;	//Speed of Serial Peripheral Interface, 1 baud = 1 bps (bits per second) Can be 2000000. Arduino serial monitor limit is 115200
int motor_speed = 150;		//Set maximum speed of motor. 0 (0V) - 255 (full voltage)

//SoftwareSerial Serial1(pin_RX, pin_TX); //Configuring serial connection with built-in library. Serial buffer is 64 bytes
/* END OF CONFIG */

void setup(){
	Serial.begin(baud_rate); //Start SPI communication
	//motor_smoothness_test(Motor_l, maximum_speed); return; //Test how motors can run regular and smoothly
	//Serial1.begin(baud_rate); //Start SPI communication through SoftwareSerial
	//Setup motors
	Motor_l.setSpeed(motor_speed);
	Motor_r.setSpeed(motor_speed);
}

void loop(){
  if(Serial.available() > 0){
    delay(50); // let the buffer fill up
    
    while(Serial.available() > 0){
      char current_symbol = Serial.read();
      command_exec(current_symbol);
    }
  }
}

//Execution of command from SPI
int command_exec(char command){
	if(command == 'w'){
		Motor_l.run(FORWARD);
		Motor_r.run(FORWARD);
		//Serial1.println("FORWARD");
	} else if(command == 's'){
		Motor_l.run(BACKWARD);
		Motor_r.run(BACKWARD);
		//Serial1.println("BACK");
	} else if(command == 'a'){
		Motor_l.run(BACKWARD);
		Motor_r.run(FORWARD);
		//Serial1.println("TURN_LEFT");
	} else if(command == 'd'){
		Motor_l.run(FORWARD);
		Motor_r.run(BACKWARD);
		//Serial1.println("TURN_RIGHT");
	} else {
		//Serial1.println("Unknown command: " + command);
	}
}
