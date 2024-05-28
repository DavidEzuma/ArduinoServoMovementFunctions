#include "MovementFunctions.h"

void MovementFunctions::MoveInTime(Servo &mover, float duration, int initialPosition, int finalPosition){
  mover.write(initialPosition);
  delay(300);
  int startTime;  // Time when the movement started
  int currentTime;  //Imedaite time to be measured during movement
  startTime = millis();  // Record the start time
  int elapsedTime =0;

  while(elapsedTime <= duration * 1000){
    currentTime = millis();  // Get the current time
    elapsedTime = currentTime - startTime;  // Calculate elapsed time

  /* The new position is a mapping of the inital to final position relative to the full duration
   based on what the elasped time is so far - it is the percentage closer to the final position that
   is equal to the percentage the elasped time is closer to the full duration
   I FEEL MASSIVE EINSTIEN BRAIN RN ඞ*/
  int newPosition = map(elapsedTime, 0, duration * 1000, initialPosition, finalPosition);
  
  //newPosition = constrain(newPosition, 0, 180); // Ensure newPosition stays within the valid range (0 to 180)
  mover.write(newPosition);
  //Serial.print(mover.read()+" ");
  }
}

void MovementFunctions::InstructionReceived(Servo* servs, int num){
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
    for(int i = 0; i < numSpaces+1; i++){
      if(words[i].equals("delay") && i+2<numSpaces + 1){
        delay(words[i+1].toFloat()*1000);
        //Serial.println("delaying");
        i+=2;
      }

      for(int j = 0; j < num; j++){
        if(String(servs[j].name()).equals(words[i]) && i+3<numSpaces + 1){
          MoveInTime(servs[j], words[i+2].toFloat(), servs[j].read(), words[i+1].toFloat());
          i+=3;
          //Serial.println("Moving");
          break;
          }
        }
    }
  }
}