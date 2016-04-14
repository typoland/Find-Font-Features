/*
	File:		BOFFont.h
 
	Contains:	Class representing a single TrueType font

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

@class BOFFontContainer;

@interface BOFFont : NSObject

+(BOFFont*)fontWithFontContainer:(BOFFontContainer*)container index:(ItemCount)index;

@property(assign,readonly) BOFFontContainer *container;

@property(assign,readonly) BOOL isDirty;
@property(strong,readonly) NSString *identifier;
@property(strong,readonly) NSString *name;
@property(strong,readonly) NSString *postScriptName;

@property(assign,readonly) void *fontPtr;

@property(strong,readonly) NSData *data;
@property(assign,readonly) void *dataPtr;
@property(assign,readonly) NSUInteger dataLength;

- (void)makeDirty;
- (void)makeClean;

- (void)testBasicUsability;
- (void)printDiagnostics;

@end

@class BOFFontTable;

@interface BOFFont_sfnt : BOFFont

- (void)rebuild;
- (void)makeClean;

- (void)testBasicUsability;
- (void)printDiagnostics;

@property(strong,readonly) NSArray *tables;
- (BOFFontTable*)tableWithTag:(NSString*)tag;
- (BOOL)createAndAddTable:(NSData*)tableData withTag:(NSString*)tag error:(NSError**)error;

@property(assign,readonly) Fixed scaler;
@property(assign,readonly) NSUInteger unitsPerEm;
@property(assign,readonly) NSUInteger checkumAdjustment;
@property(assign,readonly) BOOL isHinted;
@property(assign,readonly) BOOL hasTrueTypeGlyphs;
@property(assign,readonly) BOOL hasOTPostScriptGlyphs;
@property(assign,readonly) BOOL hasType1PostScriptGlyphs;
@property(assign,readonly) BOOL hasSbitGlyphs;
@property(assign,readonly) BOOL isSbitOnly;

@property(assign,readonly) ItemCount glyphCount;
@property(assign,readonly) ItemCount encodingCount;
@property(assign,readonly) ItemCount horizontalLongMetricsCount;
@property(assign,readonly) ItemCount verticalLongMetricsCount;
@property(assign,readonly) ItemCount globalCoordinateCount;
@property(assign,readonly) ItemCount variationAxisCount;

@property(strong,readonly) NSString *uniqueName;
@property(strong,readonly) NSString *fullName;

- (BOFGlyphID)glyphIDFromUnicode:(UnicodeScalarValue)unicode;
- (UnicodeScalarValue)unicodeFromGlyphID:(BOFGlyphID)glyphID;
	// Uses the 'cmap' only
- (UnicodeScalarValue)ExtendedUnicodeFromGlyphID:(BOFGlyphID)glyphID;
	// Uses the 'cmap', 'Zapf' table, and glyph name

- (NSString*)nameOfGlyph:(BOFGlyphID)glyphID;
- (BOOL)hasGlyphNamed:(NSString*)glyphName;
- (BOFGlyphID)glyphFromName:(NSString*)glyphName;
- (BOFGlyphID)glyphFromName:(NSString*)glyphName proposedGlyphID:(BOFGlyphID)glyphID;
- (BOFGlyphID)glyphFromName:(NSString*)glyphName proposedGlyphID:(BOFGlyphID)glyphID warnOfUndefinedGlyphs:(BOOL)warnOfUndefinedGlyphs;

#if 0

// Returns a constant indicating what kind of font this is
virtual FTFont::EFontType		GetType() const { return FTFont::kTrueTypeFontType; };

// Returns the *first* 'FOND' resouce (if any) associated with this font
virtual const FTFont_FOND		*GetFOND() const;
virtual CFStringRef				GetFONDName() const;


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

#endif

@end
