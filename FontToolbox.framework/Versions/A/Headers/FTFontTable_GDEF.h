/*
	File:			FTFontTable_GDEF.h
 
	Contains:		C++ class individual TrueType font 'GDEF' tables
 
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

#ifndef __FTFONTTABLE_GDEF__
#define __FTFONTTABLE_GDEF__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTTypes.h"

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
	
	/* The attachment point table */
	
	struct FTAttachmentPoint {
		uint16_t	fPointCount;
		uint16_t	fPointIndex[];
	};
	
	/* The attachment list table */
	
	struct FTAttachmentListTable {
		FTOpenTypeOffset	fCoverageOffset;
		uint16_t			fGlyphCount;
		FTOpenTypeOffset	fAttachmentPointOffset;
	};
	
	/* The single-coordinate caret value */
	
	struct FTCaretValueSingleCoordinate {
		uint16_t			fCaretValueFormat;		//	Should be 1
		int16_t				fCoordinate;			//	x- or y-value, in design units
	};
	
	/* The contour point caret value */
	
	struct FTCaretValueContourPoint {
		uint16_t			fCaretValueFormat;		//	Should be 2
		uint16_t			fCaretValuePoint;		//	Contour point index on glyph
	};
	
	/* The contour point caret value */
	
	struct FTCaretValueDesignUnit {
		uint16_t			fCaretValueFormat;		//	Should be 3
		int16_t				fCoordinate;			//	x- or y-value, in design units
		FTOpenTypeOffset	fCaretValuePoint;		//	Offset to device table for x- or y-value,
	};
	
	/* The ligature glyph table */
	
	struct FTLigatureGlyphTable {
		uint16_t			fCaretCount;
		FTOpenTypeOffset	fCaretValue[];
	};
	
	/* The ligature caret list table */
	
	struct FTLigatureCaretListTable {
		FTOpenTypeOffset	fCoverageOffset;
		uint16_t			fLigatureGlyphCount;
		FTOpenTypeOffset	fLigatureGlyphs[];
	};
	
	/* The mark attachment class table */
	
	struct FTMarkGlyphSetsTable {
		uint16_t			fMarkSetTableFormat;	// Should be 1
		uint16_t			fMarkSetCount;
		uint32_t			fCoverage[];
		//	Array of offsets to mark set coverage tables
	};
	
	/* The header */
	
	struct FTHeader_GDEF {
		uint32_t			fVersion;
		FTOpenTypeOffset	fGlyphClassDefOffset;
		FTOpenTypeOffset	fAttachListOffset;
		FTOpenTypeOffset	fLigCaretListOffset;
		FTOpenTypeOffset	fMarkAttachClassDefOffset;
		FTOpenTypeOffset	fMarkGlyphSetsDefOffset;
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_GDEF : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'GDEF' ),
			kInitialVersion = 0x00010000U,
			kCurrentVersion = 0x00010002U,
			
			kUndefined = 0,
			
			kGlyphArray = 1,
			kGlyphRangeArray = 2,
			
			// Glyph classes
			kBaseGlyph = 1,			// Single character, spacing glyph
			kLigatureGlyph = 2,		// Multiple character, spacing glyph
			kMarkGlyph = 3,			// Non-spacing combining glyph
			kComponentGlyph = 4,	// Part of a single character, spacing glyph
			
			kSingleValueCaretFormat = 1,
			kSinglePointCaretFormat = 2,
			kDesignUnitCaretFormat = 3,
			
			kMarkSetTableCurrentFormat	= 1,
			
		};
		
		FTFontTable_GDEF( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_GDEF( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_GDEF( const FTFontTable& iOther );
		virtual ~FTFontTable_GDEF();
		
		FTFontTable_GDEF& operator=( const FTFontTable_GDEF& iOther );
		
		virtual FourCharCode		GetTag() const { return kTag; };
		virtual uint32_t			GetVersion() const { ReadData(); return _fHeader.fVersion; };
		virtual FTOpenTypeOffset	GetGlyphClassDefOffset() const { ReadData(); return _fHeader.fGlyphClassDefOffset; };
		virtual FTOpenTypeOffset	GetAttachListOffset() const { ReadData(); return _fHeader.fAttachListOffset; };
		virtual FTOpenTypeOffset	GetLigCaretListOffset() const { ReadData(); return _fHeader.fLigCaretListOffset; };
		virtual FTOpenTypeOffset	GetMarkAttachClassDefOffset() const { ReadData(); return _fHeader.fMarkAttachClassDefOffset; };
		virtual FTOpenTypeOffset	GetMarkGlyphSetsDefOffset() const { ReadData(); return _fHeader.fMarkGlyphSetsDefOffset; };
		
		virtual uint16_t			GetGlyphClassDefType() const;
		virtual const uint16_t*		GetGlyphClassDef() const;
		virtual uint16_t			GetMarkGlyphSetsDefType() const;
		virtual const FTMarkGlyphSetsTable*
		GetMarkGlyphSetsDef() const;
		virtual ItemCount			GetMarkGlyphSetsCount() const;
		virtual uint16_t			GetIndMarkSetCoverageType( ItemCount iIndex ) const;
		virtual void *				GetIndMarkSetCoverage( ItemCount iIndex ) const;
		
	protected:
		
		FTFontTable_GDEF();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		FTHeader_GDEF	_fHeader;
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_GDEF__ */
