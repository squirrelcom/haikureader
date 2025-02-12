// Haiku eInk Reader
// Roni Bandini, Instagram @RoniBandini 
// More electronic art projects at bandini.medium.com        
// Buenos Aires, Argentina, 2021
// ESP32 to 2.9 eInk connections: Busy D4, RST D21, DC D22, CS D5, CLK D18, DIN D23, 

#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

// eInk pins
GxIO_Class io(SPI, 5, 22, 21, 4); 
GxEPD_Class display(io, 21, 4); 

// D12 and D13 buttons
int buttonPin1=12;
int buttonPin2=13;

// counter
int counter=0;

// Open screen
const unsigned char myBitmap [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x07, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0xf8, 0x00, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x18, 0x00, 0x18, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x38, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x30, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x30, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x70, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x1c, 0x00, 0x70, 0x00, 0x7f, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x1f, 0x80, 0x60, 0x00, 0x7f, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x10, 0xf0, 0xe0, 0x00, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x00, 0x10, 0x1e, 0xe0, 0x00, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x00, 0x30, 0x03, 0xc0, 0x00, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x20, 0x00, 0x40, 0x01, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x20, 0x00, 0xc0, 0x01, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf9, 0xfc, 0x60, 0x00, 0xf8, 0x01, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0x3f, 0xe0, 0x00, 0xf7, 0x01, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0x07, 0xc0, 0x00, 0xf0, 0x73, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0x00, 0xc0, 0x01, 0xf0, 0x0f, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0x00, 0x40, 0x01, 0xe0, 0x01, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xe0, 0x00, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0x80, 0x03, 0xe0, 0x00, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0xc0, 0x03, 0xc0, 0x00, 0xff, 0x80, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x00, 0xf8, 0x03, 0xc0, 0x00, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x01, 0xff, 0x87, 0xc0, 0x01, 0xff, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x01, 0xf8, 0xf7, 0xc0, 0x01, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x01, 0xf8, 0x0f, 0x80, 0x01, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x01, 0xf8, 0x01, 0x80, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf0, 0x03, 0xf0, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x03, 0xf0, 0x00, 0x60, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe7, 0xe3, 0xf0, 0x00, 0x7e, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0xff, 0xe0, 0x00, 0x7f, 0xc7, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x1f, 0xe0, 0x00, 0xf0, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x03, 0xe0, 0x00, 0xf0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x01, 0xe0, 0x00, 0xe0, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x01, 0xc0, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x01, 0xc0, 0x01, 0xe0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x03, 0xe0, 0x01, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0x80, 0x03, 0xfc, 0x01, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x03, 0xff, 0xc3, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x06, 0x0f, 0xfb, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x06, 0x01, 0xff, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x06, 0x00, 0x3f, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x0e, 0x00, 0x0f, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x0c, 0x00, 0x0f, 0xe0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x8c, 0x00, 0x1f, 0xfc, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x3c, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x3c, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x38, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x00, 0x78, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x78, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x70, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xfd, 0xff, 0xf0, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x3f, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x07, 0xe0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x20, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x30, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x7e, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x7f, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xf9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xe0, 0x00, 0xc7, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0xc0, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x01, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x01, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 
	0xff, 0xff, 0xff, 0xdf, 0xe1, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0x81, 0xff, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x3f, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x03, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x06, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x07, 0xe0, 0x18, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x0f, 0xfc, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0x90, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x09, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfc, 0x00, 0x18, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x80, 0x18, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x10, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x30, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x00, 0x3f, 0xe0, 0x3f, 0xfc, 0x0f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x03, 0xff, 
	0xff, 0xfe, 0x00, 0x0f, 0xe0, 0x3f, 0xf8, 0x0f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x01, 0xff, 
	0xff, 0xf8, 0x00, 0x07, 0xe0, 0x3f, 0xf8, 0x0f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x01, 0xff, 
	0xff, 0xf0, 0x00, 0x03, 0xe0, 0x3f, 0xfc, 0x0f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x01, 0xff, 
	0xff, 0xe0, 0x00, 0x01, 0xe0, 0x3f, 0xfc, 0x1f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x01, 0xff, 
	0xff, 0xe0, 0x00, 0x00, 0xe0, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0x01, 0xff, 
	0xff, 0xc0, 0x00, 0x00, 0xe0, 0x01, 0xf8, 0x0f, 0xf0, 0x1f, 0xc0, 0x3f, 0xc0, 0x7f, 0x01, 0xff, 
	0xff, 0xc0, 0x1e, 0x00, 0x60, 0x00, 0x78, 0x0f, 0xc0, 0x07, 0xc0, 0x3f, 0x00, 0x1f, 0x00, 0x7f, 
	0xff, 0x80, 0x3f, 0x00, 0x60, 0x00, 0x78, 0x0f, 0x80, 0x03, 0xc0, 0x3e, 0x00, 0x0f, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0x80, 0x60, 0x00, 0x38, 0x0f, 0x00, 0x01, 0xc0, 0x3c, 0x00, 0x07, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0x8f, 0xe0, 0x00, 0x38, 0x0f, 0x00, 0x01, 0xc0, 0x3c, 0x00, 0x03, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0xcf, 0xe0, 0x00, 0x38, 0x0e, 0x00, 0x00, 0xc0, 0x38, 0x02, 0x03, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0x80, 0x60, 0x00, 0x38, 0x0e, 0x00, 0x00, 0xc0, 0x38, 0x04, 0x03, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0x80, 0x60, 0x20, 0x38, 0x0e, 0x03, 0x80, 0xc0, 0x38, 0x00, 0x01, 0x00, 0x7f, 
	0xff, 0x80, 0x7f, 0x80, 0x60, 0x20, 0x38, 0x0e, 0x03, 0x80, 0x40, 0x38, 0x00, 0x01, 0x01, 0xff, 
	0xff, 0x80, 0x3f, 0x00, 0x60, 0x20, 0x38, 0x0e, 0x03, 0x80, 0xc0, 0x38, 0x00, 0x01, 0x01, 0xff, 
	0xff, 0xc0, 0x00, 0x00, 0xe0, 0x20, 0x38, 0x0c, 0x01, 0x00, 0xc0, 0x00, 0x0f, 0xff, 0x00, 0x7f, 
	0xff, 0xc0, 0x00, 0x00, 0xe0, 0x20, 0x38, 0x0c, 0x00, 0x00, 0xe0, 0x00, 0x06, 0xff, 0x00, 0x7f, 
	0xff, 0xe0, 0x00, 0x01, 0xe0, 0x20, 0x38, 0x0e, 0x00, 0x00, 0xe0, 0x04, 0x00, 0x7f, 0x00, 0x7f, 
	0xff, 0xf0, 0x00, 0x01, 0xe0, 0x20, 0x38, 0x0e, 0x00, 0x01, 0xe0, 0x04, 0x00, 0x3f, 0x80, 0x7f, 
	0xff, 0xf8, 0x00, 0x03, 0xe0, 0x20, 0x38, 0x0e, 0x00, 0x03, 0xf0, 0x06, 0x00, 0x1f, 0x80, 0x7f, 
	0xff, 0xfc, 0x00, 0x0f, 0xe0, 0x20, 0x38, 0x0e, 0x00, 0x07, 0xf8, 0x07, 0x00, 0x1f, 0xc0, 0x7f, 
	0xff, 0xfe, 0x00, 0x1f, 0xe0, 0x20, 0x38, 0x0e, 0x00, 0x0f, 0xfc, 0x07, 0x80, 0x3f, 0xf0, 0x7f, 
	0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xe0, 0xff, 0xfc, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfc, 0x06, 0x3f, 0xff, 0xff, 0xcf, 0xff, 0xcf, 0xf8, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x8c, 0x3f, 0xff, 0xff, 0x8f, 0xff, 0xc7, 0xfe, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x8c, 0x33, 0xff, 0xff, 0x8f, 0xff, 0x8f, 0xfe, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x88, 0x63, 0xff, 0xff, 0x1f, 0xff, 0x8f, 0xfe, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x00, 0x43, 0xff, 0xff, 0x1f, 0xff, 0x9f, 0xfc, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x04, 0x03, 0x80, 0x00, 0x1c, 0x0f, 0x1f, 0xfc, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x08, 0x07, 0x19, 0xc6, 0x38, 0xc7, 0x1f, 0xfc, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x18, 0x47, 0x19, 0xc6, 0x38, 0xcf, 0x3f, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x38, 0xc7, 0x31, 0xc4, 0x38, 0xfe, 0x3f, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0x31, 0xc0, 0x01, 0xc0, 0x00, 0x00, 0x07, 0xf8, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xcf, 0xe7, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };

