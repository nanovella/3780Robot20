float distance=0;
volatile float pulse_duration = 0;
volatile int input_flag = 1;
const float v_sound = 340; // speed of sound in meters per second

ISR(PCINT2_vect){ // interrupt service routine for pin change interrupt request 2
  if (PIND & 0b10000000){ // if pin 7 is high - rising edge of input pulse
    TCNT1 = 0; // reset the timer to 0
  }else{ // pin 7 is low, falling edge of input pulse
    pulse_duration = TCNT1; // store pulse duration in clock ticks
    input_flag = 0;
  }
}

int main(void){
  // setup code that only runs once
  PCICR = 0b00000100; // enable pin change interrupt 2
  PCMSK2 = 0b10000000; // enable PCINT23 on pin 7
  TCCR1A = 0b00000000; // set timer 1 to normal mode
  TCCR1B = 0b00000010; // and set prescaler to 8
  Serial.begin(9600); // initialize serial
  while(1){
    // code that loops forever
    DDRD |= 0b10000000; // pin 7 as output, prepare for output pulse
    PORTD |= 0b10000000; // pin 7 high
    _delay_ms(0.005);    // from datasheet - 5 microsec trigger pulse
    PORTD &= 0b01111111; // pin 7 low
    DDRD &= 0b01111111; // pin 7 as input, prepare for input pulse
    sei(); // enable interrupts
    input_flag = 1;
    while(input_flag == 1){
      // wait for input pulse to be measured
    }
    cli(); // disable interrupts
    // convert pulse duration to distance in centimeters 
    // note that sound travels out and back so the time 
    // corresponds to twice the distance between sensor and target
    // one clock tick is 62.5ns, timer has prescaler of 8
    distance = v_sound * pulse_duration * 8 * 62.5e-9 * 100 / 2; 
    Serial.println(distance); // print the measured distance
  }
}
