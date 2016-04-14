/*
	File:			FTFontTable_opbd.h
 
	Contains:		C++ class individual TrueType font 'opbd' tables
 
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

#ifndef __FTFONTTABLE_OPBD__
#define __FTFONTTABLE_OPBD__

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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_opbd : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'opbd' ),
		
		kDistanceBasedFormat = 0,
		kControlPointBasedFormat = 1
	};

	FTFontTable_opbd( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_opbd( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_opbd( const FTFontTable_opbd& iOther );
	virtual ~FTFontTable_opbd();
	
	FTFontTable_opbd& operator=( const FTFontTable_opbd& iOther );

	virtual FourCharCode	GetTag() const;
	virtual Fixed			GetVersion() const;
	virtual uint16_t		GetFormat() const;
	bool					IsPointBased() const { return (GetFormat() == kOPBDControlPointFormat); };
	virtual void			GetGlyphBounds( FTGlyphID iGlyph, OpbdSideValues& oBounds ) const; 

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
protected:

	FTFontTable_opbd();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	bool IsNonTrivial( const OpbdSideValues& iValues ) const;
	bool IsNonTrivial( int16_t iValue ) const;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_opbd__ */
