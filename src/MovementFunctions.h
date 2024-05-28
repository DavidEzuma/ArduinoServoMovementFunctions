#ifndef MOVEMENTFUNCTIONS_H
#define MOVEMENTFUNCTIONS_H

#include <Arduino.h>
#include <Servo.h>

// Function declarations

class MovementFunctions
{
    public:
        void MoveInTime(Servo mover, int duration, int initialPosition, int finalPosition);
        void InstructionRecieved(Servo serv);
};

#endif // MOVEMENTFUNCTIONS_H