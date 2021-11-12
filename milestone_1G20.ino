/* 
 *  starter code for milestone 1
 *  you will need to build a circuit with two H bridges to control your robot's two motors
 *  and write code for the pins you use for the H bridges
*/ 
#define LFmotor 6
#define LBmotor 5
#define RFmotor 10
#define RBmotor 9
#define delaytime 20


// declare any variables here
int delay_time_1 = 1000;
int delay_time_2 = 1000;

int main(void){ 
  // setup code that only happens once
  // use the DDR registers to set the appropriate pins as outputs
  // Left Motor
  DDRD = 0b01101000;
  TCCR0A = 0b00100001; 
  TCCR0B = 0b00000110;
  OCR0A = 0;
  OCR0B = 0;
  TIMSK1 = 0b00000010;
  //Right Motor
  DDRB = 0b00000110;
  TCCR1A = 0b00100001; 
  TCCR1B = 0b00000110;
  OCR1A = 255;
  OCR1B = 255;
  TIMSK1 = 0b00000010;
  sei();
  // sequence for milestone 1
  // call the functions in the correct order with delays either in between the function calls or in the
  // functions themselves (see example code on Canvas for using functions).
  // this example would have the robot drive forward for 1 second and then stop. 

  drive_forward();
  _delay_ms(delay_time_1); // _delay_ms() is the delay command in C (not the same as the Arduino delay() command)
  stop_robot();

  while(1){
    // infinite while loop
    // you can leave this blank for milestone 1 since the robot
    // only needs to perform the task once
  }
}

// functions for certain robot behaviors
// fill in the appropriate PORT registers
// don't forget to use masking!

int drive_forward(void){
  // change the value of OCR2B to change the PWM duty cycle
  // this example will just oscillate between 0% (0) and 100% (255) duty cycle
  // spin both wheels forward
    while(OCR0A<255){
      OCR0A++; // increment output compare register
      OCR1A++;
      _delay_ms(delaytime);
    }
}

int drive_backward(void){
  // spin both wheels backward
    while(OCR0B<255){
      OCR0B++; // increment output compare register
      OCR1B++;
      _delay_ms(delaytime);
    }
}

int turn_left(void){
  // spin left wheel backward, right wheel forward
    while(OCR0B<255){
      OCR0B++; // increment output compare register
      OCR1A++;
      _delay_ms(delaytime);
    }
}

int turn_right(void){
  // spin right wheel backward, left wheel forward
    while(OCR0B<255){
      OCR0A++; // increment output compare register
      OCR1B++;
      _delay_ms(delaytime);
    }
}
}

int stop_robot(void){
  // stop both wheels
  PORTD &= 0b10011111;
  PORTB &= 0b11111001;
}
