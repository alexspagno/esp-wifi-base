// Access Point credential
const char* APSSID = "WIFI_ESP";
const char* APPASS = "12345678";
const IPAddress APIP = IPAddress(192,168,4,1);

// WIFI variable
String newSSID;
String newPASS;

bool flagConnectedWIFI = false;
bool flagWaitConnectionWIFI;
bool flagNewWIFIcredential = false;
bool FLAGscanWIFI = false;

unsigned long timerReconnectionWIFI;

const int maxNetworks = 50; // Numero massimo di reti WiFi da scansionare
String ssidArray[maxNetworks];
int rssiArray[maxNetworks];
String encryptionModeArray[maxNetworks];
int numNetworks = 0;
