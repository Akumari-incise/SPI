/*
 * SPI_lib_Master
 *
 * Created: 12/15/2016 3:07:09 PM
 *  Author: Anju Kumari
 */ 
#include "spi_m.h"
#include<avr/interrupt.h>
#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

int main(void)
{   
       init();
	   spi_master_read();
	   _delay_ms(10);
	   spi_master_write(0b10110101);
	  return 0;
}
void init()
{
	DDRB&=~(1<<MISO);
	DDRB|=(1<<MOSI);
	DDRB|=(1<<SS);
	PORTB|=(1<<SCK);
}

void clk(int x)
{   
	DDRB|=(1<<SCK);
	if(x==1){
	  PORTB|=(1<<SCK);
	  _delay_ms(10);
    }
    else{
	   PORTB&=~(1<<SCK);
	   _delay_ms(10);
   }
}
void spi_master_write(uint8_t DR)
{
	uint8_t spi_data=DR;
	int i;
	DDRB|=(1<<SS);
    DDRB|=(1<<MOSI);
	DDRB|=(1<<SCK);
	PORTB|=(1<<SS);
		for(i=1;i<=8;i++){
		  PORTB&=~(1<<SS);
		  if((spi_data & 0x80)==128){
			 clk(0);
			  PORTB|= (1<<MOSI);
			 _delay_ms(10);
			  clk(1);
	      }
		  else{
			clk(0);
		    PORTB&=~(1<<MOSI);
		    _delay_ms(10);
			clk(1);		 		   
		 }
		 spi_data=spi_data<<1;
	 }
	  
  PORTB&=~(1<<MOSI);
  PORTB|=(1<<SS);
  PORTB|=(1<<SCK);
}

void spi_master_read(){
	uint8_t spi_data;
	int i;
	spi_data =0b00000000;
	DDRB|=(1<<SS);
	DDRB&=~(1<<MISO);
	DDRB|=(1<<SCK); 
	PORTB|=(1<<SS);
	for(i=1;i<=8;i++){
		PORTB&=~(1<<SS);
		clk(0);
		clk(1);
		if(i==8){
			if((PINB & (0x10))==16){
				spi_data=(spi_data|0x01);
			}
			else{
				spi_data=(spi_data|0x00);
			}
		}
		else{
			if((PINB & (0x10))==16){
				spi_data=(spi_data|0x01);
			}
			else{
				spi_data=(spi_data|0x00);
			}
			spi_data=(spi_data<<1);
		}
	}
	PORTD=spi_data;              //to display output at PORTD
	PORTB|=(1<<SCK);
	PORTB|=(1<<SS);
}
