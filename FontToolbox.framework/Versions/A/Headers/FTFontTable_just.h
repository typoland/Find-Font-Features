/*
	File:			FTFontTable_just.h
 
	Contains:		C++ class individual TrueType font 'just' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_just.h,v $
	Revision 1.4  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.3  2007/01/15 23:28:06  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.2  2006/10/06 01:11:57  jenkins
	Remove dependencies on high-level frameworks, rename dylib, add tests for 'mort', 'just', and 'kern' <rdar://problems/4759963&4765869&4769556>.
	
	Revision 1.1  2006/09/29 06:40:14  jenkins
	Complete initial implementation of tests required for production work <rdar://problems/4427537>.
	
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_JUST__
#define __FTFONTTABLE_JUST__

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

	typedef UInt16 JUSTJustificationFlags;

	struct JustPCConditionalAddAction {
		Fixed               substThreshhold;        /* threshold of growth factor at which subst occurs */
		UInt16              addGlyph;
		UInt16              substGlyph;
	};
	struct JUSTWidthDeltaRecord {
		Fixed	beforeGrowLimit; 			/* ems AW can grow by at most on LT */
		Fixed	beforeShrinkLimit; 			/* ems AW can shrink by at most on LT */
		Fixed	afterGrowLimit; 				/* ems AW can grow by at most on RB */
		Fixed	afterShrinkLimit; 			/* ems AW can shrink by at most on RB */
		JUSTJustificationFlags	growFlags; 					/* flags controlling grow case */
		JUSTJustificationFlags	shrinkFlags; 				/* flags controlling shrink case */
	};
	
	struct JUSTWDCElement {
		UInt32	justClass;
		JUSTWidthDeltaRecord	wdr;
	};
	
	struct JUSTWidthDeltaCluster {
		UInt32	count;
		JUSTWDCElement	wdcElements[];
	};
	
	struct JUSTDirSpecificHeader {
		UInt16	stateTableOffset;
		UInt16	wdcTableOffset;
		UInt16	pcTableOffset;
		SFNTLookupTable	lookupTable;
		/* other stuff follows here */
	};
	
	struct JUSTTable {
		Fixed	version;
		UInt16	format;
		UInt16	horizOffset;
		UInt16	vertOffset;
		JUSTDirSpecificHeader	horizTable;
	};
	
	/* Overall structure of a postcompensation table is defined in PostcompTable. */
	
	struct PostcompTable {
		SFNTLookupTable	lookupTable;
		// action records here
	};
	
	/* A PCDuctilityAction defines a ductile axis along which the glyph will be varied. */
	struct PCDuctilityAction {
		long		ductilityAxis;
		Fixed		minimumLimit;
		Fixed		noStretchValue;
		Fixed		maximumLimit;
	};
	
	/* A PCDecompositionAction defines a ligature decomposition action. */
	struct PCDecompositionAction {
		Fixed			lowerLimit;
		Fixed			upperLimit;
		uint16_t		order;
		uint16_t		count;
		uint16_t		glyphs[1];
	};
	
	/* A PCConditionalAddAction defines a glyph substitution and add action. If the addGlyph
	 is equal to noGlyphcode, then no glyph will be added, and the justification for
	 the line will be redone. */
	struct PCConditionalAddAction {
		Fixed		substThreshhold;	/* threshold of growth factor at which subst occurs */
		uint16_t	addGlyph;
		uint16_t	substGlyph;
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_just : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'just' ),
			
			kCurrentJustTableVersion = fixed1,
			
			kUnlimitedGapFlag = 0x1000,
			
			kKashidaPriority	= 0,
			kWhiteSpacePriority	= 1,
			kInterCharPriority	= 2,
			kNullJustificationPriority	= 3,
			kNumberOfJustificationPriorities	= 4
		};
		
		FTFontTable_just( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_just( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = ftx::FTFontTable::kInvalidChecksum );
		FTFontTable_just( const FTFontTable& iOther );
		virtual ~FTFontTable_just();
		
		FTFontTable_just& operator=( const FTFontTable_just& iOther );
		
		virtual FourCharCode	GetTag() const;
		
	protected:
		
		FTFontTable_just();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
	};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_JUST__ */
