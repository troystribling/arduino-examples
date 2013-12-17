
#include "LiquidCrystal440.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,     //function overloading lets the list of arguments specify if 4 or 8 data lines are used and if rw is used or tied to gnd.
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
   uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)         // I can't eliminate rw and add en2 and be unique.
{
 init(0, rs, rw, enable,255, d0, d1, d2, d3, d4, d5, d6, d7);
}
/* LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,  uint8_t en2,   //4x40 8 data bits 2 enable pins
 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
 init(0, rs, rw, enable, en2, d0, d1, d2, d3, d4, d5, d6, d7);
}
*/

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
 init(1, rs, rw, enable, 255,d0, d1, d2, d3, 0, 0, 0, 0);
}
LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t en2,
uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)    //4x40  4 data pins 2 enable pins
{
init(1, rs, rw, enable,en2, d0, d1, d2, d3, 0, 0, 0, 0);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
   uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
 init(0, rs, 255, enable,255,d0, d1, d2, d3, d4, d5, d6, d7);
}
LiquidCrystal::LiquidCrystal(uint8_t rs,  uint8_t enable,
   uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
 init(1, rs, 255, enable,255, d0, d1, d2, d3, 0, 0, 0, 0);
}


void LiquidCrystal::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t en2,
uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
 _rs_pin = rs;
 _enable_pin = enable;
 _en2 = en2;
 _chip = 0;
 _scroll_count =0;      //to fix the bug if we scroll and then setCursor w/o home() or clear()
 _x = 0;
 _y = 0;
 _numcols = 0;
 _setCursFlag = 0;
 _direction = LCD_Right;
 _data_pins[0] = d0;
 _data_pins[1] = d1;
 _data_pins[2] = d2;
 _data_pins[3] = d3;
 _data_pins[4] = d4;  //unused in 4 bit mode
 _data_pins[5] = d5;
 _data_pins[6] = d6;
 _data_pins[7] = d7;

 pinMode(d0, OUTPUT); //set data pin modes
 pinMode(d1, OUTPUT);
 pinMode(d2, OUTPUT);
 pinMode(d3, OUTPUT);
 if (! fourbitmode) {
   pinMode(d4, OUTPUT);
   pinMode(d5, OUTPUT);
   pinMode(d6, OUTPUT);
   pinMode(d7, OUTPUT);

 }
 row_offsets[0] = 00;   // DDRAM addresses inside the HD44780 are strange: 0-nColumns-1 on line 0
 row_offsets[1] = 0x40; // 64-(63+nColumns) for line 1
 row_offsets[2] = 0x14; // 20- (19+nColumns) for line 2 --- NOTHING FROM 40-63 !
 row_offsets[3] = 0x54; // 84 - (83+nColumns) for line 3  -- so 80 characters tops out at #103 !

 pinMode(_rs_pin, OUTPUT);
 // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
 if (rw != 255) {
   pinMode(rw, OUTPUT);  //once in init does it
   digitalWrite(rw,LOW); //write data to LCD mode
 }
 pinMode(_enable_pin, OUTPUT);
 if( en2 != 0) pinMode(en2,OUTPUT);  //4X40 LCD

  _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
 if (fourbitmode)
   _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

 _rw_pin = rw;
 begin(20, 1);
}

void LiquidCrystal::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
 _numlines = lines;
  _numcols = cols;
  row_offsets[2] = cols + row_offsets[0];  //should autoadjust for 16/20 or whatever columns now
  row_offsets[3] = cols + row_offsets[1];

  begin2( cols,  lines,  dotsize, 0);
  if (_en2 != 255) {                      //if we were called with a 2nd enable line i.e. 4x40 LCD
	row_offsets[2] = 0;
    row_offsets[3] = 0x40;             //each line gets its own little 40 char section of DDRAM--would be fine if there were a 4x32, I suppose.
    begin2( cols,  lines,  dotsize,0x2);//initialize the second HD44780 chip
  }
}

