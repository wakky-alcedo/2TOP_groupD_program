int IN1[] = {22, 24, 26, 28, 30}; //幫浦
int IN2[] = {32, 34, 36, 38, 40}; //幫浦
int PWM[] = {2, 3, 4, 5, 6}; //幫浦PWM

int valve_control[] = {31, 33, 35, 37, 39}; 


char mode;

void setup() {
  for(int i = 0; i<5; i++){
    pinMode(IN1[i], OUTPUT);
    pinMode(IN2[i], OUTPUT);
    pinMode(PWM[i], OUTPUT);
    pinMode(valve_control[i], OUTPUT);
  }

  Serial.begin(9600);

  delay(1000);
  //Serial.println("成功進入程式");
}

void loop() {
  while(Serial.available() == 0){};
  String str = Serial.readString();
  str.trim();

  if (str == "ON"){
    Serial.println("OPEN vavle");
    Fivepump();
  }

  else if (str == "OFF"){
    Serial.println("CLOSE vavle");
    Stop();
  }
  else if (str == "TT"){
    Serial.println("Control Five Pump");
    Fivepump();
  }
}
