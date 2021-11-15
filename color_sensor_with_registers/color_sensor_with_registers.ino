/*  Color Sensor Period Calculator 
 *   
 *  This code prints the period of the color sensed by the color sensor (pin7) using  
 *  timer 1. 
 *   
 *  Cornell University 
 *  MAE3780 - Mechatronics 
 *  Ding, Grace 
 *  28OCT2019 
 *  Last edited: 05NOV2020 
 */ 
 
 
//global variables 
volatile int period; 
volatile int timer1; 
 
/* 
*Pin change interrupt service routine for pin7 (PD7). Triggers on any logical change 
*/ 
ISR(PCINT2_vect) { //interrupt vector for PCINT2 
  if (PIND & 0b10000000) { //if pin 7 (PD7) is high 
    TCNT1=0; //reset timer 
  } 
  else { 
    timer1=TCNT1; //store timer value in variable timer1 
  } 
} 
 
/* 
Initializes registers that LED and color sensor are connected to 
and sets up timer 1 
*/ 
void initColor(){ 
  //set up I/O for sensor 
  DDRD=0b00000000; //set pin 7 (PD7) to input 
 
  //set up pin change interrupt on pin 7 (PCINT23) 
  PCICR=0b00000100; //enable PCINT2 (datasheet pg 92) 
  sei(); //enable all interrupts 
 
  //set up timer 1 
  TCCR1A=0b00000000; //set timer to normal mode (datasheet pg 171) 
  TCCR1B=0b00000001; //set prescaler to 1 (datasheet pg 173) 
} 
 
/* 
* Gets the period from the color sensor by triggering the interrupt for 5ms 
*/ 
void getColor(){ 
  PCMSK2|=0b10000000; //enable PCINT23 (datasheet pg 94) 
  _delay_ms(5); //delay 5 ms to give interrupt time to trigger 
  PCMSK2&=0b01111111; //disable PCINT23 (datasheet pg 94) 
  period=timer1*.0625*2; //convert ticks to microseconds 
} 
 
int main(void){ 
  Serial.begin(9600); 
  initColor(); //call initColor() to initialize all variables 
  while (1){ 
    getColor(); //get the color from the color sensor 
    //uncomment this if-else once you determine your thresholds for a specific color 
    /*if (THRESHOLD1<period && period<THRESHOLD2) { //checks for some color 
      //do something 
      
    } 
    else { 
      //do something else 
      
    }*/ 
    Serial.println(period); 
    _delay_ms(500); //check color every 500ms 
  } 
}
