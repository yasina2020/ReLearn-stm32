#include "sys.h"
#include "chfont.h"

//PCtolcd2002 ����->����16 ����������ͬOLEDʵ�顣
const u8 tfont16[][16]=
{

{0x00,0x00,0x04,0x01,0x04,0x02,0x24,0x02,0x1C,0x0C,0x04,0x30,0x7F,0xC0,0x04,0x00},
{0x04,0x01,0x04,0xC1,0x04,0x31,0x04,0x09,0x04,0x01,0x07,0xFE,0x00,0x00,0x00,0x00},/*"?",0*/
{0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x08,0x00,0x10,0x00,0x60,0x03,0x80},
{0x3F,0x00,0x00,0xC0,0x00,0x30,0x00,0x08,0x00,0x04,0x00,0x02,0x00,0x01,0x00,0x00},/*"?",1*/
{0x00,0x00,0x00,0x00,0x3F,0xFF,0x22,0x41,0x22,0x41,0x22,0x42,0x22,0x42,0x22,0x42},
{0x23,0xC0,0x22,0x78,0x22,0x44,0x22,0x42,0x26,0x41,0x18,0x41,0x00,0x4F,0x00,0x00},/*"?",2*/
{0x00,0x00,0x00,0x1F,0x3F,0xE0,0x22,0x21,0x22,0x21,0x3F,0xFF,0x00,0x00,0x3F,0xFF},
{0x21,0x81,0x21,0x61,0x25,0x1A,0x25,0x0C,0x25,0x12,0x3D,0xE2,0x00,0x01,0x00,0x00},/*"?",3*/
{0x00,0x40,0x00,0x40,0x04,0x41,0x08,0xA1,0x10,0xA2,0x38,0xA6,0x15,0xF8,0x13,0x20},
{0x12,0x21,0x15,0x21,0x15,0x21,0x18,0xA1,0x10,0xBF,0x00,0x40,0x00,0x40,0x00,0x00},/*"?",4*/

};

const u8 text_temperature[][16]=
{

{0x00,0x00,0x22,0x03,0x31,0x1C,0x18,0xE1,0x00,0x1F,0x3F,0x21,0x25,0x21,0x25,0x3F},
{0x25,0x21,0x25,0x21,0x25,0x3F,0x25,0x21,0x24,0xA1,0x3F,0x3F,0x00,0x01,0x00,0x00},/*"?",0*/
{0x00,0x01,0x0F,0xFE,0x10,0x01,0x14,0x21,0x14,0x21,0x1F,0x31,0x14,0xAA,0x14,0xA6},
{0x34,0xA4,0x14,0xA6,0x14,0xAA,0x1F,0xA9,0x14,0x31,0x14,0x01,0x10,0x01,0x00,0x00},/*"?",1*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0xF0,0x0F,0xFC,0x18,0x02,0x20,0x01,0x00,0x00,0x00,0x00},/*"(",2*/
{0x00,0x00,0x00,0x00,0x18,0x00,0x15,0xE0,0x1B,0xF8,0x04,0x0C,0x08,0x04,0x08,0x04},
{0x08,0x04,0x08,0x04,0x08,0x04,0x0C,0x08,0x1E,0x18,0x00,0x00,0x00,0x00,0x00,0x00},/*"?",3*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x10,0x01,0x18,0x06,0x07,0xFC,0x01,0xF0,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*")",4*/
};

