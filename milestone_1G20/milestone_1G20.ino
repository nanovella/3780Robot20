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
#define SPEED 100

// declare any variables here
int delay_time_1 = 4000;
int delay_time_2 = 2000;

int main(void){ 
  // setup code that only happens once
  // use the DDR registers to set the appropriate pins as outputs
  // Left Motor
  Serial.begin(9600);
  DDRD = 0b00001000;
  DDRB = 0b00001110;
  TCCR2A = 0b00100001; 
  TCCR2B = 0b00000110;
  //Right Motor
  TCCR1A = 0b00100001; 
  TCCR1B = 0b00000100;
  sei();
  // sequence for milestone 1
  // call the functions in the correct order with delays either in between the function calls or in the
  // functions themselves (see example code on Canvas for using functions).
  // this example would have the robot drive forward for 1 second and then stop. 
  Serial.println("forward");
  drive_backward();
  _delay_ms(delay_time_1);
  stop_robot();
  Serial.println("right");
  turn_right();
  _delay_ms(delay_time_1);
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