int venstre = A1;
int hojre = A0;

int motorMedUret = 6;
int motorModUret = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(venstre, INPUT);
  pinMode(hojre, INPUT);
  pinMode(motorMedUret, OUTPUT);
  pinMode(motorModUret, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Venstre: " + String(analogRead(venstre)));
  Serial.println("Højre: " + String(analogRead(hojre)));
  analogWrite(motorModUret, 1023);
  delay(300);
  analogWrite(motorModUret, 0);
  delay(1500);
}
