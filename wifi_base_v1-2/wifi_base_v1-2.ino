// consigliato minimal SPIFFS

#include <AsyncElegantOTA.h>
#include "htmlPage.h"
#include "wifi_variable.h"


AsyncWebServer server(80);


void setup() {
  Serial.begin(115200);
  delay(1000);
  setupWIFI(); 
  AsyncElegantOTA.begin(&server, "admin", "admin");  
  server.on("/setupwifi", pageSetupWiFi);
  server.on("/connectwifi", pageConnectWiFi);
  server.on("/scanwifi", pageScanWiFi);
  server.begin();
}

void loop() {
  checkWIFIConnection();
  
}
