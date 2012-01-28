#define LED 13

void change(void);

int light = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BOARD_BUTTON_PIN, INPUT);
  
  attachInterrupt(BOARD_BUTTON_PIN, change, RISING);
}

void loop(){
}

void change(){
  light = ~light;
  digitalWrite(LED, light);
  delay(3000);
}
