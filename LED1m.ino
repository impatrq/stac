//**********************************************************
// 
//sensor de distacia  HC-SR04 Arduino Uno
// 
//**********************************************************

#define trigPin 13  //Trig Ultrasonico -> pin 13
#define echoPin 12  //Echo Ultrasonico -> pin 12
#define ledRouge 10      //Led amarillo -> pin 11
int centimetros;
int tiempo;


void setup() {
  Serial.begin (9600);  
  pinMode(trigPin, OUTPUT);  //Trig 
  pinMode(echoPin, INPUT);   //Echo 
  pinMode(ledRouge, OUTPUT);
}

void loop() {
  long tiempo, centimetro;
   // Mandar un pulso bajo para asegurar un pulso alto
  digitalWrite(trigPin, LOW);  
  delay(200); 
  digitalWrite(trigPin, HIGH);
  delay(100); 
  digitalWrite(trigPin, LOW);
  tiempo= pulseIn(echoPin, HIGH);

  //Convertir el tiempo en distancia
  centimetros = tiempo /29/2 ;
   
  if (centimetros < 20) {  
    digitalWrite(ledRouge,HIGH);
    delay(100);
    
}
  else {   
    digitalWrite(ledRouge,LOW);
    delay(100);
  }
  
  if ( centimetros < 0){  
    Serial.println( "distancia ");
    Serial.println(centimetros);
    Serial.println(" cm ");
    Serial.println();

  }
  else {
   //Serial.print(tiempo);
    Serial.println("fuera de alcance");
   
  }
  delay(100);  
}
