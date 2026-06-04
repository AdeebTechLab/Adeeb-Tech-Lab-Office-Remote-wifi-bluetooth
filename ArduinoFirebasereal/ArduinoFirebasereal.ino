#include <WiFi.h>
#include <FirebaseESP32.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// ===== UPDATE THESE WITH YOUR WiFi DETAILS =====
#define WIFI_SSID "Adeeb Technology Lab YouTuber"           // Change this to your WiFi name
#define WIFI_PASSWORD "03092333121786"   // Change this to your WiFi password

// ===== Firebase Credentials (from your project) =====
#define FIREBASE_HOST "fir-esprelay-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBExYcRBI24hi3NtoqKNwr72f8PVBet8cQ"

// ===== Relay Pin Configuration =====
const int RELAY_PINS[8] = {23, 22, 21, 19, 18, 13, 12, 2};

// ===== BLE Configuration =====
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-ab12-ab12-ab12-abcdef123456"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
int relayState[8] = {0, 0, 0, 0, 0, 0, 0, 0};

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long lastCheck = 0;
const unsigned long CHECK_INTERVAL = 500;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("BLE Device Connected");
    }

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("BLE Device Disconnected");
      BLEDevice::startAdvertising();
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue().c_str();

      if (value.length() > 0) {
        Serial.print("BLE Received: ");
        Serial.println(value);
        
        if (value == "STATUS") {
          for (int i = 0; i < 8; i++) {
             String msg = "CH" + String(i+1) + "=" + String(relayState[i]);
             pCharacteristic->setValue(msg.c_str());
             pCharacteristic->notify();
             delay(20);
          }
        }
        else if (value == "ALL=0") {
          for (int i = 0; i < 8; i++) {
            relayState[i] = 0;
            digitalWrite(RELAY_PINS[i], HIGH);
            Firebase.setInt(fbdo, "/relays/r" + String(i + 1), 0);
          }
        }
        else if (value.startsWith("R") && value.indexOf("=") > 0) {
          int eqIdx = value.indexOf("=");
          int rIdx = value.substring(1, eqIdx).toInt() - 1;
          int state = value.substring(eqIdx + 1).toInt();
          
          if (rIdx >= 0 && rIdx < 8) {
            relayState[rIdx] = state;
            digitalWrite(RELAY_PINS[rIdx], state == 1 ? LOW : HIGH);
            Firebase.setInt(fbdo, "/relays/r" + String(rIdx + 1), state);
            
            String msg = "CH" + String(rIdx+1) + "=" + String(state);
            pCharacteristic->setValue(msg.c_str());
            pCharacteristic->notify();
          }
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n=== ESP32 Firebase Relay Control ===");
  
  // Initialize relay pins
  for (int i = 0; i < 8; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], HIGH);  // All OFF initially
  }
  Serial.println("Relay pins initialized - all OFF");
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi Failed! Check credentials.");
    return;
  }
  
  // Firebase Setup
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("Firebase Connected!");
  
  // Initialize BLE
  Serial.println("Initializing BLE...");
  BLEDevice::init("ESP32-Relay");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("BLE Started! Waiting for connections...");
  
  Serial.println("=== Ready ===\n");
}

void loop() {
  if (!Firebase.ready()) {
    delay(100);
    return;
  }
  
  if (deviceConnected) {
    delay(50);
    return; // Skip Firebase polling while BLE is actively controlling
  }
  
  unsigned long now = millis();
  if (now - lastCheck < CHECK_INTERVAL) {
    delay(50);
    return;
  }
  lastCheck = now;
  
  // Read each relay from Firebase
  for (int i = 0; i < 8; i++) {
    String path = "/relays/r" + String(i + 1);
    
    if (Firebase.getInt(fbdo, path)) {
      int val = fbdo.intData();
      relayState[i] = val; // Keep state in sync
      // Active LOW: val=1 means ON (set pin LOW), val=0 means OFF (set pin HIGH)
      digitalWrite(RELAY_PINS[i], val == 1 ? LOW : HIGH);
      Serial.printf("CH%d = %d\n", i + 1, val);
    } else {
      Serial.printf("CH%d - Error: %s\n", i + 1, fbdo.errorReason().c_str());
    }
  }
}