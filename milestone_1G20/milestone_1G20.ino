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
#define SPEED 255

// declare any variables here
int delay_time_1 = 1900;
int delay_time_2 = 500;

int main(void){ 
  // setup code that only happens once
  // use the DDR registers to set the appropriate pins as outputs
  // Left Motor
  Serial.begin(9600);
  DDRD = 0b00001000;
  DDRB = 0b00001110;
  TCCR2A = 0b10100001; 
  TCCR2B = 0b10000110;
  //Right Motor
  TCCR0A = 0b10100001; 
  TCCR0B = 0b10000100;
  sei();

  Serial.println("forward");
  _delay_ms(2000);
  drive_forward();
//  _delay_ms(delay_time_1);
//  
//  stop_robot();
//  _delay_ms(3000);
//  
//  Serial.println("right");
//  turn_right();
//  _delay_ms(delay_time_2);
//  
//  stop_robot();
//  _delay_ms(3000);
//  
//  drive_forward();
//  _delay_ms(delay_time_1);
//  
//  stop_robot();
//  _delay_ms(3000);
//  
//  Serial.println("left");
//  turn_left();
//  _delay_ms(delay_time_2);
//  
//  stop_robot();
//  _delay_ms(3000);
//
//  drive_forward();
//  _delay_ms((delay_time_1)/2);
//
//  stop_robot();
//  _delay_ms(3000);
//
//  drive_backward();
//  _delay_ms((delay_time_1)*(1.3));
//
//  stop_robot();
//  _delay_ms(3000);
//
//  turn_left();
//  _delay_ms(delay_time_2);
//
//  stop_robot();
//  _delay_ms(3000);
//
//  drive_forward();
//  _delay_ms(delay_time_1);
//
//  stop_robot();
//  _delay_ms(100000);

  while(1){
    // infinite while loop
    // you can leave this blank for milestone 1 since the robot
    // only needs to perform the task once
  }
}

int drive_forward(void){
      OCR2B = SPEED;
      OCR0B = SPEED;
}

int drive_backward(void){
  // spin both wheels backward
     
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
      OCR0B = 0;
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
