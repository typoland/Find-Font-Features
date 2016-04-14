/*
	File:			FTFontTable_glyf.h
 
	Contains:		C++ class individual TrueType font 'glyf' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
*/

#ifndef __FTFONTTABLE_GLYF__
#define __FTFONTTABLE_GLYF__

#include <Carbon/Carbon.h>

#include "FTData.h"
#include "FTDictionary.h"
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
	
	struct GLYFPoint {
		Fixed	fX;
		Fixed	fY;
	};
	
	struct GLYFCoords {
		ItemCount	fNumCoords;
		GLYFPoint	fCoords[];
	};
	
	struct GLYFPointData {
		GLYFPoint	fCoordinates;
		ItemCount	fContour;
		uint16_t	fFlags;
	};
	
	struct GLYFPoints {
		ItemCount		fPointCount;
		GLYFPointData	fPointData[];
	};
	
	struct GLYFComponent {
		uint16_t		fFlags;
		int16_t			fGlyphIndex;
		uint16_t		fRest;
	};
	
	struct GLYFBounds {
		int16_t	fXMin;
		int16_t	fYMin;
		int16_t	fXMax;
		int16_t	fYMax;
	};
	
	struct GLYFEntry {
		int16_t		fNumContours;
		GLYFBounds	fBounds;
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	class FTTrueTypeGlyph;
	
	/* PROTOTYPES */
	
	class FTFontTable_glyf : public FTFontTable {
		
	public:

        static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML, bool iStripHints);
		static FTData CreateDummyTable();

		enum {
			kTag = FOUR_CHAR_CODE( 'glyf' ),
			
			kArgs1And2AreWordsFlag	= 0x0001,
			kArgsAreXYValuesFlag	= 0x0002,
			kRoundXYToGridFlag		= 0x0004,
			kWeHaveAScaleFlag		= 0x0008,
			kObsoleteFlag			= 0x0010,
			kMoreComponentsFlag		= 0x0020,
			kWeHaveXAndYScaleFlag	= 0x0040,
			kWeHaveTwoByTwoFlag		= 0x0080,
			kWeHaveHintsFlag		= 0x0100,
			kUseMyMetricsFlag		= 0x0200,
			kOverlapCompoundFlag	= 0x0400,
			
			kOnCurveFlag			= 0x01,
			kXShortFlag				= 0x02,
			kYShortFlag				= 0x04,
			kRepeatFlag				= 0x08,
			kThisXSameFlag			= 0x10,
			kThisYSameFlag			= 0x20,
			
			kAllComponentFlags		= ( kArgs1And2AreWordsFlag | kArgsAreXYValuesFlag | kRoundXYToGridFlag |
									   kWeHaveAScaleFlag | kMoreComponentsFlag | kWeHaveXAndYScaleFlag |
									   kWeHaveTwoByTwoFlag | kWeHaveHintsFlag | kUseMyMetricsFlag | kOverlapCompoundFlag ),
		};
		
		FTFontTable_glyf( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_glyf( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_glyf( const FTFontTable& iOther );
		virtual ~FTFontTable_glyf();
		
		FTFontTable_glyf& operator=( const FTFontTable_glyf& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		CFArrayRef				GetGlyphs() const;
		const FTTrueTypeGlyph	*GetGlyph( ItemCount iIndex ) const;
		
		ItemCount CountTTGlyphParts( FTGlyphID iGlyph, ItemCount *oNumPoints, ItemCount* oNumContours ) const;

		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
		virtual bool CanGenerateTrimmedData() const { return true; };
		virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

	protected:
		
		FTFontTable_glyf();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		void				ClearGlyphData();
		
		CFArrayRef			_fGlyphs;
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_GLYF__ */
