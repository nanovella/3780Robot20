
#define QTIOpin 13; //PB5

volatile bool QTI = fdals;

ISR(PCINT0_vect) { //interrupt vector for PCINT0
  if (PINB & 0b00100000) { //if pin 13 (PB5) is high 
    QTI = true;
  }
} 

int main(void){
  initColor();
  sei();
  
  while(1){
       if(QTI) {
        Serial.println("border");
       }
       _delay_ms(50);
  }
}

void initColor(){ 
  //set up I/O for sensor 
  DDRB &= 0b11011111; //set pin 13 (PD7) to input 
  //set up pin change interrupt on pin 7 (PCINT23) 
  PCICR=0b00000001; //enable PCINT0 (datasheet pg 92) 
  PCMSK0 |= 0b00100000;
  //set up timer 0 
  TCCR0A=0b00000000; //set timer to normal mode (datasheet pg 171) 
  TCCR0B=0b00000001; //set prescaler to 1 (datasheet pg 173) 
} 
