/*
* Filename: DisAsm.c
* Author:   DisAsmCompany
* Date:     21/09/2013
*
* Description: DisAsm API implementation
*              
*              
*
*/

#include "DisAsm"
#include "OpCodeMap.h"
#define _STR_ENUM
#undef  __MNEMONIC_H__20CAFD53_E4D1_49A5_88DC_47A54ADFD022__
#undef  __REGISTER_H__8C8FA516_AFA4_402d_B1A2_8040D9312A78__
#include "DisAsm"

typedef struct DisAsmContext_t
{
    HREADER hReader;
    uint8_t size;
    uint8_t currentSize;
    uint8_t error;
	uint8_t ModRMRead;
}
DisAsmContext;

char * DisAsmMnemonicToString(Mnemonic mnemonic)
{
	return MnemonicToString(mnemonic);
}

char * DisAsmRegisterToString(Register reg)
{
	return RegisterToString(reg);
}

static uint8_t Fetch1(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint8_t result = 0;
	if (pInfo->length + 1 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 1);
		result = pInfo->bytes[pInfo->length];
		++pInfo->length;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

static uint16_t Fetch2(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint16_t result = 0;
	if (pInfo->length + 2 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 2);
		result = 
			(pInfo->bytes[pInfo->length + 1] << 8) | 
			(pInfo->bytes[pInfo->length]);
		pInfo->length += 2;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

static uint32_t Fetch4(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint32_t result = 0;
	if (pInfo->length + 4 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 4);
		result =
			(pInfo->bytes[pInfo->length + 3] << 24) | 
			(pInfo->bytes[pInfo->length + 2] << 16) | 
			(pInfo->bytes[pInfo->length + 1] << 8) | 
			(pInfo->bytes[pInfo->length]);
		pInfo->length += 4;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

static uint64_t Fetch8(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	uint64_t result = 0;
	if (pInfo->length +  8 <= kMaxInstruction)
	{
		pContext->error = 0 == ReaderRead(pContext->hReader, pInfo->bytes + pInfo->length, 8);
		result =
			((uint64_t)pInfo->bytes[pInfo->length + 7] << 56) | 
			((uint64_t)pInfo->bytes[pInfo->length + 6] << 48) | 
			((uint64_t)pInfo->bytes[pInfo->length + 5] << 40) | 
			((uint64_t)pInfo->bytes[pInfo->length + 4] << 32) | 
			((uint64_t)pInfo->bytes[pInfo->length + 3] << 24) | 
			((uint64_t)pInfo->bytes[pInfo->length + 2] << 16) | 
			((uint64_t)pInfo->bytes[pInfo->length + 1] << 8) | 
			((uint64_t)pInfo->bytes[pInfo->length]);
		pInfo->length += 8;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

static uint64_t Fetch(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t count)
{
	uint64_t result = 0;
	if (pInfo->length + count <= kMaxInstruction)
	{
		uint8_t i;
		for (i = 0; i < count; ++i)
		{
			result = (result << 8) + Fetch1(pContext, pInfo);
		}
		pInfo->length = pInfo->length + count;
	}
	else
	{
		pContext->error = 1;
	}
	return result;
}

static uint64_t FetchN(DisAsmContext * pContext, InstructionInfo * pInfo, uint8_t count)
{
	uint64_t result = 0;
	switch (count)
	{
	case 1: result = Fetch1(pContext, pInfo); break;
	case 2: result = Fetch2(pContext, pInfo); break;
	case 4: result = Fetch4(pContext, pInfo); break;
	case 8: result = Fetch8(pContext, pInfo); break;
	default: result = Fetch(pContext, pInfo, count); break;
	}
	return result;
}

static OpCodeMapElement * ChooseOpCodeExt(DisAsmContext * pContext, InstructionInfo * pInfo, uint32_t * opcode, OpCodeMapElement * map, uint32_t * ext)
{
	uint32_t index = *opcode & 0xFF;
	uint32_t offset = 0;
	/* check, if opcode has extensions for prefixes 0x66, 0xF2, 0xF3 */
	uint32_t mask = ext[index >> 5];
	if (pInfo->LegacySSEPrefix && (mask & (1 << (index & 0x1F))))
	{
		switch (pInfo->LegacySSEPrefix)
		{
		case 0x66: offset =  8; break;
		case 0xF2: offset = 16; break;
		case 0xF3: offset = 24; break;
		default: break;
		}
		/* in that case, prefix is not a prefix actually, but part of unique opcode */
		*opcode |= (*opcode & 0x00FF0000UL) ? (pInfo->LegacySSEPrefix << 24) : (pInfo->LegacySSEPrefix << 16);
		pInfo->nPrefixes = 0;
		pContext->currentSize = pContext->size;
	}
	index = offset + ((index >> 3) << 5) + (index & 0x07);
	return &map[index];
}

static const uint8_t LegacySSEPrefixes[4] = {0x00, 0x66, 0xF3, 0xF2};

static OpCodeMapElement * ChooseOpCode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	OpCodeMapElement * element = NULL;

	uint8_t byte = Fetch1(pContext, pInfo);
	uint32_t opcode = 0;

	opcode = byte;

	if (8 == pContext->size)
	{
		switch (byte)
		{
		/* REX prefix */
		case 0x40: case 0x41: case 0x42: case 0x43:
		case 0x44: case 0x45: case 0x46: case 0x47:
		case 0x48: case 0x49: case 0x4A: case 0x4B:
		case 0x4C: case 0x4D: case 0x4E: case 0x4F:
			if (pInfo->flags & (kHasREX | kHasVEX2 | kHasVEX3 | kHasXOP3))
			{
				pContext->error = 1;
				return NULL;
			}
			pInfo->flags |= kHasREX;
			pInfo->REX = byte;
			pInfo->REXW = (uint8_t) REX_W(byte);
			pInfo->REXR = (uint8_t) REX_R(byte);
			pInfo->REXX = (uint8_t) REX_X(byte);
			pInfo->REXB = (uint8_t) REX_B(byte);
			return ChooseOpCode(pContext, pInfo);
		}
	}

	switch (opcode)
	{
	/* 2-byte VEX prefix */
	case 0xC5:
		byte = Fetch1(pContext, pInfo);
		if (byte & 0xC0)
		{
			if (pInfo->flags & (kHasREX | kHasVEX2 | kHasVEX3 | kHasXOP3))
			{
				pContext->error = 1;
				return NULL;
			}
			pInfo->VEX2 = byte;
			pInfo->flags |= kHasVEX2;
			pInfo->LegacySSEPrefix = LegacySSEPrefixes[VEX2_pp(pInfo->VEX2)];
			pInfo->vvvv = (uint8_t) VEX2_vvvv(pInfo->VEX2);
			pInfo->REXR = (uint8_t) VEX2_R(pInfo->VEX2);
			opcode = Fetch1(pContext, pInfo);
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapVEXTwoByte0F, OpCodeMapVEXTwoByte0FExt);
		}
		else
		{
			pInfo->ModRM = byte;
			pContext->ModRMRead = 1;
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapOneByte, OpCodeMapOneByteExt);
		}
		pInfo->opcode = opcode;
		pContext->error |= (DB == element->mnemonic) ? 1 : 0;
		return element;
	/* 3-byte VEX prefix */
	case 0xC4:
		byte = Fetch1(pContext, pInfo);
		if (byte & 0xC0)
		{
			if (pInfo->flags & (kHasREX | kHasVEX2 | kHasVEX3 | kHasXOP3))
			{
				pContext->error = 1;
				return NULL;
			}
			pInfo->flags |= kHasVEX3;
			pInfo->VEX3 = byte | (Fetch1(pContext, pInfo) << 8);
			pInfo->LegacySSEPrefix = LegacySSEPrefixes[VEX3_pp(pInfo->VEX3)];
			pInfo->vvvv = (uint8_t) VEX3_vvvv(pInfo->VEX3);
			pInfo->REXW = (uint8_t) VEX3_W(pInfo->VEX3);
			pInfo->REXR = (uint8_t) VEX3_R(pInfo->VEX3);
			pInfo->REXX = (uint8_t) VEX3_X(pInfo->VEX3);
			pInfo->REXB = (uint8_t) VEX3_B(pInfo->VEX3);
			opcode = Fetch1(pContext, pInfo);
			switch (VEX3_mmmmmm(pInfo->VEX3))
			{
			case 0x01: element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapVEXTwoByte0F, OpCodeMapVEXTwoByte0FExt); break;
			case 0x02: element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapVEXThreeByte0F38, OpCodeMapVEXThreeByte0F38Ext); break;
			case 0x03: element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapVEXThreeByte0F3A, OpCodeMapVEXThreeByte0F3AExt); break;
			default: pContext->error = 1; return NULL;
			}
		}
		else
		{
			pInfo->ModRM = byte;
			pContext->ModRMRead = 1;
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapOneByte, OpCodeMapOneByteExt);
		}
		break;
	/* 3-byte XOP prefix */
	case 0x8F:
		if (pInfo->flags & (kHasREX | kHasVEX2 | kHasVEX3 | kHasXOP3))
		{
			pContext->error = 1;
			return NULL;
		}
		pInfo->flags |= kHasXOP3;
		pInfo->XOP3 = Fetch2(pContext, pInfo);
		pInfo->LegacySSEPrefix = LegacySSEPrefixes[XOP3_pp(pInfo->XOP3)];
		pInfo->vvvv = (uint8_t) XOP3_vvvv(pInfo->XOP3);
		pInfo->REXW = (uint8_t) XOP3_W(pInfo->XOP3);
		pInfo->REXR = (uint8_t) XOP3_R(pInfo->XOP3);
		pInfo->REXX = (uint8_t) XOP3_X(pInfo->XOP3);
		pInfo->REXB = (uint8_t) XOP3_B(pInfo->XOP3);
		opcode = Fetch1(pContext, pInfo);
		element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapVEXTwoByte0F, OpCodeMapVEXTwoByte0FExt);
		break;
	/* MVEX */
	//case 0x62:
	//	return ChooseOpCode(pContext, pInfo);
	/* L1OM */
	//case 0xD6:
	//	return ChooseOpCode(pContext, pInfo);
	case 0x0F:
		opcode = (opcode << 8) | Fetch1(pContext, pInfo);
		switch (opcode)
		{
		case 0x0F38:
			opcode = (opcode << 8) | Fetch1(pContext, pInfo);
			/* Three-Byte OpCode Map (OpCodes 0F3800h - 0FF38Fh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapThreeByte0F38, OpCodeMapThreeByte0F38Ext);
			break;
		case 0x0F3A:
			opcode = (opcode << 8) | Fetch1(pContext, pInfo);
			/* Three-Byte OpCode Map (OpCodes 0F3A00h - 0FF3AFh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapThreeByte0F3A, OpCodeMapThreeByte0F3AExt);
			break;
		default:
			/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapTwoByte0F, OpCodeMapTwoByte0FExt);
			break;
		}
		break;
	default:
		/* One-Byte Opcode Map (OpCodes 00h - FFh) */
		if (8 == pContext->size)
		{
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapOneByte64, OpCodeMapOneByte64Ext);
		}
		else
		{
			element = ChooseOpCodeExt(pContext, pInfo, &opcode, OpCodeMapOneByte, OpCodeMapOneByteExt);
		}
		/* handle prefixes */
		switch (element->mnemonic)
		{
		case LOCK:
		case REPNE:
		case REP:
		case PrefixCS:
		case PrefixSS:
		case PrefixDS:
		case PrefixES:
		case PrefixFS:
		case PrefixGS:
		case OperandSize:
		case AddressSize:
			if (pInfo->nPrefixes < kMaxPrefixes)
			{
				if (OperandSize == element->mnemonic)
				{
					pContext->currentSize = pContext->size / 2;
				}
				switch (opcode)
				{
				case 0x66:
					/* 0x66 cannot override other SSE prefixes */
					pInfo->LegacySSEPrefix = pInfo->LegacySSEPrefix ? pInfo->LegacySSEPrefix : opcode; 
					break;
				case 0xF2:
				case 0xF3:
					/* 0xF2 & 0xF3 overrides 0x66 */
					pInfo->LegacySSEPrefix = opcode;
					break;
				default: break;
				}
				pInfo->prefixes[pInfo->nPrefixes].opcode = opcode;
				pInfo->prefixes[pInfo->nPrefixes].mnemonic = element->mnemonic;
				++pInfo->nPrefixes;
				return ChooseOpCode(pContext, pInfo);
			}
			else
			{
				pContext->error = 1;
				return NULL;
			}
		default:
			break;
		}
		break;
	}
	pInfo->opcode = opcode;
	pContext->error |= (DB == element->mnemonic) ? 1 : 0;
	return element;
}

