#define RX_PIN 3
#define PWM_PIN 10
#define ledPin 13

volatile int rx_value = 0;
volatile int prev_time = 0;

int pwm_value = 0;
 
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
  
  
  //Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(RX_PIN), change, CHANGE);
}

 
void loop() { 
  //Serial.println(rx_value); 
  pwm_value = map(rx_value, 1000, 2000, 0, 200);
  pwm_value = constrain(pwm_value, 0, 200);
  int pwm_value_low = 200 - pwm_value;

  //Serial.println(pwm_value);
  
  if(pwm_value > 5){      
    pinMode(PWM_PIN, OUTPUT);                        
    digitalWrite(PWM_PIN, 0);
    delayMicroseconds(pwm_value); 
  }     
  if(pwm_value < 195){
    pinMode(PWM_PIN, INPUT);
    delayMicroseconds(pwm_value_low);   
  }
    
}
 
void change() {
  if(digitalRead(RX_PIN) == 1){
    prev_time = micros();
  }
  else {
    rx_value = micros() - prev_time;
  }
}
 
