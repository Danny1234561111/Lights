#define RED_LED_PIN 13 
#define GREEN_LED_PIN 11 
#define YELLOW_LED_PIN 12 
 
#define HAND_P 'h' 
#define AUTO_P 'a' 
#define GREEN_P 'g' 
#define RED_P 'r' 
 
 
 
 
unsigned timing=0; 
bool led_status = LOW; 

int period[4]={10000,1000,10000,1000}; 
int color[4]={GREEN_LED_PIN,YELLOW_LED_PIN,RED_LED_PIN,YELLOW_LED_PIN}; 
int interval = 0; 
int i=0; 
int mode=0; 


void setup() { 
  Serial.begin(9600); 
  pinMode(RED_LED_PIN, OUTPUT); 
  pinMode(GREEN_LED_PIN, OUTPUT); 
  pinMode(YELLOW_LED_PIN, OUTPUT); 
}; 

void boss(){ 
  if (mode==0){ 
    if (millis()-timing>period[i]){ 
      if (color[i]==11&&millis()-timing<period[i]+2000){ 
        if (millis()-timing>period[i]+interval){ 
          if (led_status==LOW){ 
            digitalWrite(color[i],LOW); 
            led_status=HIGH; 
            interval+=500; 
          } 
          else{ 
            Serial.print(i);
            digitalWrite(color[i],HIGH); 
            led_status=LOW; 
            interval+=500; 
          } 
        } 
      }  
      else{ 
        interval=0; 
        timing=millis(); 
        digitalWrite(color[i],LOW); 
        i=i+1; 
        if (i==4){ 
          i=0; 
        }; 
      } 
    } 
    else{ 
      digitalWrite(color[i],HIGH); 
    } 
  } 
}; 
void handmode() {
 if (Serial.available() > 0) {
  byte cmd = Serial.read(); 
  Serial.print(cmd); // Вывод полученного символа 
  if (mode == 1) {
   if (cmd == AUTO_P) {
    mode = 0; 
    timing=millis();
    digitalWrite(color[0], LOW); 
    digitalWrite(color[1], LOW); 
    digitalWrite(color[2], LOW); 
   } else if (cmd == GREEN_P) {
    digitalWrite(color[0], HIGH); 
    digitalWrite(color[1], LOW); 
    digitalWrite(color[2], LOW); 
   } else if (cmd == RED_P) {
    digitalWrite(color[0], LOW); 
    digitalWrite(color[1], LOW); 
    digitalWrite(color[2], HIGH);
   } else {
    Serial.println("Unknown command"); 
   }
  } 
  if (mode == 0) {
   if (cmd == HAND_P) {
    mode = 1; 
    digitalWrite(color[0], LOW); 
    digitalWrite(color[1], LOW); 
    digitalWrite(color[2], LOW); 
   } else {
    Serial.println("Unknown command"); 
   }
  }
 }
}
void loop() { 
  boss(); 
  handmode(); 
};
