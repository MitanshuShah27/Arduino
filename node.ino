#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <SoftwareSerial.h>
//#include <ESP8266HTTPClient.h>
//#include<WiFi.h>
SoftwareSerial mySerial(D1,D2);

#define FIREBASE_HOST "https://prehack-e0fa0-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyATj-z3Ey-SfYZ17A6k9-kRhCKMcneD34Y"
#define WIFI_SSID "dlink-61AC"
#define WIFI_PASSWORD "vaishujay3"

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;
void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected to Wi-Fi");

    // Set Firebase configuration
    firebaseConfig.host = FIREBASE_HOST;
    firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&firebaseConfig, &firebaseAuth);
    Firebase.reconnectWiFi(true);
}
void loop()
{
  String msg = mySerial.readStringUntil('\n');
  int fc = msg.indexOf(',');
  int sc = msg.indexOf(',', fc + 1);
  int tc = msg.indexOf(',', sc+1);
  int foc = msg.indexOf(',', tc + 1);
  int fic = msg.indexOf(',', foc + 1);

  String sv = msg.substring(0, fc);
  String hu = msg.substring(fc + 1, sc);
  String temp = msg.substring(sc + 1, tc);
  String hi = msg.substring(tc+1, foc);
  String wl = msg.substring(foc + 1, fic);
  String rain = msg.substring(fic + 1);

  int soil_val = sv.toInt();
  int humi = hu.toInt();
  int temperature = temp.toInt();
  int heat_index = hi.toInt();
  int water_lev = wl.toInt();
  int ra = rain.toInt();

  Firebase.setInt(firebaseData,"0123/Soil_Value",soil_val);
  Firebase.setInt(firebaseData,"0123/Humidity",humi);
  Firebase.setInt(firebaseData,"0123/Temperature",temperature);
  Firebase.setInt(firebaseData,"0123/Heat_index",heat_index);
  Firebase.setInt(firebaseData,"0123/Water_level",water_lev);
  Firebase.setInt(firebaseData,"0123/Rain",ra);
  delay(2000);
  Serial.println(msg);
}