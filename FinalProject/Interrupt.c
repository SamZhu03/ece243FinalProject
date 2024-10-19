#include <stdio.h>
#include "nios2_ctrl_reg_macros.h"


#define Timer       0xFF202000
#define HEX         0xFF200020
#define PushButton  0xFF200050
#define PS2			0xFF200108

//seven segment display
void update_hex_display(int value) {
    volatile int* hex_ptr = (int*)HEX;
    
    int digit_0 = value % 10;
    int digit_1 = (value / 10) % 10;
    int digit_2 = (value / 100) % 10;
    int digit_3 = (value / 1000) % 10;

    int encoded_digits[4];
    encoded_digits[0] = encode_digit(digit_0);
    encoded_digits[1] = encode_digit(digit_1);
    encoded_digits[2] = encode_digit(digit_2);
    encoded_digits[3] = encode_digit(digit_3);

    int hex_value = 0;
    hex_value |= encoded_digits[0];           
    hex_value |= encoded_digits[1] << 8;      
    hex_value |= encoded_digits[2] << 16;     
    hex_value |= encoded_digits[3] << 24;     

    *hex_ptr = hex_value;
}

int encode_digit(int digit) {
    switch (digit) {
        case 0: return 0x3F; 
        case 1: return 0x06; 
        case 2: return 0x5B; 
        case 3: return 0x4F; 
        case 4: return 0x66; 
        case 5: return 0x6D; 
        case 6: return 0x7D; 
        case 7: return 0x07; 
        case 8: return 0x7F; 
        case 9: return 0x6F; 
        default: return 0x00; 
    }
}

void timer_ISR(int start, int *end) {
    volatile int* timer_ptr = (int*)Timer;

    if (start) {
        int countdown = 30;
        *(timer_ptr) = 0x1;
        *(timer_ptr + 1) = 50000000;         //50Mhz 

        *(timer_ptr) = 0x1;
        
        while (countdown >= 0) {
            while (!(*(timer_ptr + 3) & 0x1)); 
            *(timer_ptr + 3) = 0x1; 
            update_hex_display(countdown);
            countdown--;

            for (int i = 0; i < 9000000; i++); // delay 
        }
        *end = 1;
    }
}

void pushbutton_ISR(void){
  volatile int* pushbutton_ptr = (int*)PushButton;
  int value;

  value = *(pushbutton_ptr + 3); 


  if (value & 0x02) {   //second button

  }
  if (value & 0x04) {  //third button

  }
  else{
	return;
  }

  *(pushbutton_ptr + 3) = value;
}


void ps2_ISR(){
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;
	unsigned char byte3 = 0;
	
  	volatile int * PS2_ptr = (int *)PS2;  

	int data, RVALID;

	while (1) {
		data = *(PS2_ptr);	// read the Data register in the PS/2 port
		RVALID = (data & 0x8000);	// extract the RVALID field
		if (RVALID != 0)
		{
			/* always save the last three bytes received */
			byte1 = byte2;
			byte2 = byte3;
			byte3 = data & 0xFF;
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
            break;
        case 0x1B:    //S
            //moveDown();
            break;
        case 0x23:    //D
            //moveRight();
            break;
        case 0x1D:    //W
            //moveUp();
            break;
        case 0x29:   //Space bar
            //markFlag();
            break;
        case 0x5A:   //Enter
            //performSweep();
            break;
	}
}


void interrupt_handle(void){
	int i, j;
	j = NIOS_READ_IPENDING(i);
	if((j&0x2) == 1){
		push_button_ISR();	
	}
	if((j&0x80) == 1){
		ps2_ISR();
	}
	else{
		return;
	}
}



int main(void){
	NIOS2_WRITE_STATUS(1);  //pie bit
	NIOS2_WRITE_IENABLE(0x2);   //pushbuttons
	NIOS2_WRITE_IENABLE(0x4);   //timer
	NIOS2_WRITE_IENABLE(0x80);  //keyboard

	volatile int* ps2_ienable = (int*)PS2;
	*(ps2_ienable+1) = 0x1;


	volatile int* pushbutton_ienable = (int*)PushButton;
	*(pushbutton_ienable+2) = 0xF; 
    while(1){
        printf("Loop");
    }
}