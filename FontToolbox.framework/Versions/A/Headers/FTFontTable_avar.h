/*
	File:			FTFontTable_avar.h
 
	Contains:		C++ class individual TrueType font 'avar' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2009-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_AVAR__
#define __FTFONTTABLE_AVAR__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTTypes.h"

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(push,2)

/* ----------------------------------------------------------------------------------------- */

/* NAMESPACE */

namespace ftx {

/* ----------------------------------------------------------------------------------------- */

/* CONSTANTS */

/* ----------------------------------------------------------------------------------------- */

/* TYPES */

struct AVARCorrespondence {
	FTShortFrac	fFromCoord;
	FTShortFrac	fToCoord;
};

struct AVARSegment {
	UInt16				fPairCount;
	AVARCorrespondence	fCorrespondence[];
};

struct AVARTable {
	Fixed			fVersion;
	UInt32			fAxisCount;
	AVARSegment		fSegments[];
};

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_avar : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'avar' )
		};

	FTFontTable_avar( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_avar( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_avar( const FTFontTable& iOther );
	virtual ~FTFontTable_avar();
	
	FTFontTable_avar& operator=( const FTFontTable_avar& iOther );

	virtual FourCharCode	GetTag() const;
	
protected:

	FTFontTable_avar();

	virtual void		ReadDataInternal();
#if 1
	virtual CFDataRef	RebuildDataInternal() const;
#endif

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_AVAR__ */
