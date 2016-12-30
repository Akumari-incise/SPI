#define spi_s_h
#ifdef spi_s_h
#include <avr/io.h>

#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2

void init();
void spi_slave_read();
void spi_slave_write(uint8_t DR);
void clk();

#endif
