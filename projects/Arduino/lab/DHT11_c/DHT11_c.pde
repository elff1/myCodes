int dataIn = 10;
int one = 70;
int countDelay = 1;
int initialDelay = 30;
int loopDelay = 1000;
int MaxCount = 1000;

void initialDHT();
byte getBit();
byte getByte();

void setup(){
  delay(4000);
  pinMode(dataIn, INPUT);
}

void loop(){
  byte num;
  double humi;
  double temp;
  if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS()))
    SerialUSB.println("Begin");
  initialDHT();
  num = getByte();
  humi = num;
  
  getByte();
  num = getByte();
  temp = num;
  
  getByte();
  getByte();
  getByte();    
  
  if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS())){
    SerialUSB.print("Humi:\t");
    SerialUSB.print(humi);
    SerialUSB.print("\tTemp:\t");
    SerialUSB.println(temp);
  }
  
  delay(loopDelay);
  if(SerialUSB.isConnected() && (SerialUSB.getDTR() || SerialUSB.getRTS())){
    SerialUSB.println("\nNext");
  }
}

void initialDHT(){
  pinMode(dataIn, OUTPUT);
  digitalWrite(dataIn, HIGH);
  delay(initialDelay);
  digitalWrite(dataIn, LOW);
  delay(initialDelay);
  digitalWrite(dataIn, HIGH);
  delay(initialDelay);
  pinMode(dataIn, INPUT);
  getBit();
}

byte getBit(){
  int val;
  int count;
  
  while(1){
    val = digitalRead(dataIn);
    if(val)
      break;
  }
  
  count = 0;
  while(val){
    count++;
//    delay(countDelay);
    val = digitalRead(dataIn);
    if(count > MaxCount){
      SerialUSB.println("Count overflow!");
      break;
    }
  }
  
  if(count < one)
    return 0;
  else
    return 1;
}

byte getByte(){
  int i;
  byte num = 0;
  
  for(i = 7; i >= 0; i--){
    if(getBit())
      bitSet(num, i);
  }
  
  return num;
}
