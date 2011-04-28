#ifndef CUSTOM_FORMAT_H
#define CUSTOM_FORMAT_H

#include <string.h>

#ifdef WIN32
	#include <WinDef.h>
#else
	typedef unsigned char BYTE;
	typedef unsigned short WORD;
	typedef unsigned long int DWORD;
	typedef signed long int LONG;
	typedef char STR;
#endif

#define HEADER 0x4843

typedef struct tagMAPFILEHEADER
{
	WORD chHeader;
	DWORD chSize;
	LONG chWidth;
	LONG chHeight;
	LONG chNumTiles;
	LONG chTitleLength;
} MAPFILEHEADER;

typedef struct tagTILEINFO
{
	WORD tiVar;
	WORD tiCollides;
	LONG tiHeight;
	LONG tiWidth;
	LONG tiPathLength;
} TILEINFO;

#endif