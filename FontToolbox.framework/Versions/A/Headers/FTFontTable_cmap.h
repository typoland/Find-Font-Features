/*
	File:			FTFontTable_cmap.h
 
	Contains:		C++ class individual TrueType font 'cmap' tables
 
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

#ifndef __FTFONTTABLE_CMAP__
#define __FTFONTTABLE_CMAP__

#include <Carbon/Carbon.h>
#include "FTEncoding.h"
#include "FTFontTable.h"

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(push,1)

namespace ftx {
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* CONSTANTS */
	
	enum {
		kOneByteMapClass				= 0,
		kMixedMapClass					= 1,
		kTwoByteMapClass				= 2,
		kMixedTwoFourByteMapClass		= 3,
		kFourByteMapClass				= 4,
		
		kHighWordFlagArraySize	= ( 65536 / 32 )
	};
	
	/* TYPES -- MAPPING TABLES */
	
	typedef struct {
		uint16_t	fPlatform;
		uint16_t	fScript;
		uint32_t	fOffset;
	} FTRawSubtable_cmap;
	
	typedef struct {
		uint16_t			fVersion;
		uint16_t			fNumSubtables;
		FTRawSubtable_cmap	fSubtables[];
	} FTRawTable_cmap;
	
	/* Used for formats 0, 2, 4, and 6 */
	
	typedef struct {
		uint16_t	fFormat;
		uint16_t	fLength;
		uint16_t	fLanguage;
	} FTMappingTableHeader;
	
	/* Used for formats 8.0, 10.0, 12.0, 13.0 */
	
	typedef struct  {
		Fixed		fFormat;
		uint32_t	fLength;
		uint32_t	fLanguage;
	} FTLargeMappingTableHeader;
	
	/* Header for format 14.0 is defined below */
	
	typedef struct  {
		FTMappingTableHeader	fHeader;
		uint8_t					fGlyphs[ 256 ];
	} FTFormat0MappingTable;
	
	typedef struct  {
		uint16_t	fFirstCode;
		uint16_t	fEntryCount;
		uint16_t	fIDDelta;
		uint16_t	fIDRangeOffset;
	} FTFormat2SubHeader;
	
	typedef struct  {
		FTMappingTableHeader	fHeader;
		uint16_t				fSubHeaderKeys[ 256 ];
		FTFormat2SubHeader		fSubHeaders[];
	} FTFormat2MappingTable;
	
	typedef struct {
		FTMappingTableHeader	fHeader;
		uint16_t				fSegCountTimesTwo;
		uint16_t				fSearchRange;
		uint16_t				fEntrySelector;
		uint16_t				fRangeShift;
		uint16_t				fEndCode[];
		/* actually [fSegCount] */
		/*	uint16_t			fReservedPad;							*/
		/*	uint16_t			fStartCode[segCount];					*/
		/*	int16_t				fIDDelta[segCount];						*/
		/*	uint16_t			fIDRangeOffset[segCount];				*/
		/*	uint16_t			fGlyphIndexArray[];	*/
	} FTFormat4MappingTable;
	
	typedef struct {
		FTMappingTableHeader	fHeader;
		uint16_t				fFirstChar;
		uint16_t				fRangeCount;
		uint16_t				fGlyphIndexArray[];
	} FTFormat6MappingTable;
	
	
	typedef struct {
		UnicodeScalarValue		fStartCharCode;
		UnicodeScalarValue		fEndCharCode;
		uint32_t				fStartGlyphCode;
	} FTCGGroup;
	
	typedef struct {
		FTLargeMappingTableHeader	fHeader;
		uint32_t					fIs32[ kHighWordFlagArraySize ];
		uint32_t					fNumGroups;
		FTCGGroup					fGroups[];
	} FTFormat8MappingTable;
	
	typedef struct {
		FTLargeMappingTableHeader	fHeader;
		uint32_t					fStartCharCode;
		uint32_t					fNumChars;
		uint16_t					fGlyphs[];
	} FTFormat10MappingTable;
	
	typedef struct {
		FTLargeMappingTableHeader	fHeader;
		uint32_t					fNumGroups;
		FTCGGroup					fGroups[];
	} FTFormat12MappingTable;
	
	
	typedef struct {
		uint8_t		fCharHighByte;
		uint16_t	fCharLowBytes;
		uint16_t	fGlyphID;
	} FTUVSMapping;
	
	typedef struct {
		uint32_t		fNumMappings;
		FTUVSMapping	fMappings[];
	} FTNonDefaultUVSTable;
	
	typedef struct {
		uint8_t		fCharHighByte;
		uint16_t	fCharLowBytes;
		uint8_t		fAdditionalCharCount;
	} FTUnicodeValueRange;
	
	typedef struct {
		uint32_t			fNumRanges;
		FTUnicodeValueRange	fRanges[];
	} FTDefaultUVSTable;
	
	typedef struct {
		uint8_t		fCharHighByte;
		uint16_t	fCharLowBytes;
		uint32_t	fDefaultTableOffset;
		uint32_t	fNonDefaultTableOffset;
	} FTVariationSelectorRecord;
	
	typedef struct {
		uint16_t						fFormat;
		uint32_t						fLength;
		uint32_t						fNumVarSelectorRecords;
		FTVariationSelectorRecord		fRecords[];
	} FTFormat14MappingTable;
	
	
	class FTEncoding;
	class FTSet;
	
	class FTFontTable_cmap : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'cmap' ),
			kVersion = 0
		};

        static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML, int16_t iDesiredFormat );
		static FTData CreateDummyTable();

        static CFDataRef GenerateTableData( CFArrayRef iSubtables, int16_t iDesiredFormat = FTEncoding::kSmallestFormat );
			// Take an array of 'cmap' subtables and turn them into one big 'cmap' table
		
		FTFontTable_cmap( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_cmap( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_cmap( const FTFontTable& iOther );
		virtual ~FTFontTable_cmap();
		
		FTFontTable_cmap& operator=( const FTFontTable_cmap& iOther );
		
		virtual bool operator==( const FTFontTable_cmap& iOther ) const;
		virtual bool operator!=( const FTFontTable_cmap& iOther ) const;
		
		virtual FourCharCode	GetTag() const;
		
		virtual uint16_t		Version() const;
		virtual CFArrayRef		Encodings() const;
		virtual CFIndex			EncodingCount() const;
		
		virtual const FTEncoding *GetIndEncoding( ItemCount iIndex ) const;
		virtual const FTEncoding *FindEncoding( FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage, ItemCount& oIndex, bool iExactMatch = false ) const;
		virtual const FTEncoding *operator[]( ItemCount iIndex ) const { return GetIndEncoding( iIndex ); };

		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
		virtual bool CanGenerateTrimmedData() const { return true; };
		virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

	protected:
		
		FTFontTable_cmap();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		void		DeleteData();
		
		uint16_t	_fVersion;
		CFArrayRef	_fEncodings;
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_CMAP__ */
