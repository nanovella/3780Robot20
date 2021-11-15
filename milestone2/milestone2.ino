// ==================================================================
//Constants
#define LFmotor 6
#define LBmotor 5
#define RFmotor 10
#define RBmotor 9
#define delaytime 20
#define SPEED 100

#define yLTHRESH 20
#define yUTHRESH 32
#define bLTHRESH 48
#define bUTHRESH 64
#define eLTHRESH 48
#define eUTHRESH 64

// Variables
int delay_time_1 = 4000;
int delay_time_2 = 2000;
int startcolor;
volatile int period; 
volatile int timer1; 
volatile int color;

int main(void){ 
  initColor();
  initMotors();
  calibrateColor();
  
  Serial.println("forward");
  drive_backward();
  _delay_ms(delay_time_1);
  stop_robot();
  Serial.println("right");
  turn_right();
  _delay_ms(delay_time_1);
  stop_robot();

  while(1){
    checkColor();
    if(startcolor == color)
  }
}

// functions for certain robot behaviors
// fill in the appropriate PORT registers
// don't forget to use masking!
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
    if (yLTHRESH<period && period<yUTHRESH) { //checks for some color 
      color = 2;
    }
    else if (bLTHRESH<period && period<bUTHRESH) { //checks for some color 
      color = 3;
    }
    else if (eLTHRESH<period && period<eUTHRESH) { //checks for some color 
      color = 4;
    }
}

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

void initMotors() {
    Serial.begin(9600);
  DDRD = 0b00001000;
  DDRB = 0b00001110;
  TCCR2A = 0b00100001; 
  TCCR2B = 0b00000110;
  //Right Motor
  TCCR1A = 0b00100001; 
  TCCR1B = 0b00000100;
  sei();
}

void getColor(){ 
  PCMSK2|=0b10000000; //enable PCINT23 (datasheet pg 94) 
  _delay_ms(5); //delay 5 ms to give interrupt time to trigger 
  PCMSK2&=0b01111111; //disable PCINT23 (datasheet pg 94) 
  period=timer1*.0625*2; //convert ticks to microseconds 
} 

int drive_forward(void){
  // change the value of OCR2B to change the PWM duty cycle
  // this example will just oscillate between 0% (0) and 100% (255) duty cycle
  // spin both wheels forward
      OCR2B = SPEED;
      OCR1B = SPEED;
 
}

int drive_backward(void){
  // spin both wheels backward
      OCR2A = SPEED;
      OCR1A = SPEED;
}

int turn_left(void){
  // spin left wheel backward, right wheel forward
      OCR2A = SPEED;
      OCR1B = SPEED;
}

int turn_right(void){
  // spin right wheel backward, left wheel forward
      OCR2B = SPEED;
      OCR1A = SPEED;
}


int stop_robot(void){
  // stop both wheels
      OCR2B = 0;
      OCR1B = 0;
}
