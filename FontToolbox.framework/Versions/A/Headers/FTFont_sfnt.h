/*
	File:			FTFont_sfnt.h
 
	Contains:		C++ class individual TrueType fonts
 
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

#ifndef __FTFONT_SFNT__
#define __FTFONT_SFNT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTData.h"
#include "FTEncoding.h"
#include "FTFont.h"
#include "FTFontTable_bdat.h"
#include "FTFontTable_feat.h"
#include "FTString.h"

namespace ftx {
	
	class FTBitmap;
	class FTEncoding;
	class FTFontContainer;
	class FTFont_FOND;
	class FTFontTable;
	class FTNameTableEntry;
	
#define GET_CONST_TABLE(font,tag) (dynamic_cast<const FTFontTable_##tag *> ((font).GetTaggedTable(FTFontTable_##tag::kTag)))
#define GET_TABLE(font,tag) (dynamic_cast<FTFontTable_##tag *> ((const_cast<FTFont_sfnt*>(&(font)))->GetTaggedTable(FTFontTable_##tag::kTag)))
	
	class FTFont_sfnt : public FTFont {
		
	public:
		
		enum {
			kInvalidGlyphID = 0xFFFFU,
			
			kEOTGlyphClass = 0,
			kOOBGlyphClass = 1,
			kDELGlyphClass = 2,
			kEOLGlyphClass = 3,
		};
		
		static bool IsATIFDerivedTable(FourCharCode iTag);
		static bool IsGIDDependentUneditableTable(FourCharCode iTag);
		static bool IsGIDDependentEditableTable(FourCharCode iTag);
		static bool IsNonGIDDependentTable(FourCharCode iTag);
		static bool IsUnknownDependencyTable(FourCharCode iTag);

		static FTData CreateMinimalFont(const FTString& iFontName, size_t iGlyphCount);

		FTFont_sfnt( FTFontContainer *iContainer, CFDataRef iData );
		FTFont_sfnt( FTFontContainer *iContainer, const FSRef& iFileRef, ByteCount iDirectoryOffset = 0 );
		FTFont_sfnt( FTFontContainer *iContainer, const uint8_t *iData, ByteCount iLength );
		FTFont_sfnt( FTFontContainer *iContainer, Handle iData );
		FTFont_sfnt( const FTFont_sfnt& iOther );
		
		virtual ~FTFont_sfnt();
		
		FTFont_sfnt& operator=( const FTFont_sfnt& );
		
		friend ostream& operator<<( ostream &iOut, const FTFont_sfnt& iFont );
		
		virtual void					Rebuild();
		virtual void					MakeClean() { Rebuild(); FTFont::MakeClean(); };
		
		//	Determines whether or not this font object is even parsable as
		//		an actual font
		virtual void					TestBasicUsability() const;
		
		// Returns a string which (hopefully) is a unique way of specifying a
		//		certain version of the font.  It is currently a concatination
		//		of the font's checkum (in hex) with its unique name
		virtual CFStringRef				GetIdentifier() const;
		FTString						Identifier() const { CFStringRef tReturnValue = GetIdentifier(); return tReturnValue != nullptr ? FTString(tReturnValue) : FTString("<<<ERROR>>>"); };
		
		// Returns the most useful user-visible name for the font as a string
		virtual CFStringRef				GetName() const;
		FTString						Name() const { CFStringRef tReturnValue = GetName(); return tReturnValue != nullptr ? FTString(tReturnValue) : FTString("<<<ERROR>>>"); };
		
		// Returns the PostScript name for the font as a string
		virtual CFStringRef				GetPostScriptName() const;
		FTString						PostScriptName() const { CFStringRef tReturnValue = GetPostScriptName(); return tReturnValue != nullptr ? FTString(tReturnValue) : FTString("<<<ERROR>>>"); };
		
		// Returns a constant indicating what kind of font this is
		virtual FTFont::EFontType		GetType() const { return FTFont::kTrueTypeFontType; };
		
		// Returns the *first* 'FOND' resouce (if any) associated with this font
		virtual const FTFont_FOND		*GetFOND() const;
		virtual CFStringRef				GetFONDName() const;
		
		//	Table functions
		ItemCount				CountTables() const;
		FourCharCode			GetIndTableTag( ItemCount iIndex ) const;
		FTFontTable*			GetIndTable( ItemCount iIndex ) const;
		FTFontTable*			GetTaggedTable( FourCharCode iTag ) const;
		bool					HasTaggedTable( FourCharCode iTag ) const;
		CFIndex					IndexOfTaggedTable( FourCharCode iTag ) const;
		CFMutableDataRef		CopyTaggedTableAsMutableData( FourCharCode iTag ) const;
		virtual void			SetTable( FourCharCode iTag, const FTFontTable& iTable );
		virtual void			CreateAndAddTable( FourCharCode iTag, CFDataRef iData );
		void					CreateAndAddTable( FourCharCode iTag, const FTData& iData ) { CreateAndAddTable(iTag, (CFDataRef)iData.Cast()); };
		void					CreateAndAddTables(const FTDictionary& iTables);
		virtual void			PrintDiagnostics() const;
		
		//	Getters
		virtual Fixed			GetScaler() const { return (Fixed) _fDirectoryHeader.format; };
		void					GetDirectoryHeader( sfntDirectory& oDirectory ) const { oDirectory = _fDirectoryHeader;	};
		virtual CFArrayRef		GetTables() const;
		uint16_t				GetFontUnitsPerEm() const;
		uint32_t				GetChecksumAdjustment() const;
		
		bool					IsHintedFont() const;
		bool					HasTrueTypeGlyphs() const;
		bool					HasOTPostScriptGlyphs() const;
		bool					HasType1PostScriptGlyphs() const;
		bool					HasSbitGlyphs() const;
		bool					IsSbitOnly() const;
		
		CFStringRef				GetUniqueName() const;
		FTString						UniqueName() const { CFStringRef tReturnValue = GetUniqueName(); return tReturnValue != nullptr ? FTString(tReturnValue) : FTString("<<<ERROR>>>"); };
		CFStringRef				GetFullName() const;
		FTString						FullName() const { CFStringRef tReturnValue = GetFullName(); return tReturnValue != nullptr ? FTString(tReturnValue) : FTString("<<<ERROR>>>"); };
		
		ItemCount				CountFontGlyphs() const;
		ItemCount				CountFontNames() const;
		ItemCount				CountFontEncodings() const;
		ItemCount				CountHorizontalLongMetrics() const;
		ItemCount				CountVerticalLongMetrics() const;
		ItemCount				CountGlobalCoordinates() const;
		ItemCount				CountVariationAxes() const;
		
		FTGlyphID				UnicodeToGlyphID( UnicodeScalarValue iUnicode ) const;
		UnicodeScalarValue		GlyphIDToUnicode( uint16_t iGlyphID ) const;
                                // Uses the 'cmap' only
		UnicodeScalarValue		ExtendedGlyphIDToUnicode( FTGlyphID iGlyphID ) const;
                                // Uses the 'cmap', 'Zapf' table, and glyph name

		CFStringRef				CopyGlyphName( FTGlyphID iGlyph ) const;
		FTString				GlyphName( FTGlyphID iGlyph ) const;
        bool                    HasGlyphNamed( const FTString& iName ) const;
		FTGlyphID				GlyphFromName( CFStringRef iName,
                                              FTGlyphID iProposedGlyphID = FTFont_sfnt::kInvalidGlyphID,
                                              bool iWarnOfUndefinedGlyphs = true ) const;
		FTGlyphID				GlyphFromName( const char *iName,
                                              FTGlyphID iProposedGlyphID = FTFont_sfnt::kInvalidGlyphID,
                                              bool iWarnOfUndefinedGlyphs = true ) const;
		
		virtual bool			DeleteFontName(	CFIndex iIndex );
		virtual bool			DeleteFontName( FontNameCode		iName,
													   FontPlatformCode	iPlatform,
													   FontScriptCode		iScript,
													   FontLanguageCode	iLanguage );
		
		virtual bool			DeleteFontTable( ItemCount iIndex );
		virtual bool			DeleteTaggedFontTable( FourCharCode iTag );
		
		const FTEncoding		*FindFontEncoding(
														  FontPlatformCode iPlatform,
														  FontScriptCode iScript,
														  FontLanguageCode iLanguage,
														  ItemCount& oIndex,
														  bool iExactMatch = false ) const;
		
		const FTNameTableEntry	*FindFontName(
													  FontNameCode iNameType,
													  FontPlatformCode iPlatform,
													  FontScriptCode iScript,
													  FontLanguageCode iLanguage,
													  CFIndex& oIndex ) const;
		
		const FTEncoding	*FindFontUnicodeEncoding( ItemCount& oIndex ) const;
		
		bool				FindFontFeature( uint16_t iFeatureType, FTFeatureName &oFeatureData, ItemCount &oIndex ) const;
		
		bool				FindFontSetting( uint16_t iFeatureType, ItemCount iSettingIndex, FTFeatureSelector &oSelectorData ) const;
		bool				FindFontSetting( uint16_t iFeatureType, uint16_t iSetting, FontNameCode &oNameCode, ItemCount &oIndex ) const;
		
		bool				FindFontVariation( ItemCount iAxis,
													  Fixed &oMinValue,
													  Fixed &oDefaultValue,
													  Fixed &oMaxValue,
													  FontNameCode &oNameID,
													  FourCharCode &oTag ) const;
		
		const FTEncoding	*GetIndEncoding( ItemCount iIndex ) const;
		const FTEncoding	*GetFontEncoding(
													 ItemCount iIndex,
													 FontPlatformCode& oPlatform,
													 FontScriptCode& oScript,
													 FontLanguageCode& oLanguage ) const;
		
		FTString				GetLocalizedName(FontNameCode iNameCode) const;
		const FTNameTableEntry	*GetFontName(
													 ItemCount			iIndex,
													 FontNameCode		*oName,
													 FontPlatformCode	*oPlatform,
													 FontScriptCode		*oScript,
													 FontLanguageCode	*oLanguage ) const;
		
		uint16_t				GetBitmapType() const;
		ItemCount				CountBitmapStrikes() const;
		void					GetIndStrikeData( ItemCount iStrikeIndex, FTBitmapStrikeData& oStrikeData ) const;
		FTBitmap*				GetFontBitmap( uint16_t iPointSize, FTGlyphID iGlyph ) const;
		FTBitmap*				GetIndFontBitmap( ItemCount iStrikeIndex, FTGlyphID iGlyph ) const;
		
	protected:
		
		FTFont_sfnt();
		
		ByteCount				GetDirectoryOffset() const { return _fDirectoryOffset; };
		
	private:

		static bool TagMatches(FourCharCode iTag, const FourCharCode *iTagArray);
		
		enum {
			kCalculateBitmapSize = -1,
		};
		
		void ValidateHeader() const;
		//	Perform basic validation functions to make sure
		//		this is a valid TrueType/OpenType font
		//	This function throws an exception if something is wrong
		
		void		SetTables( CFArrayRef iTables );
		void		DeleteAllData();
		void		DeleteTableData();
		FTBitmap*	FetchBitmapsFromData( FTGlyphID iGlyph, BDATBigMetrics& ioMetrics, uint16_t iImageFormat, const uint8_t *iData, CFIndex iDataLength ) const;

		static uint32_t AddTableToDirectory(FTData& iDirectory, uint32_t iCurrentOffset, FourCharCode iTag, const FTData& iTableData);

		static int TableEntryOffsetOrderCompareFunction( const void *arg1, const void *arg2 );
		static int TableEntrySizeOrderCompareFunction( const void *arg1, const void *arg2 );
		static int TableEntryAlphabeticalOrderCompareFunction( const void *arg1, const void *arg2 );
		static int32_t TableTagToInt( FourCharCode iTag );
		static const FourCharCode *GetIdealTableOrder();
		static const FourCharCode *gIdealTableOrder;
		static const FourCharCode gDefaultIdealTableOrder[];
		
		ByteCount		_fDirectoryOffset;
		sfntDirectory	_fDirectoryHeader;
		
		mutable CFArrayRef		_fTables;
		mutable CFStringRef		_fIdentifier;
		mutable CFStringRef		_fPostScriptName;
		mutable CFStringRef		_fFullName;
		mutable CFStringRef		_fFONDName;
		
		mutable CFMutableDictionaryRef _fGlyphNameCache;
		
		mutable uint16_t			_fGlyphCount;
		mutable uint16_t			_fHorizontalLongMetricsCount;
		mutable uint16_t			_fVerticalLongMetricsCount;
		mutable ItemCount			_fGlobalCoordinateCount;
		
	};
	
}

#endif /* __FTFONT_SFNT__ */
