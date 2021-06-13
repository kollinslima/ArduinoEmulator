//
// Created by kollins on 18/04/21.
//

#include "../../../include/devices/atmega328p/Timer1_ATMega328P.h"

#define SOFIA_TIMER1_ATMEGA328P_TAG "SOFIA TIMER1 ATMEGA328P"

#define T1_MASK             0x20

#define OC1A_MASK           0x02
#define OC1B_MASK           0x04

#define TOP                 0xFFFF
#define TOP8B               0x00FF
#define TOP9B               0x01FF
#define TOP10B              0x03FF
#define BOTTOM              0x0000

Timer1_ATMega328P::Timer1_ATMega328P(DataMemory_ATMega328P &dataMemory) :
        Timer_ATMega328P(dataMemory) {
    oldPIND = datMem.buffer[PIND_ADDR];

    endOfScale      = TOP;
    top             = endOfScale;
    bottom          = BOTTOM;
    outARegAddr     = PORTB_ADDR;
    outBRegAddr     = PORTB_ADDR;
    tccrxAAddr      = TCCR1A_ADDR;
    tccrxBAddr      = TCCR1B_ADDR;
    ocxaMask        = OC1A_MASK;
    ocxbMask        = OC1B_MASK;

    readHigh = 0x00;
}

void Timer1_ATMega328P::prepare() {
    Timer_ATMega328P::prepare();

    matchA = datMem.buffer[TCCR1C_ADDR] & FOCXA_MASK;
    matchB = datMem.buffer[TCCR1C_ADDR] & FOCXB_MASK;

    progress = datMem.buffer[TCNT1H_ADDR];
    progress = (progress << 8) | datMem.buffer[TCNT1L_ADDR];
}

void Timer1_ATMega328P::operate() {
    (this->*mode[((tccrxbReg >> 1) & WGM_TCCR1B_MASK) | (tccrxaReg & WGM_TCCR1A_MASK)])();
}

void Timer1_ATMega328P::writeBack() {
    datMem.buffer[TIFR1_ADDR] = interrFlags;
    datMem.buffer[TCNT1L_ADDR] = progress;
    datMem.buffer[TCNT1H_ADDR] = (progress >> 8);
}

bool Timer1_ATMega328P::clockSource_011() {
    //Prescaler 64
    return !((++clockCount) & PRESCALER_64_MASK);
}

bool Timer1_ATMega328P::clockSource_100() {
    //Prescaler 256
    return !((++clockCount) & PRESCALER_256_MASK);
}

bool Timer1_ATMega328P::clockSource_101() {
    //Prescaler 1024
    return !((++clockCount) & PRESCALER_1024_MASK);
}

bool Timer1_ATMega328P::clockSource_110() {
    bool ret = false;
    sbyte newPIND = datMem.buffer[PIND_ADDR];
    if ((oldPIND & (~newPIND)) & T1_MASK) {
        ret = true;
    }
    oldPIND = newPIND;
    return ret;
}

bool Timer1_ATMega328P::clockSource_111() {
    bool ret = false;
    sbyte newPIND = datMem.buffer[PIND_ADDR];
    if (((~oldPIND) & newPIND) & T1_MASK) {
        ret = true;
    }
    oldPIND = newPIND;
    return ret;
}

void Timer1_ATMega328P::normal() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP;
    top = endOfScale;

    Timer_ATMega328P::normal();
}

void Timer1_ATMega328P::pwmPhaseCorrect1() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP8B;
    top = endOfScale;

    Timer_ATMega328P::pwmPhaseCorrect1();

    if (progress == top) {
        //Update double buffer on TOP
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseCorrect2() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP9B;
    top = endOfScale;

    Timer_ATMega328P::pwmPhaseCorrect2();

    if (progress == top) {
        //Update double buffer on TOP
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseCorrect3() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP10B;
    top = endOfScale;

    Timer_ATMega328P::pwmPhaseCorrect3();

    if (progress == top) {
        //Update double buffer on TOP
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::ctc1() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP;
    top = ocrxa;

    Timer_ATMega328P::ctc1();
}

void Timer1_ATMega328P::fastPWM1() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP8B;
    top = endOfScale;

    Timer_ATMega328P::fastPWM1();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::fastPWM2() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP9B;
    top = endOfScale;

    Timer_ATMega328P::fastPWM2();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::fastPWM3() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP10B;
    top = endOfScale;

    Timer_ATMega328P::fastPWM3();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseAndFreqCorrect1() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    top = datMem.buffer[ICR1H_ADDR];
    top = (top << 8) | datMem.buffer[ICR1L_ADDR];

    endOfScale = TOP;

    Timer_ATMega328P::pwmPhaseAndFreqCorrect1();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseAndFreqCorrect2() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP;
    top = ocrxa;

    Timer_ATMega328P::pwmPhaseAndFreqCorrect2();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseCorrect4() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    top = datMem.buffer[ICR1H_ADDR];
    top = (top << 8) | datMem.buffer[ICR1L_ADDR];

    endOfScale = TOP;

    Timer_ATMega328P::pwmPhaseCorrect4();

    if (progress == top) {
        //Update double buffer on TOP
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::pwmPhaseCorrect5() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP;
    top = ocrxa;

    Timer_ATMega328P::pwmPhaseCorrect5();

    if (progress == top) {
        //Update double buffer on TOP
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::ctc2() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    top = datMem.buffer[ICR1H_ADDR];
    top = (top << 8) | datMem.buffer[ICR1L_ADDR];

    endOfScale = TOP;

    Timer_ATMega328P::ctc2();
}

void Timer1_ATMega328P::fastPWM4() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    top = datMem.buffer[ICR1H_ADDR];
    top = (top << 8) | datMem.buffer[ICR1L_ADDR];

    endOfScale = TOP;

    Timer_ATMega328P::fastPWM4();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}

void Timer1_ATMega328P::fastPWM5() {
    ocrxa = datMem.buffer[OCR1AH_ADDR];
    ocrxa = (ocrxa << 8) | datMem.buffer[OCR1AL_ADDR];

    ocrxb = datMem.buffer[OCR1BH_ADDR];
    ocrxb = (ocrxb << 8) | datMem.buffer[OCR1BL_ADDR];

    endOfScale = TOP;
    top = ocrxa;

    Timer_ATMega328P::fastPWM5();

    if (progress == BOTTOM) {
        //Update double buffer at the BOTTOM
        datMem.buffer[OCR1AH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AH];
        datMem.buffer[OCR1AL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1AL];
        datMem.buffer[OCR1BH_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BH];
        datMem.buffer[OCR1BL_ADDR] = datMem.doubleBuffer[DOUBLE_BUFFER_OCR1BL];
    }
}