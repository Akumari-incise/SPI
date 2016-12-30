/*
 * SPI_lib_Slave
 *
 * Created: 12/26/2016 12:12:50 PM
 *  Author: Anju Kumari
 */ 
#include "spi_s.h"
#include<avr/interrupt.h>
#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

int main(){
	init();	
	spi_slave_write(0b10110111);
	_delay_ms(10);
	spi_slave_read();	
	return 0;
}
void init(){
	DDRB&=~(1<<SCK);
	DDRB&=~(1<<SS);
	DDRB&=~(1<<MOSI);
	DDRB|=(1<<MISO);
}

void spi_slave_write(uint8_t DR)
{    
	uint8_t spi_data=DR;
	int i;
	DDRB&=~(1<<SS);
	DDRB&=~(1<<SCK);
	DDRB|=(1<<MISO);
	for(i=1;i<=8;i++){
	  while((PINB & (0x20))==0){
		if((spi_data & 0x80)==128){
			PORTB|= (1<<MISO);
			_delay_ms(21);
		}
		else{
			PORTB&=~(1<<MISO);
			_delay_ms(21);
		}
		spi_data=spi_data<<1;
	  }
	
	}
	PORTB&=~(1<<MISO);
}

void spi_slave_read(){
	uint8_t spi_data;
	int i;
	spi_data =0b00000000;
	DDRB&=~(1<<MOSI);
	DDRB&=~(1<<SCK);
	DDRB&=~(1<<SS);
	for(i=1;i<=8;i++){
			_delay_ms(29);
		if(i==8){
			if((PINB & (0x08))==8){
				spi_data=(spi_data|0x01);
			}
			else{
				spi_data=(spi_data|0x00);
			}
		}
		else{
		if((PINB & (0x08))==8){
			spi_data=(spi_data|0x01);
			
		}
		else{
			spi_data=(spi_data|0x00);
		}
	
		spi_data=spi_data<<1;
		}
	}
	PORTD=spi_data;      //to display output at PORTD
}
