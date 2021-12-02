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

#define yLTHRESH 16
#define yUTHRESH 29
#define bLTHRESH 40
#define bUTHRESH 58
#define eLTHRESH 120
#define eUTHRESH 190

// Variables
//int 15deg = 800;
//int 3in = 1000;
int border_delay = 100;

int startcolor;
int othercolor; 
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

ISR(PCINT0_vect) { //interrupt vector for PCINT0
  if (PINB & 0b00100000) { //if pin 13 (PB5) is high 
    turn_left();
    _delay_ms(300);
    drive_forward();
    Serial.println("pin 13");
  }
  else if (PINB & 0b00010000) { //if pin 12 (PB4) is high 
    turn_right();
    Serial.println("pin 12");
  }
} 

int main(void){
  _delay_ms(2000);
  initMotors();
  initColor();
  sei();
  calibrateColor();
  Serial.begin(9600);

  bool homeside = true;
  int homesides = 0;
  while(1){
    checkColor();
    Serial.println(period);
    //Serial.println(startcolor);
    if(startcolor == color) {
      drive_forward();
      if(!homeside) {
        homesides++;
        drive_forward();
        _delay_ms(100);
//        stop_robot();
//        _delay_ms(600);
//        if(homesides == 2) {
//          stop_robot();
//          break;
//        }
      }
    }
    else if(color == 4) {
      if(!homeside) {
        stop_robot();
        break;
      }
      Serial.println("black");
      stop_robot();
      turn_right();
      _delay_ms(550);
       stop_robot();
      
      
      bool black = true;
      while(black){
        checkColor();
        if(color != 4) black = false;
        
        else{      
        stop_robot();
        _delay_ms(300);
        turn_right();
        _delay_ms(1250);
        }
          
          
      }
      drive_forward();
    }
    else if(othercolor == color) {
      homeside = false;
      stop_robot();
      _delay_ms(300);
      turn_right();
      _delay_ms(1100);
      stop_robot();
      //drive_forward();
    }  
  }
}

void calibrateColor() {
  getColor();
  if (yLTHRESH<period && period<yUTHRESH) { //checks for some color 
    startcolor = 2;
    othercolor = 3;
  }
  else if (bLTHRESH<period && period<bUTHRESH) { //checks for some color 
    startcolor = 3;
    othercolor = 2;
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
      color = 4;
    }
    _delay_ms(195);
    Serial.println(color);    
}

void initColor(){ 
  //set up I/O for sensor 
  //DDRD &= 0b01111111; //set pin 17 to input
  //set up pin change interrupt on pin 7 (PCINT23) 
  PCICR=0b00000101; //enable PCINT2 (datasheet pg 92) 
  //set up timer 1 
  PCMSK0 = 0b00100000;
  TCCR1A=0b00000000; //set timer to normal mode (datasheet pg 171) 
  TCCR1B=0b00000001; //set prescaler to 1 (datasheet pg 173) 
} 

void initMotors() {
  DDRD = 0b01101000; // Forward Pins
  DDRB = 0b00001100; // Backwards Pins
  TCCR2A = 0b10110001; 
  TCCR2B = 0b00000001;
  //Right Motor
  TCCR0A = 0b10110001; 
  TCCR0B = 0b00000001;
  stop_robot();
}

void getColor(){ 
  PCMSK2|=0b10000000; //enable PCINT23 (datasheet pg 94) 
  _delay_ms(5); //delay 5 ms to give interrupt time to trigger 
  PCMSK2&=0b01111111; //disable PCINT23 (datasheet pg 94) 
  period=timer1*.0625*2; //convert ticks to microseconds 
} 

int drive_forward(void){
      OCR0A = 0;
      OCR2A = 0;
      OCR2B = 0;
      OCR0B = 0;
 
}

int drive_backward(void){
      OCR0A = 0;
      OCR2A = 0;
      OCR2B = 0;
      OCR0B = 0;
}

int turn_right(void){
  // spin left wheel backward, right wheel forward
      OCR0A = 0;
      OCR2A = 255;
      OCR2B = 255;
      OCR0B = 0;
}

int turn_left(void){
  // spin right wheel backward, left wheel forward
      OCR0A = 255;
      OCR2A = 0;
      OCR2B = 0;
      OCR0B = 255;
}

int stop_robot(void){
  // stop both wheels
      OCR0A = 128;
      OCR2A = 128;
      OCR2B = 128;
      OCR0B = 128;
}
