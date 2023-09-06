# esp-wifi-base
Basic skecth for esp32 wifi management with elegantOTA

I'm working on a basic sketch for esp32 with the following characteristics:
- Connection check with reconnection attempts
- AccessPoint activation for new network configuration
- Network scan and selection
- ElegantOTA

When esp32 starts, if it fails to connect, it generates an AccessPoint to be able to connect and configure it. 

By default:
SSID: WIFI_ESP
Password: 12345678
IP: 192.168.4.1

To access the wifi configuration page:
IP-ADDRESS/setupwifi/

To access the ElegantOTA page:
IP-ADDRESS/update/
