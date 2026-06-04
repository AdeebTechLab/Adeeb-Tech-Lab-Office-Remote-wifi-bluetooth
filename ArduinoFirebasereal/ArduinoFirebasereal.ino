#include <WiFi.h>
#include <FirebaseESP32.h>

// ===== UPDATE THESE WITH YOUR WiFi DETAILS =====
#define WIFI_SSID "Adeeb Technology Lab YouTuber"           // Change this to your WiFi name
#define WIFI_PASSWORD "03092333121786"   // Change this to your WiFi password

// ===== Firebase Credentials (from your project) =====
#define FIREBASE_HOST "fir-esprelay-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBExYcRBI24hi3NtoqKNwr72f8PVBet8cQ"

// ===== Relay Pin Configuration =====
const int RELAY_PINS[8] = {23, 22, 21, 19, 18, 13, 12, 2};

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long lastCheck = 0;
const unsigned long CHECK_INTERVAL = 500;

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
  Serial.println("=== Ready ===\n");
}

void loop() {
  if (!Firebase.ready()) {
    delay(100);
    return;
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
      // Active LOW: val=1 means ON (set pin LOW), val=0 means OFF (set pin HIGH)
      digitalWrite(RELAY_PINS[i], val == 1 ? LOW : HIGH);
      Serial.printf("CH%d = %d\n", i + 1, val);
    } else {
      Serial.printf("CH%d - Error: %s\n", i + 1, fbdo.errorReason().c_str());
    }
  }
}