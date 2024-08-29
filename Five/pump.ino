void Forward(){
  // for(int i = 0; i<4; i++){
  // digitalWrite(IN1[i], HIGH);
  // digitalWrite(IN2[i], LOW);
  // analogWrite(PWM[i], 230);
  // }
  digitalWrite(IN1[0], HIGH);
  digitalWrite(IN2[0], LOW);
  analogWrite(PWM[0], 180); //可調整(進氣量)Adjustable (air inlet)

  digitalWrite(IN1[1], HIGH);
  digitalWrite(IN2[1], LOW);
  analogWrite(PWM[1], 180); //可調整(進氣量)Adjustable (air inlet)

  digitalWrite(IN1[2], HIGH);
  digitalWrite(IN2[2], LOW);
  analogWrite(PWM[2], 180); //可調整(進氣量)Adjustable (air inlet)

  digitalWrite(IN1[3], HIGH);
  digitalWrite(IN2[3], LOW);
  analogWrite(PWM[3], 180); //可調整(進氣量)Adjustable (air inlet)

  digitalWrite(IN1[4], HIGH);
  digitalWrite(IN2[4], LOW);
  analogWrite(PWM[4], 180); //可調整(進氣量)Adjustable (air inlet)
}

void Stop(){
  for(int i = 0; i<5; i++){
  digitalWrite(IN1[i], HIGH);
  digitalWrite(IN2[i], HIGH);
  analogWrite(PWM[i], 0);
}
}

void open_vavle(){
  for(int i = 0; i<5; i++){
    digitalWrite(valve_control[i], HIGH);
}
}

void close_vavle(){
  for(int i = 0; i<5; i++){
    digitalWrite(valve_control[i], LOW);
}
}

void Fivepump(){
  Forward();
  delay(3000);//可調整(總進氣時間)Adjustable (air inlet delay time)
  Stop();
  delay(3000);//可調整(維持時間)Adjustable (time to maintain inflated state)
  open_vavle();
  delay(1500);//可調整(排氣時間)Adjustable (exhaust time)
  close_vavle();
}
