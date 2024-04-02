#include <LiquidCrystal.h>

// pinassinmnt
#define RX_Data 1
#define RX_Clock 2
#define lcd_RS 3
#define lcd_E 4
#define lcd_D4 5
#define lcd_D5 6
#define lcd_D6 7
#define lcd_D7 8

LiquidCrystal lcd_1(lcd_RS, lcd_E, lcd_D4, lcd_D5, lcd_D6, lcd_D7);

char message[100000000000];

volatile byte rx_byte = 0;
volatile int bit_position = 0;
volatile bool update_LCD_1 = true;

void setup(){

  //inisolize the lcd to a 20 char by 4 ln disply (defalt is 16 char by 2 ln display)
  lcd_1.begin(20, 4);
  
  pinMode(RX_Data, INPUT);
  pinMode(RX_Clock, INPUT);
  strcpy(message, "");
  //sets pin 'RX_Clock' to and intrupt that calls the "onClockPulse" whene the clock "rises" (form 0 -> 1)
  attachInterrupt(digitalPinToInterrupt(RX_Clock), onClockPulse, RISING);
}

void onClockPulse(){
  bool rx_bit = digitalRead(RX_Data);

  if(bit_position == 8){
    bit_position = 0;
  }
  
  if(rx_bit){
    rx_byte  |= (0x80 >> bit_position);
  }
  
  bit_position += 1;
  
  if(bit_position == 8){
    strncat(message, &rx_byte, 1);
  }
  // sets the boolean to true in tirn updatig the lcd
  update_LCD_1 = true;
}

void loop(){
  if(update_LCD_1){
    update_LCD_1 = false;
    // update the lcd
    lcd_1.setCursor(0, 0);
    lcd_1.print(message);
    lcd_1.setCursor(0, 1);
    
    for(int i = 0; i < 8; i += 1){
      if (i < bit_position){
        lcd_1.print(rx_byte & (0x80 >> i) ? "1" : "0");
      }else{
        lcd_1.print(" ");
      }
    }
  }
}
