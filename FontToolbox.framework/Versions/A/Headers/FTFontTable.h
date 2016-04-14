/*
	File:			FTFontTable.h
 
	Contains:		C++ class individual TrueType font tables
 
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

#ifndef __FTFONTTABLE__
#define __FTFONTTABLE__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTData.h"
#include "FTDictionary.h"
#include "FTString.h"

namespace ftx {
	
	class FTFont_sfnt;
	class FTXMLOptions;
	
	class FTFontTable {
		/*! \brief Base class for TrueType font tables.
		 *
		 *  FTFontTable is an base class for all sfnt-housed
		 *		font tables. Each individual class tag should
		 *		be associated with a distinct subclass to
		 *		cover its specific functionality (and to 
		 *		implement GetTag()); e.g., FTFontTable_cmap,
		 *		FTFontTable_morx.
		 */
	public:

		enum {
			kNULLTag = FOUR_CHAR_CODE( 'NULL' ),
			kInvalidChecksum = 0xFFFFFFFFU,
			
			kOTInvalidCoverageFormat = 0,
			kOTSingleRangeCoverageFormat = 1,
			kOTRangeArrayCoverageFormat = 2,
			};
			
		static FTFontTable* CreateTable( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		static FTFontTable* CreateTable( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = kInvalidChecksum );
		static FTFontTable* CreateTable( FTFont_sfnt *iFont, FourCharCode iTag, const FTData& iData, uint32_t iChecksum = kInvalidChecksum );
		static FTDictionary CreateTableFromXML( FTFont_sfnt *iFont, FourCharCode iTag, const FTString& iXML, void *ioUserData = nullptr );

		FTFontTable( FTFont_sfnt *iFont, FourCharCode iTag );
		FTFontTable( FTFont_sfnt *iFont, FourCharCode iTag, const FTData& iData, uint32_t iChecksum );
		FTFontTable( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = kInvalidChecksum );
		FTFontTable( const FTFontTable& iOther );
		virtual ~FTFontTable();
		
		FTFontTable& operator=( const FTFontTable& iOther );
		
		// These do a comparison of the raw, padded data in the table
		bool operator==( const FTFontTable& iOther ) const;
		bool operator!=( const FTFontTable* iOther ) const;

		virtual bool		IsDirty() const { return _fIsDirty; };
		virtual void		MakeDirty();
		virtual void		MakeClean() { _fIsDirty = false; };
		virtual void		PrintDiagnostics() const;
		virtual void		RebuildData() const;
		CFDataRef			CreateRebuiltData() const { return RebuildDataInternal(); };

		FTFont_sfnt				*GetFont() const { return _fFont; };
		virtual FourCharCode	GetTag() const;
		virtual ByteCount		GetOffset() const { return _fOffset; };
		virtual uint32_t		GetChecksum() const;
		virtual ByteCount		GetSize() const { return GetUnswappedDataLength(); };
		virtual const uint8_t	*GetUnswappedDataPtr() const;
		virtual ByteCount		GetUnswappedDataLength() const;
		
		CFStringRef				GetTagString() const;
		
		FTData		UnswappedData() const { return FTData(GetUnswappedDataPtr(), GetUnswappedDataLength()); };
		FTString	TagString() const { return FTString(GetTagString()); };

		static bool TableGeneratesXML(FourCharCode iTag);
		static bool TableParsesXML(FourCharCode iTag, const FTString &iXMLAsString);
		virtual FTString TableSchema() const;
		virtual	FTString ConvertToXML(const FTXMLOptions& iOptions,
                                      const FTGlyphID *iGlyphReordering) const;
		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
		virtual bool CanGenerateTrimmedData() const { return false; };
		virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const { return FTDictionary(); };

	protected:

		FTFontTable();
		
		/** @name Reading data
		 *  These functions are where data parsing takes place.
		 *		Specifically, ReadDataInternal() should be implemented
		 *		by subclasses to do their class-specific data parsing.
		 *		It is not necessary to call FTFontTable::ReadDataInternal()
		 *		in the subclass implementations.
		 */
		///@{
		virtual bool		DataRead() const { return _fDataRead; };
		virtual void		MarkDataRead() { _fDataRead = true; };
		virtual void		ReadData() const;
		virtual void		ReadDataInternal();
		
		virtual CFDataRef	RebuildDataInternal() const { return nullptr; };
		
		bool				ReadAndSwap4(const uint8_t *iPtr, uint32_t& oValue) const;
		bool				ReadAndSwap2(const uint8_t *iPtr, uint16_t& oValue) const;
		FTData				DataInRange(CFRange iRange) const;

		virtual bool		NotEqualsInternal(const FTFontTable *iOther) const;

		/** @name Reverse mapping
		 *  Used by subclasses to reverse-map a glyph ID to its index
		 *		in the given array (as a glyph ID). These are used 
		 *		when generating stripped versions of font tables.
		 */
		///@{
		static FTGlyphID MapGlyphID(FTGlyphID iOldGlyphID, const FTArray *iGlyphsToRetain);
		static FTGlyphID Swap2AndMapGlyphID(uint16_t iOldGlyphID, const FTArray *iGlyphsToRetain);
		///@}

		void CreateMappingInformation(const FTArray& iGlyphsToRetain, bool iRemoveGlyphs, bool oRetainGlyph[], FTGlyphID oGlyphIDMap[]) const;

	private:

		const void *DoGenericBinarySearchLookup( const SFNTLookupTable *table, UInt32 glyph ) const;
		const SFNTLookupSingle *FindSingle(const SFNTLookupSingleHeader *header, UInt32 glyph) const;
		const SFNTLookupSegment *FindSegment(const SFNTLookupSegmentHeader *header, UInt32 glyph) const;

		enum {
			kBufferSize = 1024
			};

		FTFont_sfnt*			_fFont;
		FourCharCode			_fTag;
		ByteCount				_fOffset;
		uint32_t				_fChecksum;
		CFDataRef				_fUnswappedData;
		mutable uint8_t*		_fUnswappedDataPtr;
		mutable ByteCount		_fUnswappedDataLength;
		
		mutable CFStringRef		_fTagString;
		
		bool					_fDataRead;
		bool					_fIsDirty;

	};
}

#endif /* __FTFONTTABLE__ */
