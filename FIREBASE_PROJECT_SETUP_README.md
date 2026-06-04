# Firebase Project Setup Guide - Complete Step by Step

## Before You Start

- ✅ Google account (Gmail)
- ✅ Internet connection
- ✅ Web browser (Chrome recommended)

---

# PART 1: CREATE FIREBASE PROJECT

## Step 1 — Go to Firebase Console

**What to do:**
1. Open your browser
2. Go to: **https://console.firebase.google.com**
3. Sign in with your **Google account**

**What you'll see:**
- Firebase logo at top left
- "Get started" section
- List of your existing projects (if any)

---

## Step 2 — Create a New Project

**What to do:**
1. Click the **"Create a project"** button (usually blue)
2. A popup appears asking for project details

**What you'll see:**
```
Step 1: Create a project
├── Project name (text field)
├── Next button
└── Terms checkbox
```

---

## Step 3 — Enter Project Name

**What to do:**
1. Click the **Project name** field
2. Type: `FirebaseEspRelay` (or any name you like)
3. Click **"Next"** button

**What you'll see:**
```
Project name: FirebaseEspRelay
[✓] I accept the Firebase terms
[Next >]
```

---

## Step 4 — Choose Google Analytics

**What to do:**
1. You'll see: **"Enable Google Analytics for this project?"**
2. Click the **toggle to OFF** (disable it)
3. Click **"Create project"** button

**What you'll see:**
```
Enable Google Analytics for this project?
☐ [OFF]

[Create project]
```

---

## Step 5 — Wait for Project Creation

**What to do:**
- Wait for Firebase to create your project (takes 30-60 seconds)
- You'll see: "Your new Firebase project is ready"

**What you'll see:**
```
✓ Your new Firebase project is ready
Getting started: Add Firebase to your app
├── iOS
├── Android
├── Web
└── C++
```

---

# PART 2: CREATE REALTIME DATABASE

## Step 6 — Go to Realtime Database

**What to do:**
1. On the left sidebar, click **"Build"** (you may need to expand it)
2. Click **"Realtime Database"**

**What you'll see:**
```
Left Sidebar:
├── Project Overview
├── Build
│   ├── Realtime Database ← Click here
│   ├── Firestore Database
│   ├── Storage
│   └── Hosting
```

---

## Step 7 — Create Database

**What to do:**
1. Click **"Create Database"** button (blue)
2. A popup appears asking about location and security

**What you'll see:**
```
Welcome to Realtime Database
[Create Database]
```

---

## Step 8 — Choose Location

**What to do:**
1. Choose region (closest to your location):
   - `us-central1` (USA)
   - `europe-west1` (Europe)
   - `asia-southeast1` (Asia)
2. Click **"Next"** button

**What you'll see:**
```
Choose a location:
├── us-central1 (USA)
├── europe-west1 (Europe)
├── asia-southeast1 (Asia)
└── [more options]

[Next]
```

---

## Step 9 — Choose Security Rules

**What to do:**
1. Select **"Start in test mode"** (the second option)
2. Read the warning about 30-day limit
3. Click **"Enable"** button

**What you'll see:**
```
Security rules:

(•) Start in locked mode
    Your data is private by default

( ) Start in test mode  ← Click this one
    Your data is open by default
    ⚠ Must update rules within 30 days

[Enable]
```

---

## Step 10 — Database Created

**What to do:**
- Wait for database to be created (30 seconds)
- You'll see your database URL at the top

**What you'll see:**
```
Realtime Database
├── URL: https://firebaseesprely-default-rtdb.firebaseio.com
├── Data tab
├── Rules tab
└── Backups tab

(Currently empty - showing null)
```

---

# PART 3: CREATE /relays STRUCTURE

## Step 11 — Add Relay Data

**What to do:**
1. Make sure you're on the **"Data"** tab
2. Click the **"+"** icon next to the URL

**What you'll see:**
```
https://your-project-default-rtdb.firebaseio.com
[+] Add data icon
```

---

## Step 12 — Create "relays" Folder

**What to do:**
1. A popup appears with **Key** and **Value** fields
2. In **Key** field, type: `relays`
3. Leave **Value** empty (it will be an object)
4. Click **"Add"** button

**What you'll see:**
```
┌─────────────────────┐
│ Key     │ Value     │
│ relays  │           │
└─────────────────────┘
[Cancel] [Add]
```

---

## Step 13 — Add Individual Relays

**What to do:**
1. Click **"+"** icon next to the new `relays` folder
2. Repeat 8 times for r1 through r8:
   - **Key:** `r1` (change number each time)
   - **Value:** `0`
   - Click **Add**

**What you'll see after Step 13:**
```
relays
├── r1: 0
├── r2: 0
├── r3: 0
├── r4: 0
├── r5: 0
├── r6: 0
├── r7: 0
└── r8: 0
```

---

# PART 4: GET YOUR CREDENTIALS

## Step 14 — Go to Project Settings

