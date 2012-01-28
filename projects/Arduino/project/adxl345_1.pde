// include the LiquidCrystal library
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

// use the SPI 2
HardwareSPI Spi(2);

// the time period of measuring
#define p_ms 10
#define period 0.001

// the data of mg for each LSB
#define LSB 3.90625
// the data of G
#define G 9.793

// ADXL Control Registers
#define ADXLREG_BW_RATE      0x2C
#define ADXLREG_POWER_CTL    0x2D
#define ADXLREG_DATA_FORMAT  0x31
#define ADXLREG_FIFO_CTL     0x38

//ADXL Data Registers
#define ADXLREG_DEVID        0x00
#define ADXLREG_DATAX0       0x32
#define ADXLREG_DATAX1       0x33
#define ADXLREG_DATAY0       0x34
#define ADXLREG_DATAY1       0x35
#define ADXLREG_DATAZ0       0x36
#define ADXLREG_DATAZ1       0x37

#define ADXLREG_VAL1         0x28
#define ADXLREG_VAL2         0x00
#define ADXLREG_VAL3         0x00

//ADXL SPI Read|Write and Multiple Bit Masks
#define RW_MASK 0x80
#define MB_MASK 0x40
#define CB_MASK (RW_MASK|MB_MASK)

//SPI Pins
#define CS  31
#define MISO 33
#define MOSI 34
#define SCLK 32

//Other Pins
#define LED_PIN 14

#define SPI_DEBUG 0 //Set this to 1 for SPI debug to enable
#define AXIS_DEBUG 0 //Set this to 1 for axis debug to enable
#define USB_DEBUG 0 // Set this to 1 for debug through USB

//This buffer will hold values read from the ADXL345 registers.
uint8 values[10];
//These variables will be used to hold the x,y and z axis accelerometer values.
int16 x,y,z;
//deviation of the there axis accelerometers
int16 dx, dy, dz;
// the there axis accelerometers
double ax, ay, az;
// the pre-accelerometers
double px, py, pz;
// the speed of the there axises
double vx, vy, vz;
// the speed, pre-speed and distance
double v, pv, s;

// the sum of data in a period of time
long long sX, sY, sZ;
// the counts of the period of time
int n;

void setup(){
  if(!USB_DEBUG){
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);
  }
  else{
    delay(5000);
  }

  // set the button as the input port
  pinMode(BOARD_BUTTON_PIN, INPUT);
  
  // attach the button pressure to data reset function
  attachInterrupt(BOARD_BUTTON_PIN, clean, RISING);
  
  // setup SPI
  if(USB_DEBUG)
    SerialUSB.println("Setup SPI");
  Spi.begin(SPI_4_5MHZ, MSBFIRST, 3);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  pinMode(MISO, INPUT_PULLDOWN);
  
  // Initialize ADXL345
  if(USB_DEBUG)
    SerialUSB.println("Initialize ADXL345");
  // setup the measure bit
  readADXL(ADXLREG_POWER_CTL, 1);
  writeADXL(ADXLREG_POWER_CTL, ADXLREG_VAL1);
  readADXL(ADXLREG_POWER_CTL, 1);
  if(USB_DEBUG)
    SerialUSB.println();
  // set the measure scale
  readADXL(ADXLREG_DATA_FORMAT, 1);
  writeADXL(ADXLREG_DATA_FORMAT, ADXLREG_VAL2);
  readADXL(ADXLREG_DATA_FORMAT, 1);
  if(USB_DEBUG)
    SerialUSB.println();
  
  readADXL(ADXLREG_FIFO_CTL, 1);
  writeADXL(ADXLREG_FIFO_CTL, ADXLREG_VAL3);
  readADXL(ADXLREG_FIFO_CTL, 1);
  if(USB_DEBUG)
    SerialUSB.println();
  
  if(USB_DEBUG)
    SerialUSB.println("Initialize finished");
  
  delay(500);
  
  if(USB_DEBUG){
    // read data test
    readADXL(ADXLREG_DEVID, 1);
    SerialUSB.print("ID code: ");
    SerialUSB.println(values[0]);
    SerialUSB.println();
  }
  
  // initialize the system data
  if(!USB_DEBUG){
    lcd.print("Initialization.");
  }
  
  dx = dy = dz = 0;
  vx = vy = vz = 0;
  px = py = pz = 0;
  s = 0;
  pv = 0;
  
  sX = sY = sZ = 0;
  n = 0;
}

