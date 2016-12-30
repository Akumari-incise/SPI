#define spi_m_h
#ifdef spi_m_h
#include <avr/io.h>

#define MOSI 3
#define MISO 4
#define SCK 5
#define SS 2

void init();
void spi_master_read();
void spi_master_write(uint8_t DR);
void clk();

#endif
