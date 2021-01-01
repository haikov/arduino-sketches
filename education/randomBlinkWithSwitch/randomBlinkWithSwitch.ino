int switchState = 0;
bool wasButtonPressed = false;
bool enabled = false;

void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(2, INPUT);

  randomSeed(analogRead(0));
}

void loop() {
  switchState = digitalRead(2);

  if (switchState == HIGH) {
    wasButtonPressed = true;
  } else {
    if (wasButtonPressed) {
      wasButtonPressed = false;
      enabled = !enabled;
    }
  }

  if (enabled == false) {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else {
    digitalWrite(3, random(0, 2) == 0 ? LOW : HIGH);
    digitalWrite(4, random(0, 2) == 0 ? LOW : HIGH);
    digitalWrite(5, random(0, 2) == 0 ? LOW : HIGH);

    delay(random(20, 100));
  }
}
