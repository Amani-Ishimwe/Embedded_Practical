#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String candidateName = "ISHIMWE AMANI SAMUEL";

void scrollName();

void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  dht.begin();

  delay(2000);
}

void loop()
{
  float temperature = dht.readTemperature();

  lcd.setCursor(0, 1);
  lcd.print("Temp:            ");

  if (isnan(temperature))
  {
    lcd.setCursor(6, 1);
    lcd.print("ERR");

    Serial.println("ERR");
  }
  else
  {
    lcd.setCursor(6, 1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");

    Serial.println(temperature);
  }

  scrollName();

  delay(2000);
}

void scrollName()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(candidateName);
}