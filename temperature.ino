#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String candidateName = "ISHIMWE AMANI SAMUEL";

int scrollIndex = 0;
unsigned long lastScroll = 0;

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

  // ================= TEMPERATURE =================
  lcd.setCursor(0, 1);
  lcd.print("Temp:            ");

  if (!isnan(temperature))
  {
    lcd.setCursor(6, 1);
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");

    Serial.println(temperature);
  }
  else
  {
    lcd.setCursor(6, 1);
    lcd.print("ERR");

    Serial.println("ERR");
  }

  // ================= SCROLL NAME =================
  if (millis() - lastScroll > 300)
  {
    scrollText();
    lastScroll = millis();
  }

  delay(200);
}

// ================= SCROLL FUNCTION =================
void scrollText()
{
  String padded = candidateName + "                ";

  lcd.setCursor(0, 0);

  for (int i = 0; i < 16; i++)
  {
    lcd.print(padded[(scrollIndex + i) % padded.length()]);
  }

  scrollIndex++;

  if (scrollIndex >= padded.length())
  {
    scrollIndex = 0;
  }
}