static uint8_t SizeForType(DisAsmContext *pContext, OperandType type)
{
	uint8_t result = 0;
	switch (LOTYPE(type))
	{
	/* byte, regardless of operand size attribute */
	case b: result = 1; break;
	/* word, regardless of operand size attribute */
	case w: result = 2; break;
	/* double-word (4 bytes), regardless of operand size attribute */
	case d: result = 4; break;
	/* quad-word, regardless of operand size attribute */
	case q:
	case oq: result = 8; break;
	/* oct-word, regardless of operand size attribute */
	case o: 
	case pb: case pk: case pi: case pj: case pq: case pw:
	case ps: case ss: case pd: case sd:
		result = 16; break;
	/* word for 16-bit operand size, or double-word for 32-bit and 64-bit operand size */
	case z:
		switch (pContext->currentSize)
		{
		case 2: result = 2; break;
		case 4:
		case 8: result = 4; break;
		default: break;
		}
		break;
	/* word, double-word or quad-word (in 64-bit mode), depending on operand size attribute */
	case v:
		switch (pContext->currentSize)
		{
		case 2: result = 2; break;
		case 4: result = 4; break;
		case 8: result = 8; break;
		default: break;
		}
		break;
    /* double-word or quad-word, depending on operand size attribute */
    case y: result = 8; break;
	case x: result = 32; break;
	case qq: result = 32; break;
	case dq: result = 16; break;
	default: result = 4; break;
	}
	return result;
}

