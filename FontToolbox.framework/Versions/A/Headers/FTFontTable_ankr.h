/*
	File:			FTFontTable_ankr.h
 
	Contains:		C++ class individual TrueType font 'ankr' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2011-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_ankr__
#define __FTFONTTABLE_ankr__

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

struct FTTableHeader_ankr {
	uint16_t	fVersion;
	uint16_t	fFlags;
	uint32_t	fLookupTableOffset;
	uint32_t	fPointTableOffset;
};

typedef struct FTTableHeader_ankr FTTableHeader_ankr;

struct FTGlyphPointList_ankr {
	uint32_t	fPointCount;
	FTPoint		fPoints[];
};

typedef struct FTGlyphPointList_ankr FTGlyphPointList_ankr;

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_ankr : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'ankr' ),
		
		kVersion0 = 0,
		kCurrentVersion = kVersion0
		};

	static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );

	FTFontTable_ankr( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_ankr( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_ankr( const FTFontTable& iOther );
	virtual ~FTFontTable_ankr();
	
	FTFontTable_ankr& operator=( const FTFontTable_ankr& iOther );

	virtual FourCharCode	GetTag() const;
	
	uint32_t	GetPointCountForGlyph( FTGlyphID iGlyph ) const;
	FTPoint		GetIndPointForGlyph( FTGlyphID iGlyph, ItemCount iPointIndex ) const;

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
	virtual bool CanGenerateTrimmedData() const { return true; };
	virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

protected:

	FTFontTable_ankr();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;
};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_ankr__ */
