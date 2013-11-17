/*
 * Filename: ELFHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFHEADER_H__
#define __ELFHEADER_H__

enum { kELFMagic = 0x464C457FUL };

enum { ELFHeaderMagic               = 0  };
enum { ELFHeaderMachine             = 18 };
enum { ELFHeaderAddressOfEntryPoint = 24 };
enum { ELFHeaderOffsetSections      = 32 };
enum { ELFHeaderOffsetPrograms      = 28 };
enum { ELFHeaderSizeOfProgram       = 42 };
enum { ELFHeaderNumberOfPrograms    = 44 };
enum { ELFHeaderSizeOfSection       = 46 };
enum { ELFHeaderNumberOfSections    = 48 };
enum { ELFHeaderSectionHeaderIndex  = 50 };

static const SDFElement ELFHeader[] =
{
	{"ELF Header"},
	{"Magic                    ", kSignature, 4, 1},
	{"Class                    ", kUnsigned, 1, 1, ELFClass},
	{"Data                     ", kUnsigned, 1, 1, ELFData},
	{"Version                  ", kUnsigned, 1, 1, ELFVersion},
	{"OS ABI                   ", kUnsigned, 1, 1, ELFABI},
	{"OS ABI Version           ", kUnsigned, 1, 1},
	{"Padding                  ", kReserved, 1, 7},
	{"Type                     ", kUnsigned, 2, 1, ELFType},
	{"Machine                  ", kUnsigned, 2, 1, _ELFMachine},
	{"Version                  ", kUnsigned, 4, 1, ELFVersion},
	{"Address Of Entry Point   ", kUnsigned, 4, 1},
	{"Offset Program Header    ", kUnsigned, 4, 1},
	{"Offset Section Header    ", kUnsigned, 4, 1},
	{"Flags                    ", kUnsigned, 4, 1},
	{"ELF Header Size          ", kUnsigned, 2, 1},
	{"Program Header Size      ", kUnsigned, 2, 1},
	{"Number OF Program Headers", kUnsigned, 2, 1},
	{"Section Header Size      ", kUnsigned, 2, 1},
	{"Number OF Section Headers", kUnsigned, 2, 1},
	{"Section Header Index     ", kUnsigned, 2, 1},
	{NULL}
};

#endif /* __ELFHEADER_H__ */
