const int sensorPin = A0;
const int humedadAire = 822;
const int humedadAgua = 420;
int porcentajeHumedad;

void setup() 
{
  Serial.begin(9600);
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

   delay(3000); // Pausa de 1 segundo
}