**What to do:**
1. Look at the top right of Firebase Console
2. Click the **gear icon (⚙️)** 
3. Click **"Project Settings"**

**What you'll see:**
```
Top Right Corner:
├── Bell icon (notifications)
├── ⚙️ Gear icon ← Click here
└── Profile icon

Menu:
├── Project settings
├── Project settings in new tab
└── [other options]
```

---

## Step 15 — Find General Tab

**What to do:**
1. You should be on **"General"** tab automatically
2. Scroll down to see **"Your apps"** section
3. Look for a section that says **"Web API Key"** or similar

**What you'll see:**
```
Project settings > General
├── Your project
│   ├── Project name
│   ├── Project ID
│   └── Project number
└── Your apps
    ├── No apps in your project (if first time)
```

---

## Step 16 — Register Web App

**What to do:**
1. Click **"<>"** (web icon) to add a web app
2. OR click **"Add app"** button and select **"Web"**
3. Enter app nickname: `ESP32 Relay Control` (any name)
4. **Check** the "Also set up Firebase Hosting" checkbox
5. Click **"Register app"** button

**What you'll see:**
```
Add Firebase to your web app
├── App nickname: [text field]
├── ☑ Also set up Firebase Hosting
└── [Register app]
```

---

## Step 17 — Copy Your Credentials

**What to do:**
1. After registration, you'll see your Firebase config
2. **Copy these values:**
   ```
   apiKey: "YOUR_API_KEY"
   authDomain: "your-project.firebaseapp.com"
   databaseURL: "https://your-project-default-rtdb.firebaseio.com"
   projectId: "your-project"
   storageBucket: "your-project.firebasestorage.app"
   messagingSenderId: "YOUR_SENDER_ID"
   appId: "1:000000000000:web:xxxxxxxxxxxxxxxx"
   measurementId: "G-XXXXXXXXXX"
   ```

**What you'll see:**
```
const firebaseConfig = {
  apiKey: "...",
  authDomain: "...",
  databaseURL: "...",
  projectId: "...",
  storageBucket: "...",
  messagingSenderId: "...",
  appId: "...",
  measurementId: "..."
};
```

**⚠️ IMPORTANT:** Save these values in a text file!

---

# PART 5: SET SECURITY RULES

## Step 18 — Go to Rules Tab

**What to do:**
1. Go back to **Realtime Database**
2. Click the **"Rules"** tab (next to "Data" tab)

**What you'll see:**
```
Realtime Database > Rules

{
  "rules": {
    ".read": false,
    ".write": false
  }
}
```

---

## Step 19 — Update Rules

**What to do:**
1. Delete the current rules
2. Paste this:
   ```json
   {
     "rules": {
       "relays": {
         ".read": true,
         ".write": true
       },
       ".read": false,
       ".write": false
     }
   }
   ```
3. Click **"Publish"** button (blue)

**What you'll see:**
```
{
  "rules": {
    "relays": {
      ".read": true,
      ".write": true
    },
    ".read": false,
    ".write": false
  }
}

[Publish]
```

---

## Step 20 — Rules Published

**What to do:**
- Wait a few seconds
- You'll see: "✓ Rules compiled successfully"

**What you'll see:**
```
✓ Rules compiled successfully
✓ Rules published
```

---

# SUMMARY

## Your Firebase Project is Complete! ✅

You now have:
1. ✅ Firebase Project: `FirebaseEspRelay`
2. ✅ Realtime Database: `https://your-project-default-rtdb.firebaseio.com`
3. ✅ `/relays` structure with r1-r8 (all set to 0)
4. ✅ Security Rules configured
5. ✅ Firebase Credentials saved

---

## What Each Tab Does

| Tab | Purpose |
|-----|---------|
| **Data** | View and edit your database structure |
| **Rules** | Control who can read/write (security) |
| **Backups** | Automatic backups of your data |
| **Usag** | Monitor how much data you're using |

---

## Quick Reference

**Database URL:**
```
https://your-project-default-rtdb.firebaseio.com
```

**Your Project ID:**
```
your-project
```

**Your API Key:**
```
Found in Project Settings > Your apps
```

---

## Troubleshooting

### Can't find Realtime Database?
- Make sure you're in the right project
- Click "Build" on left sidebar
- Scroll down to find "Realtime Database"

### Database is empty?
- Click Data tab
- Make sure you added r1-r8 values
- Check that you see: `relays → r1: 0`

### Rules won't publish?
- Make sure JSON is valid (no syntax errors)
- Check that `relays` section exists
- Click "Publish" button again

### Can't find credentials?
- Go to Project Settings (gear icon)
- Scroll to "Your apps" section
- Click on your web app
- Look for "Firebase SDK snippet"

---

## Next Steps

1. ✅ Firebase project created
2. ✅ Database initialized
3. ✅ Credentials saved
4. → Deploy web app to Firebase Hosting
5. → Upload Arduino code to ESP32
6. → Test everything!

---

**Congratulations!** Your Firebase project is ready! 🎉
