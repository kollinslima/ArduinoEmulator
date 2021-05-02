//
// Created by kollins on 18/04/21.
//

#include "../../../include/devices/atmega328p/Timer0_ATMega328P.h"

#define T0_MASK             0x10

#define OC0A_MASK           0x40
#define OC0B_MASK           0x20

#define TOP                 0xFF
#define BOTTOM              0x00

Timer0_ATMega328P::Timer0_ATMega328P(DataMemory_ATMega328P &dataMemory) :
        Timer_ATMega328P(dataMemory) {

    oldPIND = datMem.buffer[PIND_ADDR];

    top = TOP;
    bottom = BOTTOM;
    outARegAddr = PORTD_ADDR;
    outBRegAddr = PORTD_ADDR;
    ocxaMask = OC0A_MASK;
    ocxbMask = OC0B_MASK;
}

void Timer0_ATMega328P::run() {
    tccrxbReg = datMem.buffer[TCCR0B_ADDR];
    if ((this->*clockSource[tccrxbReg & CS_MASK])()) {
        tccrxaReg = datMem.buffer[TCCR0A_ADDR];
        (this->*mode[(tccrxbReg & WGM_TCCR0B_MASK) | ((tccrxaReg << 1) & WGM_TCCR0A_MASK)])();
    }
}

bool Timer0_ATMega328P::clockSource_011() {
    //Prescaler 64
    return !((++clockCount) & PRESCALER_64_MASK);
}

bool Timer0_ATMega328P::clockSource_100() {
    //Prescaler 256
    return !((++clockCount) & PRESCALER_256_MASK);
}

bool Timer0_ATMega328P::clockSource_101() {
    //Prescaler 1024
    return !((++clockCount) & PRESCALER_1024_MASK);
}

bool Timer0_ATMega328P::clockSource_110() {
    bool ret = false;
    sbyte newPIND = datMem.buffer[PIND_ADDR];
    if ((oldPIND & (~newPIND)) & T0_MASK) {
        ret = true;
    }
    oldPIND = newPIND;
    return ret;
}

bool Timer0_ATMega328P::clockSource_111() {
    bool ret = false;
    sbyte newPIND = datMem.buffer[PIND_ADDR];
    if (((~oldPIND) & newPIND) & T0_MASK) {
        ret = true;
    }
    oldPIND = newPIND;
    return ret;
}

void Timer0_ATMega328P::normal() {
    interrFlags = 0x00;
    matchA = tccrxbReg & FOCXA_MASK;
    matchB = tccrxbReg & FOCXB_MASK;

    progress = datMem.buffer[TCNT0_ADDR];
    ocrxa = datMem.buffer[OCR0A_ADDR];
    ocrxb = datMem.buffer[OCR0B_ADDR];

    Timer_ATMega328P::normal();

    datMem.buffer[TIFR0_ADDR] = interrFlags;
    datMem.buffer[TCNT0_ADDR] = progress;
}
