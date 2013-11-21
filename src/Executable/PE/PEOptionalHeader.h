/*
* Filename: PEOPtionalHeaders.h
* Author:   DisAsmCompany
* Date:     22/09/2013
*
* Description: Optional Headers structure
*              of PE file (Portable Executable)
*              
*
*/

#pragma once
#ifndef __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__
#define __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { PEOptionalHeaderMagic               = 0  };
enum { PEOptionalHeaderAddressOfEntryPoint = 16 };

static const SDFElement PEOptionalHeader[] =
{
	{"PE Optional Header"},
	{"Magic                      ", kUnsigned, 2, 1, _PEMagic},
	{"MajorLinkerVersion         ", kUnsigned, 1, 1},
	{"MinorLinkerVersion         ", kUnsigned, 1, 1},
	{"SizeOfCode                 ", kUnsigned, 4, 1},
	{"SizeOfInitializedData      ", kUnsigned, 4, 1},
	{"SizeOfUninitializedData    ", kUnsigned, 4, 1},
	{"AddressOfEntryPoint        ", kUnsigned, 4, 1},
	{"BaseOfCode                 ", kUnsigned, 4, 1},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PEOPTIONALHEADER_H__3EE5214B_CF69_4498_95E4_B3EE80EE7680__ */
