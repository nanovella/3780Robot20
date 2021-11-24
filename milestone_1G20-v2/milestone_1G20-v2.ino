/* 
 *  starter code for milestone 1
 *  you will need to build a circuit with two H bridges to control your robot's two motors
 *  and write code for the pins you use for the H bridges
*/ 
#define RFmotor 5
#define LFmotor 6
#define RBmotor 11
#define LBmotor 10
#define delaytime 20
#define SPEED 255

// declare any variables here
int delay_time_1 = 1900;
int delay_time_2 = 500;

int main(void){ 
  // setup code that only happens once
  // use the DDR registers to set the appropriate pins as outputs
  // Left Motor
  //Serial.begin(9600);
  DDRD = 0b01100000; // Forward Pins
  DDRB = 0b00001100; // Backwards Pins

  //Right Motor
  TCCR0A = 0b10100001; 
  TCCR0B = 0b10000100;

  //Serial.println("forward");
  //_delay_ms(2000);
  drive_forward();



  while(1){
    // infinite while loop
    // you can leave this blank for milestone 1 since the robot
    // only needs to perform the task once
  }
}

int drive_forward(void){

      OCR0A = 128; 
      OCR0B = 128; 
}

int drive_backward(void){
  // spin both wheels backward
      OCR2B = SPEED;
      OCR0A = 0;
      OCR0B = 0;
      OCR2A = SPEED;
}

int turn_right(void){
  // spin left wheel backward, right wheel forward
      OCR2B = 0;
      OCR0A = 0;
      OCR0B = 0;
      OCR2A = SPEED;
}

int turn_left(void){
  // spin right wheel backward, left wheel forward
      OCR2B = 0;
      OCR0A = 0;
      OCR0B = 0;
      OCR2A = SPEED;
}


int stop_robot(void){
  // stop both wheels
      OCR2B = 0;
      OCR0A = 0;
      OCR0B = 0;
      OCR2A = SPEED;
}
