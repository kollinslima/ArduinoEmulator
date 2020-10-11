// Kollins G. Lima - 10/11/2020

#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace std;

#define H_FLAG_MASK 0x20
#define S_FLAG_MASK 0x10
#define V_FLAG_MASK 0x08
#define N_FLAG_MASK 0x04
#define Z_FLAG_MASK 0x02
#define C_FLAG_MASK 0x01

typedef uint8_t sbyte;
typedef uint16_t sword16;
typedef __uint32_t spc;

int main(int argc, char *argv[])
{
    //Test shift 8b to 16b
    sbyte dataL = 0xCD;
    sbyte dataH = 0xAB;
    sword16 outData = (dataH<<8) | dataL;
    assert(outData == 0xABCD);

    //Test two complement
    sbyte data = 0x01;
    data = 0x00 - data;
    assert(data == 0xFF);

    //Test relative call
    spc pc = 0x0800;
    spc jmpValue = 0x0001;
    pc += (((__int32_t)jmpValue)<<20)>>20;
    assert(pc == 0x0801);

    pc = 0x0800;
    jmpValue = 0x0FFF;
    pc += (((__int32_t)jmpValue)<<20)>>20;
    assert(pc == 0x07FF);

    return 0;
}

