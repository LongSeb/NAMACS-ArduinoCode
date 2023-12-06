#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

// Define All Pins
int enA = 9;
int in1 = 7;
int in2 = 6;

// Bluetooth TX -> Arduino D2
const int BLUETOOTH_TX = 2;
// Bluetooth RX -> Arduino D3
const int BLUETOOTH_RX = 3;

int sliderVal, button, sliderId;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth);  // pass reference of bluetooth object to ArduinoBlue constructor.

// Setup code runs once after program starts.
void setup() {
  // Start serial monitor at 9600 bps.
  Serial.begin(9600);

  // Start bluetooth serial at 9600 bps.
  bluetooth.begin(9600);

  // delay just in case bluetooth module needs time to "get ready".
  delay(100);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.println("setup complete");
}

void loop() {
  // ID of the button pressed pressed.
  button = phone.getButton();

  // ID of the slider moved.
  sliderId = phone.getSliderId();

  // Slider value goes from 0 to 100.
  sliderVal = phone.getSliderVal();

  // Autotest
  // When this button is pressed, the motor will spin to max RPM
  // remain at max RPM for 40 sec., then spin the other direction
  // at max RPM for 40 sec., and then stop spinning
  // ENSURE ALL SLIDERS ARE SET TO ZERO PRIOR TO PRESSING
  if (button != -1 && button == 1) {
    Serial.print("Button: ");
    Serial.println(button);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255);
    delay(40000);

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 255);
    delay(40000);

    analogWrite(enA, 0);
  }

  // Killswitch
  if (button != -1 && button == 2) {
    Serial.print("Button: ");
    Serial.println(button);

    analogWrite(enA, 0);  // cuts power to motor
    delay(5000);          // delay for safety
  }

  // Displays slider data when slider moves
  if (sliderId != -1) {
    Serial.print("Slider ID: ");
    Serial.print(sliderId);
    Serial.print("\tValue: ");
    Serial.println(sliderVal);

    // 100% Voltage on Motor
    if (sliderVal == 100) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255);
    }

    // 80% Voltage on Motor
    if (sliderVal == 80) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 204);
    }

    // 60% Voltage on Motor
    if (sliderVal == 60) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 153);
    }

    // 40% Voltage on Motor
    if (sliderVal == 40) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 102);
    }

    // 20% Voltage on Motor
    if (sliderVal == 20) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 51);
    }

    // Cuts Power to Motor
    if (sliderVal == 0) {
      analogWrite(enA, 0);
    }
  }
}