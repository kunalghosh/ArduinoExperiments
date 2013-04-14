/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *    
 *   Author : Kunal Ghosh  
 *   Email : kunal dot t2 at gee maail dot com
 *   Date : 14th April 2013
 *
 *   This code was tested on an Arduino UNO R2 with a standard LCD display
 *   based on the Hitachi HD44780 driver, using the arduino LiquidCrystal 
 *   library.
 */
    

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char message[] = "This is some long message that will end up scrolling. ";
char lcdee[16];

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("My Message:");
  lcd.setCursor(0,1);
  //lcd.print(message);
  pinMode(A2,OUTPUT);
  digitalWrite(A2,HIGH);
}

void leftScroll1(char* mess,int maxCols,int row){ 
  // Doesn't roll back to the first character, while scrolling.
  // Uses a different algorithm.
  
  static char* position = mess;
  static int messLength = strlen(mess);
  strncpy(lcdee,position,maxCols);
  Serial.println(*position);
  lcd.setCursor(0,row);
  lcd.print(lcdee);
  position++;
  delay(1000);
  /*
  if( position == mess + messLength-1){
    position = mess;
  }
  */
}

void leftScroll(char* mess,int maxCols,int row){ // maxCols == total number of columns in your LCD display.
  lcd.setCursor(0,row);
  static int i = 0;//j = 0;
  int k = i;
  // the next message to be displayed must be 1 character to the right of the current starting character. To give the scrolling effect
  // So store the current starting character.
  
  for (int j = 0; j < maxCols ; i++, j++){
    if (i == strlen(mess)){ // while copying to the lcdee array if the end of message is reached, start from the beginning.
      i = 0;
    }
    Serial.print("mess[i] : ");
    Serial.println(mess[i]);
    
    Serial.print("i ");
    Serial.println(i);
    
    lcdee[j] = mess[i];
  }  
  i = k + 1; // next message to be displayed on the screen must start from 1 character to the right of the current start character.
  lcd.print(lcdee);
  Serial.println(lcdee);
  if (i == strlen(mess)){
      i = 0;
    }

}

void loop() {  
  //leftScroll1(message,16,1);
  leftScroll(message,16,1);
  delay(1000);
}
