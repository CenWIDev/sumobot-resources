#pragma once



/*
 * Interface for the TB6612FNG Motor Driver
 */
class MotorDriver {

public:
    enum class MotorId { A, B };

    struct Config {
        int AIN1;
        int AIN2;
        int PWMA;
        int BIN1;
        int BIN2;
        int PWMB;
    };

    MotorDriver(MotorDriver::Config config);

    void Init();
    void SetMotors(int speedA, int speedB);
    void SetMotor(MotorId m, int speed);

private: 
    MotorDriver::Config _config;
};