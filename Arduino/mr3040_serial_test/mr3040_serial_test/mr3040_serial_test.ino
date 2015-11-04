int led = 13; 
byte descript[5];

void setup(){   
  Serial.begin(57600);   
  pinMode(led, OUTPUT);       
}  

void loop(){  
 if(Serial.available()>1){ // ждём дескриптор и нужный символ
  if(Serial.read()=='y'){ // проверяем первый символ, если это 'Y', то продолжаем принимать, если нет, то выходим из цикла чтения 
    for(byte i=0; i < 5; i++){
         descript[i] = Serial.read();    
      } 
        
 if((descript[0] =='+') && (descript[1] =='=') && (descript[2] =='z')){
   switch(descript[3]){
      case 'a':
      digitalWrite(led, HIGH);
      Serial.println("OK on"); // ответ
      break;
      
      case 'b':
      digitalWrite(led, LOW);
      Serial.println("OK off"); // ответ
      break;
    
     }
   } else {
      for(byte i=0; i < 255; i++){
         Serial.read();    
      } 
    } 
   }// конец if (Serial.read()=='Y')
  } // конец чтение порта 
}

