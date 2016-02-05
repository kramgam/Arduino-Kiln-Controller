int soakTemp = 2050; //Enter Soak Temp (Degrees Fahrenheit) <------------Changeable
float soakTime = 35; //Enter Soak Time (Minutes. Enter 0 for no soak time.) <------------Changeable
int rampRate = 10; // heating rate (Degrees Fahrenheit per Minute) <------------Changeable

int thermoDO = 5;
int thermoCS = 4;
int thermoCLK = 3;

int relayPin = 9;
int ledPin = 13;



#include "Adafruit_MAX31855.h"

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);



float targetTemp;
float startingTemp;
float currentTemp;

float currentMillis;
float currentMinute;

bool soakStarted = false;
float soakStartTime;



void setup()
{
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("warm up");
  delay(500);

  startingTemp = thermocouple.readFarenheit();
}



void loop()
{
  currentTemp = thermocouple.readFarenheit();
  currentMillis = millis();


  targetTemp = targetTempFunction(minuteFunction(currentMillis));


  if (currentTemp < targetTemp)
  {
    heatON();
  }
  else
  {
    heatOFF();
  }


  Serial.print("{targetTemp,T,"); Serial.print(targetTemp); Serial.println("}");
  Serial.print("{currentMinute,T,"); Serial.print(currentMinute); Serial.println("}");
  Serial.print("{currentTemp,T,"); Serial.print(currentTemp); Serial.println("}");
}



float targetTempFunction (float currentMinute)
{
  float result;
  result = startingTemp + currentMinute * rampRate;

  if (result >= soakTemp)
  {
    result = soakTemp;

    if (soakStarted == false)
    {
      soakStarted = true;
      soakStartTime = currentMinute;
    }
  }

  if (soakStarted == true && currentMinute - soakStartTime >= soakTime)
  {
    while (1 == 1)
    {
      //program end
      heatOFF();
      delay(1000);
    }
  }

  return result;
}


float minuteFunction (float currentMillis)
{
  float result;
  result = currentMillis / 60000;
  return result;
}



void heatON()
{
  digitalWrite(relayPin, HIGH);
  digitalWrite(ledPin, HIGH);
  Serial.print("{heaterStatus,T,"); Serial.print(targetTemp + 5); Serial.println("}"); Serial.flush();
}

void heatOFF()
{
  digitalWrite(relayPin, LOW);
  digitalWrite(ledPin, LOW);
  Serial.print("{heaterStatus,T,"); Serial.print(targetTemp - 5); Serial.println("}"); Serial.flush();
}
