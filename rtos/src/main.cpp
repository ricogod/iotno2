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

void Temp(void* arg);
void Hum(void* arg);
void Light(void* arg);
SemaphoreHandle_t xSemaphore;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
xSemaphore = xSemaphoreCreateBinary();
xTaskCreatePinnedToCore(Temp, "Temp", 10000, NULL, 1, &tempTaskHandle, 0);
xTaskCreatePinnedToCore(Hum, "Hum", 10000, NULL, 1, &humTaskHandle, 0);
xTaskCreatePinnedToCore(Light, "Light", 10000, NULL, 1, &lightTaskHandle, 1);
}

void Temp(void *pvParameters) {
  while (1) {
  float temp= dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.println();
  xSemaphoreGive(xSemaphore);
  vTaskDelay(4000);
  }
}

void Hum(void *pvParameters) {
while(1){
  float hum= dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();
   xSemaphoreGive(xSemaphore);
  vTaskDelay(3000);
  }
}
  void Light(void *pvParameters) {
  while(1){
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.print(" lx");
  Serial.println();
  xSemaphoreGive(xSemaphore);
  vTaskDelay(3000);
  }
}

void loop() {
  
}