#define REGLINE(size1, size2, size4, size8, size16, size32) \
{size1, size2, 0, size4, 0, 0, 0, size8, 0, 0, 0, 0, 0, 0, 0, size16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, size32},

Register registers[][32] =
{
	/* E */ REGLINE(Reg8, Reg16, Reg32, Reg64, 0, 0)
	/* G */ REGLINE(Reg8, Reg16, Reg32, Reg64, 0, 0)
	/* M */ REGLINE(Reg8, Reg16, Reg32, Reg64, 0, 0)
	/* S */ REGLINE(0, RegSeg, 0, 0, 0, 0)
	/* R */ REGLINE(Reg8, Reg16, Reg32, Reg64, 0, 0)
	/* D */ REGLINE(0, RegDebug, RegDebug, RegDebug, 0, 0)
	/* C */ REGLINE(0, RegControl, RegControl, RegControl, 0, 0)
	/* U */ REGLINE(RegSSE, RegSSE, RegSSE, RegSSE, RegSSE, RegAVX)
	/* V */ REGLINE(RegSSE, RegSSE, RegSSE, RegSSE, RegSSE, RegAVX)
	/* W */ REGLINE(RegSSE, RegSSE, RegSSE, RegSSE, RegSSE, RegAVX)
	/* H */ REGLINE(RegSSE, RegSSE, RegSSE, RegSSE, RegSSE, RegAVX)
	/* P */ REGLINE(RegMMX, RegMMX, RegMMX, RegMMX, RegMMX, RegMMX)
	/* Q */ REGLINE(RegMMX, RegMMX, RegMMX, RegMMX, RegMMX, RegMMX)
	/* N */ REGLINE(RegMMX, RegMMX, RegMMX, RegMMX, RegMMX, RegMMX)
};

