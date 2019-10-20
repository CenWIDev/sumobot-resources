#include <MotorDriver.h>

MotorDriver::Config config{13, 12, 11, 8, 9, 10};
MotorDriver md(config);


void setup() {
    md.Init();
    md.SetMotors(125, 125);
}

void loop() {
}