int ch1 = A1;  // RF channel 1
int ch2 = A2;  // RF channel 2  
int ch3 = A3;  // RF channel 3
int ch4 = A4;  // RF channel 4
int ch5 = A5;  // RF channel 5

void setup() {
  Serial.begin(9600);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  pinMode(ch3, INPUT);
  pinMode(ch4, INPUT);
  pinMode(ch5, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
} 

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Arduino running...");
  
  int val1 = pulseIn(ch1, HIGH, 25000);
  int val2 = pulseIn(ch2, HIGH, 25000);
  int val3 = pulseIn(ch3, HIGH, 25000);
  int val4 = pulseIn(ch4, HIGH, 25000);
  int val5 = pulseIn(ch5, HIGH, 25000);
  
  Serial.print("CH1:");
  Serial.print(val1);
  Serial.print(" CH2:");
  Serial.print(val2);
  Serial.print(" CH3:");
  Serial.print(val3);
  Serial.print(" CH4:");
  Serial.print(val4);
  Serial.print(" CH5:");
  Serial.println(val5);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
