/*
	File:			FTFontTable_bdat.h
 
	Contains:		C++ class individual TrueType font 'bdat' tables
 
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

#ifndef __FTFONTTABLE_BDAT__
#define __FTFONTTABLE_BDAT__

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
	
	typedef UInt16 BDATImageFormat;
	
	/* The BDATSmallMetrics describes the bit-level metrics for a glyph in a single orientation;
	 the other orientation is computed. Whether the small metrics contain the horizontal or
	 vertical metrics is controlled by the flags field in the BLOCPerSizeTable struct. */
	
	struct BDATSmallMetrics {
		UInt8	fBitHeight;
		UInt8	fBitWidth;
		SInt8	fBearingX;
		SInt8	fBearingY;
		UInt8	fAdvance;
	};
	
	/* The BDATBigMetrics describes the bit-level metrics for a glyph for both horizontal and
	 vertical orientations. */
	
	struct BDATBigMetrics {
		UInt8	fBitHeight;
		UInt8	fBitWidth;
		SInt8	fHorizontalBearingX;
		SInt8	fHorizontalBearingY;
		UInt8	fHorizontalAdvance;
		SInt8	fVerticalBearingX;
		SInt8	fVerticalBearingY;
		UInt8	fVerticalAdvance;
	};

	enum {
		sizeofBDATSmallMetrics = 5,
		sizeofBDATBigMetrics = 8
	};
	
	struct BDATPointSizes {
		ItemCount	fNumSizes;
		UInt8		fSizes[];
	};
	
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_bdat : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'bdat' ),
			
			kSmallBytePropImageFormat	= 1,
			kSmallBitPropImageFormat	= 2,
			kCompressedMonoImageFormat	= 4,
			kBitMonoImageFormat			= 5,
			kBigBytePropImageFormat		= 6,
			kBigBitPropImageFormat		= 7,
			
			kSizeOfSmallMetrics			= 5,
			kSizeOfBigMetrics			= 8
		};
		
		FTFontTable_bdat( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_bdat( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_bdat( const FTFontTable& iOther );
		virtual ~FTFontTable_bdat();
		
		FTFontTable_bdat& operator=( const FTFontTable_bdat& iOther );
		
		virtual FourCharCode	GetTag() const;
		
	protected:
		
		FTFontTable_bdat();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_bdat__ */
