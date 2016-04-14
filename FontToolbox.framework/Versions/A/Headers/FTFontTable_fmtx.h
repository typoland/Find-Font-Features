/*
	File:			FTFontTable_fmtx.h
 
	Contains:		C++ class individual TrueType font 'cvt ' tables
 
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

#ifndef __FTFONTTABLE_FMTX__
#define __FTFONTTABLE_FMTX__

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

struct FMTXTable {
	Fixed		fVersion;
	uint32_t	fGlyphIndex;
	uint8_t		fHorizontalBefore;
	uint8_t		fHorizontalAfter;
	uint8_t		fHorizontalCaretHead;
	uint8_t		fHorizontalCaretBase;
	uint8_t		fVerticalBefore;
	uint8_t		fVerticalAfter;
	uint8_t		fVerticalCaretHead;
	uint8_t		fVerticalCaretBase;
};

#ifndef __cplusplus
typedef struct FMTXTable FMTXTable;
#endif


/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_fmtx : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'fmtx' ),
		};

	FTFontTable_fmtx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_fmtx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_fmtx( const FTFontTable& iOther );
	virtual ~FTFontTable_fmtx();
	
	FTFontTable_fmtx& operator=( const FTFontTable_fmtx& iOther );

	virtual FourCharCode	GetTag() const;

	Fixed		Version() const { ReadData(); return _fTable.fVersion; };
	uint32_t	GlyphIndex() const { ReadData(); return _fTable.fGlyphIndex; };
	uint8_t		HorizontalBefore() const { ReadData(); return _fTable.fHorizontalBefore; };
	uint8_t		HorizontalAfter() const { ReadData(); return _fTable.fHorizontalAfter; };
	uint8_t		HorizontalCaretHead() const { ReadData(); return _fTable.fHorizontalCaretHead; };
	uint8_t		HorizontalCaretBase() const { ReadData(); return _fTable.fHorizontalCaretBase; };
	uint8_t		VerticalBefore() const { ReadData(); return _fTable.fVerticalBefore; };
	uint8_t		VerticalAfter() const { ReadData(); return _fTable.fVerticalAfter; };
	uint8_t		VerticalCaretHead() const { ReadData(); return _fTable.fVerticalCaretHead; };
	uint8_t		VerticalCaretBase() const { ReadData(); return _fTable.fVerticalCaretBase; };

protected:

	FTFontTable_fmtx();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	
	mutable FMTXTable	_fTable;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_FMTX__ */
