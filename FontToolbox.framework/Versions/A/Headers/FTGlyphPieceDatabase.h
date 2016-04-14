/*
	File:		FTGlyphPieceDatabase.h
 
	Contains:	The database that gives information on how to create glyphs
				from pieces of other glyphs.
 
	Version:	Mac OS X
 
	Written by:	The Apple Font Group
 
	Copyright:	Copyright © 2009-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Peter Lofting
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins

*/

#ifndef __FTGLYPHPIECEDATABASE__
#define __FTGLYPHPIECEDATABASE__

/* ----------------------------------------------------------------------------------------- */

/* INCLUDES -- SYSTEM */

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

/* INCLUDES -- APPLICATION */

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

/* ----------------------------------------------------------------------------------------- */

/* TYPES */

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

namespace ftx {
	
	class FTGlyphPieceDatabase {
		
	public:
		
		static CFArrayRef		GetDatabase();
		static CFDictionaryRef	GetVerticalFormsDatabase();
	};
	
}

#endif /* __FTGLYPHPIECEDATABASE__ */
