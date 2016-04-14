/*
	File:			FTTypes.h
 
	Contains:		General type definitions
 
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

#ifndef __FTTYPES__
#define __FTTYPES__

#include <Carbon/Carbon.h>

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(push,2)

/* ----------------------------------------------------------------------------------------- */

/* NAMESPACE */

namespace ftx {
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* TYPES */
	
	struct FTPoint {
		int16_t x;
		int16_t y;
	};
	
	typedef int32_t		FTGlyphID;
	// We make this a four-byte signed int so that we can use -1 as a flag value
	//	but still include glyphs from 0 through 65534
	typedef uint16_t	FTFontTableGlyphID;
	// This is the value stored in font tables
	
	typedef int32_t		FTResourceFileRef;
	typedef int16_t		FTShortFrac;
	typedef uint16_t	FTOpenTypeOffset;
	
	typedef int32_t     FTFixed;

	/* OpenType related */
	
	struct FTGlyphArrayOTLookupTable {
		uint16_t			fTableFormat;	//	Should be 1
		FTFontTableGlyphID	fStartGlyph;
		uint16_t			fGlyphCount;
		uint16_t			fValues[];
	};
	
	struct FTGlyphRangeOTLookup {
		FTFontTableGlyphID	fStart;
		FTFontTableGlyphID	fEnd;
		uint16_t			fValue;
	};
	
	struct FTGlyphRangeArrayOTLookupTable {
		uint16_t				fTableFormat;	//	Should be 2
		uint16_t				fRangeCount;
		FTGlyphRangeOTLookup	fRanges[];
	};
	
	struct FTSingleRangeOTCoverageTable {
		uint16_t			fTableFormat;	//	Should be 1
		uint16_t			fGlyphCount;
		uint16_t			fValues[];
	};
	
	typedef struct FTGlyphRangeArrayOTLookupTable FTRangeArrayOTCoverageTable;
	
	/* Bitmap related */
	
	/* The FTBitmapLineMetrics describes metrics for the overall strike for a pointsize. */
	
	struct FTBitmapLineMetrics {
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
	
	enum {
		sizeOfFTBitmapLineMetrics = 12
	};
	
	/* The FTBitmapStrikeData describes the index entries for a single pointsize. */
	
	struct FTBitmapStrikeData {
		uint32_t				fColorRef;
		FTBitmapLineMetrics		fHorizontalLineMetrics;
		FTBitmapLineMetrics		fVerticalLineMetrics;
		uint16_t				fStartGlyphIndex;
		uint16_t				fEndGlyphIndex;
		uint8_t					fHorizontalPixelsPerEm;
		uint8_t					fVerticalPixelsPerEm;
		uint8_t					fBitDepth;
		uint8_t					fFlags;
	};
	
	// typedef BitMapHandle	FTBitmapHandle;
	
	/* A FTBitMapHandle is exactly like a BitMapHandle/PixMapHandle except that,	*/
	/*	if used to hold a PixMapHandle, there is no associated color table (yet)	*/
	/* Instead, a uniform grayscale is assumed										*/
	
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* END NAMESPACE */
	
}

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(pop)

#endif /* __FTTYPES__ */
