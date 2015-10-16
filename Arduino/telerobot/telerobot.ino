// lineItems = loadStrings("http://YOURDOMAIN.COM/file.txt");
// comPort.write(lineItems[0]); //1 line
// delay(1000); //Wait 1 second

#include <SoftwareSerial.h> //This is right way to work with SPI (I hope)
#include <AFMotor.h> //Motor library, communicates with motor shield by digital ports

/* CONFIG */
const int pin_RX = 0;		//Standard serial receive pin on Arduino is		0
const int pin_TX = 1;		//Standard serial transmit pin on Arduino is	1
const int pin_LED = 13;		//Standard integrated LED pin on Arduino is		13
AF_DCMotor Motor_l(4);		//Left motor M4
AF_DCMotor Motor_r(3);		//Right motor M3
long baud_rate = 115200;	//Speed of Serial Peripheral Interface, 1 baud = 1 bps (bits per second) Can be 2000000. Arduino serial monitor limit is 115200
int motor_speed = 150;		//Set maximum speed of motor. 0 (0V) - 255 (full voltage)

SoftwareSerial Serial1(pin_RX, pin_TX); //Configuring serial connection with built-in library. Serial buffer is 64 bytes
/* END OF CONFIG */

String input_string = ""; //Storing string from SPI buffer, which has commands
char symbol_command_end = ';';

void setup(){
	Serial.begin(baud_rate); //Start SPI communication
	//motor_smoothness_test(Motor_l, maximum_speed); return; //Test how motors can run regular and smoothly
	Serial1.begin(30000); //Start SPI communication through SoftwareSerial
	//Setup motors
	Motor_l.setSpeed(motor_speed);
	Motor_r.setSpeed(motor_speed);
}

void loop(){
	if(!Serial1.available())
		return;

	char current_symbol = Serial1.read();

	if(current_symbol == symbol_command_end){ //Executing command
		Serial1.println("Command received: " + input_string);
		command_exec(input_string);
		input_string = ""; //In the meaning of ''
	} else if(current_symbol != symbol_command_end){ //Writing symbol to make up another command in future. Ignoring symbol of command end
		input_string += String(current_symbol);
	}
}

//Execution of command from SPI
int command_exec(String command){
	if(command == "forward"){
		Motor_l.run(FORWARD);
		Motor_r.run(FORWARD);
		Serial1.println("FORWARD");
	} else if(command == "backward"){
		Motor_l.run(BACKWARD);
		Motor_r.run(BACKWARD);
		Serial1.println("BACK");
	} else if(command == "left"){
		Motor_l.run(BACKWARD);
		Motor_r.run(FORWARD);
		Serial1.println("TURN_LEFT");
	} else if(command == "right"){
		Motor_l.run(FORWARD);
		Motor_r.run(BACKWARD);
		Serial1.println("TURN_RIGHT");
	} else if(command == "stop"){
		Motor_l.run(RELEASE);
		Motor_r.run(RELEASE);
		Serial1.println("STOP");
	} else if(command == "led on"){
 		pinMode(pin_LED, OUTPUT);		//Set the onboard LED to OUTPUT
 		digitalWrite(pin_LED, HIGH);	//Sets the LED on
	} else if(command == "led off"){
 		pinMode(pin_LED, OUTPUT);
 		digitalWrite(pin_LED, LOW);	//Sets the LED off
	} else {
		Serial1.println("Unknown command: " + command);
	}
}