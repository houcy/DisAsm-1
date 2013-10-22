/*
 * Filename: ELFSectionHeader.h
 * Author:   DisAsmCompany
 * Date:     22/10/2013
 *
 * Description: ELF Section Header
 *
 *
 *
 */

#pragma once
#ifndef __ELFSECTIONHEADER_H__
#define __ELFSECTIONHEADER_H__

static const SDFElement ELFSectionHeader[] =
{
	{"ELF Section Header"},
	{"Name           ", kUnsigned, 4, 1},
	{"Type           ", kUnsigned, 4, 1, ELFSectionType},
	{"Flags          ", kUnsigned, 4, 1, ELFSectionFlags},
	{"Address        ", kUnsigned, 4, 1},
	{"Offset         ", kUnsigned, 4, 1},
	{"Size           ", kUnsigned, 4, 1},
	{"Link           ", kUnsigned, 4, 1},
	{"Info           ", kUnsigned, 4, 1},
	{"Align          ", kUnsigned, 4, 1},
	{"Size Of Entries", kUnsigned, 4, 1},
	{NULL}
};

#endif /* __ELFSECTIONHEADER_H__ */