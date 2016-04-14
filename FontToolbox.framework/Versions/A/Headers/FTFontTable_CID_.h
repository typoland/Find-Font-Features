/*
	File:			FTFontTable_CID_.h
 
	Contains:		C++ class individual TrueType font 'CID ' tables
 
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

#ifndef __FTFONTTABLE_CID___
#define __FTFONTTABLE_CID___

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
	
	class FTFontTable_CID_ : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'CID ' ),
		};
		
		FTFontTable_CID_( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_CID_( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_CID_( const FTFontTable& iOther );
		virtual ~FTFontTable_CID_();
		
		FTFontTable_CID_& operator=( const FTFontTable_CID_& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		virtual ItemCount		NumGlyphs() const { ReadData(); return _fGlyphCount; };
		
	protected:
		
		FTFontTable_CID_();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		ItemCount	_fGlyphCount;
		
	};
	
}

#pragma pack(pop)
	
#endif /* __FTFONTTABLE_CID___ */