void loop(){
  // read data from 6 registers
  readADXL(ADXLREG_DATAX0, 6);
  
  // compute the accelerometers
  //The X value is stored in values[0] and values[1].
  x = (int16)((values[1]<<8)|values[0]) - dx;
  ax = x * LSB * G / 1000;
  //The Y value is stored in values[2] and values[3].
  y = (int16)((values[3]<<8)|values[2]) - dy;
  ay = y * LSB * G / 1000;
  //The Z value is stored in values[4] and values[5].
  z = (int16)((values[5]<<8)|values[4]) - dz;
  az = z * LSB * G / 1000;
  
  if(USB_DEBUG && !AXIS_DEBUG && !SPI_DEBUG){
    SerialUSB.print(x);
    SerialUSB.print(',');
    SerialUSB.print(y);
    SerialUSB.print(',');
    SerialUSB.println(z);
  }
    
  n++;
  sX += x;
  sY += y;
  sZ += z;
    
  if(n == 100){
    dx = sX / n;
    dy = sY / n;
    dz = sX / n;
    
    // clean the screen
    lcd.clear();
    // set the cursor to column 0, line 1
    lcd.setCursor(0, 0);
    lcd.print("Spd:");
    lcd.setCursor(0, 1);
    lcd.print("Dis:");
    
    lcd.setCursor(12, 0);
    lcd.print("m/s");
    lcd.setCursor(12, 1);
    lcd.print("m");
  }
  else if(n > 100){
    // compute the speed of each axis
    vx += (ax + px) / 2 * period;
    vy += (ay + py) / 2 * period;
    //vz += (az + pz) / 2 * period;
    
    // store the accelerometers
    px = ax;
    py = ay;
    pz = az;
    
    // compute the total speed
    v = sqrt(vx*vx + vy*vy + vz*vz);
    // compute the distance
    s += (v + pv) /2 * period;
    // store the speed
    pv = v;
    
    if(!USB_DEBUG){
      // print the data
      lcd.setCursor(5, 0);
      lcd.print(v);      
      lcd.setCursor(5, 1);
      lcd.print(s);
    }
    
    //Print the results to the terminal.
    if(USB_DEBUG && AXIS_DEBUG){
      SerialUSB.println(n);
      
      SerialUSB.print(x);
      SerialUSB.print(',');
      SerialUSB.print(y);
      SerialUSB.print(',');
      SerialUSB.println(z);
      
      SerialUSB.print("Avg: ");
      SerialUSB.print(sX / n);
      SerialUSB.print(',');
      SerialUSB.print(sY / n);
      SerialUSB.print(',');
      SerialUSB.println(sZ / n);
      
      SerialUSB.print("Speed: ");
      SerialUSB.print(vx);
      SerialUSB.print(',');
      SerialUSB.print(vy);
      SerialUSB.print(',');
      SerialUSB.println(vz);
      
      SerialUSB.print("v: ");
      SerialUSB.print(v);
      SerialUSB.print(". s: ");
      SerialUSB.println(s);
      
      SerialUSB.println();
    }
  }
  
  delay(p_ms); 
}

// write data into register of ADXL
void writeADXL(uint8 reg, uint8 data){
  uint8 t[2] = {reg, data};
  
  t[0] &= (~CB_MASK);
  digitalWrite(CS, LOW);
  // write the data
  Spi.send(t, 2);
  digitalWrite(CS, HIGH);
  
  if(USB_DEBUG && SPI_DEBUG){
    SerialUSB.print("Tranferred ");
    SerialUSB.print(data, HEX);
    SerialUSB.print(" to Reg ");
    SerialUSB.println(reg, HEX);
  }
}

// read $len data from ADXL start from $reg
void readADXL(uint8 reg, uint8 len){
  uint8 addr = reg;
  
  addr |= RW_MASK;
  if(len > 1)
    addr |= MB_MASK;
  else
    addr &= (~MB_MASK);
  
  digitalWrite(CS, LOW);
  Spi.send(addr);
  // read data serially
  for(int i = 0; i < len; i++)
    values[i] = Spi.send(0x00);
  digitalWrite(CS, HIGH);
  
  if(USB_DEBUG && SPI_DEBUG){
    for(int i = 0; i < len; i++){
      SerialUSB.print(values[i], HEX);
      SerialUSB.print(' ');
    }
    SerialUSB.println();
  }
}

// reset the speed data
void clean(){
  vx = vy = vz = 0;
}
