/*
	File:			FTFontTable_bsln.h
 
	Contains:		C++ class individual TrueType font 'bsln' tables
 
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

#ifndef __FTFONTTABLE_BSLN__
#define __FTFONTTABLE_BSLN__

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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_bsln : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'bsln' ),
		kCurrentVersion = fixed1,
		
		kDistanceFormatNoMap		= 0,
		kDistanceFormatWithMap		= 1,
		kControlPointFormatNoMap	= 2,
		kControlPointFormatWithMap	= 3,
		
		kRomanBaseline				= 0,
		kIdeographicCenterBaseline	= 1,
		kIdeographicLowBaseline		= 2,
		kHangingBaseline			= 3,
		kMathBaseline				= 4,
		kLastBaseline				= 31,
		kNumBaselineClasses			= kLastBaseline + 1,
		kInvalidBaselineClass		= kNumBaselineClasses,
		kNoBaselineOverride			= 255,
	};

    static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );
    
	FTFontTable_bsln( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_bsln( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_bsln( const FTFontTable& iOther );
	virtual ~FTFontTable_bsln();
	
	FTFontTable_bsln& operator=( const FTFontTable_bsln& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
protected:

	FTFontTable_bsln();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	FTString DistanceFormatNoMapAsXML() const;
	FTString DistanceFormatWithMapAsXML(const FTArray& iGlyphsToRetain) const;
	FTString ControlPointFormatNoMapAsXML() const;
	FTString ControlPointFormatWithMapAsXML(const FTArray& iGlyphsToRetain) const;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_BSLN__ */
