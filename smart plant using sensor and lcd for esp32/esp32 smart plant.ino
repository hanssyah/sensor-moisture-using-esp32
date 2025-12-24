#define FIREBASE_DISABLE_FIRESTORE
#define FIREBASE_DISABLE_STORAGE
#define FIREBASE_DISABLE_MESSAGING
#define FIREBASE_DISABLE_CLOUD_FUNCTIONS
#include <Firebase_ESP_Client.h>

// api key from firebase
#define API_KEY "1789euiqejhdajknday8e9891"
// url from firebase
#define DATABASE_URL "htpp//:wjaidjiajidaadaiojdajdoia.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

//WIFI & PASSWORD
const char* ssid = "Name wifi";
const char* password = "Password";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin sensor soil moisture (ESP32-C3 ADC)
const int sensorPin = A0;   // atau GPIO0

// =====================SETUP========================

void setup() {
  Serial.begin(115200);
  delay(1000);
 //lcd oled
    // I2C mapping
  Wire.begin(10, 5);  // SDA = 10, SCL = 5

  // OLED start
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED tidak ditemukan!");
    while (true);
  }
    display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Sensor Kelembapan");
  display.println("Siap...");
  display.display();
  delay(1500);
  
 //sensor moiture
   Serial.println("\n=== SENSOR KELEMBAPAN TANAH ===");
  Serial.println("Membaca data setiap 2 detik...");

 //WIFI
  Serial.println("\nTes Koneksi WiFi ESP32-C3...");
  Serial.print("Menghubungkan ke: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;

    if (counter > 20) { // sekitar 10 detik
      Serial.println("\nGagal terhubung ke WiFi!");
      return;
    }
  }
  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  
  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Anonymous sign in
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase signup OK");
  } else {
    Serial.println(config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

// ===================LOOP==========================

void loop() {

  // READ SENSOR 
  int adc = analogRead(sensorPin);

  int kelembapan = map(adc, 4095, 1000, 0, 100);
  kelembapan = constrain(kelembapan, 0, 100);

  String status;
  if (kelembapan < 30)      status = "Kering";
  else if (kelembapan < 70) status = "Lembap";
  else                      status = "Basah";

  // SERIAL 
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.print("% | Status: ");
  Serial.println(status);

  // OLED 
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Kelembapan: ");
  display.print(kelembapan);
  display.println("%");

  display.setCursor(0, 16);
  display.print("Status: ");
  display.println(status);
  display.display();

  // FIREBASE 
  if (Firebase.ready()) {
    Firebase.RTDB.setInt(&fbdo, "/sensor/kelembapan", kelembapan);
    Firebase.RTDB.setString(&fbdo, "/sensor/status", status);
  }

  delay(3000);
}

