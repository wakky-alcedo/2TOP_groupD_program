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
  if (!Run) {                     // If the variable 'Run' is False (0), execute the following code block
    analogWrite(ENA, 110);        // Set the motor speed using PWM with a value of 110
    digitalWrite(IN1, HIGH);      // Set the motor direction to forward
    digitalWrite(IN2, LOW);       // Ensure the motor direction is correct
    delay(3000);                  // Run the motor for 3 seconds

    analogWrite(ENA, 0);          // Stop the motor by setting the speed to 0
    digitalWrite(IN1, HIGH);      // Prepare to change the motor direction
    digitalWrite(IN2, HIGH);      // Prepare to change the motor direction
    delay(5000);                  // Wait for 5 seconds

    digitalWrite(relayPin, HIGH); // Open the relay
    delay(3000);                  // Wait for 3 seconds

    digitalWrite(relayPin, LOW);  // Close the relay
    delay(5000);                  // Wait for 5 seconds

    Run = 1;                      // Set the variable 'Run' to True (1)
  }
}
