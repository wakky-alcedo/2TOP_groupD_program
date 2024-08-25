int IN1 = 7;   // Pins set up
int IN2 = 8;
int ENA = 9;
int relayPin = 10;

const int ledPin = LED_BUILTIN;  // the number of the LED pin

bool Run = 0;  // Status set up

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);  // Baud rate set up
}

void loop() {
  if (!Run) {                     // If the variable 'Run' is False (0), execute the following code block
    
    // Pomp
    digitalWrite(ledPin, HIGH);
    
    analogWrite(ENA, 128);        // Set the motor speed using PWM with a value of 110 　　127が最小 実際は128以上
    digitalWrite(IN1, HIGH);      // Set the motor direction to forward
    digitalWrite(IN2, LOW);       // Ensure the motor direction is correct
    delay(4000);                  // Run the motor for 3 seconds

    analogWrite(ENA, 0);          // Stop the motor by setting the speed to 0
    digitalWrite(IN1, HIGH);      // Prepare to change the motor direction
    digitalWrite(IN2, HIGH);      // Prepare to change the motor direction

    digitalWrite(ledPin, LOW);

    delay(5000);                  // Wait for 5 seconds

    // Valve 
    digitalWrite(ledPin, HIGH);

    digitalWrite(relayPin, HIGH); // Open the relay
    delay(3000);                  // Wait for 3 seconds

    digitalWrite(relayPin, LOW);  // Close the relay

    digitalWrite(ledPin, LOW);

    // delay
    delay(5000);                  // Wait for 5 seconds

    Run = 1;                      // Set the variable 'Run' to True (1)
  }
}
