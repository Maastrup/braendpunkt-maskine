int venstre = A1;
int hojre = A0;

int motorHojre = 8;
int motorVenstre = 7;

int motorOp = 12;
int motorNed = 13;

void setup() {
  // Sensor setup
  pinMode(venstre, INPUT);
  pinMode(hojre, INPUT);

  // Motor pin setup
  pinMode(motorHojre, OUTPUT);
  pinMode(motorVenstre, OUTPUT);
  pinMode(motorOp, OUTPUT);
  pinMode(motorNed, OUTPUT);

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

  
  if (ldrV > ldrH) {
    digitalWrite(motorVenstre, HIGH);
    digitalWrite(motorHojre, LOW);
    Serial.println("Drejer mod uret: LDR venstre = " + String(ldrV));
  } else if (ldrH > ldrV) {
    digitalWrite(motorHojre, HIGH);
    digitalWrite(motorVenstre, LOW);
    Serial.println("Drejer med uret: LDR hojre = " + String(ldrH));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  

  delay(500);
  
  digitalWrite(motorVenstre, LOW);
  digitalWrite(motorHojre, LOW);

  delay(3000);

  /*
  Serial.println("Venstre: " + String(analogRead(venstre)));
  Serial.println("Højre: " + String(analogRead(hojre)));
  */
}