static Register RegForType(DisAsmContext * pContext, OperandType type)
{
	OperandType HiType = (HITYPE(type) - E) >> 8;

	return registers[HiType][SizeForType(pContext, type) - 1];
}

static void OperandDecode(DisAsmContext *pContext, InstructionInfo * pInfo, Operand * pOperand)
{
	OperandType type = pOperand->type;
	OperandType HiType = HITYPE(type);
	if (Imm == pOperand->type)
	{
		pInfo->imm = pOperand->reg;
		pInfo->sizeImm = 1;
		return;
	}
	else if (Reg == pOperand->type)
	{
		if (rRegister <= pOperand->reg && pOperand->reg <= rRegister + 7)
		{
			pOperand->reg = (pOperand->reg - rRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->reg += Reg16; break;
            case 4: pOperand->reg += Reg32; break;
            case 8: pOperand->reg += Reg64; break;
            default: break;
            }
		}
		if (eRegister <= pOperand->reg && pOperand->reg <= eRegister + 7)
		{
			pOperand->reg = (pOperand->reg - eRegister);
            switch (pContext->currentSize)
            {
            case 2: pOperand->reg += Reg16; break;
            case 4: pOperand->reg += Reg32; break;
            case 8: pOperand->reg += Reg32; break;
            default: break;
            }
		}
		return;
	}
	else if (Ap == pOperand->type)
	{
		pInfo->flags |= kHasDisp | kHasSeg;
		pInfo->sizeDisp = 4;
        return;
	}
	switch (HiType)
	{
	case M: case R: case E:
	case Q: case W: case U:
		pOperand->type = (MODRM_MOD(pInfo->ModRM) != 3) ? Mem : Reg;
		pOperand->scale = pOperand->hasBase = pOperand->hasIndex = 0;
		pOperand->size = SizeForType(pContext, type);
		if (pInfo->flags & kHasSIB)
		{
			pOperand->hasBase = 1;
			pOperand->hasIndex = 1;
			pOperand->scale = 1 << SIB_SCALE(pInfo->SIB);
			if (4 == (pOperand->index = SIB_INDEX(pInfo->SIB)))
			{
				pOperand->hasIndex = 0;
			}
			if (5 == (pOperand->reg = SIB_BASE(pInfo->SIB)) && 0 == MODRM_MOD(pInfo->ModRM))
			{
				pOperand->hasBase = 0;
			}
		}
		else
		{
			pOperand->hasIndex = 0;
			pOperand->reg = MODRM_RM(pInfo->ModRM);
            pOperand->reg |= pInfo->REXB ? 8 : 0;
			pOperand->hasBase = (5 == MODRM_RM(pInfo->ModRM) && 0 == MODRM_MOD(pInfo->ModRM)) ? 0 : 1;
		}
		if (Mem == pOperand->type)
		{
            switch (pContext->currentSize)
            {
            case 2:
                pOperand->reg |= Reg16;
                pOperand->index |= Reg16;
                break;
            case 4:
                pOperand->reg |= Reg32;
			    pOperand->index |= Reg32;
                break;
            case 8:
                pOperand->reg |= Reg64;
                pOperand->index |= Reg64;
                break;
            default:
                pOperand->reg |= Reg32;
                pOperand->index |= Reg32;
                break;
            }
		}
		else
		{
			pOperand->reg |= RegForType(pContext, type);
		}
		break;
	case P: case S: case V:
	case C: case D: case G:
	case N:
		pOperand->type = Reg;
		pOperand->reg = MODRM_REG(pInfo->ModRM);
        pOperand->reg |= pInfo->REXR ? 8 : 0;
		pOperand->reg |= RegForType(pContext, type);
		break;
	case I: case J:
		pOperand->type = Imm;
		pInfo->flags |= kHasImm;
		pInfo->sizeImm = SizeForType(pContext, type);
		break;
	case O:
		pInfo->flags |= kHasDisp;
		pOperand->type = Mem;
		pOperand->hasBase = pOperand->hasIndex = 0;
		pOperand->size = SizeForType(pContext, type);
		switch (pContext->currentSize)
        {
		case 1: pInfo->sizeDisp = 1; break;
        case 2: pInfo->sizeDisp = 2; break;
        case 4: pInfo->sizeDisp = 4; break;
        case 8: pInfo->sizeDisp = 4; break;
        default:
            break;
        }
		break;
	case H:
		pOperand->type = Reg;
		pOperand->size = SizeForType(pContext, type);
		pOperand->reg = pInfo->vvvv;
		pOperand->reg |= RegForType(pContext, type);
		break;
	default:
		break;
	}
}

