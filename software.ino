#define SENSOR1 A0
#define SENSOR2 A1
#define BUTTON1 11
#define BUTTON2 13
#define LASER1 9
#define LASER2 10
#define BUZZER 8

int resistance = 0;
bool btn = true;
bool btnPrev = true;
bool enabled = true;
int laserPin = LASER1;
int sensorPin = SENSOR1;
int btnPin = BUTTON1;
int prevBtnPin = BUTTON2;


void setup() {
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(LASER1, OUTPUT);
  pinMode(LASER2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  btnPrev = btn;
  btn = digitalRead(btnPin);
  if (btnPrev == false && btn == true) {
    digitalWrite(laserPin, LOW);
    if (btnPin == BUTTON1) {
      prevBtnPin = BUTTON1;
      laserPin = LASER2;
      sensorPin = SENSOR2;
      btnPin = BUTTON2;
    } else {
      prevBtnPin = BUTTON2;
      laserPin = LASER1;
      sensorPin = SENSOR1;
      btnPin = BUTTON1;
    }
    digitalWrite(laserPin, HIGH);
    delay(100);
    if (!digitalRead(prevBtnPin)) {
      if (!enabled) {
        enabled = true;
      } else {
        enabled = false;
      }
    } 
  }
  resistance = map(analogRead(sensorPin), 0, 1023, 0, 100);
  Serial.println(resistance);
  if (resistance <= 40 && enabled) {
    tone(BUZZER, 1000, 10);
  }
  digitalWrite(laserPin, HIGH);
}
