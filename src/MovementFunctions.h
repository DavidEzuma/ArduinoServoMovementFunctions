#ifndef MOVEMENTFUNCTIONS_H
#define MOVEMENTFUNCTIONS_H

#include <Arduino.h>
#include <Servo.h>

// Function declarations

class MovementFunctions
{
    public:
        void MoveInTime(Servo &mover, float duration, int initialPosition, int finalPosition);
        void InstructionReceived(Servo* servs, int num);
};

#endif // MOVEMENTFUNCTIONS_H