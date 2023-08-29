//BERKAY SALIH YILMAZ 180208073
// IOT LED SAPKA ESP8266 KODLARI
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <WiFiManager.h>
#ifndef PSTR
 #define PSTR 
#endif
#define PIN 2
int ledPin = 13;
#define PIN 13
int sayi1= 0;
String cikti="Beko";


const char* host = "www.berkayilmazkou.site"; 
String url;
  int count = 0;
String yazi ="Merhaba";
bool res; //wifimanager oto bağlantı durumu takibi için
//Wifi Manager Girdisi
WiFiManager wm;

//NeoMatrix Ayarları

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0)};
static const unsigned long REFRESH_INTERVAL = 600; // ms
static unsigned long lastRefreshTime = 0;
static unsigned long CircleRefresh = 0;
static const unsigned long Circle_Step = 100; // ms
void setup() {
Serial.begin(115200);
  delay(100);
//////////////WIFI MANAGER AYARLARI

  //wm.resetSettings(); //bu satırı açarsak hafızadaki wifi ayarlarını temizler.
  WiFi.mode(WIFI_STA); // Özellikle modu station'a ayarlıyoruz.

  res = wm.autoConnect("IoT Sapka", "12345678"); // Wifimanager bağlanma satırı. Ağ adı olarak görünmesini istediğimiz yer
  
  if (!res) {
    Serial.println("Bağlantı Sağlanamadı");
    // ESP.restart();
  }
  else {
    //buraya gelmişse WiFi'ya bağlanmış demektir.
    Serial.println("Ağ Bağlantısı Kuruldu");
  }

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");

  
 

  delay(500);

  delay(500);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  if (sayi1== 0){
    url = "/api/led/read_all.php?id=1";
    count = count + 1;
    Serial.println("Here1");
  }
  else if (sayi1== 1){
    url = "/api/led/read_all.php?id=2";
    count = count + 1;
    Serial.println("Here2");
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
     
      if (line=="\n") { // skips the empty space at the beginning 
        section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);

      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      String led= json_parsed["led"][0]["status"];
      cikti=led;

        

        

 
        
       
        
}
  
}

  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;
int y = 3;
int toggle=1;
int diameter = 0;
int radius = 0;
int baslangic = 0;
int sayi;
int gecis = 0;


void loop() {
if (baslangic ==0){
if(millis() - CircleRefresh >= Circle_Step)
  {
    CircleRefresh += Circle_Step;
    if (diameter < 6 ) {
      diameter++ ;
               
    }
    else { 
      diameter = 0;
    }
                
  }

 
  

  
  matrix.fillScreen(0);

  matrix.fillCircle(y, 3, radius, matrix.Color(0, 0, 255));

  matrix.setCursor(x, 0);
  matrix.print(cikti);
  if(--x < -140) {
    x = matrix.width();
    if(++pass >= 2) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(75);
Serial.print(cikti);
Serial.print(cikti);
  count = count +1;
  gecis = gecis+1;
}
else if(baslangic >= 200)
{
  baslangic = 0;
}





  
if(count == 100){
Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  if (sayi == 0){
    url = "/api/led/read_all.php?id=1";
    count = count + 1;
    Serial.println("Here1");
  }
  else if (sayi == 1){
    url = "/api/led/read_all.php?id=2";
    count = count + 1;
    Serial.println("Here2");
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { 
     
      if (line=="\n") { 
        section="json";
      }
    }
    else if (section=="json") {  
      section="ignore";
      String result = line.substring(1);

      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      String led= json_parsed["led"][0]["status"];
       cikti=led;
     baslangic = 0;
     count = 0;
      

        

        

 
        
       
        
}
  
}
}

else if(count == 151);{
  count == 0;
}
}
