#include <Stepper.h>

#define STEPS 2048
const int paso = 50;
const int rpm = 10;

Stepper motorZ(STEPS, 8,10,9,11);
Stepper motorX(STEPS, 4,6,5,7);
Stepper motorY(STEPS, 22,24,23,25);

void setup() {
  Serial.begin(115200);
  motorZ.setSpeed(rpm);
  motorX.setSpeed(rpm);
  motorY.setSpeed(rpm);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch(cmd) {
      case 'Q': motorZ.step(paso); break;
      case 'E': motorZ.step(-paso); break;
      case 'A': motorX.step(-paso); break;
      case 'D': motorX.step(paso); break;
      case 'W': motorY.step(paso); break;
      case 'S': motorY.step(-paso); break;
    }
  }
}