const u8 text_humidity[][16]=
{
{0x00,0x00,0x02,0x03,0x21,0x5C,0x18,0xA1,0x08,0x41,0x3F,0x39,0x25,0x05,0x25,0xFF},
{0x25,0x01,0x25,0x01,0x25,0xFF,0x25,0x01,0x25,0x09,0x3F,0x31,0x00,0x01,0x00,0x00},/*"?",0*/
{0x00,0x01,0x0F,0xFE,0x10,0x01,0x14,0x21,0x14,0x21,0x1F,0x31,0x14,0xAA,0x14,0xA6},
{0x34,0xA4,0x14,0xA6,0x14,0xAA,0x1F,0xA9,0x14,0x31,0x14,0x01,0x10,0x01,0x00,0x00},/*"?",1*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0xF0,0x0F,0xFC,0x18,0x02,0x20,0x01,0x00,0x00,0x00,0x00},/*"(",2*/
{0x0F,0x00,0x10,0x84,0x0F,0x38,0x00,0xC0,0x07,0x78,0x18,0x84,0x00,0x78,0x00,0x00},/*"%",3*/
{0x10,0x04,0x1F,0xFC,0x11,0x04,0x11,0x00,0x11,0xC0,0x11,0x30,0x0E,0x0C,0x00,0x04},/*"R",4*/
{0x10,0x04,0x1F,0xFC,0x10,0x84,0x00,0x80,0x00,0x80,0x10,0x84,0x1F,0xFC,0x10,0x04},/*"H",5*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x10,0x01,0x18,0x06,0x07,0xFC,0x01,0xF0,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*")",6*/
};

const u8 text_airQuality[][16]=
{
{0x00,0x00,0x0E,0x01,0x10,0xA1,0x11,0x21,0x12,0x21,0x14,0x21,0x10,0x21,0x30,0x3F},
{0x10,0x21,0x14,0x21,0x12,0x21,0x11,0x21,0x10,0xA1,0x13,0x21,0x0C,0x01,0x00,0x00},/*"��",0*/
{0x00,0x00,0x04,0x00,0x09,0x00,0x15,0x00,0x65,0x00,0x25,0x00,0x25,0x00,0x25,0x00},
{0x25,0x00,0x25,0x00,0x25,0x00,0x25,0x00,0x24,0xF8,0x20,0x07,0x00,0x07,0x00,0x00},/*"��",1*/
{0x00,0x00,0x00,0x0F,0x3F,0xF1,0x24,0x01,0x25,0xFD,0x25,0x01,0x25,0x02,0x25,0x04},
{0x3F,0x78,0x25,0x04,0x25,0x04,0x25,0x04,0x25,0x02,0x25,0xFD,0x00,0x01,0x00,0x00},/*"��",2*/
{0x00,0x00,0x02,0x01,0x3A,0x75,0x36,0xB5,0x36,0xB5,0x36,0xB5,0x36,0xB5,0x36,0xB5},
{0x36,0xFF,0x36,0xB5,0x36,0xB5,0x36,0xB5,0x3E,0xB5,0x02,0x75,0x02,0x01,0x00,0x00},/*"��",3*/
};

const u8 text_airPressure[][16]=
{
{0x00,0x00,0x04,0x00,0x09,0x00,0x15,0x00,0x65,0x00,0x25,0x00,0x25,0x00,0x25,0x00},
{0x25,0x00,0x25,0x00,0x25,0x00,0x25,0x00,0x24,0xF8,0x20,0x07,0x00,0x07,0x00,0x00},/*"?",0*/
{0x00,0x00,0x1F,0xFF,0x20,0x00,0x20,0x00,0x20,0x01,0x20,0x81,0x20,0x81,0x20,0x81},
{0x2F,0xFE,0x20,0x81,0x20,0xC1,0x20,0xB1,0x20,0x8D,0x20,0x01,0x00,0x00,0x00,0x00},/*"?",1*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0xF0,0x0F,0xFC,0x18,0x02,0x20,0x01,0x00,0x00,0x00,0x00},/*"(",2*/
{0x10,0x04,0x1F,0xFC,0x10,0x84,0x10,0x80,0x10,0x80,0x10,0x80,0x0F,0x00,0x00,0x00},/*"P",3*/
{0x00,0x00,0x00,0x98,0x01,0x24,0x01,0x44,0x01,0x44,0x01,0x44,0x00,0xFC,0x00,0x04},/*"a",4*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x10,0x01,0x18,0x06,0x07,0xFC,0x01,0xF0,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*")",5*/
};

