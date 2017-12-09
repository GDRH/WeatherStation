void setup() {
  // Setup serial
  Serial.begin(9600);
  // Set builtin led (13)
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // set on led
  digitalWrite(LED_BUILTIN, HIGH);
  // read analog senzor
  int a0 = analogRead(0);
  // write row value to serial as line
  Serial.println(a0);
  // wait 0.5 seconds to have builtin led visible
  delay(500);
  // set builtin led off
  digitalWrite(LED_BUILTIN, LOW);

  // periodic 2 seconds wait 
  delay(2000);
}
