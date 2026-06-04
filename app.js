import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getDatabase, ref, set, onValue, update } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-database.js";

const firebaseConfig = {
  apiKey: "AIzaSyCLR8UodRtGnt1NqFhjHQwA82Lr3Ekwy1k",
  authDomain: "vrealyautomation-93b37.firebaseapp.com",
  databaseURL: "https://vrealyautomation-93b37-default-rtdb.firebaseio.com",
  projectId: "vrealyautomation-93b37",
  storageBucket: "vrealyautomation-93b37.firebasestorage.app",
  messagingSenderId: "956073094857",
  appId: "1:956073094857:web:5f28ab91b3c56f5f9de718",
  measurementId: "G-7SLLD0T8MT"
};

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

const devices = [
  { id: 1, name: "Light", path: "M9 21h6v-1H9v1zm3-19C8.14 2 5 5.14 5 9c0 2.38 1.19 4.47 3 5.74V17c0 .55.45 1 1 1h6c.55 0 1-.45 1-1v-2.26c1.81-1.27 3-3.36 3-5.74 0-3.86-3.14-7-7-7z" },
  { id: 2, name: "Fan", path: "M12 12c0-3 2.5-5.5 5.5-5.5S23 9 23 12H12zm0 0c0 3-2.5 5.5-5.5 5.5S1 15 1 12h11zm0 0c-3 0-5.5-2.5-5.5-5.5S9 1 12 1v11zm0 0c3 0 5.5 2.5 5.5 5.5S15 23 12 23V12z" },
  { id: 3, name: "Hardware", path: "M22.7 19l-9.1-9.1c.9-2.3.4-5-1.5-6.9-2-2-5-2.4-7.4-1.3L9 6 6 9 1.6 4.7C.5 7.1.9 10.1 2.9 12.1c1.9 1.9 4.6 2.4 6.9 1.5l9.1 9.1c.4.4 1 .4 1.4 0l2.3-2.3c.5-.4.5-1.1.1-1.4z" },
  { id: 4, name: "Studio", path: "M20 18c1.1 0 1.99-.9 1.99-2L22 6c0-1.1-.9-2-2-2H4c-1.1 0-2 .9-2 2v10c0 1.1.9 2 2 2H0v2h24v-2h-4zM4 6h16v10H4V6z" },
  { id: 5, name: "Class", path: "M5 4v11h14V4H5zm16 13c0 .55-.45 1-1 1h-2l-2-2h-8l-2 2H4c-.55 0-1-.45-1-1v-1h18v1z" },
  { id: 6, name: "Light 2", path: "M9 21h6v-1H9v1zm3-19C8.14 2 5 5.14 5 9c0 2.38 1.19 4.47 3 5.74V17c0 .55.45 1 1 1h6c.55 0 1-.45 1-1v-2.26c1.81-1.27 3-3.36 3-5.74 0-3.86-3.14-7-7-7z" },
  { id: 7, name: "Printer", path: "M19 8H5c-1.66 0-3 1.34-3 3v6h4v4h12v-4h4v-6c0-1.66-1.34-3-3-3zm-3 11H8v-5h8v5zm3-7c-.55 0-1-.45-1-1s.45-1 1-1 1 .45 1 1-.45 1-1 1zm-1-9H6v4h12V3z" },
  { id: 8, name: "LED", path: "M7 19h10v2H7zM5 3h14c1.1 0 2 .9 2 2v11c0 1.1-.9 2-2 2H5c-1.1 0-2-.9-2-2V5c0-1.1.9-2 2-2z" }
];

const grid = document.getElementById("relayGrid");
const cloudPill = document.getElementById("cloud-pill");
const mainStatus = document.getElementById("main-status");

devices.forEach((d) => {
  const el = document.createElement("div");
  el.className = "relay";
  el.id = `r-${d.id}`;
  el.onclick = () => toggleRelay(d.id);
  el.innerHTML = `
    <span class="relay-num">CH${d.id}</span>
    <svg viewBox="0 0 24 24" aria-hidden="true"><path d="${d.path}"/></svg>
    <span class="label">${d.name}</span>`;
  grid.appendChild(el);
});

