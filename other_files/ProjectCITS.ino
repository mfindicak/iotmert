#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "DHT.h"

#define FIREBASE_HOST "iotmert-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "fWLCwfcg9BJnMOJEtr6t5bjx2VisRQK731tjrogm"
#define WIFI_SSID "Mert"
#define WIFI_PASSWORD "Mert5157Onur"

const int buzzerPin = 13;
const int temperaturePin = 2;
const int motionPin = 4;
const int lightPin = A0;

float humidity;
float temperature;
int lightPower;
bool isThereMotion;

#define DHTTYPE DHT11
DHT dht(temperaturePin, DHTTYPE);

FirebaseData firebaseData;
FirebaseData buzzerData;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  pinMode(buzzerPin, OUTPUT);
  pinMode(motionPin, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void sensorUpdate()
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  Serial.print("Nem: ");
  Serial.println(humidity);

  Serial.print("Sıcaklık: ");
  Serial.println(temperature);

  lightPower = analogRead(lightPin);

  Serial.print("Işık: ");
  Serial.println(lightPower);

  isThereMotion = digitalRead(motionPin);
  Serial.print("Hareket: ");
  Serial.println(isThereMotion);

  Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", temperature);
  Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", humidity);
  Firebase.setFloat(firebaseData, "/FirebaseIOT/light", lightPower);
  Firebase.setBool(firebaseData, "/FirebaseIOT/motion", isThereMotion);

  Serial.println("Saved.");
  Serial.println("");
}

void loop()
{
  sensorUpdate();

  if (Firebase.getBool(buzzerData, "/FirebaseIOT/buzzer"))
  {
    if (buzzerData.boolData())
    {
      digitalWrite(buzzerPin, HIGH);
    }
    else
    {
      digitalWrite(buzzerPin, LOW);
    }
  }

  delay(100);
}
