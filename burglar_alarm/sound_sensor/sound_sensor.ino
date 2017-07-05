/*
This is the code to make a LED blink with the music.
You have to set the threshold so it' sensible enough to make the led blink.
You connect an LED to PIN13 and the Sound Sensor to Analog Pin 0
 */
 
int threshold = 500; //Change This
int volume;
#define buzzer 6
void setup() {                
  Serial.begin(9600); // For debugging
  pinMode(buzzer, OUTPUT);     
}

void loop() {
//  digitalWrite(buzzer,HIGH);
  volume = analogRead(A0); // Reads the value from the Analog PIN A0
  /*
    //Debug mode
    Serial.println(volume);
    delay(100);
  */
  
  if(volume>=threshold){
    
//    digitalWrite(led, HIGH); //Turn ON Led
    Serial.println(analogRead(A0));
  }  
  else{
//    digitalWrite(led, LOW); // Turn OFF Led
  }

}
