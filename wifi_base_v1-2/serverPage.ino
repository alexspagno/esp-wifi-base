void pageSetupWiFi(AsyncWebServerRequest *request){
  String response_message = "";
  
  // head of page
  response_message += htmlHead;
  
  // status
  response_message += "<h3>Status:</h3>"; 
  if (WiFi.status() == WL_CONNECTED){ 
    response_message += "<table><tbody>";         
    response_message += "<tr><td>WIFI:</td><td>Connected</td></tr>";
    response_message += "<tr><td>SSID:</td><td>"    + WiFi.SSID() + "</td></tr>";
    response_message += "<tr><td>Signal:</td><td>"  + String(WiFi.RSSI()) + " dBm</td></tr>";
    response_message += "<tr><td>IP:</td><td>"      + String(WiFi.localIP().toString()) + "</td></tr>";
    response_message += "<tr><td>Subnet:</td><td>"  + String(WiFi.subnetMask().toString()) + "</td></tr>";
    response_message += "<tr><td>Gateway:</td><td>" + String(WiFi.gatewayIP().toString()) + "</td></tr>";  
    response_message += "</tbody></table><br><br>";    
  }else{
    response_message += "WIFI: Disconnected<br><br>";
  }
       
  // network list
  response_message += R"------( 
    <p>
      <h3>Select WIFI network:
      <button onclick="window.location.href='\scanwifi'">WIFI SCAN</button></h3>
    </p> 
  )------";
   
  if (numNetworks == 0){
    response_message += "No WIFI network found.<br>";
  }else{
    response_message += R"------(
    
    <form action="/connectwifi" method="post">
    <table border="1">
      <thead>
        <tr>
          <th>Select</th>
          <th>SSID</th>
          <th>Encrypt</th>
          <th>RSSI</th>
        </tr>
    </thead>
    <tbody>
            
    )------"; 
    
    // Show access points
    for (uint8_t ap_idx = 0; ap_idx < numNetworks; ap_idx++){
      response_message += R"------(<tr><td><input type="radio" name="wifiSSID_value" value=")------" + ssidArray[ap_idx] + R"------("></td>)------";
      response_message += "<td>" + ssidArray[ap_idx] + "</td><td>" + encryptionModeArray[ap_idx] + "</td><td>" + rssiArray[ap_idx] + " dBm</td></tr>";
    }
    response_message += R"------(
    
      </tbody>
    </table>
    <br>Password:
    <input type="text" name="wifiPASS_value">
    <input type="submit" value="Connect">
    </form><br><br>
    
    )------";
  
  }
  response_message += "</body></html>";
  
  request->send(200, "text/html", response_message);
}

void pageScanWiFi(AsyncWebServerRequest *request){  
  String response_message = "";
  response_message += htmlHead + htmlScan;
  request->send(200, "text/html", response_message);
  FLAGscanWIFI = true;
}

void pageConnectWiFi(AsyncWebServerRequest *request){
  String response_message = "";
  response_message += htmlHead + htmlConnect;
  request->send(200, "text/html", response_message);
  if (request->args() == 2){
    if (request->argName(0) == "wifiSSID_value" && request->argName(1) == "wifiPASS_value"){
      setupNewWIFIcredential(request->arg("wifiSSID_value"),request->arg("wifiPASS_value"));     
    }
  }  
}

void setupNewWIFIcredential(String ssid, String pass){
  newSSID = ssid;
  newPASS = pass;
  flagNewWIFIcredential = true; 
  timerReconnectionWIFI = millis();  
}
