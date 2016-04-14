/*
	File:			FTFontTable_hmtx.h
 
	Contains:		C++ class individual TrueType font 'hmtx' tables
 
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

#ifndef __FTFONTTABLE_HMTX__
#define __FTFONTTABLE_HMTX__

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
	
	struct HMTXEntry {
		uint16_t	fAdvanceWidth;
		int16_t		fLeftSidebearing;
	};
	
#ifndef __cplusplus
	typedef struct HMTXEntry HMTXEntry;
#endif
	
	struct HMTXTable {
		HMTXEntry	fEntries[];
		/*	SInt16		leftSidebearing[]; */
	};
	
#ifndef __cplusplus
	typedef struct HMTXTable HMTXTable;
#endif
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_hmtx : public FTFontTable {
		
	public:
		
        static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );
		static FTData CreateDummyTable(size_t iGlyphCount);

		enum {
			kTag = FOUR_CHAR_CODE( 'hmtx' )
		};
		
		FTFontTable_hmtx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_hmtx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_hmtx( const FTFontTable& iOther );
		virtual ~FTFontTable_hmtx();
		
		FTFontTable_hmtx& operator=( const FTFontTable_hmtx& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		virtual HMTXEntry	GetMetrics( uint16_t iGlyphID ) const;
		
		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
		virtual bool CanGenerateTrimmedData() const { return true; };
		virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

	protected:
		
		FTFontTable_hmtx();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		ItemCount UpdateHHEA(uint32_t iGlyphCount, const HMTXEntry *iEntries, FTDictionary& oTableData) const;

		HMTXEntry		*_fEntries;
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_HMTX__ */
