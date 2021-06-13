//
// Created by kollins on 19/09/20.
//

#ifndef PROJECTSOFIA_AVRCPU_H
#define PROJECTSOFIA_AVRCPU_H

#include "../../generic/GenericCPU.h"
#include "../../generic/GenericMemory.h"
#include "../../generic/GenericProgramMemory.h"
#include "../memory/GenericAVRDataMemory.h"

#define INSTRUCTION_DECODER_SIZE 65536 //2^16

class AVRCPU : public GenericCPU {

public:
    typedef enum {
        AVR,
        AVRe,
        AVRxm,
        AVRxt,
        AVRrc,
    } Core;

    typedef enum {
        PC09,
        PC16,
        PC22,
    } PCBits;

    AVRCPU(GenericProgramMemory& programMemory, GenericAVRDataMemory& dataMemory, Core core = AVRCPU::Core::AVR);
    virtual ~AVRCPU();

    void setPCSize(PCBits pcBits);
    void setIOBaseAddr(smemaddr16 addr);

protected:
    typedef void (AVRCPU::*Instruction)();

    Instruction instructionDecoder[INSTRUCTION_DECODER_SIZE];

    GenericProgramMemory& progMem;
    GenericAVRDataMemory& datMem;
    Core core;
    PCBits pcBits;
    smemaddr16 ioBaseAddr;

    short needExtraCycles;
    bool canInterrupt;
    spc32 interAddr;

    sword16 instruction;
    smemaddr16 sregAddr;
    smemaddr16 stackLAddr, stackHAddr;

    /**********Auxiliar for processing************/
    sbyte regD, regR, sreg, result;
    smemaddr16 regDAddr, regRAddr, wbAddr;

    sbyte offset, dataL, dataH;
    smemaddr16 dataLAddr, dataHAddr;
    sword16 outData, immediate;
    sword16 testJMP_CALL, testLDS_STS;

    smemaddr16 stackPointer;
    spc32 jumpValue;

    sbyte regD_and_regR;
    sbyte notRegD_and_regR;
    sbyte regR_and_result;
    sbyte immediate_and_result;
    sbyte not_result, not_regD;
    sbyte hc_flag;
    /*********************************************/

    void setupInstructionDecoder();

    void instruction_ADC_ROL();

    void instruction_ADD_LSL();

    void instruction_ADIW();

    void instruction_AND_TST();

    void instruction_ANDI_CBR();

    void instruction_ASR();

    void instruction_BCLR_CLC_CLH_CLI_CLN_CLS_CLT_CLV_CLZ();

    void instruction_BLD();

    void instruction_BREAK();

    void instruction_BRBC_BRCC_BRGE_BRHC_BRID_BRNE_BRPL_BRSH_BRTC_BRVC();

    void instruction_BRBS_BRCS_BREQ_BRHS_BRIE_BRLO_BRLT_BRMI_BRTS_BRVS();

    void instruction_BSET_SEC_SEH_SEI_SEN_SES_SET_SEV_SEZ();

    void instruction_BST();

    virtual void instruction_CALL();

    virtual void instruction_CBI();

    void instruction_CLR_EOR();

    void instruction_COM();

    void instruction_CP();

    void instruction_CPC();

    void instruction_CPI();

    void instruction_CPSE();

    void instruction_DEC();

    void instruction_DES();

    void instruction_EICALL();

    virtual void instruction_EIJMP();

    virtual void instruction_ELPM1();
    virtual void instruction_ELPM2();
    virtual void instruction_ELPM3();

    void instruction_FMUL();

    void instruction_FMULS();

    void instruction_FMULSU();

    virtual void instruction_ICALL();

    void instruction_IJMP();

    void instruction_IN();

    void instruction_INC();

    void instruction_JMP();

    void instruction_LAC();

    void instruction_LAS();

    void instruction_LAT();

    virtual void instruction_LD_X_UNCHANGED();
    virtual void instruction_LD_X_POST_INCREMENT();
    virtual void instruction_LD_X_PRE_DECREMENT();

    virtual void instruction_LD_Y_UNCHANGED();
    virtual void instruction_LD_Y_POST_INCREMENT();
    virtual void instruction_LD_Y_PRE_DECREMENT();
    virtual void instruction_LDD_Y();

    virtual void instruction_LD_Z_UNCHANGED();
    virtual void instruction_LD_Z_POST_INCREMENT();
    virtual void instruction_LD_Z_PRE_DECREMENT();
    virtual void instruction_LDD_Z();

    void instruction_LDI_SER();

    void instruction_LDS();
    void instruction_LDS16();

    void instruction_LPM_Z_UNCHANGED_DEST_R0();
    void instruction_LPM_Z_UNCHANGED();
    void instruction_LPM_Z_POST_INCREMENT();

    void instruction_LSR();

    void instruction_MOV();

    void instruction_MOVW();

    void instruction_MUL();

    void instruction_MULS();

    void instruction_MULSU();

    void instruction_NEG();

    void instruction_NOP();

    void instruction_OR();

    void instruction_ORI_SBR();

    void instruction_OUT();

    void instruction_POP();

    virtual void instruction_PUSH();

    virtual void instruction_RCALL();

    virtual void instruction_RET();

    virtual void instruction_RETI();

    void instruction_RJMP();

    void instruction_ROR();

    void instruction_SBC();

    void instruction_SBCI();

    virtual void instruction_SBI();

    void instruction_SBIC();

    void instruction_SBIS();

    void instruction_SBIW();

    void instruction_SBRC();

    void instruction_SBRS();

    void instruction_SLEEP();

    void instruction_SPM_Z_UNCHANGED();
    void instruction_SPM_POST_INCREMENT();

    virtual void instruction_ST_X_UNCHANGED();
    virtual void instruction_ST_X_POST_INCREMENT();
    virtual void instruction_ST_X_PRE_DECREMENT();

    virtual void instruction_ST_Y_UNCHANGED();
    virtual void instruction_ST_Y_POST_INCREMENT();
    virtual void instruction_ST_Y_PRE_DECREMENT();
    virtual void instruction_STD_Y();

    virtual void instruction_ST_Z_UNCHANGED();
    virtual void instruction_ST_Z_POST_INCREMENT();
    virtual void instruction_ST_Z_PRE_DECREMENT();
    virtual void instruction_STD_Z();

    void instruction_STS();
    void instruction_STS16();

    void instruction_SUB();

    void instruction_SUBI();

    void instruction_SWAP();

    void instruction_WDR();

    void instruction_XCH();

    void unknownInstruction();
};


#endif //PROJECTSOFIA_AVRCPU_H