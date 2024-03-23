include <LiquidCrystal.h >

// pinassinmnt

#define RX_Data 1

#define lcd_RS 2

#define lcd_E 3

#define lcd_D4 4

#define lcd_D5 5
  
#define lcd_D6 6
  
#define lcd_D7 7

LiquidCrystal lcd_1(lcd_RS, lcd_E, lcd_D4, lcd_D5, lcd_D6, lcd_D7);

char message[16];

byte rx_byte = 0;
int bit_position = 0;

void setup(){
  
  //inisolize the lcd to a 16 char by 2 ln disply
  lcd_1.begin(20, 4);
  
  pinMode(TX_Data, INPUT);
  
  strcpy(message, "");
}

void loop(){
  delay(200);
  bool rxbit = digitalRead(RX_Data);
  ;
  if(bit_position == 8){
    bit_position = 0
  }
  
  if (rx_bit(){
    rx_byte  |= (ox80 >> bit_position);
  }
  
  bit_position += 1;
  
  if(bit_position == 8){
    strncat(message, &rx_byte, 1);
  }
  
  lcd_1.setCursor(0, 0);
  lcd_1.print(message);
  lcd_1.setCursor(0, 1);
  for(int 1 = 0; i < 8; i += 1){
    if (i < bit_position){
      lcd_1.print(rx_byte & (0x80 >> i) ? "1" : "0");
    }else{
      lcd_1.print(" ");
    }
  }
}
