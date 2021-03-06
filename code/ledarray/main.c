#include <avr/io.h>
#include <util/delay.h>
#define WD 1
#define HD 4
#define COL_EN 0b00000001
#define COL_D 0b00000010
#define COL_CLK 0b00000100
char buffer[WD*HD];

void main(void);
void col_write(char w);
 
void main(void){
    DDRD = 0xff;
    
    for(;;){
		buffer[0] = 0xe9;
		buffer[1] = 0x6c;
		buffer[2] = 0x4b;
		buffer[3] = 0x38;
		
	    PORTD |= ROW_CLK;
        PORTD |= ROW_D;
        PORTD &= ~ROW_CLK;
         
        for(char i=0;i<WD*8;i++){
            for(char j=0;j<HD;j++){
                col_write(buffer[i*HD+j]);
            }
            PORTD |= COL_EN;
            _delay_ms(10);
        }    
    }
}

void col_write(char w){
    for(char i=0;i<8;i++){
        PORTD |= COL_CLK;
        if(w & (1 << i)){
            PORTD |= COL_D;
        }else{
            PORTD &= ~COL_D;
        }
        PORT &= ~COL_CLK;
    }
}
