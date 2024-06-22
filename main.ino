#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define DHT22_PIN 3
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHT22_PIN, DHTTYPE);

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void displaySensorDetails(void) {
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup() {
  Serial.begin(9600);

  Wire.begin();

  dht.begin();

  lcd.init();
  lcd.backlight();

  if(!bmp.begin()) {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  displaySensorDetails();
}

void loop() {

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(10, 0);
  lcd.print(hum);
  lcd.setCursor(15, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temperat:");
  lcd.setCursor(10, 1);
  lcd.print(temp);
  lcd.setCursor(15, 1);
  lcd.print("C");

  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");

    float bmpTemperature;
    bmp.getTemperature(&bmpTemperature);
    Serial.print("Temperature: ");
    Serial.print(bmpTemperature);
    Serial.println(" C");

    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    Serial.println(" m");
    Serial.println("");
  } else {
    Serial.println("Sensor error");
  }

  delay(2000);
}
