//Main code

//set the IND time for digital clock
int h = 9;
int m = 39;
int s = 0;

//default time IST (00:00)
//For india 00:00
int temp_h = 0;
int temp_m = 0;  //1-15min; 2-30min; 3-45min

//default time UTC (00:00)
//For india 05:30
// int temp_h = 5;
// int temp_m = 2;  //1-15min; 2-30min; 3-45min

void setup() {
  pinMode(8, OUTPUT);        //min_frwd
  pinMode(9, OUTPUT);        //min_com
  pinMode(10, OUTPUT);       //hr_frwd
  pinMode(11, OUTPUT);       //hr_com
  pinMode(12, OUTPUT);       //min_rvs
  pinMode(13, OUTPUT);       //hr_rvs
  pinMode(2, INPUT_PULLUP);  //temp_switch
  pinMode(3, INPUT_PULLUP);  //temp_switch
  pinMode(4, INPUT_PULLUP);  //temp_switch
  pinMode(5, INPUT_PULLUP);  //temp_switch
  pinMode(6, INPUT_PULLUP);  //temp_switch
  pinMode(7, INPUT_PULLUP);  //temp_switch
  Serial.begin(9600);
}

void loop() {
  int s1 = digitalRead(2);
  int s2 = digitalRead(3);
  int s3 = digitalRead(4);
  int s4 = digitalRead(5);
  int s5 = digitalRead(6);
  int s6 = digitalRead(7);
  delay(1000);
  s++;
  check(h, m);
  Serial.print("H:");
  Serial.print(h);
  Serial.print("  M:");
  Serial.println(m);
  Serial.print("S:");
  Serial.println(s);

  if (s == 60) {
    run(8, 9);
    s = 0;
    m++;
  }

  else if (m == 60) {
    for (float i = 0; i <= 5; i++) {
      run(10, 11);
      m = 0;
      h++;
    }
  }

  else if (s1 == LOW) {
    Serial.println("IND");
    time_zone(0, 0);  //1-15min; 2-30min; 3-45min
  }

  else if (s2 == LOW) {
    Serial.println("UTC");
    time_zone(-5, 2);  //1-15min; 2-30min; 3-45min
  }

  else if (s3 == LOW) {
    Serial.println("Los Angeles");
    time_zone(-12, 2);  //1-15min; 2-30min; 3-45min
  }

  else if (s4 == LOW) {
    Serial.println("Tokyo");
    time_zone(3, 2);  //1-15min; 2-30min; 3-45min
  }

  else if (s5 == LOW) {
    Serial.println("Sydney");
    time_zone(4, 2);  //1-15min; 2-30min; 3-45min
  }

  else if (s6 == LOW) {
    Serial.println("London");
    time_zone(-4, 2);  //1-15min; 2-30min; 3-45min
  }
}

//User defined function

float minute_set(float x) {
  Serial.println("Setting Min");
  for (float i = 0; i < 22.5 * abs(x); i++) {
    if (x > 0)
      run(8, 9);
    else if (x < 0)
      run(12, 9);
  }
}

float hour_set(float x) {
  Serial.println("Setting Hour");
  for (float i = 0; i < 7.5 * abs(x); i++) {
    if (x > 0)
      run(10, 11);
    else if (x < 0)
      run(13, 11);
  }
}

int time_zone(int a, int b) {
  hour_set(-temp_h);
  minute_set(-temp_m);
  if (a < 0 && b > 0) {
    hour_set(a - 1);
    minute_set(-b);
  } else {
    hour_set(a);
    minute_set(b);
  }

  if (temp_h < 0 && temp_m > 0)
    temp_m = -temp_m;
  if (a < 0 && b > 0)
    b = -b;
  h += (a + temp_h);
  m += (b * 15) + (temp_m * 15);
  check(h, m);
  temp_h = -a;
  temp_m = -b;
}

void check(int a, int b) {
  if (a >= 24) {
    h = a - 24;
  } else if (a < 0) {
    h = 24 + a;
  } else if (b < 0) {
    m = 60 + b;
    h -= 1;
  } else if (b >= 60) {
    m = b - 60;
    h += 1;
  }
}

void run(int a, int b) {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  delay(5);
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  delay(10);
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  delay(5);
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  delay(10);
//Have the pwm as per your requirements
  // digitalWrite(a, HIGH);
  // digitalWrite(b, LOW);
  // delay(5);
  // digitalWrite(a, HIGH);
  // digitalWrite(b, LOW);
  // delay(10);
  // digitalWrite(a, LOW);
  // digitalWrite(b, HIGH);
  // delay(5);
  // digitalWrite(a, LOW);
  // digitalWrite(b, HIGH);
  // delay(10);
}
