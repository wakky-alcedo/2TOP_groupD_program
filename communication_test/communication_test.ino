int IN1 = 7;   // Pins set up
int IN2 = 8;
int ENA = 9;
int relayPin = 10;

bool Run = 0;  // Status set up

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);  // Baud rate set up
}

void loop() {
  // Continuously check for serial input
  while (Serial.available() > 0) {
    // Read the string from the serial input
    String command = Serial.readString();

    // Check if the command received is "ON"
    if (command == "ON") {
      // Set motor speed using PWM and control motor direction
      analogWrite(ENA, 140);        // Set PWM duty cycle to 140
      digitalWrite(IN1, HIGH);      // Set IN1 to HIGH (motor direction)
      digitalWrite(IN2, LOW);       // Set IN2 to LOW (motor direction)
      delay(2500);                  // Wait for 2.5 seconds

      // Stop the motor
      analogWrite(ENA, 0);          // Set PWM duty cycle to 0 (stop motor)
      digitalWrite(IN1, HIGH);      // Set IN1 to HIGH
      digitalWrite(IN2, HIGH);      // Set IN2 to HIGH (stop motor)
      delay(5000);                  // Wait for 5 seconds

      // Control a relay pin
      digitalWrite(relayPin, HIGH); // Activate relay
      delay(3000);                  // Wait for 3 seconds

      // Deactivate the relay pin
      digitalWrite(relayPin, LOW);  // Deactivate relay
      delay(5000);                  // Wait for 5 seconds

      // Print "Task Completed" to the Serial Monitor
      Serial.println("Task Completed");
    } else {
      // If the command is not "ON", print "Task Failed" to the Serial Monitor
      Serial.println("Task Failed");
    }
  }
}
