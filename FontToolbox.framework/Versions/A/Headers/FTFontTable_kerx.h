/*
	File:			FTFontTable_kerx.h
 
	Contains:		C++ class individual TrueType font 'kerx' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2010-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_kerx__
#define __FTFONTTABLE_kerx__

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

struct FTHeader_kerx {
	Fixed		fVersion;
	uint32_t	fNumSubtables;
};

struct FTSubtableHeader_kerx {
	uint32_t	fLength;
	uint32_t	fCoverage;
	uint32_t	fTupleIndex;
};

struct FTOrderedListSubtable_kerx {
	uint32_t	fNumPairs;
	uint32_t	fSearchRange;
	uint32_t	fEntrySelector;
	uint32_t	fRangeShift;
};

struct FTKernPair_kerx {
	uint16_t	fLeftGlyph;
	uint16_t	fRightGlyph;
	int16_t		fValue;
};

struct FTStateTableSubtable_kerx {
	STXHeader	fHeader;
	uint32_t	fValueTableOffset;
};

struct FTArraySubtable_kerx {
	uint32_t	fRowWidth;
	uint32_t	fLeftOffsetTableOffset;
	uint32_t	fRightOffsetTableOffset;
	uint32_t	fValueArrayOffset;
};

struct FTCompactSubtable_kerx {
	uint16_t	fGlyphCount;
	uint16_t	fKernValueCount;
	uint16_t	fLeftClassCount;
	uint16_t	fRightClassCount;
	uint16_t	fFlags;
};

struct FTClassTableHeader_kerx {
	uint16_t	fFirstGlyph;
	uint16_t	fNumGlyphs;
	uint32_t	fOffsetArray[];
};

struct FTPositioningTableHeader_kerx {
	uint16_t	fGlyphCount;
	uint16_t	fKernValueCount;
	uint16_t	fLeftClassCount;
	uint16_t	fRightClassCount;
	uint16_t	fFlags;
};

struct FTControlPointStateTableHeader_kerx {
	STXHeader	fHeader;
	uint32_t	fFlags;
};

struct FTControlPointTable_kerx {
	uint16_t	fControlPoint;
	uint16_t	fCurrentGlyphControlPoint;
};

struct FTControlPointCoordinates {
	int16_t		fMarkX;
};

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

	class FTSet;

class FTFontTable_kerx : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'kerx' ),
        kGlyphCoverageTableIntroducedVersion = 3*fixed1,
		kOldVersion = 2*fixed1,
		kVersion = 3*fixed1,

		kNoGlyphCoverage = 0xFFFFFFFFU,
		
		kVerticalAdjustmentsMask = 0x80000000U,
		kCrossStreamValuesMask = 0x40000000U,
		kVariationValuesMask = 0x20000000U,
		kProcessGlyphsLastToFirstMask = 0x10000000U,
		kFormatMask = 0x000000FFU,
		
		kOrderedListFormat = 0,
		kStateTableFormat = 1,
		kArrayFormat = 2,
		kCompactArrayFormat = 3,
		kControlPointStateTableFormat = 4,
		
		kPushActionMask = 0x8000U,
		kNoAdvanceActionMask = 0x4000U,
		kResetKerningActionMask = 0x2000U,
		kStopKerning = 0xFFFFU,
		
		kNoAction = 0xFFFFU,
		
		kTableHasCoordinatesMask = 0x80000000U,
		kTableUsesAnchorPointsMask = 0x40000000U,
		kTableOffsetMask = 0x00FFFFFFU,
		
		kMarkGlyphMask = 0x8000U,
		kDontAdvanceMask = 0x4000U,
		kControlPointIndexMask = 0x3FFF,
		};

	static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML, bool iCompatibilityMode = false );

	FTFontTable_kerx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_kerx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_kerx( const FTFontTable& iOther );
	virtual ~FTFontTable_kerx();
	
	FTFontTable_kerx& operator=( const FTFontTable_kerx& iOther );

	virtual FourCharCode	GetTag() const;
	virtual Fixed			GetVersion() const { ReadData(); return _fVersion; };
	virtual uint32_t		GetSubtableCount() const { ReadData(); return _fNumSubtables; };

	FTSet					GetSubtableGlyphCoverage(uint32_t iIndex) const;

protected:

	FTFontTable_kerx();

	virtual void		ReadDataInternal();

private:

	mutable Fixed		_fVersion;
	mutable uint32_t	_fNumSubtables;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_kerx__ */
