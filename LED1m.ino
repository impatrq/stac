//**********************************************************
// 
//sensor de distacia  HC-SR04 Arduino Uno
// 
//**********************************************************

#define trigPin 13  //Trig Ultrasonico -> pin 13
#define echoPin 12  //Echo Ultrasonico -> pin 12
#define ledRojo 10      //Led amarillo -> pin 11

void setup() {
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig 
  pinMode(echoPin, INPUT);   //Echo 
  pinMode(ledRojo, OUTPUT);
}

void loop() {
  long duration, distance;
   // Mandar un pulso bajo para asegurar un pulso alto
  digitalWrite(trigPin, LOW);  
  delay(200); 
  digitalWrite(trigPin, HIGH);
  delay(100); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Convertir el tiempo en distancia
  distance = duration /29/2 ;
   
  if (distance <= 100) {  
    digitalWrite(ledRojo,HIGH);
    delay(100);
    
}
  else {   
    digitalWrite(ledRojo,LOW);
    delay(100);
  }
  
  if ( distance < 0){  
    Serial.println("fuera de alcance");
  }
  else {
    Serial.print( "distancia ");
    Serial.print(distance);
    Serial.println(" cm ");
  }
  delay(100);  
}
