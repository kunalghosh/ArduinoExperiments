ArduinoExperiments
==================

# EXPERIMENT 1 : 7 Segment LED Clock - Time Sync from Computer
## Hardware Required
1. Arduino UNO R3 x 1
2. Jumper Wires x 30
3. BreadBoard x 1
4. 74HC595 ( Serial Shift Register ) x 1
5. Multiplexed 7-Segment LED display ( 4 individual seven segment LED modules ) x 1

## Software
Code in ./sevenSegmentTimePCSync/LED7SegmentTime.ino just paste the code in the Arduino
sketch area ( connect your arduino ) and hit upload.

## Summary 
The idea is to take the time from the computer from the serial port. The Time is then
displayed on the seven segment display in 24Hr format. Since my 7-Segment module did not
have a separator between the hour and minutes so the code also doesn't display a separator.