static void CopyElementInfo(InstructionInfo * pInfo, OpCodeMapElement * pElement)
{
	pInfo->mnemonic = pElement->mnemonic;
	pInfo->nOperands = OPCOUNT(pElement->type);
	pInfo->operands[0].type = pElement->type[0];
	pInfo->operands[1].type = pElement->type[1];
	pInfo->operands[2].type = pElement->type[2];
	pInfo->operands[3].type = pElement->type[3];
	pInfo->operands[0].reg = pElement->reg[0];
	pInfo->operands[1].reg = pElement->reg[1];
	pInfo->operands[2].reg = pElement->reg[2];
	pInfo->operands[3].reg = pElement->reg[3];
}

static void GroupDecode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	if (GROUP1 <= pInfo->mnemonic && pInfo->mnemonic <= GROUPP)
	{
		uint32_t index = ((pInfo->mnemonic - GROUP1) << 3) + MODRM_REG(pInfo->ModRM);
		OpCodeMapElement * pElement = &OpCodeMapGroup[index];
		if (pElement->type[0])
		{
			CopyElementInfo(pInfo, pElement);
		}
		pInfo->mnemonic = pElement->mnemonic;
		if (pElement->mnemonic == GROUP7_EXT2)
		{
			index = ((pInfo->mnemonic - GROUP1) << 3) + MODRM_RM(pInfo->ModRM);
			pElement = &OpCodeMapGroup[index];
			pInfo->mnemonic = pElement->mnemonic;
		}
		pContext->error |= (DB == pInfo->mnemonic) ? 1 : 0;
	}
}

