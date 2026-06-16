#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String candidateName = "ISHIMWE AMANI SAMUEL";

void setup()
{
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  dht.begin();

  lcd.clear();
}

void loop()
{
  // =========================
  // READ TEMPERATURE ONLY
  // =========================
  float temperature = dht.readTemperature();

  if (isnan(temperature))
  {
    Serial.println("Sensor Error");
    return;
  }

  // =========================
  // LCD SECOND ROW
  // =========================
  lcd.setCursor(0, 1);
  lcd.print("Temp:            ");

  lcd.setCursor(6, 1);
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");

  // =========================
  // SERIAL OUTPUT (FOR PC / MQTT)
  // =========================
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  // =========================
  // SCROLL NAME (FIRST ROW)
  // =========================
  scrollName();

  delay(2000);
}

void scrollName()
{
  if (candidateName.length() <= 16)
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(candidateName);
    return;
  }

  for (int i = 0; i <= candidateName.length() - 16; i++)
  {
    lcd.setCursor(0, 0);
    lcd.print(candidateName.substring(i, i + 16));
    delay(300);
  }
}