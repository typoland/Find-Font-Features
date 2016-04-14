/*
	File:			FTFontTable_bloc.h
 
	Contains:		C++ class individual TrueType font 'bloc' tables
 
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

#ifndef __FTFONTTABLE_BLOC__
#define __FTFONTTABLE_BLOC__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTFontTable_bdat.h"

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
	
	typedef uint16_t BLOCIndexFormat;
	
	/* The BLOCIndexSubtableHeader. */
	
	struct BLOCIndexSubtableHeader {
		BLOCIndexFormat	fIndexFormat;
		BDATImageFormat	fImageFormat;
		uint32_t	fImageDataOffset;
	};
	
#ifndef __cplusplus
	typedef struct BLOCIndexSubtableHeader BLOCIndexSubtableHeader;
#endif
	
	/* The BLOCIndexSubtableFormat1. */
	
	struct BLOCIndexSubtableFormat1 {
		BLOCIndexSubtableHeader	fHeader;
		uint32_t	fOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct BLOCIndexSubtableFormat1 BLOCIndexSubtableFormat1;
#endif
	
	/* The BLOCIndexSubtableFormat2. */
	
	struct BLOCIndexSubtableFormat2 {
		BLOCIndexSubtableHeader	fHeader;
		uint32_t			fImageSize;
		BDATBigMetrics		fBigMetrics;
	};
	
#ifndef __cplusplus
	typedef struct BLOCIndexSubtableFormat2 BLOCIndexSubtableFormat2;
#endif
	
	/* The BLOCIndexSubtableFormat3. */
	
	struct BLOCIndexSubtableFormat3 {
		BLOCIndexSubtableHeader	fHeader;
		uint16_t	fOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct BLOCIndexSubtableFormat3 BLOCIndexSubtableFormat3;
#endif
	
	/* The BLOCIndexSubtableArrayEntry. */
	
	struct BLOCIndexSubtableArrayEntry {
		uint16_t	fFirstGlyph;
		uint16_t	fLastGlyph;
		uint32_t	fOffsetToIndexSubtable; 	/* added to BLOCPerSizeTable.offsetToIndexSubtables */
	};
	
#ifndef __cplusplus
	typedef struct BLOCIndexSubtableArrayEntry BLOCIndexSubtableArrayEntry;
#endif
	
	/* The BLOCLineMetrics describes metrics for the overall strike for a pointsize. */
	
	struct BLOCLineMetrics {
		int8_t	fAscent;
		int8_t	fDescent;
		uint8_t	fMaximumWidth;
		int8_t	fCaretSlopeNumerator;
		int8_t	fCaretSlopeDenominator;
		int8_t	fCaretOffset;
		int8_t	fMinimumWithStreamBearing;
		int8_t	fMinimumWithStreamAdvance;
		int8_t	fMaximumCrossStreamBearing;
		int8_t	fMaximumCrossStreamAdvance;
		int8_t	fPadding1;
		int8_t	fPadding2;
	};
	
#ifndef __cplusplus
	typedef struct BLOCLineMetrics BLOCLineMetrics;
#endif
	
	/* The BLOCPerSizeTable describes the index entries for a single pointsize. */
	
	struct BLOCPerSizeTable {
		uint32_t			fOffsetToIndexSubtables;
		uint32_t			fIndexSubtableSize;
		uint32_t			fNumIndexSubtables;
		uint32_t			fColorRef;
		BLOCLineMetrics		fHorizontalLineMetrics;
		BLOCLineMetrics		fVerticalLineMetrics;
		uint16_t			fStartGlyphIndex;
		uint16_t			fEndGlyphIndex;
		uint8_t				fHorizontalPixelsPerEm;
		uint8_t				fVerticalPixelsPerEm;
		uint8_t				fBitDepth;
		uint8_t				fFlags;
	};
	
#ifndef __cplusplus
	typedef struct BLOCPerSizeTable BLOCPerSizeTable;
#endif
	
	/* The BLOCTable defines the top-level structure of a 'bloc' table. */
	
	struct BLOCTable {
		Fixed				fVersion;
		uint32_t			fNumSizes;
		BLOCPerSizeTable	fPerSizeTables[];
	};
	
#ifndef __cplusplus
	typedef struct BLOCTable BLOCTable;
#endif
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_bloc : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'bloc' ),
			
			kHorizontalFlag					= 0x01,
			kVerticalFlag					= 0x02,
			
			kLongProportionalIndexFormat	= 1,
			kMonospaceIndexFormat			= 2,
			kShortProportionalIndexFormat	= 3
		};
		
		FTFontTable_bloc( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_bloc( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_bloc( const FTFontTable& iOther );
		virtual ~FTFontTable_bloc();
		
		FTFontTable_bloc& operator=( const FTFontTable_bloc& iOther );
		
		virtual FourCharCode	GetTag() const;
		
	protected:
		
		FTFontTable_bloc();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_bloc__ */
