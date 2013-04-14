ArduinoExperiments
==================

# EXPERIMENT 1 : 7 Segment LED Clock - Time Sync from Computer
## Hardware Required
1. Arduino UNO R2 x 1
2. Jumper Wires x 30
3. BreadBoard x 1
4. 74HC595 ( Serial Shift Register ) x 1
5. Multiplexed 7-Segment LED display ( 4 individual seven segment LED modules ) x 1

## Software
Copy the 'Time' folder to the arduino 'Libraries' folder first. The arduino time library
is courtesy http://playground.arduino.cc/Code/time.
Copy the code in ./sevenSegmentTimePCSync/LED7SegmentTime.ino and paste it in the Arduino
sketch area ( connect your arduino ) and hit upload.

## Summary 
The idea is to take the time from the computer from the serial port. The Time is then
displayed on the seven segment display in 24Hr format. Since my 7-Segment module did not
have a separator between the hour and minutes so the code also doesn't display a separator.

# EXPERIMENT 2 : LCD Single Row left Scroll.
## Hardware Required
1. Arduino UNO R2 x 1
2. Jumper Wires x 16
3. (16 x 2) LCD display x 1

## Software
Copy the code in ./lcdOneLineLeftScrollExperiment/lcd1lineScrollExperiment.ino and paste it in the Arduino
sketch area ( connect your arduino ) and hit upload.

## Summary
The motivation behind this sketch was to create a function which will LEFT scroll a single row of the lcd display,
without refreshing the whole screen. Given a character array to display, with each invocation of the function, the row
specified is scrolled one character to the left.
Please use the leftScroll() method, the leftScroll1() method is present to show my attempts before I reached the final
solution ( And both use completely different algorithms ).

