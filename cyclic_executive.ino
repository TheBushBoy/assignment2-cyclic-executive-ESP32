// Pin definition
const byte T1_Pin = 15;

// Store previous counters of time
unsigned int currentMicros = micros();
unsigned int previousMicros = 0;

void task1() {
  // Execution time
  unsigned int t1 = micros();
  
  // Store previous counters of time
  currentMicros = micros();

  // Store previous state of the output
  bool state = 0;
  
  // High for 200us
  if(currentMicros - previousMicros < 200 && !state) {
    digitalWrite(T1_Pin, HIGH);
    state = 1;
  }
  // Low for 50us
  if(currentMicros - previousMicros < 200 + 50 && state) {
    digitalWrite(T1_Pin, LOW);
    state = 0;
  }
  // High for 30us
  if(currentMicros - previousMicros < 200 + 50 + 30 && !state) {
    digitalWrite(T1_Pin, HIGH);
    state = 1;
  }
  else {
    state = 0;
  }

  // Execution time
  unsigned int t2 = micros();
  Serial.print(t2-t1);
}

void setup() {
  Serial.begin(9600);
  pinMode(T1_Pin, OUTPUT);
}

void loop() {
  task1();  
}
