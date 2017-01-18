byte termometre[8] = //icon for termometer
{
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};
///////////////////// yuz////////////
unsigned char i;
unsigned char j; 
/*Port Definitions*/
int Max7219_pinCLK = 12;
int Max7219_pinCS = 11;
int Max7219_pinDIN = 10;

unsigned char smile[1][8]={

  {
    0xc4,0xc2,0x01,0x19,0x19,0x01,0xc2,0xc4    }
  ,// smiling face
};
unsigned char normal[1][8]={

  {
    0xc0,0xc1,0x01,0x19,0x19,0x01,0xc1,0xc0    }
  , // Normal Face
};
unsigned char angry[1][8]={

  {
    0xc0,0xc1,0x02,0x1a,0x1a,0x02,0xc1,0xc0    }
  , //Angry Face
};
void Write_Max7219_byte(unsigned char DATA) 
{   
  unsigned char i;
  digitalWrite(Max7219_pinCS,LOW);		
  for(i=8;i>=1;i--)
  {		  
    digitalWrite(Max7219_pinCLK,LOW);
    digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
    DATA = DATA<<1;
    digitalWrite(Max7219_pinCLK,HIGH);
  }                                 
}


void Write_Max7219(unsigned char address,unsigned char dat)
{
  digitalWrite(Max7219_pinCS,LOW);
  Write_Max7219_byte(address);           //address，code of LED
  Write_Max7219_byte(dat);               //data，figure on LED 
  digitalWrite(Max7219_pinCS,HIGH);
}

void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00);       //decoding ：BCD
  Write_Max7219(0x0a, 0x03);       //brightness 
  Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
  Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
  Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

/////////////////////////////////////
#include <OneWire.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

OneWire  ds(2);  // on pin 12z

void setup(){
  lcd.createChar(1,termometre);
  ///////////yuz/////////////////////////

  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);
  Init_MAX7219();
  ////////////////////////////////////////
  lcd.begin(20, 4);
  Wire.begin();

  Serial.begin(9600);
  //  lcd.setCursor(3,0);
  //  lcd.print("Hello, world!");
  //  lcd.setCursor(2,1);
  //  lcd.print("Ywrobot Arduino!");
  //   lcd.setCursor(0,2);
  //  lcd.print("Arduino LCM IIC 2004");
  //   lcd.setCursor(2,3);
  //  lcd.print("Power By Ec-yuan!");
  //  delay(2000);
  ////////////////gulen yuz//////////////////////////
  for(i=1;i<9;i++){
    Write_Max7219(i,smile[j][i-1]);
    // delay(200);
  }
  //////////////////////////////////////////
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("LUTFEN BEKLEYINIZ");
  lcd.setCursor(3,1);
  lcd.print("BILGI ALINIYOR");
  // prints the value read
  lcd.setCursor(0,3);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));
  delay(1000);
  tone(9,2000,100);
  lcd.print(char(255));



}

void loop(){
  printDate();
  delay(2000);

  delay(2000);

  int airQuality = analogRead(0);       // read analog input pin 0
  airQuality=map(airQuality,0,1023,100,0);

  lcd.setCursor(0,2);
  lcd.print(" TEHLIKELI GAZ: %");
  airQuality= 100 - airQuality;
  lcd.print(airQuality);  // prints the value read

  if (airQuality > 40){
    for(i=1;i<9;i++){
      Write_Max7219(i,angry[j][i-1]);
      // delay(200);
    }
  }
  else { 
    if(airQuality >20 && airQuality <40 ){ 
      for(i=1;i<9;i++){
        Write_Max7219(i,normal[j][i-1]);
      } 
    }
    if(airQuality < 20 ){
      for(i=1;i<9;i++){
        Write_Max7219(i,smile[j][i-1]);
        // delay(200);
      }
    }      
  }
  ////////////////////////////////////

}

byte bcdToDec(byte val)  {
  // Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}
////////////////////////////////////////////////
////////////////////////////////////////////////
///////////////18B20////////////////////////////


////////////////////////////////////////////////////
////////////////////////////////////////////////////
///////////////GAS SENSOR///////////////////////////
void hava(){
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
/////////////RTC////////////////////////////////////
void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);

  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.read());
  int minute = bcdToDec(Wire.read());
  int hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.read());
  int month = bcdToDec(Wire.read());
  int year = bcdToDec(Wire.read());

  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(2500);
    return;
  }

  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return;
  }
  Serial.println();

  // the first ROM byte indicates which chip
  switch (addr[0]) {
  case 0x10:
    Serial.println("  Chip = DS18S20");  // or old DS1820
    type_s = 1;
    break;
  case 0x28:
    Serial.println("  Chip = DS18B20");
    type_s = 0;
    break;
  case 0x22:
    Serial.println("  Chip = DS1822");
    type_s = 0;
    break;
  default:
    Serial.println("Device is not a DS18x20 family device.");
    return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present,HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // convert the data to actual temperature

  unsigned int raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // count remain gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } 
  else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
    // default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;

  //////////////////////////////dISARI SICAKLIK

  int disarisicaklik = analogRead(2);
  disarisicaklik = (5.0 * disarisicaklik * 100.0)/1024.0;
  delay(200);

  lcd.clear();
  //print the date EG   3/1/11 23:59:59
  lcd.setCursor(2,0);
  lcd.print("TARIH: ");
  lcd.print(monthDay);
  lcd.print("/");
  lcd.print(month);
  lcd.print("/");
  lcd.print(year);
  lcd.setCursor(0,1);
  lcd.print("    SAAT :");
  lcd.print(" ");
  lcd.print(hour);
  lcd.print(":");
  lcd.print(minute);
  //  lcd.print(":");
  //  lcd.print(second);

  Serial.print("TARIH: ");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.println(year);
  
  Serial.print("    SAAT :");
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);


  //  lcd.clear();
  lcd.setCursor(1, 2);
  lcd.print("ICERISI");
  lcd.setCursor(9, 2);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print(" DISARI");

  lcd.setCursor(0, 3);
  lcd.write(1);
  lcd.print(celsius);
  lcd.print(char(223));
  lcd.print("C");
  lcd.setCursor(9, 3);
  lcd.print(char(255));
  lcd.print(char(255));
  lcd.print("  ");
  lcd.write(1);

  lcd.print(disarisicaklik);
  lcd.print(char(223));

  lcd.print("C");

  // lcd.print("F");
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");

}