void LiquidCrystal::begin2(uint8_t cols, uint8_t lines, uint8_t dotsize, uint8_t chip) {
 _chip = chip;

 uint8_t en = _enable_pin;
 if (chip == 2) en=_en2;
 if (lines > 1) {
   _displayfunction |= LCD_2LINE;
 }

 // for some 1 line displays you can select a 10 pixel high font
 if ((dotsize != 0) && (lines == 1)) {
   _displayfunction |= LCD_5x10DOTS;
 }

 // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
 // according to datasheet, we need at least 40ms after power rises above 2.7V
 // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
 delayMicroseconds(60000); //I don't think I can adequately test this number; it will depend a little on which Arduino or clone you have and probably
                           //could also vary with the power source applied to that board. The way to test is really to load your program, remove power
                           //and then reapply power so that the program starts up as power is applied. If anyone finds they need a larger number please
                           //let me know: raine001 at tc dot umn dot edu
 // Now we pull both RS and R/W low to begin commands
 digitalWrite(_rs_pin, LOW);
 digitalWrite(en, LOW);

 //put the LCD into 4 bit or 8 bit mode
 if (! (_displayfunction & LCD_8BITMODE)) {
   // this is according to the hitachi HD44780 datasheet
   // figure 24, pg 46

   // we start in 8bit mode, try to set 4 bit mode
//at this point we are in 8 bit mode but of course in this interface 4 pins are dangling unconnected and the values on them don't matter for these instructions.
   write4bits(0x03,LOW);
   delayMicroseconds(5000); // I have one LCD for which 4500 here was not long enough.
   // second try
   write4bits(0x03,LOW);
   delayMicroseconds(150); // wait
   // third go!
   write4bits(0x03,LOW);
   delayMicroseconds(150);
   // finally, set to 4-bit interface
   write4bits(0x02,LOW);
 } else {
   // this is according to the hitachi HD44780 datasheet
   // page 45 figure 23  -- this is 8 bit mode

   // Send function set command sequence
   command(LCD_FUNCTIONSET | _displayfunction);
   delayMicroseconds(5000);  // again, one LCD I have needed more than 4500

   // second try
   command(LCD_FUNCTIONSET | _displayfunction);
   delayMicroseconds(150);

   // third go
   command(LCD_FUNCTIONSET | _displayfunction);
 }

 // finally, set # lines, font size, etc.
 command(LCD_FUNCTIONSET | _displayfunction);

 // turn the display on with no cursor or blinking default
 _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  display();

 // clear it off
 clear();

 // Initialize to default text direction (for romance languages)
 _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
 // set the entry mode
 command(LCD_ENTRYMODESET | _displaymode);
}

/********** high level commands, for the user! */
void LiquidCrystal::clear()
{
 if (_en2 != 255) {
   _chip=2;
   command(LCD_CLEARDISPLAY);
   _chip=0;
   command(LCD_CLEARDISPLAY);
   delayMicroseconds(2000);
   setCursor(0,0);
 }
 else {
   command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
   delayMicroseconds(2000);  // this command takes a long time!
 }
 _scroll_count = 0;
}

void LiquidCrystal::home()
{
 commandBoth(LCD_RETURNHOME);  // set cursor position to zero      //both chips.
 delayMicroseconds(2000);  // this command takes a long time!
 _scroll_count = 0;
 if (_en2 != 255) setCursor(0,0);
}


// Turn the display on/off (quickly)
void LiquidCrystal::noDisplay() {
 _displaycontrol &= ~LCD_DISPLAYON;
 commandBoth(LCD_DISPLAYCONTROL | _displaycontrol);  //both chips
}
void LiquidCrystal::display() {
 _displaycontrol |= LCD_DISPLAYON;
 commandBoth(LCD_DISPLAYCONTROL | _displaycontrol);   //both chips
}

