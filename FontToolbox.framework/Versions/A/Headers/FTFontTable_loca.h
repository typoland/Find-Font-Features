/*
	File:			FTFontTable_loca.h
 
	Contains:		C++ class individual TrueType font 'loca' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_LOCA__
#define __FTFONTTABLE_LOCA__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"

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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_loca : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'loca' )
		};

	static FTData CreateDummyTable(size_t iNullGlyphLength, size_t iGlyphCount);

	FTFontTable_loca( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_loca( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_loca( const FTFontTable& iOther );
	virtual ~FTFontTable_loca();
	
	FTFontTable_loca& operator=( const FTFontTable_loca& iOther );

	virtual FourCharCode	GetTag() const;

	virtual ByteCount	GetGlyphOffset( uint16_t iGlyphID ) const;
	virtual ByteCount	GetGlyphLength( uint16_t iGlyphID ) const;
	
protected:

	FTFontTable_loca();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	ByteCount		*fOffsets;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_LOCA__ */
