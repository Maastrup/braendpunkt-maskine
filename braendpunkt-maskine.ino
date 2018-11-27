int venstre = A0;
int hojre = A1;

int motorHojre = 6;
int motorVenstre = 5;

int motorOp = 10;
int motorNed = 11;


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

  int dLight = ldrV - ldrH; 

  int powerOut = map(absolut(dLight), 0, 200, 0, 512);
  Serial.println("Diff: " + String(dLight));
  Serial.println("Venstre: " + String(ldrV));
  Serial.println("Hojre: " + String(ldrH));
  
  if (ldrV > ldrH) {
    analogWrite(motorVenstre, powerOut);
    digitalWrite(motorHojre, LOW);
    Serial.println("Drejer mod uret: LDR venstre = " + String(ldrV));
  } else if (ldrH > ldrV) {
    analogWrite(motorHojre, powerOut);
    digitalWrite(motorVenstre, LOW);
    Serial.println("Drejer med uret: LDR hojre = " + String(ldrH));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  
  Serial.println("Power output = " + String(powerOut));
  delay(10);
}

int absolut(int val){
  if(val < 0){
    val *= -1;
  }
  return val;
}
