# ESP32 Firebase + Bluetooth Relay Control - Complete Setup Guide

## Your Firebase Project Details

**Project Name:** vrealyautomation-93b37  
**Database URL:** https://vrealyautomation-93b37-default-rtdb.firebaseio.com  
**Project ID:** vrealyautomation-93b37  

---

## Files You Have

1. **index.html** - Web app (don't change)
2. **app.js** - JavaScript (has your credentials + Bluetooth support)
3. **style.css** - Styling (don't change)
4. **firebase.json** - Firebase config
5. **ArduinoFirebasereal.ino** - ESP32 code (UPDATE WiFi details, has Bluetooth support)

---

## Step 1: Deploy Web App to Firebase

Open Command Prompt and do these steps:

### Step 1a - Install Firebase CLI (do this once)
```
npm install -g firebase-tools
```

### Step 1b - Create project folder
Create a folder called `esp32-app` on your desktop with:
```
esp32-app/
├── index.html
├── app.js
├── style.css
└── firebase.json
```

### Step 1c - Login to Firebase
```
firebase login
```
(Browser opens - sign in with Google account)

### Step 1d - Initialize project
Open Command Prompt in `esp32-app` folder and run:
```
firebase init hosting
```
When asked:
- Select project: **vrealyautomation-93b37**
- Public directory: **.** (just a dot)
- Single page app: **N**
- Overwrite: **N**

### Step 1e - Deploy
```
firebase deploy
```

Wait for:
```
✔ Deploy complete!
Hosting URL: https://vrealyautomation-93b37.web.app
```

**Your web app is now live at:** `https://vrealyautomation-93b37.web.app`

---

## Step 2: Update Arduino Code with WiFi

Open **ArduinoFirebasereal.ino** in Arduino IDE.

Find these lines at the top:
```cpp
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASSWORD "Your_WiFi_Password"
```

Replace with YOUR WiFi details:
```cpp
#define WIFI_SSID "Oppo"                    // Your WiFi name
#define WIFI_PASSWORD "1234567899"          // Your WiFi password
```

---

## Step 3: Upload Arduino Code

1. Select **Tools → Board → DOIT ESP32 DEVKIT V1**
2. Select **Tools → Port → COM[?]**
3. Click **Upload** (→ button)

Watch Serial Monitor (115200 baud):
```
WiFi Connected!
IP: 192.168.x.x
Firebase Connected!
=== Ready ===
```

---

## Step 4: Test Everything

### Test Web App
1. Open browser
2. Go to: `https://vrealyautomation-93b37.web.app`
3. Should show **"Cloud Online"** (blue indicator)
4. Tap relay buttons - they turn green

### Test Bluetooth (Optional)
1. Make sure ESP32 is powered on and Bluetooth is initialized
2. Click **"Connect BT"** button in web app
3. Select "ESP32_Relay_Control" from Bluetooth devices
4. Bluetooth indicator will turn blue when connected
5. Commands will be sent via both Firebase and Bluetooth

### Test Arduino
1. Open Serial Monitor (115200 baud)
2. You should see relay states updating:
   ```
   CH1 = 0
   CH2 = 0
   ...
   ```

### Test Full Connection
1. Tap button in web app
2. Watch Serial Monitor - should show `CH1 = 1`
3. Open Firebase Console
4. Check `/relays/r1` - should be 1

---

## Troubleshooting

### Web app shows "Connection Error"
- Check internet connection
- Check Firebase credentials in app.js
- Check if `/relays` exists in Firebase database

### Arduino won't connect to WiFi
- Check WiFi SSID and password spelling
- Make sure WiFi is 2.4GHz (not 5GHz)
- Restart ESP32

### Arduino connects but Firebase fails
- Check FIREBASE_HOST is correct
- Check FIREBASE_AUTH API key is correct
- Make sure Database URL is: `fir-esprelay-default-rtdb.firebaseio.com`

### Relays don't respond
- Check relay wiring to GPIO pins
- Check relay module power (5V + GND)
- Test with LEDs first before real relays

---

## Your Credentials (For Reference)

**Firebase Config:**
```javascript
apiKey: "AIzaSyCLR8UodRtGnt1NqFhjHQwA82Lr3Ekwy1k"
authDomain: "vrealyautomation-93b37.firebaseapp.com"
databaseURL: "https://vrealyautomation-93b37-default-rtdb.firebaseio.com"
projectId: "vrealyautomation-93b37"
storageBucket: "vrealyautomation-93b37.firebasestorage.app"
messagingSenderId: "956073094857"
appId: "1:956073094857:web:5f28ab91b3c56f5f9de718"
measurementId: "G-7SLLD0T8MT"
```

**Firebase Host:** `vrealyautomation-93b37-default-rtdb.firebaseio.com`  
**Firebase Auth:** `AIzaSyCLR8UodRtGnt1NqFhjHQwA82Lr3Ekwy1k`

---

## How It Works

```
Your Mobile Phone (WiFi/4G/Bluetooth)
        ↓
   Firebase Cloud OR Bluetooth
        ↓
   ESP32 (Home WiFi)
        ↓
   8 Relay Channels
```

- **Web App** talks to Firebase OR Bluetooth
- **Arduino** reads from Firebase every 500ms AND listens to Bluetooth
- When you tap a button, it updates Firebase AND sends via Bluetooth (if connected)
- Arduino sees the change and controls relays
- Works from **anywhere in the world** via Firebase OR locally via Bluetooth!

---

## Next Steps

1. ✅ Create folder with 4 files
2. ✅ Run `firebase deploy`
3. ✅ Update WiFi in Arduino code
4. ✅ Upload Arduino code
5. ✅ Open web app and test
6. ✅ Done!

Good luck! 🚀
