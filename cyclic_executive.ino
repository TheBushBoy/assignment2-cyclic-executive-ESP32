#include <B31DGMonitor.h>
#include <Ticker.h>

#define FRAME_DURATION_MS 4

unsigned long frameCounter = 0;

// Pin definition
const byte T1_Pin = 0;
const byte T2_Pin = 19;
const byte T3_Pin = 18;
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

B31DGCyclicExecutiveMonitor monitor;
Ticker periodicTicker;

void setup() {
  Serial.begin(9600);

  monitor.startMonitoring();  
  periodicTicker.attach_ms(FRAME_DURATION_MS, frame);
  frame();
  
  pinMode(T1_Pin, OUTPUT);
  pinMode(T2_Pin, INPUT);
  pinMode(T3_Pin, INPUT);
  pinMode(T4_Pin, INPUT);
}

void frame() {
  unsigned int slot = frameCounter % 50;
  switch (slot) {
    case 0:  task1();          task3(); task4();          break;
    case 1:  task1(); task2();                   task5(); break;
    case 2:  task1();          task3();                   break;
    case 3:  task1();                                     break;
    case 4:  task1();          task3();                   break;
    case 5:  task1(); task2();          task4();          break;
    case 6:  task1();          task3();                   break;
    case 7:  task1();                                     break;
    case 8:  task1();          task3();                   break;
    case 9:  task1();                                     break;
    case 10: task1();          task3(); task4();          break;
    case 11: task1(); task2();                            break;
    case 12: task1();          task3();                   break;
    case 13: task1();                                     break;
    case 14: task1();          task3();                   break;
    case 15: task1(); task2();          task4();          break;
    case 16: task1();          task3();                   break;
    case 17: task1();                                     break;
    case 18: task1();          task3();                   break;
    case 19: task1();                                     break;
    case 20: task1();          task3(); task4();          break;
    case 21: task1(); task2();                            break;
    case 22: task1();          task3();                   break;
    case 23: task1();                                     break;
    case 24: task1();          task3();                   break;
    case 25: task1(); task2();          task4();          break;
    case 26: task1();          task3();          task5(); break;
    case 27: task1();                                     break;
    case 28: task1();          task3();                   break;
    case 29: task1();                                     break;
    case 30: task1();          task3(); task4();          break;
    case 31: task1(); task2();                            break;
    case 32: task1();          task3();                   break;
    case 33: task1();                                     break;
    case 34: task1();          task3();                   break;
    case 35: task1(); task2();          task4();          break;
    case 36: task1();          task3();                   break;
    case 37: task1();                                     break;
    case 38: task1();          task3();                   break;
    case 39: task1();                                     break;
    case 40: task1();          task3(); task4();          break;
    case 41: task1(); task2();                            break;
    case 42: task1();          task3();                   break;
    case 43: task1();                                     break;
    case 44: task1();          task3();                   break;
    case 45: task1(); task2();          task4();          break;
    case 46: task1();          task3();                   break;
    case 47: task1();                                     break;
    case 48: task1();          task3();                   break;
    case 49: task1();                                     break;
  }
  frameCounter++;
}

void task1() {
  monitor.jobStarted(1);
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
  monitor.jobEnded(1);
}

void task2() {
  monitor.jobStarted(2);
  // Execution time
  /*unsigned int t1 = micros();*/

  unsigned int pulseTime = pulseIn(T2_Pin, HIGH, 2500);
  freq1 = (pulseTime == 0) ? 0 : 1e6/(2*pulseTime);

  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T2: %d\nPulse In: %d\nFreq1: %f\n", t2-t1, pulseTime, freq1);*/
  monitor.jobEnded(2);
}

void task3() {
  monitor.jobStarted(3);
  // Execution time
  /*unsigned int t1 = micros();*/

  unsigned int pulseTime = pulseIn(T3_Pin, HIGH, 2200);
  freq2 = (pulseTime == 0) ? 0 : 1e6/(2*pulseTime);

  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T3: %d\nPulse In: %d\nFreq2: %f\n", t2-t1, pulseTime, freq2);*/
  monitor.jobEnded(3);
}

void task4() {
  monitor.jobStarted(4);
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
    //digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    //digitalWrite(LED_BUILTIN, LOW);
  }
  
  // Execution time
  /*unsigned int t2 = micros();
  Serial.printf("Execution time T4: %d\n", t2-t1);*/
  monitor.jobEnded(4);
}

void task5() {
  monitor.jobStarted(5);
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
  monitor.jobEnded(5);
}

void loop() {}
