// Definerer input pins til LDR sensorer
#define venstreSens A0
#define hojreSens A1
#define opSens A2
#define nedSens A3

// Definerer motor output pins til aktivering
#define motorHojre 6
#define motorVenstre 5
#define motorOp 10
#define motorNed 11


void setup() {
  // Sensor pin setup
  pinMode(venstreSens, INPUT);
  pinMode(hojreSens, INPUT);
  pinMode(opSens, INPUT);
  pinMode(nedSens, INPUT);

  // Motor pin setup
  pinMode(motorHojre, OUTPUT);
  pinMode(motorVenstre, OUTPUT);
  pinMode(motorOp, OUTPUT);
  pinMode(motorNed, OUTPUT);

  // Starter seriel kommunikation på serielport 9600
  Serial.begin(9600);
}

void loop() {
  //input fra LDR
  int vVal = analogRead(venstreSens);
  int hVal = analogRead(hojreSens);
  int opVal = analogRead(opSens);
  int nedVal = analogRead(nedSens);

  //forskel på LDR
  int dLys_vandret = vVal - hVal;
  int dLys_lodret = opVal - nedVal;

/*   Serial.println("Diff: " + String(dLys_vandret));
  Serial.println("Venstre: " + String(vVal));
  Serial.println("Hojre: " + String(hVal)); */
  
  // Vandret korrektion
  int powerOut = map(absolut(dLys_vandret), 0, 200, 0, 512);

  if (vVal > hVal) {
    analogWrite(motorVenstre, powerOut);
    digitalWrite(motorHojre, LOW);
    Serial.println("Drejer mod uret: LDR venstre = " + String(vVal));
  } else if (hVal > vVal) {
    analogWrite(motorHojre, powerOut);
    digitalWrite(motorVenstre, LOW);
    Serial.println("Drejer med uret: LDR hojre = " + String(hVal));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  Serial.println("Power output = " + String(powerOut));

  // Vinkel korrektion
  powerOut =  map(absolut(dLys_lodret), 0, 200, 0, 1023);

  if (opVal > nedVal) {
    analogWrite(motorOp, powerOut);
    digitalWrite(motorNed, LOW);
    Serial.println("Forstørrer linse vinkel: LDR op = " + String(opVal));
  } else if (nedVal > opVal) {
    analogWrite(motorNed, powerOut);
    digitalWrite(motorOp, LOW);
    Serial.println("Mindsker linse vinkel: LDR ned = " + String(nedVal));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  
  Serial.println("Power output = " + String(powerOut));
  
  delay(10);
}



//tager absolut værdigen af et tal
int absolut(int val){
  if(val < 0){
    val *= -1;
  }
  return val;
}
