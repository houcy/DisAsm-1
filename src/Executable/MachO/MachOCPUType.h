/*
 * Filename: MachOCPUType.h
 * Author:   DisAsmCompany
 * Date:     14/10/2013
 *
 * Description: Mach-OCPU Type (x86, x64, PowerPC, etc)
 *)
 *              
 *
 */

#pragma once
#ifndef __MACHOCPUTYPE_H__
#define __MACHOCPUTYPE_H__

static const SDFEnum MachOCPUType[] =
{
	{"CPU_TYPE_MC680x0",   0x00000006UL},
	{"CPU_TYPE_X86",       0x00000007UL},
	{"CPU_TYPE_X86_64",    0x01000007UL},
	{"CPU_TYPE_ARM",       0x0000000CUL},
	{"CPU_TYPE_POWERPC",   0x00000012UL},
	{"CPU_TYPE_POWERPC64", 0x01000012UL},
	{NULL}
};

#endif /* __MACHOCPUTYPE_H__ */