const int lowerButton = 5, higherButton = 6;
const int piezo = 4;
const int correctLight = 8, incorrectLight = 7;

int isPosOrNeg() {

  if(random(-5, 5) > 0) {
    return 1;
  }
  else
    return -1;
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(lowerButton, INPUT);
  pinMode(higherButton, INPUT);

  pinMode(piezo, OUTPUT);
  pinMode(correctLight, OUTPUT);
  pinMode(incorrectLight, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //-1 is down, +1 is up
  int changeVector = isPosOrNeg();

  int baseFreq = random(300, 2000);

  int freqChange = random(100, 500) * changeVector;
  
  for(int i = 0; i < 3; i++) {
    tone(piezo, baseFreq);

    delay(500);

    noTone(piezo);

    delay(250);
  }


  tone(piezo, baseFreq + freqChange);
  delay(500);
  noTone(piezo);
  delay(250);

  bool increased = false;
  
  if(changeVector > 0) {
    increased = true;
  }

  // {lower, higher}
  bool input[] = {false, false};

  bool answerGiven = false;

  for(int i = 0; i < 1000; i++) {

    if(digitalRead(lowerButton) == HIGH || digitalRead(higherButton) == HIGH) {

      input[0] = digitalRead(lowerButton);
      input[1] = digitalRead(higherButton);

      answerGiven = true;

      break;
    }

    delay(10);
    
    
  }

  if(answerGiven == false) {

    timeUp();
    return;
  }

  bool correct;

  //correct if answers line up
  if(increased && input[1]) {
    correct = true;
  }
  else if(!increased && input[0]) {
    correct = true;
  }
  else {
    correct = false;
  }

  if(correct) {
    congrats();
  }
  else {
    fail();
  }

}

void congrats() {

  for(int i = 0; i < 3; i++) {
    
  digitalWrite(correctLight, HIGH);

  delay(250);

  digitalWrite(correctLight, LOW);

  delay(250);
  }
}

void fail() {

  digitalWrite(incorrectLight, HIGH);

  delay(2000);

  digitalWrite(incorrectLight, LOW);
}

void timeUp() {

  int freq = 1000;

  tone(piezo, freq);
  
  for(int i = 0; i < 3; i++){

    digitalWrite(correctLight, HIGH);

    delay(250);

    digitalWrite(correctLight, LOW);
    digitalWrite(incorrectLight, HIGH);

    delay(250);

    digitalWrite(incorrectLight, LOW);

    delay(250);

    tone(piezo, freq - 250*(i+1));
  }

  noTone(piezo);

  delay(500);
  
}
