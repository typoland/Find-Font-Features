/*
	File:			FTFontTable_gasp.h
 
	Contains:		C++ class individual TrueType font 'gasp' tables
 
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

#ifndef __FTFONTTABLE_GASP__
#define __FTFONTTABLE_GASP__

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

struct GASPRange {
	uint16_t	rangeMaxPPEM;
	uint16_t	rangeGaspBehavior;
};

#ifndef __cplusplus
typedef struct GASPRange GASPRange;
#endif

typedef GASPRange FTRange_gasp;

struct GASPTable {
	uint16_t	version;
	uint16_t	numRanges;
	GASPRange	gaspRange[];
};

#ifndef __cplusplus
typedef struct GASPTable GASPTable;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_gasp : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'gasp' ),

		kCurrentVersion = 1,
		
		kGridFit			= 1, 	/*	Use gridfitting	*/
		kDoGray				= 2, 	/*	Use grayscale rendering	*/
		kSymmetricGridFit	= 4,	/*	Use gridfitting with ClearType® symmetric smoothing */
		kSymmetricSmoothing	= 8,	/* Use smoothing along multiple axes with ClearType® */

		kMaxFlag	= kSymmetricSmoothing
	};

	FTFontTable_gasp( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_gasp( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_gasp( const FTFontTable& iOther );
	virtual ~FTFontTable_gasp();
	
	FTFontTable_gasp& operator=( const FTFontTable_gasp& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual uint16_t		GetVersion() const { ((FTFontTable_gasp*)this)->ReadDataInternal(); return _fVersion; };
	virtual ItemCount		GetNumRanges() const { ((FTFontTable_gasp*)this)->ReadDataInternal(); return _fNumRanges; };
	virtual FTRange_gasp	GetIndRange( ItemCount iIndex ) const;
	virtual uint16_t		GetIndRangeMaxPPM( ItemCount iIndex ) const {FTRange_gasp tRange = GetIndRange( iIndex ); return tRange.rangeMaxPPEM; };
	virtual bool			GridFitIndRange( ItemCount iIndex ) const { FTRange_gasp tRange = GetIndRange( iIndex ); return ( tRange.rangeGaspBehavior & kGridFit ) != 0; };
	virtual bool			DoGrayIndRange( ItemCount iIndex ) const { FTRange_gasp tRange = GetIndRange( iIndex ); return ( tRange.rangeGaspBehavior & kDoGray ) != 0; };
	virtual bool			SymmetricGridFitIndRange( ItemCount iIndex ) const { FTRange_gasp tRange = GetIndRange( iIndex ); return ( tRange.rangeGaspBehavior & kSymmetricGridFit ) != 0; };
	virtual bool			SymmetricSmoothingIndRange( ItemCount iIndex ) const { FTRange_gasp tRange = GetIndRange( iIndex ); return ( tRange.rangeGaspBehavior & kSymmetricSmoothing ) != 0; };

protected:

	FTFontTable_gasp();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	
	uint16_t	_fVersion;
	ItemCount	_fNumRanges;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_GASP__ */
