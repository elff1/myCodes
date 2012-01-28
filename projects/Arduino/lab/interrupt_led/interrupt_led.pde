#define LED1 13
#define LED2 14
#define LED_RATE 2000000

void open(void);
void close(void);
void changeMode(void);

int light = 0;
/*
  The light time of the period.
  Mode 0 refers to 0; 1 to 1/3; 2 to 2/3.
  The default mode is mode 1.
*/
int mode = 1;
int preMode = 1;

void setup(){
  int top;
  
  pinMode(LED2, OUTPUT);
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BOARD_BUTTON_PIN, changeMode, RISING);
  
  Timer1.pause();
  Timer1.setPeriod(LED_RATE);
  Timer1.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  Timer1.setChannel2Mode(TIMER_OUTPUTCOMPARE);
  top = Timer1.getOverflow();
  Timer1.setCompare1(0);
  Timer1.setCompare2(top / 3);
  Timer1.attachCompare1Interrupt(open);
  Timer1.attachCompare2Interrupt(close);
  Timer1.refresh();
  Timer1.resume();
}

void loop(){
  int top;
  
  if(mode != preMode){
    Timer1.pause();
    Timer1.setPeriod(LED_RATE);
    Timer1.setChannel1Mode(TIMER_OUTPUTCOMPARE);
    Timer1.setChannel2Mode(TIMER_OUTPUTCOMPARE);
    top = Timer1.getOverflow();
    Timer1.setCompare1(0);
    Timer1.setCompare2(mode * top / 3);
    Timer1.attachCompare1Interrupt(open);
    Timer1.attachCompare2Interrupt(close);
    Timer1.refresh();
    Timer1.resume();
    
    preMode = mode;
  }
  
  digitalWrite(LED2, light);
}

void changeMode(){
  mode = (mode + 1) % 3;
}

void open(){
  light = 1;
}

void close(){
  light = 0;
}
