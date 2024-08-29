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
    int receive_data = (byte)Serial.read();
    int pomp_speed = 0b11111111 & receive_data;
    bool is_valve_open = (0b100000000 & receive_data) >> 8;

    Serial.println((String)("receive_data:"+receive_data));

    // pomp control
    if(pomp_speed == 0){
      // Stop the motor
      analogWrite(ENA, 0);          // Set PWM duty cycle to 0 (stop motor)
      digitalWrite(IN1, HIGH);      // Set IN1 to HIGH
      digitalWrite(IN2, HIGH);      // Set IN2 to HIGH (stop motor)
    }else{
      // Set motor speed using PWM and control motor direction
      analogWrite(ENA, pomp_speed);        // Set PWM duty cycle to 140
      digitalWrite(IN1, HIGH);      // Set IN1 to HIGH (motor direction)
      digitalWrite(IN2, LOW);       // Set IN2 to LOW (motor direction)
    }

    // valve control
    digitalWrite(relayPin, is_valve_open);
  }
}
