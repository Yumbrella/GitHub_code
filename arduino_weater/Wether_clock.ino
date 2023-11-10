#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "STXINWEI50.h"
#include "weather_60.h"
#include "NTPClient.h"
#include "WiFiUdp.h"

TFT_eSPI tft = TFT_eSPI();
const char* ssid = "Sshvcn";
const char* passwd = "123456789";

const char* server = "api.seniverse.com";
const int httpport = 80;
int Now_tem = 0;
int Code_num = 0;
const char* id;
const char* name;
const char* path;
const char* country; 
const char* text;
const char* temperature;
const char* wind_scale;

WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeclient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);


void weather_connect()
{
  if(client.connect(server, httpport)==1){
    client.print("GET https://api.seniverse.com/v3/weather/now.json?key=SYES5WypsQjuBxioC&location=山东济南&language=zh-Hans&unit=c HTTP/1.1\r\n");
    client.print("host:api.seniverse.com\r\n");
    client.print("Accept-Language:zh-Hans\r\n");
    client.print("Connection:close\r\n\r\n"); //向心知天气的服务器发送请求。

    String status_code = client.readStringUntil('\r');
    Serial.println("服务器--连接成功");
    Serial.println(status_code);
    if(client.find("\r\n\r\n")==1){
      String json_form_server = client.readStringUntil('\n');
      parseUserdata(json_form_server);
      //Serial.println(json_form_server);
    }
    delay(5000);
  }
  else {
    Serial.println("连接失败....");
  }
}

void parseUserdata(String content)
{
  StaticJsonDocument<10000> jsonBuffer;
  DeserializationError error = deserializeJson(jsonBuffer, content);
  if(error){
    Serial.print("deserializejson() failed: ");
    Serial.println(error.f_str());
    return;
  }
  id = jsonBuffer["results"][0]["location"]["id"];
  name = jsonBuffer["results"][0]["location"]["name"];
  path = jsonBuffer["results"][0]["location"]["path"];
  country = jsonBuffer["results"][0]["location"]["country"];
  text = jsonBuffer["results"][0]["now"]["text"];
  temperature = jsonBuffer["results"][0]["now"]["temperature"];
  wind_scale = jsonBuffer["results"][0]["now"]["wind_scale"];
 // Serial.println(id);
  //Serial.println(name);
 // Serial.println(country);
  //Serial.println(text);
 // Serial.println(temperature);
 // Serial.println(path);

}

void TFT_Display()
{
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0, 0, 240, 240, back_ground);
  tft.setTextColor(TFT_BLACK);
  tft.pushImage(150 ,70 ,60, 60, sunny60);
  tft.drawFastHLine(0, 59, 240,TFT_BLACK);
  tft.drawFastHLine(0, 60, 240,TFT_BLACK);
  tft.drawFastHLine(0, 61, 240,TFT_BLACK);
  tft.loadFont(STXINWEI50);
  tft.drawString("天气", 5, 80);
  tft.drawString("风力", 5, 190);
  tft.drawString(text, 126, 135);
  tft.drawString(name, 5, 135);
  tft.unloadFont();
  tft.setCursor(107, 80, 4);
  tft.println(":");
  tft.setCursor(107, 190, 4);
  tft.println(":");
  tft.drawNumber(2, 130, 190);
  tft.loadFont(STXINWEI50);
  tft.drawString("级", 155, 190);
  tft.unloadFont();
}

void RTC_clock()
{
  timeclient.update();
  String clock = timeclient.getFormattedTime();
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString(clock, 5, 10, 4);
}

void setup() 
{
  // put your setup code here, to run once:
  tft.init();

  Serial.begin(9600);
  delay(1000);
    WiFi.begin(ssid, passwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("connected...");
  }
  Serial.println("wifi———连接成功");
}

int count_num= 1;
void loop() {
  // put your main code here, to run repeatedly:
  weather_connect();
  while(1){
  TFT_Display();
  RTC_clock();
  delay(1000);
  count_num += 1;
  if(count_num = 300);
    continue;
  }
}
