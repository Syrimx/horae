#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

/*
	64	32	16	8	4 	2 	1
	2^6 2^5 2^4 2^3 2^2 2^1 2^0

*/

//Global variables

int minArray[6] = {0};
int valueArray[6] = {1,2,4,8,16,32};


// Compute the logical (binary) representation of minutes and hours 
// The logical representation is presentated in an array consist of 0 or 1 
// supply an adequat counter variable for computing minutes (5) or hours (4)
// example: computing the binary representation of 45 minutes 
// -> computeTimeLogic(45)
// das least signifanct bit ist im array links und das most significant bit im array ganz rechts
// 2^0 2^1 2^2 2^3 2^4 2^5
void computeTimeLogic(int input) {
	int result  = input;
	int counter = 5;

	while(counter >= 0) {
		//Input is divisible by 64
		if((result - valueArray[counter]) >= 0) {
			result -= valueArray[counter];
			minArray[counter] = 1;
		} else {
			minArray[counter] = 0;
		}
		counter--;
	}
}

void printingMinArray() {
	printf("[*] printing the minArray...\n");
	for(int i = 0; i < 6; i++) {
		printf("%d", minArray[i]);
	}
}


//this functio translates the logical arrays containing the bitset 
//onto the LED Ports.
//The desired translation to LEDs representing the hours or minutes 
//can be flagged with respectively 1 (hours) or 0 (minutes)
void logicalToHardware(int mode) {
	//minute mode -> 0
	if(mode == 0) {
		for(int i = 0; i < 6; i++) {
			if(minArray[i] == 1) {
				PORTC |= (1<<i);
			}
			else if(minArray[i] == 0) {
				PORTC &= ~(1<<i);
			}
		}
		_delay_ms(100);
	}
	//hour mode -> 1
	else if(mode == 1) {
		for(int i = 0; i < 5; i++) {
			if(minArray[i] == 1) {
				PORTD |= (1<<(i+3));
			}
			else if(minArray[i] == 0) {
				PORTD &= ~(1<<(i+3));
			}
		}
		_delay_ms(100);
	}
}


void main() {
	DDRC=0xff;
	DDRD=0xff;


	while(1) {
		//Testing Counting up the Hours
		for(int i = 0; i < 24; i++) {
			computeTimeLogic(i);
			logicalToHardware(1);
			//Testing counting to 60 (Minutes)
			for(int j = 1; j <= 60; j++) {
				computeTimeLogic(j);
				logicalToHardware(0);
			}
		}


		//Testing Counting up the Hours
		PORTD |= (1<<3);
	}
}