const u8 text_altitude[][16]=
{
{0x00,0x00,0x22,0x01,0x31,0x8E,0x00,0x70,0x04,0x40,0x18,0xFC,0x67,0x44,0x24,0x44},
{0x24,0x64,0x27,0xDD,0x24,0x45,0x24,0x45,0x24,0x45,0x27,0xFE,0x20,0x44,0x00,0x00},/*"?",0*/
{0x00,0x00,0x04,0x21,0x04,0x21,0x3F,0xFE,0x04,0x42,0x00,0x84,0x04,0x18,0x04,0x61},
{0x7F,0x81,0x05,0x62,0x05,0x14,0x15,0x18,0x14,0xA4,0x0C,0xC2,0x04,0x01,0x00,0x00},/*"?",1*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x03,0xF0,0x0F,0xFC,0x18,0x02,0x20,0x01,0x00,0x00,0x00,0x00},/*"(",2*/
{0x01,0x04,0x01,0xFC,0x01,0x04,0x01,0x00,0x01,0xFC,0x01,0x04,0x01,0x00,0x00,0xFC},/*"m",3*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x10,0x01,0x18,0x06,0x07,0xFC,0x01,0xF0,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*")",4*/
};

const u8 text_GYMCU680[][24]=
{
{0x00,0x00,0x00,0x00,0x3F,0x80,0x01,0xFF,0xE0,0x03,0x80,0x70,0x06,0x00,0x18,0x04,0x00,0x08,0x04,0x02,0x08,0x04,0x02,0x08},
{0x02,0x03,0xF0,0x07,0x83,0xF0,0x00,0x02,0x00,0x00,0x02,0x00},/*"G",0*/
{0x04,0x00,0x00,0x06,0x00,0x00,0x07,0x80,0x00,0x07,0xE0,0x08,0x04,0x7C,0x08,0x00,0x1F,0xF8,0x00,0x07,0xF8,0x00,0x18,0x08},
{0x04,0xE0,0x08,0x07,0x00,0x00,0x06,0x00,0x00,0x04,0x00,0x00},/*"Y",1*/
{0x04,0x00,0x08,0x07,0xFF,0xF8,0x07,0x80,0x08,0x07,0xFC,0x00,0x00,0x7F,0xC0,0x00,0x03,0xF8,0x00,0x07,0xC0,0x00,0x78,0x00},
{0x07,0x80,0x08,0x07,0xFF,0xF8,0x07,0xFF,0xF8,0x04,0x00,0x08},/*"M",2*/
{0x00,0x00,0x00,0x00,0x3F,0x80,0x01,0xFF,0xE0,0x03,0x80,0x70,0x02,0x00,0x18,0x04,0x00,0x08,0x04,0x00,0x08,0x04,0x00,0x08},
{0x04,0x00,0x10,0x06,0x00,0x20,0x07,0x80,0xC0,0x00,0x00,0x00},/*"C",3*/
{0x04,0x00,0x00,0x07,0xFF,0xE0,0x07,0xFF,0xF0,0x04,0x00,0x18,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08,0x00,0x00,0x08},
{0x00,0x00,0x08,0x04,0x00,0x10,0x07,0xFF,0xE0,0x04,0x00,0x00},/*"U",4*/
{0x00,0x00,0x00,0x00,0x3F,0x80,0x01,0xFF,0xE0,0x03,0x84,0x30,0x02,0x08,0x18,0x04,0x10,0x08,0x04,0x10,0x08,0x04,0x10,0x08},
{0x07,0x18,0x10,0x03,0x0F,0xF0,0x00,0x07,0xC0,0x00,0x00,0x00},/*"6",5*/
{0x00,0x00,0x00,0x01,0xE1,0xE0,0x03,0xF7,0xF0,0x06,0x34,0x10,0x04,0x18,0x08,0x04,0x18,0x08,0x04,0x0C,0x08,0x04,0x0C,0x08},
{0x06,0x16,0x18,0x03,0xF3,0xF0,0x01,0xC1,0xE0,0x00,0x00,0x00},/*"8",6*/
{0x00,0x00,0x00,0x00,0x7F,0x80,0x01,0xFF,0xE0,0x03,0x80,0x70,0x06,0x00,0x18,0x04,0x00,0x08,0x04,0x00,0x08,0x06,0x00,0x18},
{0x03,0x80,0x70,0x01,0xFF,0xE0,0x00,0x7F,0x80,0x00,0x00,0x00},/*"0",7*/
{0x00,0x00,0x00,0x01,0x80,0xC0,0x01,0x83,0x80,0x01,0x9C,0x00,0x3F,0xFF,0xFF,0x01,0xB0,0x00,0x01,0x8E,0x00,0x00,0x03,0x21},
{0x0C,0x00,0x21,0x0C,0xFF,0x21,0x0C,0x99,0x23,0x3E,0x99,0x22,0x0C,0x99,0x26,0x0C,0x99,0x2C,0x0C,0x99,0xF8,0x0C,0x99,0x20},
{0x0C,0x99,0x30,0x3E,0x99,0x28,0x0C,0x99,0x24,0x0C,0x99,0x22,0x0C,0xFF,0x23,0x0C,0x00,0x21,0x00,0x00,0x21,0x00,0x00,0x00},/*"?",8*/
{0x00,0x00,0x00,0x00,0x40,0x04,0x00,0x40,0x0C,0x00,0x40,0x08,0x1F,0xFF,0xF8,0x00,0x40,0x10,0x00,0x40,0x31,0x00,0x46,0x23},
{0x02,0x06,0x62,0x02,0x06,0x04,0x02,0x06,0x18,0x02,0x06,0x30,0x02,0x06,0xE0,0x3F,0xFF,0x00,0x02,0x06,0x00,0x02,0x07,0xC0},
{0x02,0x06,0x70,0x02,0x06,0x18,0x02,0x06,0x0C,0x03,0xFE,0x06,0x00,0x06,0x03,0x00,0x06,0x01,0x00,0x06,0x00,0x00,0x00,0x00},/*"?",9*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

const u8 text_bottom1[][24]=	//����
{
{0x00,0x00,0x00,0x00,0xC0,0x04,0x00,0xC0,0x04,0x00,0xC0,0x08,0x1F,0xFF,0xF8,0x00,0xC0,0x10,0x00,0xC0,0x20,0x00,0x40,0x60},
{0x03,0xF8,0x00,0x02,0x05,0xFF,0x32,0x85,0x11,0x1E,0x45,0x11,0x0A,0x25,0x11,0x02,0x05,0x11,0x02,0x05,0x11,0x03,0xFD,0x11},
{0x06,0x35,0x11,0x1A,0x65,0x11,0x32,0xC5,0x11,0x02,0x85,0x11,0x02,0x05,0xFF,0x03,0xFC,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"?",0*/
{0x00,0x00,0x00,0x02,0x00,0x03,0x02,0x00,0x0E,0x02,0x00,0x38,0x02,0x01,0xE0,0x3F,0xFF,0x00,0x02,0x00,0x01,0x02,0x00,0x01},
{0x02,0x00,0x01,0x02,0x00,0x01,0x02,0x00,0x03,0x03,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x08,0x00,0x01},
{0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x0F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"?",1*/
};

const u8 text_bottom2[][24]=	//��С
{
{0x00,0x00,0x00,0x04,0x00,0x0C,0x06,0x00,0x38,0x03,0x80,0xE0,0x00,0xC7,0x83,0x00,0x04,0x1E,0x00,0x03,0xF0,0x07,0xFE,0x00},
{0x04,0x00,0x00,0x0C,0x8F,0xE0,0x0C,0x88,0x11,0x0C,0x88,0x11,0x0C,0x88,0x12,0x0C,0x88,0x16,0x0C,0x8F,0xF4,0x0C,0x00,0x08},
{0x3F,0xF8,0x10,0x0C,0x0F,0xE0,0x0C,0x00,0xF0,0x3C,0x03,0x8C,0x1C,0x1E,0x03,0x07,0xF0,0x03,0x00,0x00,0x3E,0x00,0x00,0x00},/*"?",0*/
{0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0xE0,0x00,0x03,0x80,0x00,0x1E,0x00,0x01,0xF0,0x00,0x00,0x00,0x02,0x00,0x00,0x01},
{0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x1F,0xFF,0xFF,0x1F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x78,0x00,0x00,0x0F,0x00,0x00,0x01,0xF0,0x00,0x00,0x18,0x00,0x00,0x00},/*"?",1*/
};
