#include <Servo.h>

int ch1 = A0;  // RF channel 1 rotate left/right
int ch2 = A1;  // RF channel 2  
int ch3 = A2;  // RF channel 3
int ch4 = A3;  // RF channel 4 Forward/reverse
int ch5 = A4;  // RF channel 5
int ch6 = A5;  // RF channel 6 right shoulder switch - no action currently
int ch7 = 4;   // RF channel 7 (D4) - moved from D2
int ch8 = 3;   // RF channel 8 (D3) left shoulder swithch - no action currently

// ESC objects for mecanum wheels
Servo escFL;  // Front Left ESC (D9)
Servo escFR;  // Front Right ESC (D10) 
Servo escBL;  // Back Left ESC (D6)
Servo escBR;  // Back Right ESC (D7)

void setup() {
  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(ch5, INPUT);
  pinMode(ch6, INPUT);
  pinMode(ch7, INPUT);
  pinMode(ch8, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Attach ESCs to pins
  escBL.attach(8);  // Back Left
  escBR.attach(7);   // Back Right
  escFL.attach(9);   // Front Left
  escFR.attach(10);  // Front Right 
  
  // Initialize ESCs to neutral (1500µs)
  escFL.writeMicroseconds(1500);
  escFR.writeMicroseconds(1500);
  escBL.writeMicroseconds(1500);
  escBR.writeMicroseconds(1500);
  delay(2000);  // ESC calibration delay
} 

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  
  int val1 = pulseIn(ch1, HIGH, 25000);
  int val2 = pulseIn(ch2, HIGH, 25000);
  int val3 = pulseIn(ch3, HIGH, 25000);
  int val4 = pulseIn(ch4, HIGH, 25000);
  int val5 = pulseIn(ch5, HIGH, 25000);
  int val6 = pulseIn(ch6, HIGH, 25000);
  int val7 = pulseIn(ch7, HIGH, 25000);
  int val8 = pulseIn(ch8, HIGH, 25000);
  
  // Filter out interference - ignore readings below 900µs (invalid PWM)
  if (val1 < 900) val1 = 0;
  if (val2 < 900) val2 = 0;
  if (val3 < 900) val3 = 0;
  if (val4 < 900) val4 = 0;
  if (val5 < 900) val5 = 0;
  if (val6 < 900) val6 = 0;
  if (val7 < 900) val7 = 0;
  if (val8 < 900) val8 = 0;
  
  // Simple controller input display with consistent spacing
  Serial.print("\r");
  Serial.print("CH1:");
  if(val1 < 1000) Serial.print(" ");
  if(val1 < 100) Serial.print(" ");
  if(val1 < 10) Serial.print(" ");
  Serial.print(val1);
  Serial.print(" CH2:");
  if(val2 < 1000) Serial.print(" ");
  if(val2 < 100) Serial.print(" ");
  if(val2 < 10) Serial.print(" ");
  Serial.print(val2);
  Serial.print(" CH3:");
  if(val3 < 1000) Serial.print(" ");
  if(val3 < 100) Serial.print(" ");
  if(val3 < 10) Serial.print(" ");
  Serial.print(val3);
  Serial.print(" CH4:");
  if(val4 < 1000) Serial.print(" ");
  if(val4 < 100) Serial.print(" ");
  if(val4 < 10) Serial.print(" ");
  Serial.print(val4);
  Serial.print(" CH5:");
  if(val5 < 1000) Serial.print(" ");
  if(val5 < 100) Serial.print(" ");
  if(val5 < 10) Serial.print(" ");
  Serial.print(val5);
  Serial.print(" CH6:");
  if(val6 < 1000) Serial.print(" ");
  if(val6 < 100) Serial.print(" ");
  if(val6 < 10) Serial.print(" ");
  Serial.print(val6);
  Serial.print(" CH7:");
  if(val7 < 1000) Serial.print(" ");
  if(val7 < 100) Serial.print(" ");
  if(val7 < 10) Serial.print(" ");
  Serial.print(val7);
  Serial.print(" CH8:");
  if(val8 < 1000) Serial.print(" ");
  if(val8 < 100) Serial.print(" ");
  if(val8 < 10) Serial.print(" ");
  Serial.print(val8);
  Serial.print("    "); // Clear any leftover characters
  
  // Stop all motors
  escFL.writeMicroseconds(1500);
  escFR.writeMicroseconds(1500);
  escBL.writeMicroseconds(1500);
  escBR.writeMicroseconds(1500);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
