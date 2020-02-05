//Fill in the values below with the pins that you chose to use

const int POT_PIN = 0;
const int BUTTON_PIN = 3;
const int HOT_PIN = 9;
const int COLD_PIN = 11;
const int DRY_PIN = 12;
const int LOCK_PIN = 13;

enum State {
  Off,
  Hot,
  Medium,
  Cold,
  Dry2,
  Dry7
};

State currentState = Off;

void setup() {
  pinMode(HOT_PIN, OUTPUT);
  pinMode(COLD_PIN, OUTPUT);
  pinMode(DRY_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  nextState(currentState);
}

State nextState(State state){
  switch (currentState){

    case Off:
      digitalWrite(LOCK_PIN, LOW);
      digitalWrite(HOT_PIN, LOW);
      digitalWrite(COLD_PIN, LOW);
      digitalWrite(DRY_PIN, LOW);

      if (digitalRead(BUTTON_PIN) == LOW){
        if (analogRead(POT_PIN) == 1023){
           currentState = Hot;
        }
        else if (analogRead(POT_PIN) == 0){
          currentState = Cold;
        }
        else{
          currentState = Medium;
        }
      }
      break;
      

    case Hot:
     digitalWrite(HOT_PIN, HIGH);
     digitalWrite(LOCK_PIN, HIGH);
     delay (7000);
     if (analogRead(POT_PIN) != 0){
           currentState = Dry7;
        }
        else{
          currentState = Dry2;
        }
      break;
     

    case Medium:
     digitalWrite(HOT_PIN, HIGH);
     digitalWrite(LOCK_PIN, HIGH);
     delay (7000);
     digitalWrite(HOT_PIN, HIGH);
     digitalWrite(COLD_PIN, HIGH);
     delay (7000);
     if (analogRead(POT_PIN) != 0){
           currentState = Dry7;
        }
        else{
          currentState = Dry2;
        }
      break;


    case Cold:
    digitalWrite(COLD_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay (5000);
    if (analogRead(POT_PIN) == 0){
           currentState = Dry2;
        }
        else{
          currentState = Dry7;
        }
      break;

    case Dry2:
    digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay(2000);
    currentState = Off;
    break;

    case Dry7:
     digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, HIGH);
    digitalWrite(LOCK_PIN, HIGH);
    delay(7000);
    currentState = Off;
    break;
  }
}
