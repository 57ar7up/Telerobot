#include <AFMotor.h>

AF_DCMotor Motor_l(4); // левый мотор M4
AF_DCMotor Motor_r(3); // правый мотор M3
char incomingbyte; // переменная для приема данных

void setup()
{
	Serial.begin(115200);
	Motor_l.setSpeed(150);
	Motor_r.setSpeed(150);
}

void loop(){
	if (Serial.available() > 0){
		incomingbyte = Serial.read();
		Serial.println(incomingbyte);

		if (incomingbyte = 'forward'){
			Motor_l.run(FORWARD); //delante
			Motor_r.run(FORWARD);
			Serial.println("FORWARD");

		}
		
		if (incomingbyte = 'backward'){
			Motor_l.run(BACKWARD); //atras
			Motor_r.run(BACKWARD);
			Serial.println("BACK");

		} 

		if (incomingbyte == '2'){
			Motor_l.run(RELEASE); //paro
			Motor_r.run(RELEASE);
			Serial.println("STOP");



		}

		if (incomingbyte = 'left'){
			Motor_l.run(BACKWARD); //paro
			Motor_r.run(FORWARD);
			Serial.println("TURN_LEFT");



		}

		if (incomingbyte = 'right'){
			Motor_l.run(FORWARD); //paro
			Motor_r.run(BACKWARD);
			Serial.println("TURN_RIGHT");



		}
	} 
}