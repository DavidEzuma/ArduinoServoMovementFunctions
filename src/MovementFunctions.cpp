#include "MovementFunctions.h"

void MovementFunctions::MoveInTime(Servo& mover, int duration, int initialPosition, int finalPosition) {
    mover.write(initialPosition);
    delay(300);
    Serial.println(mover.read());

    int startTime = millis();  // Time when the movement started
    int elapsedTime = 0;

    while (elapsedTime <= duration * 1000) {
        int currentTime = millis();  // Get the current time
        elapsedTime = currentTime - startTime;  // Calculate elapsed time

        // Calculate new position based on elapsed time
        int newPosition = map(elapsedTime, 0, duration * 1000, initialPosition, finalPosition);
        newPosition = constrain(newPosition, 0, 180); // Ensure newPosition stays within valid range (0 to 180)

        mover.write(newPosition);
        Serial.println(mover.read());
    }
}

void MovementFunctions::InstructionReceived(Servo& serv) {
    if (Serial.available() > 0) {
        String data = Serial.readString();  // Collect the data
        int numSpaces = 0;
        for (int i = 0; i < data.length(); i++) {
            if (data.charAt(i) == ' ') {
                numSpaces++;
            }
        }

        String words[numSpaces + 1];  // Dynamically allocate memory for the words array
        // Parse the string into words
        int wordIndex = 0;
        int startIndex = 0;
        for (int i = 0; i < data.length(); i++) {
            if (data.charAt(i) == ' ') {
                words[wordIndex++] = data.substring(startIndex, i);
                startIndex = i + 1;
            }
        }
        words[wordIndex] = data.substring(startIndex);  // Add the last word

        for (int i = 0; i < numSpaces + 1; i++) {
            if (words[i].equals("delay")) {
                delay(words[i + 1].toFloat() * 1000);
                i += 1;  // Move to the next command
            }
            else if (words[i].equals(serv.name())) {  // Check if the servo name matches
                MoveInTime(serv, words[i + 2].toFloat(), serv.read(), words[i + 1].toFloat());
                i += 2;  // Move to the next command
            }
        }
    }
}
