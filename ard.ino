#include"DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600);
  dht.begin();
}
void loop()
{
  int soil_value = analogRead(A0);
  int water_level = analogRead(A1);
  int rain = analogRead(A2);
  delay(3000);
  int humidity = dht.readHumidity();
  int temp = dht.readTemperature();
  int hi = dht.computeHeatIndex(temp,humidity,false);
  Serial.print(soil_value);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(hi);
  Serial.print(",");
  Serial.print(water_level);
  Serial.print(",");
  Serial.print(rain);
  Serial.println();
  delay(1000);
}