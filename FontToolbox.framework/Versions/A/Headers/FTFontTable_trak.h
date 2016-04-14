/*
	File:			FTFontTable_trak.h

	Contains:		C++ class individual TrueType font 'trak' tables

	Version:		Mac OS X

	Written by:		The Apple Font Group

	Copyright:		© 2013 by Apple Inc. All rights reserved.

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

#ifndef __FTFONTTABLE_trak__
#define __FTFONTTABLE_trak__

#include <Carbon/Carbon.h>
#include <vector>

#include "FTArray.h"
#include "FTFontTable.h"

using namespace std;

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

struct FTTableEntry_trak {
	Fixed		fValue;
	uint16_t	fNameCode;
	uint16_t	fSizeDataOffset;
};

struct FTTableHeader_trak {
	Fixed		fVersion;
	uint16_t	fFormat;
	uint16_t	fHorizontalDataOffset;
	uint16_t	fVerticalDataOffset;
	uint16_t	fPadding;
};

struct FTTableData_trak {
	uint16_t	fNumTraks;
	uint16_t	fNumSizes;
	uint32_t	fSizeTableOffset;
};

class FTFontTable_trak : public FTFontTable {
	
public:
	
	enum {
		kNoData = 0,
		kCurrentVersion = fixed1,
		kTag = FOUR_CHAR_CODE( 'trak' ),
	};
	
	FTFontTable_trak( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_trak( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_trak( FTFont_sfnt *iFont, const FTData& iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_trak( const FTFontTable_trak& iOther );
	virtual ~FTFontTable_trak();
	
	FTFontTable_trak& operator=( const FTFontTable_trak& iOther );
	
	virtual FourCharCode	GetTag() const;
	
	Fixed					GetVersion() const { return kCurrentVersion; };
	
	CFIndex					GetHorizontalTrakCount() const;
	CFIndex					GetHorizontalSizeCount() const;
	FTTableEntry_trak		GetIndHorizontalTableEntry(CFIndex iIndex) const;
	Fixed					GetIndHorizontalSize(CFIndex iSizeIndex) const;
	int16_t					GetIndHorizontalTrakValue(CFIndex iTrakIndex, CFIndex iSizeIndex) const;
	
	CFIndex					GetVerticalTrakCount() const;
	CFIndex					GetVerticalSizeCount() const;
	FTTableEntry_trak		GetIndVerticalTableEntry(CFIndex iIndex) const;
	Fixed					GetIndVerticalSize(CFIndex iSizeIndex) const;
	int16_t					GetIndVerticalTrakValue(CFIndex iTrakIndex, CFIndex iSizeIndex) const;
	
		
protected:
	
	FTFontTable_trak();
	
	virtual void		ReadDataInternal();

	virtual bool		NotEqualsInternal(const FTFontTable *iOther) const;

private:
	
	void FillInData(uint16_t iOffset, vector<FTTableEntry_trak>& oTraks, vector<Fixed>& oSizes, vector<int16_t>& oValues);
	
	vector<FTTableEntry_trak>	_fHorizontalTraks;
	vector<Fixed>				_fHorizontalSizes;
	vector<int16_t>				_fHorizontalValues;
	
	vector<FTTableEntry_trak>	_fVerticalTraks;
	vector<Fixed>				_fVerticalSizes;
	vector<int16_t>				_fVerticalValues;
	
};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_trak__ */
