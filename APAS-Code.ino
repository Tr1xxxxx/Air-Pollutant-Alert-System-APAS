#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Pin connections for the LCD
const int rs = 2;
const int en = 3;
const int d4 = 6;
const int d5 = 7;
const int d6 = 8;
const int d7 = 9;

// Initialize the LiquidCrystal object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DHT sensor configuration
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Air quality sensor pin
#define GAS_SENSOR A0
int gasLevel = 0;
String quality = "";

void setup() {
  // Initialize LCD and DHT sensor
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);

  // Display initialization message
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void air_sensor() {
  // Read gas sensor value
  gasLevel = analogRead(GAS_SENSOR);

  // Determine air quality
  if (gasLevel < 400) {
    quality = "Excellent :D";
  } else if (gasLevel < 1000) {
    quality = "Good :)";
  } else if (gasLevel < 2000) {
    quality = "Moderate :|";
  } else if (gasLevel < 5000) {
    quality = "Unhealthy :(";
  } else {
    quality = "Hazardous :0";
  }

  // Display air quality
  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasLevel);

  lcd.setCursor(0, 1);
  lcd.print("AQ: ");
  lcd.print(quality);
}

void sendSensor() {
  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    return;
  }

  // Display temperature and humidity
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("RH: ");
  lcd.print(h);
  lcd.print("%");
}

void loop() {
  // Alternate between displaying air quality and DHT data
  air_sensor();
  delay(2000);

  lcd.clear();
  sendSensor();
  delay(2000);

  lcd.clear();
}