void setupWIFI(){
  //WiFi.mode(WIFI_STA);
  WiFi.mode(WIFI_STA);
  WiFi.begin(); 
  delay(1000);
  WiFi.reconnect();
  delay(1000);
  Serial.println("WIFI CONNECTION:");
  Serial.print("Try to connect: ");  Serial.println(WiFi.SSID());
  unsigned long prevmillis = millis();
  while ((millis() - prevmillis) < 10000UL){
    if(WiFi.status() == WL_CONNECTED){
      break;      
    }
    Serial.print(".");
    delay(1000);    
  }
  Serial.println("");
  
  if(WiFi.status()!= WL_CONNECTED) {
    Serial.println("WIFI connection FAIL");
    setAccessPointMode();
  } else {
    SuccessConnectedToWIFI(); 
  }
}

void checkWIFIConnection(){
  if (FLAGscanWIFI)scanWIFI();
  
  if ( (flagNewWIFIcredential) && ((millis() - timerReconnectionWIFI) > 2000UL) ) connectNewWIFI(newSSID,newPASS);
  
  if(flagConnectedWIFI) { 
    if(WiFi.status()!= WL_CONNECTED) { // se WIFI era connesso ed ha perso la connessione
      Serial.println("WIFI connection LOST");
      setAccessPointMode();
    }
  }else{     
    if(WiFi.status()== WL_CONNECTED) {  // se WIFI NON era connesso ed è riuscito a connettersi      
      SuccessConnectedToWIFI(); 
    }else {                             // se WIFI NON era connesso e NON è riuscito a connettersi                                    
      tryToReconnectWIFI();
    }           
  }      
}

void scanWIFI() {
  Serial.println("Scan WIFI networks... ");
  numNetworks = WiFi.scanNetworks();

  if (numNetworks == 0) {
    Serial.println("NO networks found");
  } else {
    Serial.print(numNetworks);
    Serial.println(" Network found:");
    for (int i = 0; i < numNetworks; i++) {
      ssidArray[i] = WiFi.SSID(i);
      rssiArray[i] = WiFi.RSSI(i);
      switch (WiFi.encryptionType(i)){
        case 0:
          encryptionModeArray[i] = "open";
          break;
        case 1:
          encryptionModeArray[i] = "WEP";
          break;
        case 2:
          encryptionModeArray[i] = "WPA";
          break;
        case 3:
          encryptionModeArray[i] = "WPA2";
          break;
        case 4:
          encryptionModeArray[i] = "WPA+WPA2";
          break;
        case 5:
          encryptionModeArray[i] = "WPA2-EAP";
          break;
        case 6:
          encryptionModeArray[i] = "WPA3";
          break;
        case 7:
            encryptionModeArray[i] = "WPA2+WPA3";
            break;
        case 8:
            encryptionModeArray[i] = "WAPI";
            break;
        default:
            encryptionModeArray[i] = "unknown";
        }
              
      Serial.print("RSSI: "); Serial.print(rssiArray[i]);
      Serial.print("\tEncryption: ");
      Serial.print(encryptionModeArray[i]);
      Serial.print("\tSSID: ");
      Serial.println(ssidArray[i]);      
      Serial.println("---------------");
    }
  }
  FLAGscanWIFI = false; 
}

void setAccessPointMode(){  
  Serial.println("Set WIFI Access Point");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(APSSID, APPASS);
  delay(100);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255,255,255,0));
  Serial.print("SSID: ");Serial.println(APSSID);
  Serial.print("PASS: ");Serial.println(APPASS);
  Serial.print("Server IP address: ");Serial.println(APIP);  
  timerReconnectionWIFI = millis();
  flagWaitConnectionWIFI = false;
  flagConnectedWIFI = false; 
}

void SuccessConnectedToWIFI(){
  Serial.println("WIFI connected");
  WiFi.mode(WIFI_STA);
  Serial.print("SSID:    ");  Serial.println(WiFi.SSID());
  Serial.print("Signal:  ");  Serial.print(WiFi.RSSI());Serial.println("dBm");
  Serial.print("IP:      ");  Serial.println(WiFi.localIP());
  Serial.print("Subnet:  ");  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");  Serial.println(WiFi.gatewayIP());
  flagConnectedWIFI = true;  
}

void tryToReconnectWIFI(){
  if(flagWaitConnectionWIFI){
    if ((millis() - timerReconnectionWIFI) > 6000UL){
      timerReconnectionWIFI = millis();
      Serial.println("Try WIFI Reconnection FAIL");
      WiFi.mode(WIFI_AP);
      flagWaitConnectionWIFI = false;      
    }    
  } else {
    if ((millis() - timerReconnectionWIFI) > 30000UL){
      timerReconnectionWIFI = millis();
      Serial.println("Try reconnet WIFI...");
      WiFi.mode(WIFI_AP_STA);
      WiFi.reconnect();
      flagWaitConnectionWIFI = true; 
    }
  }  
}

void connectNewWIFI(String ssid, String pass){
  flagNewWIFIcredential = false;
  Serial.print("Try to connect new SSID: "); Serial.println(ssid);
  
  char ssidChar[20] ;
  char passChar[20] ;  

  ssid.toCharArray(ssidChar, ssid.length() + 1);
  pass.toCharArray(passChar, pass.length() + 1);
 
  WiFi.mode(WIFI_STA);
  WiFi.persistent(true);
  WiFi.begin(ssidChar, passChar);
  delay(2000);
  ESP.restart();  
}
