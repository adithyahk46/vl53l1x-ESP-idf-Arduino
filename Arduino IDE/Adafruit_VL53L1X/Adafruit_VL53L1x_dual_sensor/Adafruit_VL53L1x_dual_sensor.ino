#include "Adafruit_VL53L1X.h"

//if code is not working uncomment this two lines
#define XSHUT_PIN 4
#define XSHUT_PIN2 25

#define IRQ_PIN 26
#define IRQ_PIN2 3

Adafruit_VL53L1X SENSOR1 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
Adafruit_VL53L1X SENSOR2 = Adafruit_VL53L1X(XSHUT_PIN2, IRQ_PIN2);
//Add many sensors 

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  // pinMode(XSHUT_PIN1, OUTPUT);
  //pinMode(XSHUT_PIN2, OUTPUT);
  // digitalWrite(XSHUT_PIN1, LOW);
  //digitalWrite(XSHUT_PIN2, LOW);

  Serial.println(F("Adafruit VL53L1X sensor demo"));

  Wire.begin();
  /*------------------------------------------------------------------
                          Intializing Sensor 1
  --------------------------------------------------------------------*/
  if ( SENSOR1.begin(0x52, &Wire)){
    Serial.println(F("SENSOR1 INITIATED AT 0x52"));
  }
  else {
    Serial.print(F("Error on init of sensor1: "));
    Serial.println(SENSOR1.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("SENSOR1 OK!"));
  Serial.print(F("Sensor ID: 0x"));
  Serial.println(SENSOR1.sensorID(), HEX);

  /*--------------------------------------------------------------------
                          Intializing Sensor 2
  ----------------------------------------------------------------------*/

  if ( SENSOR2.begin(0x53, &Wire)){
    Serial.println(F("SENSOR2 INITIATED AT 0x53"));
  }
  else if (! SENSOR1.begin(0x53, &Wire)) {
    Serial.print(F("Error on init of sensor2: "));
    Serial.println(SENSOR2.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("SENSOR2 OK!"));
  Serial.print(F("Sensor ID: 0x"));
  Serial.println(SENSOR2.sensorID(), HEX);

/*-------------------------------------------------------------------------*/

  if (SENSOR1.startRanging()) {
    Serial.println(F("SENSOR1 Ranging started"));
  }
  else {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(SENSOR1.vl_status);
    while (1)       delay(10);
  }

  if (SENSOR2.startRanging()) {
    Serial.println(F("SENSOR2 Ranging started"));
  }
  else {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(SENSOR2.vl_status);
    while (1)       delay(10);
  }
  

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  SENSOR1.setTimingBudget(50);
  Serial.print(F("Timing budget1 (ms): "));
  Serial.println(SENSOR1.getTimingBudget());

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  SENSOR2.setTimingBudget(50);
  Serial.print(F("Timing budget2 (ms): "));
  Serial.println(SENSOR2.getTimingBudget());

  /*
  vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
  vl.VL53L1X_SetInterruptPolarity(0);
  */
}

void loop() {
  int16_t distance1;
  int16_t distance2;

  if (SENSOR1.dataReady()) {
    // new measurement for the taking!
    if (SENSOR1.distance() == -1){
      // something went wrong!
      Serial.print(F("Couldn't get distance1: "));
      Serial.println(SENSOR1.vl_status);
      return;
    }
    else {
      distance1 = SENSOR1.distance();
      Serial.print(F("Distance1: "));
      Serial.print(distance1);
      Serial.print(" mm\t");
    }
     // data is read out, time for another reading!
    SENSOR1.clearInterrupt();
  }
   

  if (SENSOR2.dataReady()) {
    // new measurement for the taking!
    if (SENSOR2.distance() == -1) {
      // something went wrong!
      Serial.print(F("Couldn't get distance2: "));
      Serial.println(SENSOR2.vl_status);

      return;
    }
    else{
      distance2 = SENSOR2.distance();
    Serial.print(F("Distance2: "));
    Serial.print(distance2);
    Serial.println(" mm");
    }
    // data is read out, time for another reading!
    SENSOR2.clearInterrupt();
  }
  
}
