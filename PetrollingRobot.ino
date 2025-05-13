#define BLYNK_TEMPLATE_ID "TMPL3cBBuF_we"
#define BLYNK_TEMPLATE_NAME "Patrolling Robot"
#define BLYNK_AUTH_TOKEN "zJe2M77ODfkQTkwyVpDa-gaPElQnRRKj"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPS++.h>

// Define pins
#define IR_SENSOR_PIN  15        // IR Sensor (object detection)
#define BUZZER_PIN     4        // Buzzer
#define SOUND_SENSOR_PIN  18     // Sound sensor
#define LDR_PIN        34        // LDR sensor (light detection)
#define LED_PIN  5
int fw1=25;
int bw1=26;
int fw2=32;
int bw2=33;

// GPS setup
HardwareSerial mySerial(1);
TinyGPSPlus gps;

// Blynk setup
char auth[] = "zJe2M77ODfkQTkwyVpDa-gaPElQnRRKj"; 
 
// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "kpi";
char pass[] = "12345678";

void setup() {
  // Serial monitor for debugging
 Serial.begin(115200);
 mySerial.begin(9600, SERIAL_8N1, 16, 17);  // GPS communication
   WiFi.begin(ssid, pass);
   
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  



  // Pin setup
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN,OUTPUT);
 pinMode(fw1,OUTPUT);
pinMode(bw1,OUTPUT);
pinMode(fw2,OUTPUT);
pinMode(bw2,OUTPUT);

}

void loop() {
  // Blynk loop
  Blynk.run();

  // Read IR sensor for object detection
  int irState = digitalRead(IR_SENSOR_PIN);
  if (irState == LOW) {   // Object detected
    digitalWrite(BUZZER_PIN, HIGH);
    Blynk.virtualWrite(V4, "Object Detected");  // Update Object Detection status
  } else {                  // No object detected
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.virtualWrite(V4, "No Object Detected");  // Update Object Detection status
  }

  // Read sound sensor and update Blynk
  int soundState = digitalRead(SOUND_SENSOR_PIN);
  if (soundState == LOW) {
    Blynk.virtualWrite(V7, "Sound Detected");  // Send sound detection state to Blynk
  } else {
    Blynk.virtualWrite(V7, "No Sound Detected");  // Send sound detection state to Blynk
  }

  // Read LDR value and control LED (turn on if it's dark)
  int ldrValue = analogRead(LDR_PIN);
  Blynk.virtualWrite(V6, ldrValue);    // Send LDR value to Blynk
  if (ldrValue > 500) {                // Low light condition
    digitalWrite(LED_PIN, HIGH);   // Turn on LED
    Blynk.virtualWrite(V5, "Night");   // Update Day/Night status
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn off LED
    Blynk.virtualWrite(V5, "Day");     // Update Day/Night status
  }

  // GPS reading and sending data to Blynk
  while (mySerial.available() > 0) {
    gps.encode(mySerial.read());
    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
       String location = String(latitude, 6) + ", " + String(longitude, 6);
      Blynk.virtualWrite(V8, location);  // Send GPS data to Blynk as a string
    }
  }
}

BLYNK_WRITE(V0)
{
  int pinstate1=param.asInt();
  if(pinstate1==1)
  {
    digitalWrite(fw1,HIGH);
    digitalWrite(fw2,HIGH);
    digitalWrite(bw1,LOW);
  digitalWrite(bw2,LOW);
  }
  else
   
 {
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,LOW);
  digitalWrite(bw2,LOW);
  }
}

 BLYNK_WRITE(V1)
{
  int pinstate2=param.asInt();
  if(pinstate2==1)
  {
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,HIGH);
  digitalWrite(bw2,HIGH);
  }
  else
  { 
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,LOW);
    digitalWrite(bw2,LOW);
  }
}

 BLYNK_WRITE(V2)
{
  int pinstate3=param.asInt();
  if(pinstate3==1)
  {
    digitalWrite(fw1,HIGH);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,LOW);
  digitalWrite(bw2,HIGH);
  }
  else
  { 
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,LOW);
    digitalWrite(bw2,LOW);
  }
}

 
BLYNK_WRITE(V3)
{
  int pinstate9=param.asInt();
  if(pinstate9==1)
  {
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,HIGH);
    digitalWrite(bw1,HIGH);
  digitalWrite(bw2,LOW);
  }
  else
   
 {
    digitalWrite(fw1,LOW);
    digitalWrite(fw2,LOW);
    digitalWrite(bw1,LOW);
  digitalWrite(bw2,LOW);
  }
}
