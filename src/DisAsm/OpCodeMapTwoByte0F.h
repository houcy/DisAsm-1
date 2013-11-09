/*
* Filename: OpCodeMapTwoByte0F.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh)
*              
*              
*
*/

#ifndef __OPCODEMAPTWOBYTE0F_H__
#define __OPCODEMAPTWOBYTE0F_H__

/* Two-Byte Opcode Map (OpCodes 0F00h - 0FFFh) */

/* 
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 0 X X X X U X X X 0 X X   X   X X + 0
0x66 0                 0                 0
0xF2 0                 0                 0
0xF3 0                 0                 0
NONE 1 X X             1 X X X X X X X X 1
0x66 1 X X             1                 1
0xF2 1 X X             1                 1
0xF3 1 X X             1                 1
NONE 2 X X X X U U U U 2 X X             2
0x66 2                 2 X X             2
0xF2 2                 2                 2
0xF3 2                 2                 2
NONE 3 X X X X X X     3 +   +           3
0x66 3                 3                 3
0xF2 3                 3                 3
0xF3 3                 3                 3
NONE 4 X X X X X X X X 4 X X X X X X X X 4
0x66 4                 4                 4
0xF2 4                 4                 4
0xF3 4                 4                 4
NONE 5   X X X X X X X 5 X X     X X X X 5
0x66 5   X     X X X X 5 X X     X X X X 5
0xF2 5   X             5 X X     X X X X 5
0xF3 5   X             5 X X     X X X X 5
NONE 6                 6                 6
0x66 6                 6                 6
0xF2 6                 6                 6
0xF3 6                 6                 6
NONE 7               X 7                 7
0x66 7                 7                 7
0xF2 7                 7                 7
0xF3 7                 7                 7
       0 1 2 3 4 5 6 7   8 9 A B C D E F
NONE 8 X X X X X X X X 8 X X X X X X X X 8
0x66 8                 8                 8
0xF2 8                 8                 8
0xF3 8                 8                 8
NONE 9 X X X X X X X X 9 X X X X X X X X 9
0x66 9                 9                 9
0xF2 9                 9                 9
0xF3 9                 9                 9
NONE A X X X X X X     A X X X X X X X X A
0x66 A                 A                 A
0xF2 A                 A                 A
0xF3 A                 A                 A
NONE B X X   X     X X B   X X X     X X B
0x66 B                 B                 B
0xF2 B                 B                 B
0xF3 B                 B                 B
NONE C X X             C X X X X X X X X C
0x66 C                 C                 C
0xF2 C                 C                 C
0xF3 C                 C                 C
NONE D                 D X X X X X X X X D
0x66 D                 D X X X X X X X X D
0xF2 D                 D                 D
0xF3 D                 D                 D
NONE E                 E X X X X X X X X E
0x66 E                 E X X X X X X X X E
0xF2 E                 E                 E
0xF3 E                 E                 E
NONE F                 F X X X X X X X X F
0x66 F                 F X X X X X X X   F
0xF2 F                 F                 F
0xF3 F                 F                 F
       0 1 2 3 4 5 6 7   8 9 A B C D E F
*/

