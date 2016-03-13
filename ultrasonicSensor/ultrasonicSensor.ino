#include <stdio.h>
const int TriPin = 12;
const int EchoPin = 13;

const int variationThreshold = 2;
const int distAvgArraySize = 5;

void serCommand(){ //a general function to call the command flag for issuing all other commands
  Serial.write(0xFE);
}

/**
 * Returns a single reading of the ultrasonic sensor.
 */
unsigned long readDistance()
{
  unsigned long cm;
  digitalWrite (TriPin, LOW);
  delayMicroseconds (2);
  digitalWrite (TriPin, HIGH); 
  delayMicroseconds (10);
  digitalWrite (TriPin, LOW);
  cm = pulseIn (EchoPin, HIGH, 100000) / 58.0;
  cm = (int (cm * 100.0)) / 100.0; 
  return cm;
}

/**
 * Return the smallest value in a given array of the specified size
 */
unsigned long smallest(unsigned long array[], int arraySize){
  unsigned long smallest = array[0];
  for(int i = 1; i < arraySize; i++){
    if(array[i] < smallest){
      smallest = array[i];
    }
  }
  return smallest;
}
/**
 * Return the largest value in a given array of the specified size
 */
unsigned long largest(unsigned long array[], int arraySize){
  float largest = array[0];
  for(int i = 1; i < arraySize; i++){
    if(array[i] > largest){
      largest = array[i];
    }
  }
  return largest;
}

/**
 * put the given element in the front of the array, and shift all the other elements back. Removes the last element.
 */
void putFrontAndShift(unsigned long array[], int arraySize, unsigned long element){
  for(int i = arraySize - 2; i >= 0; i--){
    array[i + 1] = array[i]; 
  }
  array[0] = element;
}
/**
 * Print the given array
 */
void printArray(unsigned long array[], int arraySize){
  Serial.print("[");
  for(int i = 0; i < arraySize; i++){
    Serial.print(array[i]);
    Serial.print(", ");
  }
  Serial.println("]");
}
/**
 * Returns a verified distance
 */
unsigned long avgDistance(int arraySize){
  unsigned long distReadings[arraySize];
  unsigned long variation;
  unsigned long newReading;
  for(int i = 0; i < arraySize; i++){//Put the first x readings into the array
    distReadings[i] = readDistance();
  }
  variation = largest(distReadings, arraySize) - smallest(distReadings, arraySize);
  //Serial.println(distReadings);
  printArray(distReadings, arraySize);
  Serial.print("variation out of loop: ");
  Serial.println(variation);
  while(variation > variationThreshold){
     putFrontAndShift(distReadings, arraySize, readDistance());
     variation = largest(distReadings, arraySize) - smallest(distReadings, arraySize);
     //Serial.println(distReadings);
     printArray(distReadings, arraySize);
     Serial.print("variation in loop: ");
     Serial.println(variation);
  }
  //return the average
  unsigned long sum = 0;
  for(int i = 0; i < arraySize; i++){
    sum += distReadings[i];
  }
  return sum / arraySize;
}
 
void setup()
{
  Serial.begin(9600);
  pinMode (TriPin, OUTPUT);
  pinMode (EchoPin, INPUT);
}
 
void loop()
{
  Serial.println(avgDistance(distAvgArraySize));
  delay (1000);
}
