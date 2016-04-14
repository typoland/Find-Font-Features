/*
	File:			FTFontTable_prop.h
 
	Contains:		C++ class individual TrueType font 'prop' tables
 
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

#ifndef __FTFONTTABLE_PROP__
#define __FTFONTTABLE_PROP__

#include <Carbon/Carbon.h>

#include "FTFontTable.h"
#include "FTFont_sfnt.h"
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

typedef uint16_t FTPropertyValue;

struct FTTable_prop
	{
	Fixed				fVersion;
	uint16_t			fFormat;
	uint16_t			fDefaultProperty;
	SFNTLookupTable		fLookup;
	};

#ifndef __cplusplus
typedef struct FTTable_prop FTTable_prop;
#endif

struct FTSymmetricSwapPair
	{
	uint16_t	fOpenSemantic;
	uint16_t	fCloseSemantic;
	};

#ifndef __cplusplus
typedef struct FTSymmetricSwapPair FTSymmetricSwapPair;
#endif

struct FTPropRange
{
	FTGlyphID			fRangeStart;
	FTPropertyValue		fValue;
};

#ifndef __cplusplus
typedef struct FTPropRange FTPropRange;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_prop : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'prop' ),

		kInvalidProperty			= 0xFFFFU,

		kOriginalVersion			= 0x00010000L,
		kConnectsRightVersion		= 0x00020000L,
		kUnicode3_0Version			= 0x00030000L,
		
		kHasNoLookupData			= 0,
		kHasLookupData				= 1,
		
		kIsFloater 						= 0x8000U,
		kIsLeftTopHanger				= 0x4000U,
		kIsRightBottomHanger			= 0x2000U,
		kUseRLBracketingGlyph			= 0x1000U,
		kBracketingGlyphOffsetMask		= 0x0F00U,
		kBracketingGlyphOffsetShift		= 0x0008U,
		kShiftedBracketingGlyphMask		= ( kBracketingGlyphOffsetMask >> kBracketingGlyphOffsetShift ),
		kGlyphConnectsOnRight			= 0x0080U,
		kReservedPropBits				= 0x0070U,
		kDirectionClassMask				= 0x000FU,
		
		kNonMirroringPropertiesMask		= kIsFloater + kIsLeftTopHanger + kIsRightBottomHanger + kGlyphConnectsOnRight + kDirectionClassMask,
		
		kInvalidVersion1Bits			= kGlyphConnectsOnRight | kReservedPropBits,
		
		kLeftToRightClass				= 0,
		kRightToLeftClass				= 1,
		kArabicLetterClass				= 2,
		kEuropeanNumberClass			= 3,
		kEuropeanNumberSeperatorClass	= 4,
		kEuropeanNumberTerminatorClass	= 5,
		kArabicNumberClass				= 6,
		kCommonNumberSeperatorClass		= 7,
		kBlockSeperatorClass			= 8,
		kSegmentSeperatorClass			= 9,
		kWhitespaceClass				= 10,
		kOtherNeutralClass				= 11,
		kSpecialEuropeanNumberClass		= 12,
		kNumDirectionalityClasses
		};

    static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );

	FTFontTable_prop( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_prop( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_prop( const FTFontTable& iOther );
	virtual ~FTFontTable_prop();
	
	FTFontTable_prop& operator=( const FTFontTable_prop& iOther );

	virtual FourCharCode	GetTag() const;
	
	Fixed				GetVersion() const { ReadData(); return _fVersion; };
	uint16_t			GetFormat() const { ReadData(); return _fFormat; };
	FTPropertyValue		GetDefaultProperties() const { ReadData(); return _fDefaultProperty; };
	FTPropertyValue		GetProperties( ItemCount iIndex ) const;
	static FTPropertyValue		
						MakePairMask( FTGlyphID iFromGlyph, FTGlyphID iToGlyph, bool iIsRLScript );
	static FTPropertyValue
						UnicodeTagToDirectionality( CFStringRef iString );
	static CFDataRef	MakePropTableFromArray( FTPropertyValue *iPropArray, ItemCount iGlyphCount );

	static void			InterpretProperties(FTPropertyValue iProperties,
											bool& oIsFloater, bool& oIsLeftTopHanger, bool& oIsRightBottomHanger, bool& oGlyphConnectsOnRight,
											int& oMirrorGlyphOffset, int8_t& oDirectionality);
	static const char *DirectionalityClassToUnicodeTag( FTPropertyValue iProperties );

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;

protected:

	FTFontTable_prop();
	
	void ClearData();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	static CFDataRef	MakeFormat0Table( FTPropertyValue *iPropArray, ItemCount iGlyphCount );
	static CFDataRef	MakeFormat2Table( FTPropertyValue *iPropArray, ItemCount iGlyphCount );

	FTString			PropertiesAsXML(const FTXMLOptions& iOptions,
										FTGlyphID iGID,
										const FTArray* iGlyphsToRetain = nullptr,
										FTGlyphID iActualGID = FTFont_sfnt::kInvalidGlyphID) const;

	Fixed				_fVersion;
	uint16_t			_fFormat;
	uint16_t			_fDefaultProperty;
	const FTPropertyValue *_fProperties;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_prop__ */
