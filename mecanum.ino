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
  escFL.attach(9);   // Front Left
  escFR.attach(10);  // Front Right 
  escBL.attach(6);   // Back Left
  escBR.attach(7);   // Back Right
  
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
  
  Serial.print("\r");
  Serial.print("CH1:");
  Serial.print(val1);
  Serial.print(" CH2:");
  Serial.print(val2);
  Serial.print(" CH3:");
  Serial.print(val3);
  Serial.print(" CH4:");
  Serial.print(val4);
  Serial.print(" CH5:");
  Serial.print(val5);
  Serial.print(" CH6:");
  Serial.print(val6);
  Serial.print(" CH7:");
  Serial.print(val7);
  Serial.print(" CH8:");
  Serial.print(val8);
  Serial.print("    ");
  
  // Convert PWM values to motor speeds (-500 to 500 for mixing)
  int forward = map(val4, 1000, 2000, -500, 500);  // CH4: Forward/reverse
  int strafe = map(val2, 1000, 2000, -500, 500);   // CH2: Strafe left/right (try this first)
  int rotate = map(val1, 1000, 2000, -500, 500);   // CH1: Rotate left/right
  
  // Apply deadband (ignore small movements)
  if (abs(forward) < 50) forward = 0;
  if (abs(strafe) < 50) strafe = 0;
  if (abs(rotate) < 50) rotate = 0;
  
  // Mecanum wheel kinematics
  int frontLeft = forward + strafe + rotate;
  int frontRight = forward - strafe - rotate;
  int backLeft = forward - strafe + rotate;
  int backRight = forward + strafe - rotate;
  
  // Convert to ESC signals (1000-2000µs, 1500 = stop)
  int escFLSignal = constrain(map(frontLeft, -1000, 1000, 1000, 2000), 1000, 2000);
  int escFRSignal = constrain(map(frontRight, -1000, 1000, 1000, 2000), 1000, 2000);
  int escBLSignal = constrain(map(backLeft, -1000, 1000, 1000, 2000), 1000, 2000);
  int escBRSignal = constrain(map(backRight, -1000, 1000, 1000, 2000), 1000, 2000);
  
  // Write to ESCs
  escFL.writeMicroseconds(escFLSignal);
  escFR.writeMicroseconds(escFRSignal);
  escBL.writeMicroseconds(escBLSignal);
  escBR.writeMicroseconds(escBRSignal);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