onValue(
  ref(database, "relays"),
  (snapshot) => {
    if (snapshot.exists()) {
      cloudPill.classList.add("online");
      mainStatus.innerHTML = 'System: <span class="online">Cloud Online</span>';

      const data = snapshot.val();
      for (let i = 1; i <= 8; i++) {
        const state = data["r" + i] || 0;
        const el = document.getElementById(`r-${i}`);
        if (el) el.classList.toggle("active", state === 1);
      }
    } else {
      cloudPill.classList.remove("online");
      mainStatus.innerHTML = 'System: <span class="pending">Waiting for data...</span>';
    }
  },
  () => {
    cloudPill.classList.remove("online");
    mainStatus.innerHTML = 'System: <span class="error">Connection Error</span>';
  }
);

let bleCharacteristic = null;
let bleConnected = false;

document.getElementById("bleBtn").onclick = async () => {
  if (bleConnected) {
    if (bleCharacteristic && bleCharacteristic.service.device) {
      bleCharacteristic.service.device.gatt.disconnect();
    }
    return;
  }
  
  try {
    const device = await navigator.bluetooth.requestDevice({
      filters: [{ name: "ESP32-Relay" }],
      optionalServices: ["12345678-1234-1234-1234-123456789abc"]
    });
    
    device.addEventListener('gattserverdisconnected', () => {
      bleConnected = false;
      bleCharacteristic = null;
      document.getElementById("bleBtn").classList.remove("connected");
      document.getElementById("bleBtn").innerHTML = `
        <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M17.71 7.71L12 2h-1v7.59L6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 11 14.41V22h1l5.71-5.71-4.3-4.29 4.3-4.29zM13 5.83l1.88 1.88L13 9.59V5.83zm1.88 10.46L13 18.17v-3.76l1.88 1.88z"/></svg>
        <span>Connect BLE</span>`;
    });

    const server = await device.gatt.connect();
    const service = await server.getPrimaryService("12345678-1234-1234-1234-123456789abc");
    bleCharacteristic = await service.getCharacteristic("abcd1234-ab12-ab12-ab12-abcdef123456");
    
    bleConnected = true;
    document.getElementById("bleBtn").classList.add("connected");
    document.getElementById("bleBtn").innerHTML = `
        <svg viewBox="0 0 24 24" aria-hidden="true"><path d="M17.71 7.71L12 2h-1v7.59L6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 11 14.41V22h1l5.71-5.71-4.3-4.29 4.3-4.29zM13 5.83l1.88 1.88L13 9.59V5.83zm1.88 10.46L13 18.17v-3.76l1.88 1.88z"/></svg>
        <span>BLE Connected</span>`;
        
    await bleCharacteristic.startNotifications();
    bleCharacteristic.addEventListener('characteristicvaluechanged', (e) => {
      const val = new TextDecoder().decode(e.target.value);
      if (val.startsWith("CH") && val.includes("=")) {
        const id = val.substring(2, val.indexOf("="));
        const state = parseInt(val.substring(val.indexOf("=") + 1));
        const el = document.getElementById(`r-${id}`);
        if (el) {
          if (state === 1) el.classList.add("active");
          else el.classList.remove("active");
        }
      }
    });
    
    await sendBleCommand("STATUS");
  } catch (error) {
    console.error("BLE Error:", error);
  }
};

async function sendBleCommand(cmd) {
  if (!bleConnected || !bleCharacteristic) return false;
  try {
    const data = new TextEncoder().encode(cmd);
    await bleCharacteristic.writeValue(data);
    return true;
  } catch (err) {
    console.error("BLE Send Error:", err);
    return false;
  }
}

function toggleRelay(id) {
  const el = document.getElementById(`r-${id}`);
  const newState = el.classList.contains("active") ? 0 : 1;
  
  if (bleConnected) {
    sendBleCommand(`R${id}=${newState}`);
  } else {
    set(ref(database, `relays/r${id}`), newState).catch(console.error);
  }
}

document.getElementById("killAllBtn").onclick = () => {
  if (bleConnected) {
    sendBleCommand("ALL=0");
  } else {
    const updates = {};
    for (let i = 1; i <= 8; i++) updates[`relays/r${i}`] = 0;
    update(ref(database), updates).catch(console.error);
  }
};

function pad(n) {
  return String(n).padStart(2, "0");
}

function updateClock() {
  const now = new Date();
  document.getElementById("clock").textContent =
    `${pad(now.getHours())}:${pad(now.getMinutes())}:${pad(now.getSeconds())}`;
}

updateClock();
setInterval(updateClock, 1000);

mainStatus.innerHTML = 'System: <span class="pending">Connecting...</span>';
