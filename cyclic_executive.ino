// Pin definition
const byte T1_Pin = 15;
const byte T2_Pin = 20;
const byte T3_Pin = 21;
const byte T4_Pin = 22;
const byte T5_Pin = 23;

// Maximum values
const unsigned int maxValue = 3300;
const unsigned int freq1Min = 333;
const unsigned int freq2Min = 500;
const unsigned int freqMax = 1000;

// Values measured
unsigned int freq1 = -1;
unsigned int freq2 = -1;
unsigned int avg = -1;

// Store previous counters of time
unsigned int currentMicros;
unsigned int previousMicros = 0;

// Store 4 values for the task 4
unsigned int values[4];

void setup() {
  Serial.begin(9600);
  
  pinMode(T1_Pin, OUTPUT);
  pinMode(T2_Pin, INPUT);
  pinMode(T3_Pin, INPUT);
  pinMode(T4_Pin, INPUT);
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

  freq1 = freqCount(T2_Pin);

  // Execution time
  if(freq != -1) {
    unsigned int t2 = micros();
    Serial.printf("Execution time T2: %d\n", t2-t1);
  }
}

void task3() {
  // Execution time
  unsigned int t1 = micros();

  freq2 = freqCount(T3_Pin);

  // Execution time
  if(freq != -1) {
    unsigned int t2 = micros();
    Serial.printf("Execution time T3: %d\n", t2-t1);
  }
}

void task4() {
  // Execution time
  unsigned int t1 = micros();
  
  unsigned short i;

  values[3] = values[2];
  values[2] = values[1]
  values[1] = values[0];
  values[0] = analogRead(T4_Pin);

  for(i = 0; i < 4; i++) {
    avg += values[i];
  }
  avg /= i;

  if(avg >= maxValue /2) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // Execution time
  unsigned int t2 = micros();
  Serial.printf("Execution time T4: %d\n", t2-t1);
}

void task5() {
  // Execution time
  unsigned int t1 = micros();

  println("%d,%d", (freq1 - freq1Min) / (freqMax - freq1Min) * 99, (freq1 - freq2Min) / (freqMax - freq2Min) * 99);
  
  // Execution time
  unsigned int t2 = micros();
  Serial.printf("Execution time T5: %d\n", t2-t1);
}

void loop() {
  task1();
  task2();
  task3();
  task4();
  task5();
  Serial.print("\n");
}
