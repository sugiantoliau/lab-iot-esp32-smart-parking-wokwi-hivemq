
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

// --- Konfigurasi WiFi & MQTT ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// --- Konfigurasi Pin ---
const int PIN_TRIG = 5;
const int PIN_ECHO = 18;
const int PIN_PIR  = 19;
const int PIN_LDR  = 34;
const int PIN_LED  = 12;
const int PIN_SERVO = 13;

Servo gateServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel Kontrol
bool isGateOpen = false;

void setup_wifi() {
  delay(10);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IOT SMART PARKING SYSTEM");
  delay(500);
  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  lcd.setCursor(0, 1);
  lcd.print("WiFi Connected!");
  delay(1000);
  lcd.clear();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // ID Client unik untuk simulasi
    if (client.connect("ESP32_SmartParking_Unique_ID")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SMART GATE IOT");
  lcd.setCursor(0, 1);
  lcd.print("INITIALIZING...");

  // Inisialisasi Pin
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  
  // Inisialisasi Servo
  gateServo.attach(PIN_SERVO);
  gateServo.write(0); 

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void sendDataToCloud(float dist, int light, String gateStatus) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Membungkus data ke format JSON
  String payload = "{\"distance\":" + String(dist) + 
                   ",\"light\":" + String(light) + 
                   ",\"gate\":\"" + gateStatus + "\"}";
  
  client.publish("wokwi/smartparking/data", payload.c_str());
}

void loop() {
  // 1. Membaca Sensor
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  float distance = pulseIn(PIN_ECHO, HIGH) * 0.034 / 2;
  int lightVal = analogRead(PIN_LDR);
  int motionDetected = digitalRead(PIN_PIR);

  String gateStatusStr = isGateOpen ? "Open" : "Closed";

  // --- LOGIKA UTAMA (Edge Processing) ---

  // Logika 1: Buka Gerbang (Ultrasonic)
  if (distance > 0 && distance < 10 && !isGateOpen) {
    gateServo.write(90);
    isGateOpen = true;
    gateStatusStr = "Open";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GATE: OPENED");
    lcd.setCursor(0, 1);
    lcd.print("WELCOME GUEST");
    delay(1000);
  }

  // Logika 2: Tutup Gerbang (PIR)
  if (isGateOpen && motionDetected == HIGH) {
    delay(2000); // Tunggu mobil masuk sepenuhnya
    gateServo.write(0);
    isGateOpen = false;
    gateStatusStr = "Closed";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GATE: CLOSED");
    lcd.setCursor(0, 1);
    lcd.print("SAFE DRIVE!");
    delay(2000);
    lcd.clear();
  }

  // Logika 3: Kontrol Lampu (LDR)
  if (lightVal > 2500) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }

  // Logika 4: Tampilan Standby LCD
  if (!isGateOpen) {
    lcd.setCursor(0, 0);
    lcd.print("DIST: "); lcd.print(distance); lcd.print("cm   ");
    lcd.setCursor(0, 1);
    lcd.print("LDR: "); lcd.print(lightVal); lcd.print("    ");
  }

  // 2. Monitoring Serial & Cloud
  Serial.print("D: "); Serial.print(distance);
  Serial.print(" | L: "); Serial.println(lightVal);
  
  sendDataToCloud(distance, lightVal, gateStatusStr);
  
  delay(500);
}
