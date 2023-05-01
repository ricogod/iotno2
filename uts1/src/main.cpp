#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DhtPin 5
#define DhtType DHT11
DHT dht(DhtPin, DhtType);

BH1750 lightMeter(0x23);

TaskHandle_t tempTaskHandle=NULL;
TaskHandle_t humTaskHandle=NULL;
TaskHandle_t lightTaskHandle=NULL;

void Temp(void *pvParameters) {
  for(;;){
  float temp= dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  vTaskDelay(4000);
  }
}

void Hum(void *pvParameters) {
  for(;;){
  float hum= dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  vTaskDelay(3000);
  }
}
  void Light(void *pvParameters) {
  for(;;){
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  vTaskDelay(3000);
  }
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();

xTaskCreatePinnedToCore(Temp, "Temp", 10000, NULL, 1, &tempTaskHandle, 0);
xTaskCreatePinnedToCore(Hum, "Hum", 10000, NULL, 1, &humTaskHandle, 0);
xTaskCreatePinnedToCore(Light, "Light", 10000, NULL, 1, &lightTaskHandle, 1);
}

void loop() {
  
}