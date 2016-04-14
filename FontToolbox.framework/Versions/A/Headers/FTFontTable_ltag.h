/*
	File:			FTFontTable_ltag.h
 
	Contains:		C++ class individual TrueType font 'ltag' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2012-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_LTAG__
#define __FTFONTTABLE_LTAG__

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
	
	struct FTStringRange {
		uint16_t		fOffset;
		uint16_t		fLength;
	};
	
	typedef struct FTStringRange FTStringRange;
	
	struct FTHeader_ltag {
		uint32_t		fVersion;
		uint32_t		fFlags;
		uint32_t		fNumTags;
		FTStringRange	fRanges[];
	};
	
	typedef struct FTHeader_ltag FTHeader_ltag;
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTData;
	
	class FTFontTable_ltag : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'ltag' ),
			kCurrentVersion = 1,
			kNotFound = -1,
			kAppendNewTags = true,
			kDontAppendNewTags = false,
			kLanguageTagFeature = 39,
			// This isn't defined in SFNTLayoutTypes.h yet
		};
		
		FTFontTable_ltag( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_ltag( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_ltag( FTFont_sfnt *iFont, const FTData& iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_ltag( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_ltag( const FTFontTable& iOther );
		virtual ~FTFontTable_ltag();
		
		FTFontTable_ltag& operator=( const FTFontTable_ltag& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		CFIndex		GetNumLanguageTags() const;
		CFStringRef	GetIndTag( CFIndex iIndex ) const;
		bool		GetIndTag( CFIndex iIndex, char *oTag, CFIndex iBufferSize ) const;
		CFIndex		IndexOfTag( CFStringRef iTag ) const;
		CFIndex		IndexOfTag( const char *iTag ) const;
		CFIndex		IndexOfTag( CFStringRef iTag, bool iAppendNewTags );
		CFIndex		IndexOfTag( const char *iTag, bool iAppendNewTags );
		
		CFDataRef	CreateTableData() const;
		
	protected:
		
		FTFontTable_ltag();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		CFMutableArrayRef _fTags;
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_LTAG__ */
