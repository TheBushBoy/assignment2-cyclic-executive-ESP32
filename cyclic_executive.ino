// Pin definition
const byte T1_Pin = 15;
const byte T2_Pin = 20;
const byte T3_Pin = 21;

// Store previous counters of time
unsigned int currentMicros;
unsigned int previousMicros = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(T1_Pin, OUTPUT);
  pinMode(T2_Pin, INPUT);
  pinMode(T3_Pin, INPUT);
}

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
  Serial.printf("Execution time T1: %d\n", t2-t1);
}

unsigned int freqCount(const byte pinNumber) {
  unsigned int freq = -1;
  
  // Measure time of a period
  unsigned int t1, t2;

  // Is this measuring
  bool measuring = false;

  unsigned int value = analogRead(pinNumber) * 1000;
  bool state = (value <= 50) ? 0 : 1;

  if(state != (state + 1) % 2 && !measuring) {
    t1 = millis();
    measuring = true;
  }
  else if(state != (state + 1) % 2 && measuring) {
    t2 = millis();
    measuring = false;
    freq = 1 / (t2 - t1);
  }

  return freq;
}

void task2() {
  // Execution time
  unsigned int t1 = micros();

  unsigned int freq = freqCount(T2_Pin);

  // Execution time
  if(freq != -1) {
    unsigned int t2 = micros();
    Serial.printf("Execution time T2: %d\n", t2-t1);
  }
}

void task3() {
  // Execution time
  unsigned int t1 = micros();

  unsigned int freq = freqCount(T3_Pin);

  // Execution time
  if(freq != -1) {
    unsigned int t2 = micros();
    Serial.printf("Execution time T3: %d\n", t2-t1);
  }
}

void loop() {
  task1();
  task2();
  task3();
  Serial.print("\n");
}
