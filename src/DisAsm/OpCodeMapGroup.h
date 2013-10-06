/*
* Filename: OpCodeMapGroup.h
* Author:   DisAsmCompany
* Date:     06/10/2013
*
* Description: Opcode Map for GROUP extensions
*              (GROUP1 - GROUPP)
*              
*
*/

#pragma once
#ifndef __OPCODEMAPGROUP_H__
#define __OPCODEMAPGROUP_H__

OpCodeMapElement OpCodeMapGroup[] =
{
	/* GROUP1 */
	{ADD}, {OR}, {ADC}, {SBB}, {AND}, {SUB}, {XOR}, {CMP},
	/* GROUP1A */
	{POP}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP2 */
	/*
	Intel doesn't define /6 form
	AMD defines both /4 and /6 as SHL/SAL (that are essentially same instruction)
	*/
	{ROL}, {ROR}, {RCL}, {RCR}, {SHL}, {SHR}, {SAL}, {SAR},
	/* GROUP3 */
	{TEST}, {TEST}, {NOT}, {NEG}, {MUL}, {IMUL}, {DIV}, {IDIV},
	/* GROUP4 */
	{INC, OP1(Eb)}, {DEC, OP1(Eb)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP5 */
	{INC, OP1(Ev)}, {DEC, OP1(Ev)}, {CALL, OP1(Ev)}, {CALL, OP1(Mp)}, {JMP, OP1(Ev)}, {JMP, OP1(Mp)}, {PUSH, OP1(Ev)}, {DB},
	/* GROUP6 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP7 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP8 */
	{DB}, {DB}, {DB}, {DB}, {BT}, {BTS}, {BTR}, {BTC},
	/* GROUP9 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP10 */
	/*
	according to AMD manual, all GROUP10 variants are defined as UD1
	according to Intel, it is just unnamed undefined instructions
	*/
	{UD1}, {UD1}, {UD1}, {UD1}, {UD1}, {UD1}, {UD1}, {UD1},
	/* GROUP11 */
	{MOV}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP12 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP13 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP14 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP15 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP16 */
	/*
	according to AMD manual, /4 - /7 forms are defines as valid instructions (NOPs)
	for compatibility with future PREFETCH instructions
	*/
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUP17 */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* GROUPP */
	/*
	Intel defines just /0 for PREFETCHW
	AMD defines /0, /1 and /3, others are aliases to /0 for compatibility with future PREFETCH instructions
	*/
	{PREFETCHW}, {PREFETCHW}, {PREFETCHW}, {PREFETCHW}, {PREFETCHW}, {PREFETCHW}, {PREFETCHW}, {PREFETCHW},
};

#endif /* __OPCODEMAPGROUP_H__ */