OpCodeMapElement OpCodeMapTwoByte0F[] =
{
	/* 0F00h - 0F07h */
	{GROUP6}, {GROUP7}, {LAR, OP2(Gv, Ew)}, {LSL, OP2(Gv, Ew)}, {LOADALL}, {SYSCALL}, {CLTS}, {SYSRET},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F08h - 0F0Fh */
	{INVD}, {WBINVD}, {DB}, {UD2}, {DB}, {GROUPP}, {FEMMS}, {ESCAPE3DNOW},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F10h - 0F17h */
	{MOVUPS, OP2(Vps, Wps)}, {MOVUPS, OP2(Wps, Vps)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{MOVUPD, OP2(Vss, Wss)}, {MOVUPD, OP2(Wss, Vss)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{MOVSD,  OP2(Vsd, Wsd)}, {MOVSD,  OP2(Wsd, Vsd)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{MOVSS,  OP2(Vss, Wss)}, {MOVSS,  OP2(Wss, Vss)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F18h - 0F1Fh */
	{GROUP16}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)}, {NOP, OP1(Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F20h - 0F27h */
	{MOV, OP2(Rd, Cd)}, {MOV, OP2(Rd, Dd)}, {MOV, OP2(Cd, Rd)}, {MOV, OP2(Dd, Rd)}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F28h - 0F2Fh */
	{MOVAPS, OP2(Vps, Wps)}, {MOVAPS, OP2(Wps, Vps)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{MOVAPD, OP2(Vss, Wss)}, {MOVAPD, OP2(Wss, Vss)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F30h - 0F37h */
	{WRMSR}, {RDTSC}, {RDMSR}, {RDPMC}, {SYSENTER}, {SYSEXIT}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F38h - 0F3Fh */
	{ESCAPE}, {DB}, {ESCAPE}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F40h - 0F47h */
	{CMOVO, OP2(Gv, Ev)}, {CMOVNO, OP2(Gv, Ev)}, {CMOVB, OP2(Gv, Ev)}, {CMOVAE, OP2(Gv, Ev)}, {CMOVE, OP2(Gv, Ev)}, {CMOVNE, OP2(Gv, Ev)}, {CMOVBE, OP2(Gv, Ev)}, {CMOVA, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F48h - 0F4Fh */
	{CMOVS, OP2(Gv, Ev)}, {CMOVNS, OP2(Gv, Ev)}, {CMOVP, OP2(Gv, Ev)}, {CMOVNP, OP2(Gv, Ev)}, {CMOVL, OP2(Gv, Ev)}, {CMOVNL, OP2(Gv, Ev)}, {CMOVLE, OP2(Gv, Ev)}, {CMOVNLE, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F50h - 0F57h */
	{DB}, {SQRTPS, OP2(Vps, Wps)}, {RSQRTPS, OP2(Vps, Wps)}, {RCPPS, OP2(Vps, Wps)}, {ANDPS, OP2(Vps, Wps)}, {ANDNPS, OP2(Vps, Wps)}, {ORPS, OP2(Vps, Wps)}, {XORPS, OP2(Vps, Wps)},
	{DB}, {SQRTPD, OP2(Vpd, Wpd)}, {DB}, {DB}, {ANDPD, OP2(Vpd, Wpd)}, {ANDNPD, OP2(Vpd, Wpd)}, {ORPD, OP2(Vpd, Wpd)}, {XORPD, OP2(Vpd, Wpd)},
	{DB}, {SQRTSD, OP2(Vsd, Wsd)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {SQRTSS, OP2(Vss, Wss)}, {RSQRTSS, OP2(Vss, Wss)}, {RCPSS, OP2(Vss, Wss)}, {DB}, {DB}, {DB}, {DB},
	/* 0F57h - 0F5Fh */
	{ADDPS, OP2(Vps, Wps)}, {MULPS, OP2(Vps, Wps)}, {DB}, {DB}, {SUBPS, OP2(Vps, Wps)}, {MINPS, OP2(Vps, Wps)}, {DIVPS, OP2(Vps, Wps)}, {MAXPS, OP2(Vps, Wps)},
	{ADDPD, OP2(Vpd, Wpd)}, {MULPD, OP2(Vpd, Wpd)}, {DB}, {DB}, {SUBPD, OP2(Vpd, Wpd)}, {MINPD, OP2(Vpd, Wpd)}, {DIVPD, OP2(Vpd, Wpd)}, {MAXPD, OP2(Vpd, Wpd)},
	{ADDSD, OP2(Vsd, Wsd)}, {MULSD, OP2(Vsd, Wsd)}, {DB}, {DB}, {SUBSD, OP2(Vsd, Wsd)}, {MINSD, OP2(Vsd, Wsd)}, {DIVSD, OP2(Vsd, Wsd)}, {MAXSD, OP2(Vsd, Wsd)},
	{ADDSS, OP2(Vss, Wss)}, {MULSS, OP2(Vss, Wss)}, {DB}, {DB}, {SUBSS, OP2(Vss, Wss)}, {MINSS, OP2(Vss, Wss)}, {DIVSS, OP2(Vss, Wss)}, {MAXSS, OP2(Vss, Wss)},
	/* 0F60h - 0F67h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F68h - 0F6Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F70h - 0F77h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {EMMS},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F78h - 0F7Fh */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F80h - 0F87h */
	{JO, OP1(Jz)}, {JNO, OP1(Jz)}, {JB, OP1(Jz)}, {JAE, OP1(Jz)}, {JE, OP1(Jz)}, {JNE, OP1(Jz)}, {JBE, OP1(Jz)}, {JA, OP1(Jz)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F88h - 0F8Fh */
	{JS, OP1(Jz)}, {JNS, OP1(Jz)}, {JP, OP1(Jz)}, {JNP, OP1(Jz)}, {JL, OP1(Jz)}, {JNL, OP1(Jz)}, {JLE, OP1(Jz)}, {JNLE, OP1(Jz)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F90h - 0F97h */
	{SETO, OP1(Eb)}, {SETNO, OP1(Eb)}, {SETB, OP1(Eb)}, {SETAE, OP1(Eb)}, {SETE, OP1(Eb)}, {SETNE, OP1(Eb)}, {SETBE, OP1(Eb)}, {SETA, OP1(Eb)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0F98h - 0F9Fh */
	{SETS, OP1(Eb)}, {SETNS, OP1(Eb)}, {SETP, OP1(Eb)}, {SETNP, OP1(Eb)}, {SETL, OP1(Eb)}, {SETNL, OP1(Eb)}, {SETLE, OP1(Eb)}, {SETNLE, OP1(Eb)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FA0h - 0FA7h */
	{PUSH, OP1(FS)}, {POP, OP1(FS)}, {CPUID}, {BT, OP2(Ev, Gv)}, {SHLD, OP3(Ev, Gv, Ib)}, {SHLD, OP3(Ev, Gv, CL)}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FA8h - 0FAFh */
	{PUSH, OP1(GS)}, {POP, OP1(GS)}, {RSM}, {BTS, OP2(Ev, Gv)}, {SHRD, OP3(Ev, Gv, Ib)}, {SHRD, OP3(Ev, Gv, CL)}, {GROUP15}, {IMUL, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB0h - 0FB7h */
	{CMPXCHG, OP2(Eb, Gb)}, {CMPXCHG, OP2(Ev, Gv)}, {DB}, {BTR, OP2(Ev, Gv)}, {DB}, {DB}, {MOVZX, OP2(Gv, Eb)}, {MOVZX, OP2(Gv, Ew)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FB8h - 0FBFh */
	{DB}, {GROUP10}, {GROUP8, OP2(Ev, Ib)}, {BTC, OP2(Ev, Gv)}, {DB}, {DB}, {MOVSX, OP2(Gv, Eb)}, {MOVSX, OP2(Gv, Ev)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FC0h - 0FC7h */
	{XADD, OP2(Eb, Gb)}, {XADD, OP2(Ev, Gv)}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FC8h - 0FCFh */
	{BSWAP, OP1(rAX)}, {BSWAP, OP1(rCX)}, {BSWAP, OP1(rDX)}, {BSWAP, OP1(rBX)}, {BSWAP, OP1(rSP)}, {BSWAP, OP1(rBP)}, {BSWAP, OP1(rBP)}, {BSWAP, OP1(rDI)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FD0h - 0FD7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FD8h - 0FDFh */
	{PSUBUSB, OP2(Pq, Qq)}, {PSUBUSW, OP2(Pq, Qq)}, {PMINUB, OP2(Pq, Qq)}, {PAND, OP2(Pq, Qq)}, {PADDUSB, OP2(Pq, Qq)}, {PADDUSW, OP2(Pq, Qq)}, {PMAXUB, OP2(Pq, Qq)}, {PANDN, OP2(Pq, Qq)},
	{PSUBUSB, OP2(Vo, Wo)}, {PSUBUSW, OP2(Vo, Wo)}, {PMINUB, OP2(Vo, Wo)}, {PAND, OP2(Vo, Wo)}, {PADDUSB, OP2(Vo, Wo)}, {PADDUSW, OP2(Vo, Wo)}, {PMAXUB, OP2(Vo, Wo)}, {PANDN, OP2(Vo, Wo)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FE0h - 0FE7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FE8h - 0FEFh */
	{PSUBSB, OP2(Pq, Qq)}, {PSUBSW, OP2(Pq, Qq)}, {PMINSW, OP2(Pq, Qq)}, {POR, OP2(Pq, Qq)}, {PADDSB, OP2(Pq, Qq)}, {PADDSW, OP2(Pq, Qq)}, {PMAXSW, OP2(Pq, Qq)}, {PXOR, OP2(Pq, Qq)},
	{PSUBSB, OP2(Vo, Wo)}, {PSUBSW, OP2(Vo, Wo)}, {PMINSW, OP2(Vo, Wo)}, {POR, OP2(Vo, Wo)}, {PADDSB, OP2(Vo, Wo)}, {PADDSW, OP2(Vo, Wo)}, {PMAXSW, OP2(Vo, Wo)}, {PXOR, OP2(Vo, Wo)},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FF0h - 0FF7h */
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	/* 0FF8h - 0FFFh */
	{PSUBB, OP2(Pq, Qq)}, {PSUBW, OP2(Pq, Qq)}, {PSUBD, OP2(Pq, Qq)}, {PSUBQ, OP2(Pq, Qq)}, {PADDB, OP2(Pq, Qq)}, {PADDW, OP2(Pq, Qq)}, {PADDD, OP2(Pq, Qq)}, {UD0},
	{PSUBB, OP2(Vo, Wo)}, {PSUBW, OP2(Vo, Wo)}, {PSUBD, OP2(Vo, Wo)}, {PSUBQ, OP2(Vo, Wo)}, {PADDB, OP2(Vo, Wo)}, {PADDW, OP2(Vo, Wo)}, {PADDD, OP2(Vo, Wo)}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
	{DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB}, {DB},
};

#endif /* __OPCODEMAPTWOBYTE0F_H__ */
