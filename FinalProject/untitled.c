int pixel_buffer_start; // global variable
int m = 0;

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        *one_pixel_address = line_color;
}



#include <stdio.h>

void ps2_ISR(){
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	
  	volatile int * PS2_ptr = (int *) 0xFF200100;  // PS/2 port address

	int PS2_data, RVALID;

	while (1) {    //需要信号控制，不然死循环
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
            //moveLeft();
		m++;
		for(int i=3; i<238; i++){   //blue
        	plot_pixel(m, i, 0x00);
    	}
            break;
        case 0x1B:    //S
          //  moveDown();
		for(int i=3; i<238; i++){
        	plot_pixel(69, i, 0x000);  //black
    	}
            break;
        case 0x23:    //D
            //moveRight();
		   for(int i=3; i<238; i++){
       		 plot_pixel(95, i, 0x0FF);
    		}

            break;
        case 0x1D:    //W
            //moveUp();
			for(int j=40; j<281; j++){
        plot_pixel(j, 55, 0x000);
    }
            break;
        case 0x29:   //Space bar
           // markFlag();
			for(int j=40; j<281; j++){
        plot_pixel(j, 211, 0x000);
    }
            break;
        case 0x5A:   //Enter
            //performSweep();
			for(int j=40; j<281; j++){
        plot_pixel(j, 211, 0x0F1);
    }
            break;
	}
}

void clear_screen(){
    for (int i = 0; i < 320; i++){
        for (int j = 0; j < 240; j++){ 
            plot_pixel(i, j, 0xffff);
        }
    }   
}
int main(void){
	    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;

    // Enable the pixel buffer
    pixel_buffer_start = *pixel_ctrl_ptr;
	clear_screen();
	while(1){

		ps2_ISR();
	}
	return 0;
}