static void x87Decode(DisAsmContext * pContext, InstructionInfo * pInfo)
{
	if (ESCAPEX87 == pInfo->mnemonic)
	{
		uint32_t index = 0;
		if (3 == MODRM_MOD(pInfo->ModRM))
		{
			index = MODRM_RM(pInfo->ModRM) + (MODRM_REG(pInfo->ModRM) << 3) + ((pInfo->opcode - 0xD7) << 6);
		}
		else
		{
			index = MODRM_REG(pInfo->ModRM) + ((pInfo->opcode - 0xD8) << 3);
		}
		CopyElementInfo(pInfo, &OpCodeMapX87[index]);
		pContext->error |= (DB == pInfo->mnemonic) ? 1 : 0;
	}
}

uint32_t PrintOpCode(uint32_t OpCode)
{
	uint32_t length = 0;
	uint8_t i = 0;
	OpCodeMapElement * pElement = &OpCodeMapOneByte[OpCode];

	char * mnemonic = (char*)MnemonicToString(pElement->mnemonic);
	
	uint8_t nOperands = OPCOUNT(pElement->type);

	switch (pElement->mnemonic)
	{
	case PrefixCS: mnemonic = "CS"; break;
	case PrefixSS: mnemonic = "SS"; break;
	case PrefixDS: mnemonic = "DS"; break;
	case PrefixES: mnemonic = "ES"; break;
	case PrefixFS: mnemonic = "FS"; break;
	case PrefixGS: mnemonic = "GS"; break;
	/* FIXME */
	case _IN : mnemonic = "IN"; break;
	case _INT: mnemonic = "INT"; break;
	case _OUT: mnemonic = "OUT"; break;
	default: break;
	}
	length += xstrlen(mnemonic);

	ConsoleIOPrint(mnemonic);

	for (i = 0; i < nOperands; ++i)
	{
		ConsoleIOPrint(i == 0 ? " " : ", ");
		length += i == 0 ? 1 : 2;
		if (Reg == pElement->type[i])
		{
			char * reg = (char*)RegisterToString(pElement->reg[i]);
			length += xstrlen(reg);
			ConsoleIOPrint(reg);
		}
		else if (Imm == pElement->type[i])
		{
			ConsoleIOPrintFormatted("%d", pElement->reg[i]);
			++length;
		}
		else
		{
			OperandType hi = HITYPE(pElement->type[i]);
			OperandType lo = LOTYPE(pElement->type[i]);

			length += 2;

			switch (hi)
			{
			case E: ConsoleIOPrint("E"); break;
			case G: ConsoleIOPrint("G"); break;
			case I: ConsoleIOPrint("I"); break;
			case J: ConsoleIOPrint("J"); break;
			case M: ConsoleIOPrint("M"); break;
			case O: ConsoleIOPrint("O"); break;
			case X: ConsoleIOPrint("X"); break;
			case Y: ConsoleIOPrint("Y"); break;
			case F: ConsoleIOPrint("F"); break;
			case S: ConsoleIOPrint("S"); break;
			case R: ConsoleIOPrint("R"); break;
			case D: ConsoleIOPrint("D"); break;
			case C: ConsoleIOPrint("C"); break;
			case U: ConsoleIOPrint("U"); break;
			case V: ConsoleIOPrint("V"); break;
			case W: ConsoleIOPrint("W"); break;
			case P: ConsoleIOPrint("P"); break;
			case Q: ConsoleIOPrint("Q"); break;
			case A: ConsoleIOPrint("A"); break;
			default: --length; break;
			}
			switch (lo)
			{
			case b:  ConsoleIOPrint("b"); break;
			case v:  ConsoleIOPrint("v"); break;
			case z:  ConsoleIOPrint("z"); break;
			case p:  ConsoleIOPrint("p"); break;
			case w:  ConsoleIOPrint("w"); break;
			case q:  ConsoleIOPrint("q"); break;
			case d:  ConsoleIOPrint("d"); break;
			case o:  ConsoleIOPrint("o"); break;
			case ps: ConsoleIOPrint("ps"); ++length; break;
			case ss: ConsoleIOPrint("ss"); ++length; break;
			case pd: ConsoleIOPrint("pd"); ++length; break;
			case sd: ConsoleIOPrint("sd"); ++length; break;
			case a:  ConsoleIOPrint("a"); break;
			default: --length; break;
			}
		}
	}
	return length;
}

