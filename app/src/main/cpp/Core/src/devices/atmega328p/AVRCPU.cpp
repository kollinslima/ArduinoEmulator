//
// Created by kollins on 19/09/20.
//

#include <cstdlib>
#include "../../../include/devices/atmega328p/AVRCPU.h"
#include "../../../include/CommonCore.h"

#define INSTRUCTION_ADC_MASK  0x1C00
#define INSTRUCTION_ADD  1
#define INSTRUCTION_ADIW  2
#define INSTRUCTION_AND  3
#define INSTRUCTION_ANDI  4
#define INSTRUCTION_ASR  5
#define INSTRUCTION_BCLR  6
#define INSTRUCTION_BLD  7
#define INSTRUCTION_BRBC  8
#define INSTRUCTION_BRBS  9
#define INSTRUCTION_BREAK  10
#define INSTRUCTION_BSET  11
#define INSTRUCTION_BST  12
#define INSTRUCTION_CALL  13
#define INSTRUCTION_CBI  14
#define INSTRUCTION_COM  15
#define INSTRUCTION_CP  16
#define INSTRUCTION_CPC  17
#define INSTRUCTION_CPI  18
#define INSTRUCTION_CPSE  19
#define INSTRUCTION_DEC  20
#define INSTRUCTION_EOR  21
#define INSTRUCTION_FMUL  22
#define INSTRUCTION_FMULS  23
#define INSTRUCTION_FMULSU  24
#define INSTRUCTION_ICALL  25
#define INSTRUCTION_IJMP  26
#define INSTRUCTION_IN  27
#define INSTRUCTION_INC  28
#define INSTRUCTION_JMP  29
#define INSTRUCTION_LD_X_POST_INCREMENT  30
#define INSTRUCTION_LD_X_PRE_INCREMENT  31
#define INSTRUCTION_LD_X_UNCHANGED  32
#define INSTRUCTION_LD_Y_POST_INCREMENT  33
#define INSTRUCTION_LD_Y_PRE_INCREMENT  34
#define INSTRUCTION_LD_Y_UNCHANGED  35
#define INSTRUCTION_LD_Z_POST_INCREMENT  36
#define INSTRUCTION_LD_Z_PRE_INCREMENT  37
#define INSTRUCTION_LD_Z_UNCHANGED  38
#define INSTRUCTION_LDD_Y  39
#define INSTRUCTION_LDD_Z  40
#define INSTRUCTION_LDI  41 //LDI - SER
#define INSTRUCTION_LDS  42
#define INSTRUCTION_LPM_Z_POST_INCREMENT  43
#define INSTRUCTION_LPM_Z_UNCHANGED_DEST_R0  44
#define INSTRUCTION_LPM_Z_UNCHANGED  45
#define INSTRUCTION_LSR  46
#define INSTRUCTION_MOV  47
#define INSTRUCTION_MOVW  48
#define INSTRUCTION_MUL  49
#define INSTRUCTION_MULS  50
#define INSTRUCTION_MULSU  51
#define INSTRUCTION_NEG  52
#define INSTRUCTION_NOP  53
#define INSTRUCTION_OR  54
#define INSTRUCTION_ORI  55
#define INSTRUCTION_OUT  56
#define INSTRUCTION_POP  57
#define INSTRUCTION_PUSH  58
#define INSTRUCTION_RCALL  59
#define INSTRUCTION_RET  60
#define INSTRUCTION_RETI  61
#define INSTRUCTION_RJMP  62
#define INSTRUCTION_ROR  63
#define INSTRUCTION_SBC  64
#define INSTRUCTION_SBCI  65
#define INSTRUCTION_SBI  66
#define INSTRUCTION_SBIC  67
#define INSTRUCTION_SBIS  68
#define INSTRUCTION_SBIW  69
#define INSTRUCTION_SBRC  70
#define INSTRUCTION_SBRS  71
#define INSTRUCTION_SLEEP  72
#define INSTRUCTION_SPM  73
#define INSTRUCTION_ST_X_POST_INCREMENT  74
#define INSTRUCTION_ST_X_PRE_INCREMENT  75
#define INSTRUCTION_ST_X_UNCHANGED  76
#define INSTRUCTION_ST_Y_POST_INCREMENT  77
#define INSTRUCTION_ST_Y_PRE_INCREMENT  78
#define INSTRUCTION_ST_Y_UNCHANGED  79
#define INSTRUCTION_ST_Z_POST_INCREMENT  80
#define INSTRUCTION_ST_Z_PRE_INCREMENT  81
#define INSTRUCTION_ST_Z_UNCHANGED  82
#define INSTRUCTION_STD_Y  83
#define INSTRUCTION_STD_Z  84
#define INSTRUCTION_STS  85
#define INSTRUCTION_SUB  86
#define INSTRUCTION_SUBI  87
#define INSTRUCTION_SWAP  88
#define INSTRUCTION_WDR  89

#define SOFIA_AVRCPU_TAG "SOFIA AVRCPU CONTROLLER"

AVRCPU::AVRCPU(const ProgramMemory_ATMega328P& programMemory) {
    pc = 0;
    progMem = programMemory;
    setupInstructionDecoder();
}

AVRCPU::~AVRCPU() {
}

void AVRCPU::setupInstructionDecoder() {
    for (int i = 0; i < INSTRUCTION_DECODER_SIZE; ++i) {
        if (!((i & INSTRUCTION_ADC_MASK) ^ INSTRUCTION_ADC_MASK)) {
            instructionDecoder[i] = instructionADC;
            continue;
        }
        instructionDecoder[i] = unknownInstruction;
    }
}

void AVRCPU::run() {
    instructionDecoder[progMem.loadInstruction(pc++)]();
    pc = 0;
}

void AVRCPU::instructionADC() {
//    LOGD(SOFIA_AVRCPU_TAG, "Instruction ADC");
}

void AVRCPU::unknownInstruction() {
//    LOGD(SOFIA_AVRCPU_TAG, "Unknown Instruction");
}