void setup() {

  pinMode(buttonPin1, INPUT_PULLUP);  
  pinMode(buttonPin2, INPUT_PULLUP);  
    
  display.init();

  display.setTextColor(GxEPD_BLACK);     
  
}

void loop() 
{

 int buttonReading1 = digitalRead(buttonPin1);
 int buttonReading2 = digitalRead(buttonPin2);


  if (buttonReading1==0){    
    counter=counter-1;      
    if (counter<0) {counter=0;}
     updateHaiku(); 
  }

  if (buttonReading2==0){
    counter=counter+1;    
    if (counter>4) {counter=4;}
     updateHaiku();
  }
  
  delay(50);
     
  
}

void updateHaiku() {

   display.fillScreen(GxEPD_WHITE); 

   if (counter==0){
      display.fillScreen(GxEPD_BLACK);
      display.drawBitmap(0, 0, myBitmap, 128, 296, GxEPD_WHITE);
      display.update();  
    }
    
   if (counter==1){    
    
    display.setCursor(1, 1);
    display.setTextSize(0);
    display.println("Matsuo Basho");
    display.println("(1644-1694)");
    display.println("");
    display.println("An old silent pond...");
    display.println("A frog jumps into the pond,");
    display.println("splash, silence again");
    display.println("");
    display.println("Autumn moonlight");
    display.println("a worm digs silently");
    display.println("into the chestnut.");
    display.println("");
    display.println("In the twilight rain");
    display.println("these brilliant-hued hibiscus -");
    display.println("A lovely sunset.");
    
    display.update();
      
  
  }

    if (counter==2){
      
     display.setCursor(1, 1);
     display.setTextSize(0);
     display.println("Yosa Buson");
     display.println("(1716-1784)");
     display.println("");              

     display.println("A summer river being crossed");
     display.println("how pleasing");
     display.println("with sandals in my    hands!");
     display.println("");
     display.println("Light of the moon");
     display.println("Moves west, flowers' shadows");
     display.println("Creep eastward.");
     display.println("");
     display.println("In the moonlight,");
     display.println("The color and scent   of the wisteria");
     display.println("Seems far away.");

     display.update();
      
  
  }

    if (counter==3){
      
    display.setCursor(1, 1); 
    display.setTextSize(0);     
    display.println("Masaoka Shiki ");
    display.println("(1867-1902)");
    display.println("");               

    display.println("I want to sleep");
    display.println("Swat the flies");
    display.println("Softly, please.");
    display.println("");
    display.println("After killing");
    display.println("a spider, how lonely I feel");
    display.println("in the cold of night!");
    display.println("");
    display.println("For love and for hate");
    display.println("I swat a fly and      offer it");
    display.println("to an ant.");
    
    display.update();
      
  
  }

     if (counter==4){
      
    display.setCursor(1, 1); 
    display.setTextSize(0);     
    display.println("Natsume Soseki ");
    display.println("(1867-1916)");
    display.println("");               

    display.println("The lamp once out");
    display.println("Cool stars enter");
    display.println("The window frame.");
    display.println("");
    display.println("Plum flower temple:");
    display.println("Voices rise");
    display.println("From the foothills");
    display.println("");
    display.println("The crow has flown   away:");
    display.println("swaying in the        evening sun,");
    display.println("a leafless tree.");
       
    display.update();
      
  
  }

  
  }