void DisAsmPrintOpCodeMap()
{
	uint32_t width = 16;
	uint32_t i = 0;
	uint32_t j = 0;
	uint8_t k = 0;

	ConsoleIOPrint("  ");
	for (i = 0x00; i < 0x08; ++i)
	{
		ConsoleIOPrintFormatted("        %X       ", i);
	}
	ConsoleIOPrint("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("%X ", i);
		for (j = 0x00; j < 0x08; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) ConsoleIOPrint(" ");
		}
		ConsoleIOPrint("\n");
	}
	ConsoleIOPrint("\n");
	ConsoleIOPrint("  ");
	for (i = 0x08; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("        %X       ", i);
	}
	ConsoleIOPrint("\n");
	for (i = 0x00; i < 0x10; ++i)
	{
		ConsoleIOPrintFormatted("%X ", i);
		for (j = 0x08; j < 0x10; ++j)
		{
			uint32_t padding = width - PrintOpCode((i << 4) | j);
			for (k = 0; k < padding; ++k) ConsoleIOPrint(" ");
		}
		ConsoleIOPrint("\n");
	}
}

uint8_t DisAsmInstructionDecode(uint8_t bitness, HREADER hReader, InstructionInfo * pInfo)
{
	InstructionInfo info;
	DisAsmContext context;
	OpCodeMapElement * pElement = 0;
	uint8_t i = 0;

	pInfo = pInfo ? pInfo : &info;
	pInfo->length = 0;
	pInfo->nPrefixes = 0;
	pInfo->REX = 0;
	pInfo->LegacySSEPrefix = 0;
	pInfo->mnemonic = DB;
	pInfo->REXW = pInfo->REXR = pInfo->REXX = pInfo->REXB = 0;

	context.error = 0;
	context.hReader = hReader;
	context.currentSize = context.size = bitness >> 3;
	context.ModRMRead = 0;

	pElement = ChooseOpCode(&context, pInfo);
	if (1 == context.error)
	{
		return 0;
	}
    if (8 == context.currentSize)
    {
        context.currentSize = pInfo->REXW ? 8 : 4;
    }
	pInfo->flags = 0;
	pInfo->set = GP;
	if (ESCAPEX87 == pElement->mnemonic || (GROUP1 <= pElement->mnemonic && pElement->mnemonic <= GROUPP))
	{
		pInfo->flags |= kHasModRM;
	}

	CopyElementInfo(pInfo, pElement);
	pInfo->flags |= HASMODRM(pInfo->operands[0].type) ? kHasModRM : 0;
	pInfo->flags |= HASMODRM(pInfo->operands[1].type) ? kHasModRM : 0;
	pInfo->flags |= HASMODRM(pInfo->operands[2].type) ? kHasModRM : 0;
	pInfo->flags |= HASMODRM(pInfo->operands[3].type) ? kHasModRM : 0;

	if (pInfo->flags & kHasModRM)
	{
		uint8_t ModRM_Mod, ModRM_RM;
		if (!context.ModRMRead)
		{
			pInfo->ModRM = Fetch1(&context, pInfo);
		}
		ModRM_Mod = MODRM_MOD(pInfo->ModRM);
		ModRM_RM  = MODRM_RM(pInfo->ModRM);
		pInfo->flags |= ((ModRM_Mod != 3) && (ModRM_RM == 4)) ? kHasSIB : 0;

		GroupDecode(&context, pInfo);
		x87Decode(&context, pInfo);
		if (1 == context.error)
		{
			return 0;
		}
		pInfo->SIB = (pInfo->flags & kHasSIB) ? Fetch1(&context, pInfo) : 0;
		switch (ModRM_Mod)
		{
		case 0:
			if (5 == ModRM_RM || ((pInfo->flags & kHasSIB) && 5 == SIB_BASE(pInfo->SIB)))
			{
				pInfo->flags |= kHasDisp;
				pInfo->sizeDisp = 4;
			}
			break;
		case 1:
			pInfo->flags |= kHasDisp;
			pInfo->sizeDisp = 1;
			break;
		case 2:
			pInfo->flags |= kHasDisp;
			pInfo->sizeDisp = 4;
			break;
		}
	}
	for (i = 0; i < pInfo->nOperands; ++i) OperandDecode(&context, pInfo, &pInfo->operands[i]);
	{
		/* to avoid unnecessary branches, let's fetch displacement, segment and immediate operand at once */
		uint8_t offset = pInfo->length;
		uint8_t size;
		uint8_t offsetDisp;
		uint8_t offsetSeg;
		uint8_t offsetImm;

		static const uint64_t mask[9] = {0, U64(0xFF), U64(0xFFFF), 0, U64(0xFFFFFFFF), 0, 0, 0, U64(0xFFFFFFFFFFFFFFFF)};

		offsetDisp = offset;
		size = (pInfo->flags & kHasDisp) ? pInfo->sizeDisp : 0;
		offsetSeg = offset + size;
		size += (pInfo->flags & kHasSeg) ? 2 : 0;
		offsetImm = offset + size;
		size += (pInfo->flags & kHasImm) ? pInfo->sizeImm : 0;

		FetchN(&context, pInfo, size);

		pInfo->disp = *(uint64_t*)(pInfo->bytes + offsetDisp) & mask[pInfo->sizeDisp];
		pInfo->seg = *(uint16_t*)(pInfo->bytes + offsetSeg);
		pInfo->imm = *(uint64_t*)(pInfo->bytes + offsetImm) & mask[pInfo->sizeImm];
	}
	return pInfo->length;
}
