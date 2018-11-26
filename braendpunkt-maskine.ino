int venstre = A1;
int hojre = A0;

int motorHojre = 6;
int motorVenstre = 5;

int motorOp = 10;
int motorNed = 11;

int powerPin = 3;

void setup() {
  // Sensor setup
  pinMode(venstre, INPUT);
  pinMode(hojre, INPUT);

  // Motor pin setup
  pinMode(motorHojre, OUTPUT);
  pinMode(motorVenstre, OUTPUT);
  pinMode(motorOp, OUTPUT);
  pinMode(motorNed, OUTPUT);

  pinMode(powerPin, OUTPUT);

  /*
  digitalWrite(motorOp, LOW);
  digitalWrite(motorNed, LOW);
  digitalWrite(motorOp, LOW);
  digitalWrite(motorNed, LOW);  */
  Serial.begin(9600);
}

void loop() {
  
  int ldrV = analogRead(venstre);
  int ldrH = analogRead(hojre);

  int dLight = ldrV - ldrH; 

  
  if (ldrV > ldrH) {
    analogWrite(motorVenstre, abs(dLight));
    digitalWrite(motorHojre, LOW);
    Serial.println("Drejer mod uret: LDR venstre = " + String(ldrV));
  } else if (ldrH > ldrV) {
    analogWrite(motorHojre, abs(dLight));
    digitalWrite(motorVenstre, LOW);
    Serial.println("Drejer med uret: LDR hojre = " + String(ldrH));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  
  Serial.println("Power output = " + String(0.00488759f * dLight));
  

  delay(500);
  
  digitalWrite(motorVenstre, LOW);
  digitalWrite(motorHojre, LOW);

  delay(3000);

  /*
  Serial.println("Venstre: " + String(analogRead(venstre)));
  Serial.println("Højre: " + String(analogRead(hojre)));
  */
}
