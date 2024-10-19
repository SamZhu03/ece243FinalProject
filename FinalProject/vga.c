#include <stdio.h>
#include <stdint.h>

#include "flag_png.h"
#include "bomb_png.h"
#include "number_four.h"
#include "number_three.h"
#include "number_two.h"
#include "number_one.h"
#include "number_zero.h"

extern const uint16_t flag [25][25];
extern const uint16_t bomb [25][25];
extern const uint16_t zero [25][31];
extern const uint16_t one [25][25];
extern const uint16_t two [25][34];
extern const uint16_t three [25][22];
extern const uint16_t four [25][25];


int pixel_buffer_start; // global variable

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        *one_pixel_address = line_color;
}


void clear_screen(){
    for (int i = 0; i < 320; i++){
        for (int j = 0; j < 240; j++){ 
            plot_pixel(i, j, 0xffff);
        }
    }   
}


void draw_grid(){
    for(int i=3; i<238; i++){
        plot_pixel(43, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(69, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(95, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(121, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(147, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(173, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(199, i, 0x000);
    }
    
    for(int i=3; i<238; i++){
        plot_pixel(225, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(251, i, 0x000);
    }

    for(int i=3; i<238; i++){
        plot_pixel(277, i, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 29, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 55, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 81, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 107, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 133, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 159, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 185, 0x000);
    }

    for(int j=40; j<281; j++){
        plot_pixel(j, 211, 0x000);
    }

}

void choose_coordinate(int x, int y){
    for(int i=0; i<26; i++){
        for(int j=0; j<1; j++){
           plot_pixel(x+i, y+j, 0xF800); 
        }
    }

    for(int i=0; i<26; i++){
        for(int j=0; j<1; j++){
           plot_pixel(x+i, y+26+j, 0xF800); 
        }
    }

    for(int i=0; i<26; i++){
        for(int j=0; j<1; j++){
           plot_pixel(x+j, y+i, 0xF800); 
        }
    }

    for(int i=0; i<26; i++){
        for(int j=0; j<1; j++){
           plot_pixel(x+26+j, y+i, 0xF800); 
        }
    }

}



int main(void) {
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;

    // Enable the pixel buffer
    pixel_buffer_start = *pixel_ctrl_ptr;

    // Step 2: Write image data to the VGA pixel buffer
    int x, y;
	x = 43;
	y = 55;
	
	clear_screen();
    draw_grid();
    choose_coordinate(x, y);
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(148 + j, 82+ i, flag[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(226 + j, 186+ i, bomb[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}

	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(174 + j, 82+ i, zero[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(200 + j, 108+ i, two[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(70 + j, 212+ i, three[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(252 + j, 186+ i, four[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
	for (int i = 0; i < 25; i++) {
    	for (int j = 0; j < 25; j++) {
       		 plot_pixel(44 + j, 56+ i, one[i][j]); // Plot pixel at position (90 + j, 180 + i) with color from bomb array
    	}
	}
	
    return 0;
}