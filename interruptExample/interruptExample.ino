#define Led 26
#define Pushbutton 25

void cb(void){
static int state = 0;
if(state == 0) {
  digitalWrite(Led ,HIGH);
  state = 1;
}
else{
  digitalWrite(Led, LOW);
  state = 0;
}

}

void setup() {
  // put your setup code here, to run once:
pinMode(Led, OUTPUT);
pinMode(Pushbutton, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(Pushbutton), cb , FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
delay(5000);
}
