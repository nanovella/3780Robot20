// ==================================================================
//Constants
#define LFmotor 11
#define LBmotor 3
#define RFmotor 10
#define RBmotor 9
#define QTIRpin 12
#define QTILpin 13
#define delaytime 20
#define SPEED 80

#define yLTHRESH 20
#define yUTHRESH 32
#define bLTHRESH 48
#define bUTHRESH 64
#define eLTHRESH 48
#define eUTHRESH 64

// Variables
int delay_time_1 = 4000;
int delay_time_2 = 2000;
int border_delay = 100;
int startcolor;
volatile int period; 
volatile int timer1; 
volatile int color;
volatile bool QTI = false;

ISR(PCINT2_vect) { //interrupt vector for PCINT2 
  if (PIND & 0b10000000) { //if pin 7 (PD7) is high 
    TCNT1=0; //reset timer 
  } 
  else { 
    timer1=TCNT1; //store timer value in variable timer1 
  } 
} 

//ISR(PCINT0_vect) { //interrupt vector for PCINT0
//  if (PINB & 0b00100000) { //if pin 13 (PB5) is high 
//    stop_robot();
//    turn_right();
//    _delay_ms(border_delay);
//    stop_robot();
//  }
//  else if (PINB & 0b00010000) { //if pin 12 (PB4) is high 
//    stop_robot();
//    turn_left();
//    _delay_ms(border_delay);
//    stop_robot();
//  }
//} 

int main(void){
  initMotors();
  initColor();
  sei();
  calibrateColor();
  Serial.begin(9600);
  
  bool homeside = true;
  while(1){
    checkColor();
    Serial.println(period);
    if(startcolor == color) {
      Serial.println("hi");
      drive_forward();
      _delay_ms(1000);
      if(!homeside) {
        _delay_ms(100);
        stop_robot();
      }
    }
    else if(color == 4) {
      stop_robot();
      turn_right();
      bool black = true;
      while(black){
        checkColor();
        if(color != 4) black = false;
      }
    }
    else if(startcolor != color) {
      homeside = false;
      drive_forward();
      _delay_ms(100);
      stop_robot();
      turn_right();
      _delay_ms(2*delay_time_2);
      drive_forward();
    }
    
  }
}

void calibrateColor() {
  getColor();
  if (yLTHRESH<period && period<yUTHRESH) { //checks for some color 
    startcolor = 2;
  }
  else if (bLTHRESH<period && period<bUTHRESH) { //checks for some color 
    startcolor = 3;
  }
  else if (eLTHRESH<period && period<eUTHRESH) { //checks for some color 
    startcolor = 4;
  }  
}

void checkColor() {
    getColor();
    if (yLTHRESH<period && period<yUTHRESH) { //checks for some color 
      color = 2;
    }
    else if (bLTHRESH<period && period<bUTHRESH) { //checks for some color 
      color = 3;
    }
    else if (eLTHRESH<period && period<eUTHRESH) { //checks for some color 
      color = startcolor;
    }
}

void initColor(){ 
  //set up I/O for sensor 
  DDRD &= 0b01111111; //set pin 17 to input
  //set up pin change interrupt on pin 7 (PCINT23) 
  PCICR=0b00000100; //enable PCINT2 (datasheet pg 92) 
  //set up timer 1 
  TCCR1A=0b00000000; //set timer to normal mode (datasheet pg 171) 
  TCCR1B=0b00000001; //set prescaler to 1 (datasheet pg 173) 
} 

void initMotors() {
  DDRD = 0b00001000;
  DDRB = 0b00001110;
  TCCR2A = 0b10100001; 
  TCCR2B = 0b10000110;
  //Right Motor
  TCCR0A = 0b10100001; 
  TCCR0B = 0b10000100;
}

void getColor(){ 
  PCMSK2|=0b10000000; //enable PCINT23 (datasheet pg 94) 
  _delay_ms(5); //delay 5 ms to give interrupt time to trigger 
  PCMSK2&=0b01111111; //disable PCINT23 (datasheet pg 94) 
  period=timer1*.0625*2; //convert ticks to microseconds 
} 

int drive_forward(void){
      OCR2B = SPEED;
      OCR0B = SPEED;
 
}

int drive_backward(void){
      OCR2A = SPEED;
      OCR0A = SPEED;
}

int turn_right(void){
  // spin left wheel backward, right wheel forward
      OCR2B = 0;
      OCR0A = 0;
      OCR2A = SPEED;
      OCR0B = SPEED;
}

int turn_left(void){
  // spin right wheel backward, left wheel forward
      OCR1B = 0;
      OCR2A = 0;
      OCR2B = SPEED;
      OCR0A = SPEED;
}

int stop_robot(void){
  // stop both wheels
      OCR0A = 0;
      OCR2A = 0;
      OCR2B = 0;
      OCR0B = 0;
}
