#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "Vk_qI-LUS1ZLWJq_qK3ld7-zr7oMQ7kT";
char ssid[] = "66";
char password[] = "11111111";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor(){
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  if(isnan(suhu)||isnan(kelembaban)){
    Serial.println("Gagal membaca Sensor !");
    return;
  }
  Blynk.virtualWrite(V5,suhu);
  Blynk.virtualWrite(V6,kelembaban);
}
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth,ssid,password);
  dht.begin();
  timer.setInterval(1000L,sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  
  float suhu = dht.readTemperature();
  float kelembaban = dht.readHumidity();
  
  Serial.print("Suhu : ");
  Serial.print(suhu);
  Serial.print(" *C   ");
  Serial.print("Kelembaban : ");
  Serial.print(kelembaban);
  Serial.println(" %");
  delay(5000);
}
