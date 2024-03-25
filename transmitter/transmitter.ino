#include <LiquidCrystal.h>
#include <Wire.h>

// pinassinmnt
#define TX_Data 1
#define TX_Clock 2
#define lcd_RS 3
#define lcd_E 4
#define lcd_D4 5
#define lcd_D5 6
#define lcd_D6 7
#define lcd_D7 8

// targit transmit raite
int TX_Bit_Raite = 5;

LiquidCrystal lcd_1(lcd_RS, lcd_E, lcd_D4, lcd_D5, lcd_D6, lcd_D7);

const char *message = "Hello, Wornd!";

void setup(){

  Wire.begin();
  
  //inisolize the lcd to a 16 char by 2 ln disply
  lcd_1.begin(20, 4);

  pinMode(TX_Data, OUTPUT);
  pinMode(TX_Clock, OUTPUT);
  
  // set the curosor to top left and print the "message"
  lcd_1.setCursor(0, 0);
  lcd_1.print(message);
/*
  // gose thrue all the byts in the "message"
  for(int byte_idx = 0; byte_idx < strlen(message); byte_idx++){
    char tx_byte = message[byte_idx];
    // sets the cursor to the char that is being transmited sets sets the courser to line 2 (line one stars at '0') and puts 8 spaces to "clear" the second ln then sets cursor off
    lcd_1.noCursor();
    lcd_1.setCursor(0, 1);
    lcd_1.print("       ");
    lcd_1.print(byte_idx, 0);
    lcd_1.cursor();

    // loops thru each bit of the byte in the letter most sanifacent bit first
    for(int bit_idx = 0; bit_idx < 8; bit_idx++){

      // tests if the bit that is set is a "1" or a "0" then 
      // sets TX_Data HIGH or LOW depending
      bool tx_bit = tx_byte & (0x80 >> bit_idx);
      digitalWrite(TX_Data, tx_bit);
      delay((1000/TX_Bit_Raite)/2);
      digitalWrite(TX_Clock, HIGH);
      
      // sets the cursror to ln 2 of the desplay then prints a "1" or a "0" whan dun sets the couser to the char that is being transmited
      lcd_1.noCursor();
      lcd_1.setCursor(tx_bit, 1);
      lcd_1.print(tx_bit ? "1" : "0");
      lcd_1.setCursor(byte_idx, 0);
      lcd_1.cursor();
      delay((1000/TX_Bit_Raite)/2);
      digitalWrite(TX_Clock, LOW);
    } 

  }
*/
}



void loop(){
  Wire.requestFrom(0, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    lcd_1.print(c, 0);         // print the character
  }
}
