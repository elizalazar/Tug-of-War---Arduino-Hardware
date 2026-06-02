int latchPin = 12;
int clockPin = 13;
int dataPin = 11;
int ledPin = 4;
int buttonApin = 2;
int buttonBpin = 3;
int button = 3;
int end = 0;
byte leds = 0;


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  Serial.begin(9600);
  leds = 0;
}


void loop() {
  bitSet(leds, button);
  updateShiftRegister();
  if (digitalRead(buttonApin) == LOW || digitalRead(buttonBpin) == LOW) {
    if (digitalRead(buttonApin) == LOW) {
      button += 1;
      leds = 1;
      bitSet(leds, button);
      updateShiftRegister();
      Serial.println("A");
      Serial.println(button);
      leds = 0;
      bitSet(leds, button);
      updateShiftRegister();
      while (digitalRead(buttonApin) == LOW || digitalRead(buttonBpin) == LOW)
        ;
      checkEnd();
    }
    if (digitalRead(buttonBpin) == LOW) {
      button -= 1;
      leds = 1;
      bitSet(leds, button);
      updateShiftRegister();
      Serial.println("B");
      Serial.println(button);
      leds = 0;
      bitSet(leds, button);
      updateShiftRegister();
      while (digitalRead(buttonApin) == LOW || digitalRead(buttonBpin) == LOW)
        ;
      checkEnd();
    }
  }
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void checkEnd() {
  if (button == 0 || button == 6) {
    if (button == 0) {
      for (int i = 0; i < 8; i++) {
        leds = 1;
        bitSet(leds, i);
        updateShiftRegister();
        delay(800);
        leds = 0;
        bitSet(leds, i);
        updateShiftRegister();
        end = 1;
      }
    }
    if (button == 6) {
      for (int i = 7; i > 0; i--) {
        leds = 1;
        bitSet(leds, i);
        updateShiftRegister();
        delay(800);
        leds = 0;
        bitSet(leds, i);
        updateShiftRegister();
        end = 1;
      }
    }
  }
  if (end == 1)
    restart();
  else loop();
}

void restart() {
  button = 3;
  end = 0;
  loop();
}