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
  // Vandret motor har gule ledninger på print
  pinMode(motorHojre, OUTPUT);
  pinMode(motorVenstre, OUTPUT);
  // Vinkelmotor har orange ledninger på print
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
  int dLys_vand = vVal - hVal;
  int dLys_lod = opVal - nedVal;
  
  // Vandret korrektion
  Serial.println("!-----Vandret-----!");
  int powerOut = map(absolut(dLys_vand), 0, 200, 512, 1023);

  if (vVal > hVal) {
    // Hvis venstre sensors spændingsfald er højere end højre sensors
    // Drej mod venstre
    analogWrite(motorVenstre, powerOut);
    analogWrite(motorHojre, LOW);
    Serial.println("Drejer mod uret: LDR venstre = " + String(vVal));
  } else if (hVal > vVal) {
    // drej mod højre
    analogWrite(motorHojre, powerOut);
    analogWrite(motorVenstre, LOW);
    Serial.println("Drejer med uret: LDR hojre = " + String(hVal));
  } else {
    Serial.println("Equalized light absorbsion");
  }
  Serial.println("Power output = " + String(powerOut));

  // Vinkel korrektion
  Serial.println("!-----Vinkel-----!");

  if (opVal > nedVal) {
    // Hvis den øverste LDR har størst spændingsfald
    // Så vip op
    analogWrite(motorOp, 1023);
    analogWrite(motorNed, LOW);
    Serial.println("Forstørrer linsens vinkel: LDR op = " + String(opVal));
  } else if (nedVal > opVal) {
    // Vip op, hvis omvendt
    analogWrite(motorNed, 1023);
    analogWrite(motorOp, LOW);
    Serial.println("Mindsker linsens vinkel: LDR ned = " + String(nedVal));
  } else {
    Serial.println("Equalized light absorbsion");
  }
}

void stopMotors(){
  analogWrite(motorNed, LOW);
  analogWrite(motorOp, LOW);
  analogWrite(motorVenstre, LOW);
  analogWrite(motorHojre, LOW);
}

//tager absolut værdien af et tal
int absolut(int val){
  if(val < 0){
    val *= -1;
  }
  return val;
}
