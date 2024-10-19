#include <stdio.h>
#define RLEDs ((volatile long *) 0xFF200000)

void ps2_ISR(){
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	
  	volatile int * PS2_ptr = (int *) 0xFF200100;  // PS/2 port address

	int PS2_data, RVALID;

	while (1) {
		PS2_data = *(PS2_ptr);	// read the Data register in the PS/2 port
		RVALID = (PS2_data & 0x8000);	// extract the RVALID field
		if (RVALID != 0)
		{
			/* always save the last three bytes received */
			byte1 = byte2;
			byte2 = byte3;
			byte3 = PS2_data & 0xFF;
		}
		if ( (byte2 == 0xAA) && (byte3 == 0x00) )
		{
			// mouse inserted; initialize sending of data
			*(PS2_ptr) = 0xF4;
		}
		// Display last byte on Red LEDs
		//*RLEDs = byte3;
		scan_code_decode(byte3);
		printf("the key pressed is %d", byte3);
	}
}



void scan_code_decode(unsigned char scan_code) {
    switch(scan_code) {
        case 0x1C:    //A
            moveLeft();
            break;
        case 0x1B:    //S
            moveDown();
            break;
        case 0x23:    //D
            moveRight();
            break;
        case 0x1D:    //W
            moveUp();
            break;
        case 0x29:   //Space bar
            markFlag();
            break;
        case 0x5A:   //Enter
            performSweep();
            break;
	}
}
