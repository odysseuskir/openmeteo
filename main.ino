#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "DHT.h"

#define DHT22_PIN 3
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHT22_PIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(10,0);
  lcd.print(hum);
  lcd.setCursor(15,0);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Tempratu:");
  lcd.setCursor(10,1);
  lcd.print(temp);
  lcd.setCursor(15,1);
  lcd.print("C");

  delay(2000);
}
