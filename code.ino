#define BLYNK_TEMPLATE_ID "TMPL3GbyR9d7Q"
#define BLYNK_TEMPLATE_NAME "AIR QUALITY"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp32.h> 
#define DHT11PIN 16
#define DHTTYPE DHT11
#define MQ135PIN 34
DHT dht(DHT11PIN, DHT11);
#define BLYNK_PRINT Serial
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
char auth[] = "naWwV_rZKYKlWZN6cpeUDeoLgoR5mH9O";
Char ssid[]=“SOEII”
Char Pass[]=“soe@mru”
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);}
display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("DHT11 & MQ135 with OLED");
  display.display();
  delay(2000);
  display.clearDisplay();}
void loop() {
  float humi = dht.readHumidity();
float temp = dht.readTemperature();
  float airQuality = analogRead(MQ135PIN);
String airQualityLabel;
if (airQuality < 400) {
    airQualityLabel = "GOOD! ";
  } else if (airQuality > 400 && airQuality < 800) {
    airQualityLabel = "  Poor!  ";
  } else if (airQuality > 800 && airQuality < 1200) {
    airQualityLabel = "  Very bad!  ";
  } else if (airQuality > 1200 && airQuality < 2000) {
    airQualityLabel = "  Toxic!  ";
  } else {
    airQualityLabel = "  Toxic  ";
  }
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
  Serial.print("Air Quality: ");
Serial.print(airQuality);
  Serial.print(" (");
  Serial.print(airQualityLabel);
 Serial.println(")");
if (airQuality >=300) {
      Serial.println("Air Quality is changing to Toxic level");
      Blynk.logEvent("airQualityMonitoring", "Air Quality is changing to Toxic level") ;
      delay(500);
    }
Blynk.virtualWrite(V0, temp); 
  Blynk.virtualWrite(V1, humi); 
  Blynk.virtualWrite(V2, airQuality); 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");
  display.print("Humidity: ");
  display.print(humi);
  display.println(" %");
  display.print("Air Quality: ");
  display.print(airQuality);
  display.print(" (");
  display.print(airQualityLabel);
  display.println(")");
  display.display();
  delay(1000); 
}









