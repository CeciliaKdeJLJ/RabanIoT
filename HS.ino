#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // altura de la pantalla OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int sensorPin = A0;
const int humedadAire = 822;
const int humedadAgua = 420;
int porcentajeHumedad;

void setup() 
{
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() 
{
   int humedad = analogRead(sensorPin);
   Serial.println(humedad);
   
   porcentajeHumedad = map(humedad, humedadAire, humedadAgua, 0, 100);
   if (porcentajeHumedad > 100) {
     porcentajeHumedad = 100;
   }

   Serial.print(porcentajeHumedad);
   Serial.println("%"); 

   display.clearDisplay();
   display.setTextSize(2);
   display.setTextColor(WHITE);
   display.setCursor(0, 0);
   display.println("Humedad:");
   display.print(porcentajeHumedad);
   display.println("%");
   display.display();

   delay(3000); // Pausa de 3 segundos
}
