/*
	File:			FTFontTable_head.h
 
	Contains:		C++ class individual TrueType font 'head' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_head.h,v $
	Revision 1.4  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.3  2007/01/15 23:28:05  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.2  2006/08/01 19:50:40  jenkins
	Moved useful enum values into class
	
	Revision 1.1  2006/07/07 17:44:03  jenkins
	First checked in.
	

	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_HEAD__
#define __FTFONTTABLE_HEAD__

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
	
	struct BigDate {
		uint32_t	bc;
		uint32_t	ad;
	};
	
#ifndef __cplusplus
	typedef struct BigDate BigDate;
#endif
	
	struct HEADTable {
		Fixed		version;
		Fixed		fontRevision;
		uint32_t	checkSumAdjustment;
		uint32_t	magicNumber;
		uint16_t	flags;
		uint16_t	unitsPerEm;
		BigDate		created;
		BigDate		modified;
		int16_t		xMin;
		int16_t		yMin;
		int16_t		xMax;
		int16_t		yMax;
		uint16_t	macStyle;
		uint16_t	lowestRecPPEM;
		int16_t		fontDirectionHint;
		int16_t		indexToLocFormat;
		int16_t		glyphDataFormat;
	};
	
#ifndef __cplusplus
	typedef struct HEADTable HEADTable;
#endif
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_head : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'head' ),
			kVersion = 0x00010000U,
			
			kShortGlyphOffsets				= 0,
			kLongGlyphOffsets				= 1,
			
			kYValueOfZeroIsBaseline			= 1,
			kXPositionOfLeftmostBitIsLSB	= 2,
			kScaledAndActualPointSizeDiffer	= 4,
			kUseIntegerScaling				= 8,
			kBit4							= 16,
			kInstructionsMayAlterGlyphWidth	= 16,	// OpenType only
			kLayoutVertically				= 32,
			kBit6							= 64,
			kFontRequiresLayout				= 128,
			kFontHasDefaultMorts			= 256,
			kFontHasRTLGlyphs				= 512,
			kFontHasIndicRearrangements		= 1024,
			kBit11							= 2048,
			kDataIsLossless					= 2048,	// OpenType only
			kBit12							= 4096,
			kFontIsConverted				= 4096,	// OpenType only
			kOptimizedForClearType			= 8192,	// OpenType only
			kBit14							= 16384,
			kLastResortFont					= kBit14,
			kBit15							= 32768,
			
			kMinUnitsPerEm					= 16,
			kMaxUnitsPerEm					= 16384,
			
			kMaxReasonableLowestPPEM		= 24,
			
			kStronglyR2LorB2TWithNeutrals	= -2,
			kStronglyR2LorB2T				= -1,
			kFullyMixedDirectionHint		=  0,
			kStronglyL2RorT2B				=  1,
			kStronglyL2RorT2BWithNeutrals	=  2,
			
			kMagicNumber					= 0x5F0F3CF5UL
			
		};
		
        static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );
		static FTData CreateDummyTable();

        FTFontTable_head( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_head( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_head( const FTFontTable& iOther );
		virtual ~FTFontTable_head();
		
		FTFontTable_head& operator=( const FTFontTable_head& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		void		SetModifiedDateToNow();
		void		SetModifiedDateToToday();
		
		Fixed		Version() const;
		Fixed		FontRevision() const;
		uint32_t	CheckSumAdjustment() const;
		uint32_t	MagicNumber() const;
		uint16_t	Flags() const;
		uint16_t	UnitsPerEm() const;
		int64_t		Created() const;
		void		GetCreated( BigDate& oDate ) const;
		int64_t		Modified() const;
		void		GetModified( BigDate& oDate ) const;
		int16_t		XMin() const;
		int16_t		YMin() const;
		int16_t		XMax() const;
		int16_t		YMax() const;
		uint16_t	MacStyle() const;
		uint16_t	LowestRecPPEM() const;
		int16_t		FontDirectionHint() const;
		int16_t		IndexToLocFormat() const;
		int16_t		GlyphDataFormat() const;
		bool		FontUsesLongGlyphOffsets() const { return IndexToLocFormat() == kLongGlyphOffsets; };
		
	protected:

		FTFontTable_head();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		void		SetModifiedDate( uint64_t iNewDate );
		
		Fixed		fVersion;
		Fixed		fFontRevision;
		uint32_t	fCheckSumAdjustment;
		uint32_t	fMagicNumber;
		uint16_t	fFlags;
		uint16_t	fUnitsPerEm;
		int64_t		fCreated;
		int64_t		fModified;
		int16_t		fXMin;
		int16_t		fYMin;
		int16_t		fXMax;
		int16_t		fYMax;
		uint16_t	fMacStyle;
		uint16_t	fLowestRecPPEM;
		int16_t		fFontDirectionHint;
		int16_t		fIndexToLocFormat;
		int16_t		fGlyphDataFormat;
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_HEAD__ */
