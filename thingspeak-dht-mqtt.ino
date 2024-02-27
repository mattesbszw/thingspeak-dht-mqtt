#include <DHT.h>
#include <WiFi.h>
//hier muss eine Bibliothek für MQTT eingebunden werden

#define DHT_PIN 4
#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

// WLAN-Zugansdaten
const char* ssid = "...";
const char* password = "...";

WiFiClient wifiClient;
// PubSubClient erzeugen

//Thingspeak-Daten: MQTT-Server/Port sowie die exportierten MQTT-Daten
const char* MQTT_SERVER = "mqtt3.thingspeak.com";
const long MQTT_PORT = 1883;

//Thingspeak-Daten wie gem. Video generiert

const long THINGSPEAK_CHANNEL = 0;
const char MQTT_USERNAME[] = "...";            
const char MQTT_PASSWORD[] = "...";         
const char MQTT_CLIENTID[] = "...";


void setup(void){
  
  Serial.begin(115200);
  dht.begin();              // init DHT sensor
  connectWiFi();

  // init MQTT client
  // ...
  
}

//hier wird wird der ESP mit dem WLAN verbunden
void connectWiFi(){

  WiFi.mode(WIFI_STA);
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  Serial.print("Connecting to " + String(ssid));
  WiFi.begin(ssid, password); 
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(5000);     
  } 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(void){ 

  if (WiFi.status() != WL_CONNECTED){
    connectWiFi();
  }
  
  float hTmp = dht.readTemperature();
  String dhtTemperature = "0";
  if (!isnan(hTmp)) {
    dhtTemperature = hTmp;
  }
  Serial.print("Sensor (*C): "); 
  Serial.println(dhtTemperature);
 
  float hHum = dht.readHumidity();
  String dhtHumidity = "0";
  if (!isnan(hHum)) {
    dhtHumidity = hHum;
  }
  Serial.print("Sensor (%): "); 
  Serial.println(dhtHumidity);

  // hmmmmm ...
  // ...
  
  delay(4000);
}

void mqttConnect(){
  /*hier soll sich der ESP mit dem Thingspeak-MQTT Broker verbinden.
  bitte hier eine Schleife verwenden, damit eine Verbindung garantiert wird*/
}

void reconnect(){
  /*Hier soll sich der Client neu verbinden*/
}

void mqttSubscribe(long subChannelID){
  /*diese Funktion soll den übergebenen Channel abonieren*/
}

void mqttPublish(long pubChannelID, String message) {
  /*bei Aufruf dieser Funktion soll im übergebenen Channel eine Nachricht veröffentlicht werden
  Diese Nachricht soll verschiendene Felder beinhalten (Die beiden Temperaturen und vll die Luftfeuchtigkeit)*/
}

void mqttSubscriptionCallback( char* topic, byte* payload, unsigned int length ) {
  /*Diese Funktion wird aufgerufen, wenn ein abonnierter Channel geupdated wurde
  /Die empfangene Nachricht (payload) und das Topic sollen auf dem seriellen Monitor ausgegeben werden*/
}
