// Pin definition
const byte T1_Pin = 0;
const byte T2_Pin = 1;
const byte T3_Pin = 2;
const byte T4_Pin = 3;

// Maximum values
const unsigned int maxValue = 3300;
const unsigned int freq1Min = 333;
const unsigned int freq2Min = 500;
const unsigned int freqMax = 1000;

// Values measured
float freq1 = 0;
float freq2 = 0;
unsigned int avg = 0;

// Store 4 values for the task 4
unsigned int values[4];

void setup() {
  Serial.begin(115200);
  
  pinMode(T1_Pin, OUTPUT);
  pinMode(T2_Pin, INPUT);
  pinMode(T3_Pin, INPUT);
  pinMode(T4_Pin, INPUT);
}

void task1() {
  // Execution time
  /*unsigned int t1 = micros();*/

  // High for 200us
  digitalWrite(T1_Pin, HIGH);
  delayMicroseconds(200);
  
  // Low for 50us
  digitalWrite(T1_Pin, LOW);
  delayMicroseconds(50);
  
  // High for 30us
  digitalWrite(T1_Pin, HIGH);
  delayMicroseconds(30);

  digitalWrite(T1_Pin, LOW);

  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T1: %d\n", t2-t1);*/
}

float freqCount(const byte pinNumber) {
  // Measure time of a period
  unsigned int t1, t2;

  // Measuring the time the signal is high and low
  do {
    t1 = pulseIn(pinNumber, HIGH, 1e6);
    t2 = pulseIn(pinNumber, LOW, 1e6);
  }
  // Keep only the consistent values
  while(t1 == 0 || t2 == 0 || t1 <= 50 || t2 <= 50);
  
  return 1e6/(t2 + t1);
}

void task2() {
  // Execution time
  /*unsigned int t1 = micros();*/

  freq1 = freqCount(T2_Pin);

  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T2: %d\n", t2-t1);*/
}

void task3() {
  // Execution time
  /*unsigned int t1 = micros();*/

  freq2 = freqCount(T3_Pin);

  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T3: %d\n", t2-t1);*/

}

void task4() {
  // Execution time
  /*unsigned int t1 = micros();*/
  
  unsigned short i;

  values[3] = values[2];
  values[2] = values[1];
  values[1] = values[0];
  values[0] = analogRead(T4_Pin);

  for(i = 0; i < 4; i++) {
    avg += values[i];
  }
  avg /= i+1;

  if(avg >= maxValue /2) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T4: %d\n", t2-t1);*/
}

void task5() {
  // Execution time
  /*unsigned int t1 = micros();*/

  int freq1Scaled = (freq1 - freq1Min) / (freqMax - freq1Min) * 99;
  int freq2Scaled = (freq2 - freq2Min) / (freqMax - freq2Min) * 99;

  freq1Scaled = (freq1Scaled < 0) ? 0 : freq1Scaled;
  freq1Scaled = (freq1Scaled > 99) ? 99 : freq1Scaled;
  freq2Scaled = (freq2Scaled < 0) ? 0 : freq2Scaled;
  freq2Scaled = (freq2Scaled > 99) ? 99 : freq2Scaled;

  Serial.printf("%d,%d\n", freq1Scaled, freq2Scaled);
  
  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T5: %d\n", t2-t1);*/
}

void loop() {
  task1();
  task2();
  task3();
  task4();
  task5();
  Serial.print("\n");
}
