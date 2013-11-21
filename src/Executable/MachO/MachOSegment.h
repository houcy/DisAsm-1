/*
 * Filename: MachOSegment.h
 * Author:   DisAsmCompany
 * Date:     11/10/2013
 *
 * Description: Mach-O Segment (Load Command)
 *
 *              
 *
 */

#pragma once
#ifndef __MACHOSEGMENT_H__775B491F_0466_413A_AB30_EB2453142367__
#define __MACHOSEGMENT_H__775B491F_0466_413A_AB30_EB2453142367__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum { kMachOSegmentNumberOfSections = 40 };

static const SDFElement MachOSegment[] =
{
	{"Mach-O Segment"},
	{"Name            ", kStringASCII, 16, 1},
	{"VirtualAddress  ", kUnsigned, 4, 1},
	{"VirtualSize     ", kUnsigned, 4, 1},
	{"FileOffset      ", kUnsigned, 4, 1},
	{"FileSize        ", kUnsigned, 4, 1},
	{"ProtectionMax   ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"ProtectionInit  ", kUnsigned, 4, 1, MachOMemoryProtection},
	{"NumberOfSections", kUnsigned, 4, 1},
	{"Flags           ", kUnsigned, 4, 1, MachOSegmentAttributes},
	{NULL}
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MACHOSEGMENT_H__775B491F_0466_413A_AB30_EB2453142367__ */
