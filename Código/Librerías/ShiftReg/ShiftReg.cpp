/*
 ShiftReg.cpp - Library for using Mayhew Labs' Mux Shield.
 Created by Mark Mayhew, December 29, 2012.
 Released into the public domain.
 */

#include "Arduino.h"
#include "ShiftReg.h"

int _shiftReg1[16]={0};
int _shiftReg2[16]={0};
int _shiftReg3[16]={0};

ShiftReg::ShiftReg(int SRCLK, int S1, int S2, int LATCH, int OUTMD,int IOS1, int IOS2, int IOLATCH, int SERIAL_OUT, int IO2, int IO3)
{
    _SRCLK = SRCLK;
    _S1 = S1;
    _S2 = S2;
    _LATCH = LATCH;
    _OUTMD = OUTMD; 
    _IOS1 = IOS1; 
    _IOS2 = IOS2;
    _IOS3 = IOLATCH;
    _SERIAL_OUT = SERIAL_OUT; 
    _IO2 = IO2;
    _IO3 = IO3;
    
    pinMode(_SRCLK,OUTPUT);
    pinMode(_S1,OUTPUT);
    pinMode(_S2,OUTPUT);
    pinMode(_LATCH,OUTPUT);
    pinMode(_OUTMD,OUTPUT);
    digitalWrite(_OUTMD,LOW);
    pinMode(_IOS1,OUTPUT);
    pinMode(_IOS2,OUTPUT);
    pinMode(_IOS3,OUTPUT);
}

ShiftReg::ShiftReg()
{
    _SRCLK = 9;
    _LATCH = 8;
	_OUTMD = 7; 
	_SERIAL_OUT = 6; 
	
    _S1 = 4;
    _S2 = 5;
    _IOS1 = 10; 
    _IOS2 = 11;
    _IOS3 = 12;

    _IO2 = A1;
    _IO3 = A2;
        
    pinMode(_SRCLK,OUTPUT);
    pinMode(_S1,OUTPUT);
    pinMode(_S2,OUTPUT);
    pinMode(_LATCH,OUTPUT);
    pinMode(_OUTMD,OUTPUT);
    digitalWrite(_OUTMD,LOW);
    pinMode(_IOS1,OUTPUT);
    pinMode(_IOS2,OUTPUT);
    pinMode(_IOS3,OUTPUT);
    
    
}

void ShiftReg::setMode(int mux, int mode) 
{
    switch (mux) {
        case 1:
            switch (mode) {
                case DIGITAL_IN:
                    pinMode(_SERIAL_OUT,INPUT);
                    digitalWrite(_IOS1,LOW);
                    break;
                case DIGITAL_IN_PULLUP:
                    pinMode(_SERIAL_OUT,INPUT_PULLUP);
                    digitalWrite(_IOS1,LOW);
                    break;
                case DIGITAL_OUT:
                    pinMode(_SERIAL_OUT,OUTPUT);
                    digitalWrite(_IOS1,HIGH);
                    break;
                case ANALOG_IN:
                    digitalWrite(_IOS1,LOW);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            switch (mode) {
                case DIGITAL_IN:
                    pinMode(_IO2,INPUT);
                    digitalWrite(_IOS2,LOW);
                    break;
                case DIGITAL_IN_PULLUP:
                    pinMode(_IO2,INPUT_PULLUP);
                    digitalWrite(_IOS2,LOW);
                    break;
                case DIGITAL_OUT:
                    pinMode(_IO2,OUTPUT);
                    digitalWrite(_IOS2,HIGH);
                    break;
                case ANALOG_IN:
                    digitalWrite(_IOS2,LOW);
                    break;
                default:
                    break;
            }
            break;
        case 3:
            switch (mode) {
                case DIGITAL_IN:
                    pinMode(_IO3,INPUT);
                    digitalWrite(_IOS3,LOW);
                    break;
                case DIGITAL_IN_PULLUP:
                    pinMode(_IO3,INPUT_PULLUP);
                    digitalWrite(_IOS3,LOW);
                    break;
                case DIGITAL_OUT:
                    pinMode(_IO3,OUTPUT);
                    digitalWrite(_IOS3,HIGH);
                    break;
                case ANALOG_IN:
                    digitalWrite(_IOS3,LOW);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

}

void ShiftReg::digitalWriteMS(int mux, int chan, int val)
{
    int i;
    
    digitalWrite(_LATCH,LOW);                              //LATCH here is LCLK
    digitalWrite(_OUTMD,HIGH);                          //set to output mode
    switch (mux) {
        case 1:
            _shiftReg1[chan] = val;                     //store value until updated again
            
            for (i=15; i>=0; i--) {
                digitalWrite(_SRCLK,LOW);                  //SRCLK here is i/o1 _sclk
                digitalWrite(_SERIAL_OUT,_shiftReg1[i]);       //put value
                digitalWrite(_SRCLK,HIGH);                 //lactch in value
            }
            break;
        case 2:
            _shiftReg2[chan] = val;                     //store value until updated again
            
            for (i=15; i>=0; i--) {
                digitalWrite(_S1,LOW);                  //S1 here is i/o2 _sclk
                digitalWrite(_IO2,_shiftReg2[i]);       //put value
                digitalWrite(_S1,HIGH);                 //lactch in value
            }
            break;
        case 3:
            _shiftReg3[chan] = val;                     //store value until updated again
            
            for (i=15; i>=0; i--) {
                digitalWrite(_S2,LOW);                  //S2 here is i/o3 _sclk
                digitalWrite(_IO3,_shiftReg3[i]);       //put value
                digitalWrite(_S2,HIGH);                 //lactch in value
            }
            break;
        default:
            break;   
    }
    digitalWrite(_LATCH,HIGH);                     //latch in ALL values
    digitalWrite(_OUTMD,LOW);                   //Exit output mode
    
}

int ShiftReg::digitalReadMS(int mux, int chan)
{
    digitalWrite(_OUTMD,LOW);   //Set outmode off (i.e. set as input mode)
    int val;
    switch (mux) {
        case 1:
            digitalWrite(_SRCLK, (chan&1));    
            digitalWrite(_S1, (chan&3)>>1); 
            digitalWrite(_S2, (chan&7)>>2); 
            digitalWrite(_LATCH, (chan&15)>>3); 

            val = digitalRead(_SERIAL_OUT); 
            break;
        case 2:
            digitalWrite(_SRCLK, (chan&1));    
            digitalWrite(_S1, (chan&3)>>1); 
            digitalWrite(_S2, (chan&7)>>2); 
            digitalWrite(_LATCH, (chan&15)>>3); 
 
            val = digitalRead(_IO2); 
            break;
        case 3:
            digitalWrite(_SRCLK, (chan&1));    
            digitalWrite(_S1, (chan&3)>>1); 
            digitalWrite(_S2, (chan&7)>>2); 
            digitalWrite(_LATCH, (chan&15)>>3); 

            val = digitalRead(_IO3); 
            break;
        default:
            break;
    }
    return val;
}

int ShiftReg::analogReadMS(int mux, int chan)
{
    digitalWrite(_OUTMD,LOW);
    int val;

    digitalWrite(_SRCLK, (chan&1));    
    digitalWrite(_S1, (chan&3)>>1); 
    digitalWrite(_S2, (chan&7)>>2); 
    digitalWrite(_LATCH, (chan&15)>>3); 
    
    switch (mux) {
        case 1:
            val = analogRead(_SERIAL_OUT); 
            break;
        case 2:
            val = analogRead(_IO2); 
            break;
        case 3:
            val = analogRead(_IO3); 
            break;
        default:
            break;
    }
    return val;
}