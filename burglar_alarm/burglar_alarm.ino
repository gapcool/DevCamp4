/**
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
int i=0;
int check3time = 0;
int reed = 0;
char password[5] = {};
char lock[] = {'1','2','3','4','#'};
byte rowPins[ROWS] = {7, 8, 9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 12, 13}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define redLED 6 // buzzer
#define touchPin 3    // the number of the pushbutton pin
#define ledPin 2      // the number of the LED pin
#define reedSwitch 5
#define buttonPin 4 // the number of the buttin pin
#define soundSensor A0vol // soundSensor
int ledState = 0;         // the current state of the output pin
int ledState2 = 0;         // the current state of the output pin
int touchState;             // the current reading from the input pin
int buttonState;             // the current reading from the input pin
int volume;
int lastTouchState = LOW;   // the previous reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int reedSwitchState = HIGH;
int threshold = 500; //Change This
long lastDebounceTime = 0;  // the last time the output pin was toggled
long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
long debounceDelay2 = 50;    // the debounce time; increase if the output flickers
void setup()
{
  pinMode(touchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // set initial LED state
  digitalWrite(ledPin, ledState);
  pinMode(redLED, OUTPUT);
  pinMode(reedSwitch, INPUT);
  Serial.begin(9600);
  lcd.begin();
  lcd.setCursor(1,0);
  setEnterPassword();
  lcd.setCursor(0, 1);
  lcd.noAutoscroll();
  
  // Initialize the serial port at a speed of 9600 baud
}
void loop()
{
  //Serial.println(digitalRead(reedSwitchState));
  char s[] = "Password Correct";
  char r[] = "Pass Incorrect";
  char key = keypad.getKey();
  volume = analogRead(A0); // Reads the value from the Analog PIN A0
  Serial.println(volume);
  // Write all characters received with the serial port to the LCD.
    int reading = digitalRead(touchPin);
    int reading2 = digitalRead(buttonPin);
    reed = digitalRead(reedSwitch);
    digitalWrite(redLED, LOW);
    if (reed == LOW){
    digitalWrite(redLED ,HIGH);
    while(1){}
//    Serial.println(digitalRead(reedSwitchState));
  }
  if (reading != lastTouchState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != touchState) {
      touchState = reading;
      if (touchState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  lastTouchState = reading;
  lastButtonState = reading2;
  if (reading2 != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay2) {
    if (reading2 != buttonState) {
      buttonState = reading2;
      if (buttonState == HIGH) {
        ledState2 = !ledState2;
      }
    }
  }
//  digitalWrite(ledPin, ledState);
  lastTouchState = reading;
  lastButtonState = reading2;
   if(volume>700){
    digitalWrite(redLED, HIGH); //Turn ON Led
    Serial.println(volume);
    while(1){}
  }
//  Serial.println(volume);
//  delay(500);
  if(buttonState == 1){
//    Serial.print("if button ==1");
    digitalWrite(redLED, LOW);
    delay(3000);
    while(1){
       int reed = digitalRead(reedSwitch);
       if(reed==HIGH){
        delay(5000);
        break;
       }
     }
  }
  if(ledState==1){
    digitalWrite(redLED, LOW);
    if (key){
    password[i] = key;
//    Serial.println(password[i]);
    i++;
//     Serial.println(i);
    lcd.print(key);
    if (i == 5 && key != '*'){
      int check = 0;
//      Serial.println(check);
      for (int j = 0 ; j<5 ;j++){
        if (password[j]==lock[j]){
            check++;
          }
        }
//      Serial.println(check);
      if (check==5)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        for (i = 0; i < strlen(s); i++) {
          lcd.print(s[i]);
          check3time=0;
        }
        ledState=0;
        digitalWrite(redLED,LOW);
        delay(2000);
        if(reed==LOW){
          digitalWrite(redLED,LOW);
        }
        delay(3000);
        while(1){
          int reed = digitalRead(reedSwitch);
          if(reed==HIGH){
            delay(5000);
            break;
          }
       }
      }
      else{
//        Serial.print("Before = ");
//        Serial.println(check3time);
        check3time = check3time +1;
//        Serial.print("After = ");
//        Serial.println(check3time);
        lcd.clear();
        lcd.setCursor(0, 0);
        for (i = 0; i < strlen(r); i++) {
          lcd.print(r[i]);
         }
         
         if (check3time == 3){
          digitalWrite(redLED,HIGH);
          while(1){}
       }
       ledState=0;
       delay(2000);
      }
//      Serial.print("After else = ");
//      Serial.println(check3time);
      lcd.setCursor(0,1);
//      Serial.print("After  3= ");
//      Serial.println(check3time);
      i=0;
      ledState=0;
      setEnterPassword();      
    }
//    Serial.print("After  4= ");
//    Serial.println(check3time);
   }
   if (key == '*'){
    i=0;
    setEnterPassword();
    }
  }
 }
 void setEnterPassword(){
    char s[] = "Enter Password.";
    lcd.clear();
    lcd.backlight();
  for (int i = 0; i < strlen(s); i++) {
    lcd.print(s[i]);
  }
    lcd.setCursor(0, 1);
    lcd.noAutoscroll();
  }
