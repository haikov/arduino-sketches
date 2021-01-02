const int TEMPERATURE_SENSOR_PIN = A0;

float baselineTemp = 20.0;

int LED_1 = 2;
int LED_2 = 3;
int LED_3 = 4;

int LED_1_THRESHOLD = 1;
int LED_2_THRESHOLD = 3;
int LED_3_THRESHOLD = 5;

float convertSensorValueToCelsius(int sensorValue) {
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
  // analogRead emits values in a range of 0 -> 2**10
  // which is equal to volrage range of 0 -> 5 Volts.
  float voltage = (sensorValue / 1024.0) * 5.0;

  // https://www.arduino.cc/en/uploads/Main/TemperatureSensor.pdf
  // TMP36 used here, which produces -40 -> +125 C
  // in voltage output range of 100 to 2000 mV
  // TMP36 has offset equal to 0.5V
  float temperature = (voltage - 0.5) * 100;

  return temperature;
}

int getTemperatureSensorValue() {
  return analogRead(TEMPERATURE_SENSOR_PIN);
}

float getCurrentTemperature() {
  return convertSensorValueToCelsius(getTemperatureSensorValue());
}

void changeValueForAllLeds(int newValue) {
  for (int i = 2; i < 5; i++) {
    digitalWrite(i, newValue);
  }
}

void setup() {
  Serial.begin(9600);

  for (int i = 2; i < 5; i++) {
    pinMode(i, OUTPUT);
  }

  changeValueForAllLeds(HIGH);

  delay(2000);

  // Get initial temperature
  baselineTemp = getCurrentTemperature();

  changeValueForAllLeds(LOW);
}

void loop() {
  float temperatureDifference = getCurrentTemperature() - baselineTemp;

  digitalWrite(LED_1, temperatureDifference > LED_1_THRESHOLD ? HIGH : LOW);
  digitalWrite(LED_2, temperatureDifference > LED_2_THRESHOLD ? HIGH : LOW);
  digitalWrite(LED_3, temperatureDifference > LED_3_THRESHOLD ? HIGH : LOW);
}
