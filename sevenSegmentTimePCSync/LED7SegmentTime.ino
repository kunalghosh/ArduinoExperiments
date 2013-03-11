/*
 *Get Time Data from PC. Paste the following code snippet on the shell
 *TZ_adjust=5.5;d=$(date +%s);t=$(echo "60*60*$TZ_adjust/1" | bc);echo T$(echo $d+$t | bc ) > /dev/ttyACM0
 */
#include <Time.h>

#define TIME_MSG_LEN 11
#define TIME_HEADER 'T'
#define TIME_REQUEST 7

int dataPin = 6;
int clockPin = 7;
int latchPin = 8;

const int MU = 2; //Pin responsible for displaying the tenth's place of hour.
const int MT = 3; //Pin responsible for displaying the unit's place of hour.
const int HU = 4; //Pin responsible for displaying the tenth's place of minute.
const int HT = 5; //Pin responsible for displaying the unit's place of minute.

const int ON = HIGH;
const int OFF = LOW;

void setup(){
        pinMode(2,OUTPUT);
        pinMode(3,OUTPUT);
        pinMode(4,OUTPUT);
        pinMode(5,OUTPUT);
        pinMode(6,OUTPUT);
        pinMode(7,OUTPUT);
        pinMode(8,OUTPUT);
        Serial.begin(9600);
}

void loop(){
        if(Serial.available()){
                processSyncMessage();
        }
        if( timeStatus() == timeNotSet )
                Serial.println("Wait for sync message");
        else
                digitalClockDisplay(hour(),minute());
//        delay(500);                                                                                                                                                                            
}

void processSyncMessage(){
        while(Serial.available() >= TIME_MSG_LEN){
                char c = Serial.read();
                Serial.print(c);
                if ( c == TIME_HEADER ){
                        time_t pctime = 0;
                        for ( int i = 0; i < TIME_MSG_LEN -1 ; i++ ){
                                c = Serial.read();
                                if ( c >= '0' && c <= '9' ){
                                        pctime = ( 10 * pctime ) + ( c - '0' );
                                }
                        }
                        setTime(pctime);
                }
        }
}

void digitalClockDisplay(int H, int M){ // H = Hour ( 7 am => 7 ,
                                        // 8 PM => 20 ) , M = Minute
        disp7Segment( H , 'H' );
        disp7Segment( M , 'M' );
        //----------------
          // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void disp7Segment( int value , char ch ){
        if ( 'H' == ch ){
                if ( value > 10 ){
                    sevenSegment( HT , value/10 ); // works even if value < 10
                }
                sevenSegment( HU , value%10 );
        }
        if ( 'M' == ch ){
                if ( value > 10 ){
                    sevenSegment( MT , value/10 ); // works even if value < 10
                }
                sevenSegment( MU , value%10 );
        }
}

void sevenSegment(int Pin , int value ){
        switch( value ){
                case 0 : shiftRegWrite(B11111100);
                         break;
                case 1 : shiftRegWrite(B01100000);
                         break;          
                case 2 : shiftRegWrite(B11011010);
                         break;
                case 3 : shiftRegWrite(B11110010);
                         break;          
                case 4 : shiftRegWrite(B01100110);
                         break;          
                case 5 : shiftRegWrite(B10110110);
                         break;
                case 6 : shiftRegWrite(B10111110);
                         break;          
                case 7 : shiftRegWrite(B11100000);
                         break;
                case 8 : shiftRegWrite(B11111110);
                         break;
                case 9 : shiftRegWrite(B11110110);
                         break;
                default : break ;
        }
        digitalWrite( Pin, ON );
        delay(10);
        digitalWrite( Pin, OFF );
}

void shiftRegWrite( int value ){
        int bitInverse = value ^ 255; 
	// XOR with 255 because the LED module 
	// is selected by setting select the pin high.
	// Having done that we need to set the individual 
	// led pins low to complete the circuit.
	// It is easier for us to think of numbers on the 7segment LED
	// as setting the individual LEDs high.
	// But to actually display the digits, we need to set the 
	// high to low and low to high, so that the circuit completes.
	// And the number is displayed.
        digitalWrite( latchPin , LOW );
        Serial.println(bitInverse);
        shiftOut( dataPin , clockPin , LSBFIRST , bitInverse );
        digitalWrite( latchPin , HIGH );
}

