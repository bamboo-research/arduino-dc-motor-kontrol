/*
*
* Arduino DC motor hız ve yön kontrolü
* © ahmethakanbesel.com.tr
* 08/05/2017
*
*/

int butonPin = 8;
int potPin = A0; //A0 analog pini pot değişkenine atadık
int potdeger; //Kodlarımız içerisinde kullanacağımız potdeger değişkenini oluşturduk
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int state = HIGH;      
int reading;       
int previous = LOW;
long time = 0;         
long debounce = 200;

void setup()   {
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  Serial.begin(9600);
  pinMode(potPin, INPUT); //pot u giriş olarak ayarladık
  pinMode(butonPin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  reading = digitalRead(butonPin);
  potdeger = analogRead(potPin);
  Serial.println(potdeger);
  int hiz = map(potdeger, 0, 1023, 0, 255);
  boolean ters = digitalRead(butonPin);
  motorCalistir(hiz, ters);
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;
    time = millis();
  }
  if (state == 1) {
  } else {
    digitalWrite(ters, state);
  }
  previous = reading;
  delay(5);
}

void motorCalistir(int hiz, boolean ters)
{
  analogWrite(enablePin, hiz);
  digitalWrite(in1Pin, ! ters);
  digitalWrite(in2Pin, ters);
}

