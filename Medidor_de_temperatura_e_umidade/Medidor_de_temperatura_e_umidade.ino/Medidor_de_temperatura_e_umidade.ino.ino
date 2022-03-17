#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//QUAL PINO?
#define DHTPIN A2

// AQUI É SEMPRE DHT11 (POR QUE É O TIPO DO MEU
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

byte temp[8] = {
  B00000100,
  B00001010,
  B00001010,
  B00001010,
  B00001010,
  B00011111,
  B00011111,
  B00001110
};

byte humd[8] = {
  B00000100,
  B00000100,
  B00001010,
  B00001010,
  B00010001,
  B00010001,
  B00010001,
  B00001110,
};

byte grau[8] = { B00001100,
                 B00010010,
                 B00010010,
                 B00001100,
                 B00000000,
                 B00000000,
                 B00000000,
                 B00000000,
               };

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  lcd.clear();
  lcd.createChar(0, temp);
  lcd.createChar(1, humd);
  lcd.createChar(2, grau);
  dht.begin();
}

void loop()
{
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(t);
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))   {
    lcd.setBacklight(LOW);
    Serial.println("Failed to read from DHT");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp. - Umidade");
    lcd.setCursor(1, 1);

    // Temperatura
    lcd.write((byte)0); // Simbolo de termômetro
    lcd.print(" ");
    lcd.print(t, 1);
    lcd.write((byte)2);

    lcd.print("  ");

    // Umidade
    lcd.write((byte)1); // Simbolo de umidade
    lcd.print(" ");
    lcd.print(h, 1);
    lcd.print("%");
  }
  delay(1000);
}
