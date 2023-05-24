#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BH1750.h>

#define SCREEN_WIDTH 128 // ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // altura de la pantalla OLED
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR      0x3C
#define SENSOR_ADDR    0x23
#define SENSOR_PIN     A0
#define HUMEDAD_AIRE   822
#define HUMEDAD_AGUA   420
#define DELAY_TIME     3000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
BH1750 lightMeter(SENSOR_ADDR);

void setup() 
{
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() 
{
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Humidity processing
  int humedad = analogRead(SENSOR_PIN);
  int porcentajeHumedad = map(humedad, HUMEDAD_AIRE, HUMEDAD_AGUA, 0, 100);
  if (porcentajeHumedad > 100) {
    porcentajeHumedad = 100;
  }

  // Light processing
  if(!lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE)) {
    Serial.println(F("Could not begin BH1750"));
    for(;;); // Don't proceed, loop forever
  }
  float lux = lightMeter.readLightLevel();

  // Display humidity and light data
  Serial.print("Humedad: ");
  Serial.print(porcentajeHumedad);
  Serial.println("%"); 
  Serial.print("Luz: ");
  Serial.print(lux);
  Serial.println(" lux");

  // Display Humidity
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Humedad:");
  display.print(porcentajeHumedad);
  display.println("%");

  // Display Light
  display.setTextSize(2);
  display.setCursor(0, 32);
  display.println("Luz:");
  display.print(lux);
  display.println(" lux");

  display.display();

  delay(DELAY_TIME);
}
