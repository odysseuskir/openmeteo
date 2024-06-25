#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

#define DHT22_PIN 3
#define DHTTYPE DHT22
#define SWITCH_PIN 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT22_PIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(9600);

  Wire.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  if (!bmp.begin()) {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
}

void loop() {
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == HIGH) {
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

  } else {
    sensors_event_t event;
    bmp.getEvent(&event);
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pres:");
    lcd.setCursor(6, 0);
    lcd.print(event.pressure);
    lcd.setCursor(13, 0);
    lcd.print("hPa");

    lcd.setCursor(0, 1);
    lcd.print("Altitude:");
    lcd.setCursor(10, 1);
    lcd.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    lcd.setCursor(15, 1);
    lcd.print("m");
  }
  delay(2000);
}
