const unsigned long REPORT_INTERVAL = 1000;
unsigned long lastReport = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println("Ralsei mood creature: online");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReport >= REPORT_INTERVAL) {
    lastReport = now;

    Serial.print("Alive - uptime: ");
    Serial.print(now / 1000);
    Serial.println(" seconds");
  }
}