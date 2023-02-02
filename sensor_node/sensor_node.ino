#include <Wire.h>
#include <BH1750.h>       // adds BH1750 library file 
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <LoRa.h>


#define SS 5
#define RST 14
#define DI0 2
 
//#define TX_P 17
//#define ENCRYPT 0x78
#define BAND 433E6
#define rain_sensor 34
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;


BH1750 lightMeter;
String LoRaMessage = "";
char device_id[12] = "MyDevice123";

void setup()
{

  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();  
   
  pinMode (rain_sensor, INPUT);
  while (!Serial);
 
  Serial.println(F("LoRa Sender"));
 
  LoRa.setPins(SS, RST, DI0);
  //oRa.setTxPower(TX_P);
  //LoRa.setSyncWord(ENCRYPT);

  if (!LoRa.begin(BAND))
  {
    Serial.println(F("Starting LoRa failed!"));
    while (1);
  }
  if (!bme.begin(0x76))
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
 
}
 
void loop()
{
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();
 
   double dewPoint = dewPointFast(temperature, humidity);
   
  int rainfall = analogRead(rain_sensor);
  if (rainfall >= 100)
  {
   // rainfall = 100;
  }
  if (rainfall <= 0)
  {
    rainfall = 0;
  }
 
   
  float lux = lightMeter.readLightLevel();
 
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(F("*C"));
 
  Serial.print(F("Pressure = "));
  Serial.print(pressure);
  Serial.println(F("hPa"));
 
  Serial.print(F("Approx. Altitude = "));
  Serial.print(altitude);
  Serial.println(F("m"));
 
  Serial.print(F("Humidity = "));
  Serial.print(humidity);
  Serial.println(F("%"));
 
 
  Serial.print(F("Rainfall = "));
  Serial.print(rainfall);
  Serial.println(F("%"));
 
  Serial.print(F("Light = "));
  Serial.print(lux);
  Serial.println(F(" lx"));
 
  Serial.println();
 
  LoRaMessage = String(device_id) + "/" + String(temperature) + "&" + String(pressure)
                + "#" + String(altitude) + "@" + String(humidity) + "$" + String(dewPoint)
                + "^" + String(rainfall) + "!" + String(lux);
 
  // send packet
  Serial.print("lora packet"); 
   
  LoRa.beginPacket();
  Serial.print("working");
  
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  delay(1000);
}



double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}