// Turns the underline cursor on/off
void LiquidCrystal::noCursor() {
 _displaycontrol &= ~LCD_CURSORON;
 command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal::cursor() {
 _displaycontrol |= LCD_CURSORON;
 command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal::noBlink() {
 _displaycontrol &= ~LCD_BLINKON;
 command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal::blink() {
 _displaycontrol |= LCD_BLINKON;
 command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal::scrollDisplayLeft(void) {
 commandBoth(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);  //both chips
 _scroll_count++;
 if (_scroll_count >= 40) _scroll_count -= 40;   //  -39< scroll_count<39
}
void LiquidCrystal::scrollDisplayRight(void) {
 commandBoth(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);  //both chips
 _scroll_count--;
 if (_scroll_count <= -40) _scroll_count += 40;
}

// This is for text that flows Left to Right
void LiquidCrystal::leftToRight(void) {
 _displaymode |= LCD_ENTRYLEFT;
 _direction = LCD_Right;
 commandBoth(LCD_ENTRYMODESET | _displaymode);     //both chips
}

// This is for text that flows Right to Left
void LiquidCrystal::rightToLeft(void) {
 _displaymode &= ~LCD_ENTRYLEFT;
 _direction = LCD_Left;
 commandBoth(LCD_ENTRYMODESET | _displaymode);    //both chips
}


// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal::createChar(uint8_t location, uint8_t charmap[]) {
 location &= 0x7; // we only have 8 locations 0-7
 if (_en2 == 255) {
   command(LCD_SETCGRAMADDR | (location << 3));
   for (int i=0; i<8; i++) {
     send(charmap[i],HIGH);
   }
 }
 else {
   uint8_t chipSave = _chip;
   _chip = 0;
   command(LCD_SETCGRAMADDR | (location << 3));
   for (uint8_t i=0; i<8; i++) {
     send(charmap[i],HIGH);
   }
   _chip = 2;
   command(LCD_SETCGRAMADDR | (location << 3));
   for (uint8_t i=0; i<8; i++) {
     send(charmap[i],HIGH);
}
_chip = chipSave;
 }
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)         // this can be called by the user but is also called before writing some characters.
{
 if ( row > _numlines ) {
   row = _numlines-1;    // we count rows starting w/0
 }
 _y = row;
 _x = col;
 _setCursFlag = 0;                                                 //user did a setCursor--clear the flag that may have been set in write()
 int8_t high_bit = row_offsets[row] & 0x40;                        // this keeps coordinates pegged to a spot on the LCD screen even if the user scrolls right or
 int8_t  offset = col + (row_offsets[row] &0x3f)  + _scroll_count; //left under program control. Previously setCursor was pegged to a location in DDRAM
//the 3 quantities we add are each <40
 if (offset > 39) offset -= 40;                                    // if the display is autoscrolled this method does not work, however.
 if (offset < 0) offset += 40;
 offset |= high_bit;
 if (_chip != (row & 0b10)) noCursor();  //turn off cursor on chip we are leaving
 _chip = row & 0b10;                     //if it is row 0 or 1 this is 0; if it is row 2 or 3 this is 2
 command(LCD_SETDDRAMADDR | (byte) offset );
}
// This will 'right justify' text from the cursor
void LiquidCrystal::autoscroll(void) {           //to count the number of times we scrolled; here we'd need to keep track of microseconds and divide. I'm not going there.
 _displaymode |= LCD_ENTRYSHIFTINCREMENT;
 commandBoth(LCD_ENTRYMODESET | _displaymode);   //both chips
}

// This will 'left justify' text from the cursor
void LiquidCrystal::noAutoscroll(void) {
 _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;   //both chips
 commandBoth(LCD_ENTRYMODESET | _displaymode);
}


/*********** mid level commands, for sending data/cmds */
inline void LiquidCrystal::command(uint8_t value) {
 send(value, LOW);
}

void LiquidCrystal::commandBoth(uint8_t value) {  //for many of the commands that need to be sent twice if 2 controller chips
 if (_en2 == 255) {
   send(value, LOW);  //not 40x4
 }
 else {
   uint8_t chipSave = _chip;
   _chip = 0;
   send(value,LOW);   //send command to first HD44780
   _chip = 2;
   send(value,LOW);   //send to 2nd HD44780
   _chip=chipSave;
  }
}

size_t LiquidCrystal::write(uint8_t value) {                            //print calls  this to send characters to the LCD
if ((_scroll_count != 0) || (_setCursFlag != 0) ) setCursor(_x,_y);   //first we call setCursor and send the character
if ((value != '\r') && (value != '\n') )send(value, HIGH);

 _setCursFlag = 0;
 if (_direction == LCD_Right) {                    // then we update the x & y location for the NEXT character
   _x++;
   if ((value == '\r') ||(_x >= _numcols) ) {      //romance languages go left to right

     _x = 0;
     _y++;
     _setCursFlag = 1;          //we'll need a setCursor() before the next char to move to begin of next line
   }
 }
 else {
   _x--;
   if ( (value == '\n') || (_x < 0)) {   //emulate right to left text mode which is built in but would be defeated by my code above
     _x = _numcols-1;
     _y++;
     _setCursFlag = 1;
   }
 }
 if (_y >= _numlines) _y = 0;   //wrap last line up to line 0
 return 1;
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void LiquidCrystal::send(uint8_t value, uint8_t mode) {
 digitalWrite(_rs_pin, mode);
 if (_displayfunction & LCD_8BITMODE) {
   write8bits(value,mode);
    delayMicroseconds(100);
 } else {
   write4bits(value>>4, mode);
   write4bits(value, mode);
    delayMicroseconds(100);
 }
}

void LiquidCrystal::pulseEnable(void) {
 byte en = _enable_pin;
 if ((_en2 != 255) && (_chip)) en = _en2;               //I have a 4x40 LCD with 2 controller chips with separate enable lines if we called w 2 enable pins and are on lines 2 or 3 enable chip 2
 digitalWrite(en,LOW);
 digitalWrite(en, HIGH);   // enable pulse must be >450ns
// delayMicroseconds(1);    // but this is unnecessary see:
 digitalWrite(en, LOW);    //http://billgrundmann.wordpress.com/2009/03/03/to-use-or-not-use-writedigital/
}


void LiquidCrystal::write4bits(uint8_t value, uint8_t mode) {

 digitalWrite(_rs_pin,mode);
 for (uint8_t i = 0; i < 4; i++) {
   digitalWrite(_data_pins[i], (value >> i) & 0x01);
 }
 pulseEnable();
}

void LiquidCrystal::write8bits(uint8_t value, uint8_t mode) {
 digitalWrite(_rs_pin,mode);
 for (uint8_t i = 0; i < 8; i++) {
   digitalWrite(_data_pins[i], (value >> i) & 0x01);
 }
 pulseEnable();
}
