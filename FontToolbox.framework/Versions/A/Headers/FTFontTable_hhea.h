/*
	File:			FTFontTable_hhea.h
 
	Contains:		C++ class individual TrueType font 'hhea' tables
 
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

#ifndef __FTFONTTABLE_HHEA__
#define __FTFONTTABLE_HHEA__

#include <Carbon/Carbon.h>
#include "FTData.h"
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

struct HHEATable {
		Fixed		fVersion;
		int16_t		fAscender;
		int16_t		fDescender;
		int16_t		fLineGap;
		uint16_t	fAdvanceMax;
		int16_t		fSideBearingMin;
		int16_t		fOtherSideBearingMin;
		int16_t		fExtentMax;
		int16_t		fCaretSlopeRise;
		int16_t		fCaretSlopeRun;
		int16_t		fCaretOffset;
		uint16_t	fFiller[ 4 ];
		int16_t		fMetricDataFormat;
		uint16_t	fNumberLongMetrics;
	};

#ifndef __cplusplus
typedef struct HHEATable HHEATable;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_hhea : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'hhea' ),
		kVersion = 0x00010000U,
		};

	static FTData CreateDummyTable(size_t iGlyphCount);

	FTFontTable_hhea( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_hhea( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_hhea( const FTFontTable& iOther );
	virtual ~FTFontTable_hhea();
	
	FTFontTable_hhea& operator=( const FTFontTable_hhea& iOther );

	virtual FourCharCode	GetTag() const;

	Fixed			Version() const;
	int16_t			Ascender() const;
	int16_t			Descender() const;
	int16_t			LineGap() const;
	uint16_t		AdvanceMax() const;
	int16_t			SideBearingMin() const;
	int16_t			OtherSideBearingMin() const;
	int16_t			ExtentMax() const;
	int16_t			CaretSlopeRise() const;
	int16_t			CaretSlopeRun() const;
	int16_t			CaretOffset() const;
	const uint16_t*	Filler() const;
	int16_t			MetricDataFormat() const;
	uint16_t		NumberLongMetrics() const;
	
protected:

	FTFontTable_hhea();
	virtual void	ReadDataInternal();

private:

	Fixed		_fVersion;
	int16_t		_fAscender;
	int16_t		_fDescender;
	int16_t		_fLineGap;
	uint16_t	_fAdvanceMax;
	int16_t		_fSideBearingMin;
	int16_t		_fOtherSideBearingMin;
	int16_t		_fExtentMax;
	int16_t		_fCaretSlopeRise;
	int16_t		_fCaretSlopeRun;
	int16_t		_fCaretOffset;
	uint16_t	_fFiller[ 4 ];
	int16_t		_fMetricDataFormat;
	uint16_t	_fNumberLongMetrics;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_HHEA__ */
