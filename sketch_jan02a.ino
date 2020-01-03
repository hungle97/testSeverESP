#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "mana.h"

ESP8266WebServer sv(80);
void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("nghich", "12345679");
  WiFi.begin("Wifi-101", "matkhauvannhucu");
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
    delay(100);
  Serial.begin(115200);
  Serial.println(WiFi.localIP());
  
  sv.on("/index", [] {
    sv.send(200, "text/html",readData("index.html"));
  });
  sv.on("/script", [] {
    sv.send(200, "text/html",readData("script.js"));
  });
  sv.on("/css", [] {
    sv.send(200, "text/html",readData("mycss.css"));
  });
  sv.on("/a0.html", [] {
    sv.send(200, "text/html",String(analogRead(A0)));
  });
  sv.on("/bat.html", [] {
    digitalWrite(D1,HIGH);
    sv.send(200, "text/html","");
  });
  sv.on("/tat.html", [] {
    digitalWrite(D1,LOW);
    sv.send(200, "text/html","");
  });
  sv.on("/transFile",HTTP_ANY, [] {
    sv.send(200, "text/html", 
      "<meta charset='UTF-8'>"
      "<form method='POST' action='/transFile' enctype='multipart/form-data'>"
      "<input type='file' name='Chọn File'>"
      "<input type='submit' value='gửi flie'>"
      "</form>"
    );
   },[] {
    HTTPUpload& file = sv.upload();
    if (file.status == UPLOAD_FILE_START){
      clearData(file.filename.c_str());
    }else if (file.status == UPLOAD_FILE_WRITE){
      saveData(file.filename.c_str(),(const char*)file.buf,file.currentSize);
    }
    
  });
 
  sv.begin();
  pinMode(D1,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  sv.handleClient();
}
