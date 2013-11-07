/*
* Filename: InstructionInfo.h
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: information about instruction
*              (opcode, number and types of
*              operands, subset, etc)
*
*/

#pragma once
#ifndef __INSTRUCTIONINFO_H__
#define __INSTRUCTIONINFO_H__

typedef struct InstructionInfo_t
{
	uint8_t length;
	OpCode opcode;
	Mnemonic mnemonic;
	uint8_t hasModRM : 1;
	uint8_t hasSIB   : 1;
	uint8_t hasSeg   : 1;
	uint8_t hasDisp  : 1;
	uint8_t hasImm   : 1;
	uint8_t hasREX   : 1;
	uint8_t hasVEX2  : 1;
	uint8_t hasVEX3  : 1;
	uint8_t hasXOP   : 1;
	uint8_t sizeDisp;
	uint8_t sizeImm;
	uint16_t seg;
	ModRMu ModRM;
	SIBu SIB;
	REXu REX;
	VEX2u VEX2;
	VEX3u VEX3;
	XOPu XOP;
	uint8_t nOperands;
	Operand operands[4];
	uint64_t disp;
	uint64_t imm;
	uint8_t nPrefixes;
	Prefix prefixes[MAX_PREFIXES];
	uint8_t bytes[16];
	InstructionSet set;
}
InstructionInfo;

#endif /* __INSTRUCTIONINFO_H__ */
