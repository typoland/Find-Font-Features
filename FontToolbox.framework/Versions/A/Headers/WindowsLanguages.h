/*
	File:			WindowsLanguages.h
 
	Contains:		Convert Windows language IDs to strings
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2007-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Peter Lofting
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins

*/ 
#ifndef __WINDOWSLANGUAGES__
#define __WINDOWSLANGUAGES__

/* ----------------------------------------------------------------------------------------- */

/* HEADERS -- SYSTEM */

#include <Carbon/Carbon.h>

/* ----------------------------------------------------------------------------------------- */

/* HEADERS -- APPLICATION */

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#if PRAGMA_STRUCT_ALIGN
#pragma options align = mac68k
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack( push, 2 ) 
#elif PRAGMA_STRUCT_PACK
#pragma pack( 2 ) 
#endif

namespace ftx {

/* ----------------------------------------------------------------------------------------- */

/* TYPES */

struct TWindowsLanguageName
	{
	int			fID;
	const char	*fName;
	};

#ifndef __cplusplus
typedef struct TWindowsLanguageName TWindowsLanguageName;
#endif

extern const TWindowsLanguageName gWindowsLanguageName[];

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

#ifdef __cplusplus
extern "C" {
#endif

    extern const char*	FTWindowsLanguageIDToName( int iID );
    extern int          FTWindowsLanguageTagToID( CFStringRef iTag );

#ifdef __cplusplus
}
#endif

}

#if PRAGMA_STRUCT_ALIGN
	#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
	#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
	#pragma pack()
#endif

#endif /* __WINDOWSLANGUAGES__ */
