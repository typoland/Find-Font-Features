/*
	File:			FTFontTable_OS_2.h
 
	Contains:		C++ class individual TrueType font 'OS_2' tables
 
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

#ifndef __FTFONTTABLE_OS_2__
#define __FTFONTTABLE_OS_2__

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

struct PANOSE
	{
	uint8_t	bFamilyType;
	uint8_t	bSerifStlye;
	uint8_t	bWeight;
	uint8_t	bProportion;
	uint8_t	bContrast;
	uint8_t	bStrokeVariation;
	uint8_t	bArmStyle;
	uint8_t	bLetterform;
	uint8_t	bMidline;
	uint8_t	bXHeight;
	};

#ifndef __cplusplus
typedef struct PANOSE PANOSE;
#endif

struct OS2Table
	{
	uint16_t		version;
	int16_t			filler1;
	uint16_t		usWeightClass;
	uint16_t		usWidthClass;
	int16_t			filler2[12];
	PANOSE			panose;
	uint32_t		filler3[4];
	FourCharCode	filler4;
	uint16_t		fsSelection;
	uint16_t		filler5[2];
	/* In the MS versions, other stuff follows here */
	};

#ifndef __cplusplus
typedef struct OS2Table OS2Table;
#endif

struct OS2TableVersion1
	{
	uint16_t		version;
	int16_t			xAvgCharWidth;
	uint16_t		usWeightClass;
	uint16_t		usWidthClass;
	int16_t			fsType;
	int16_t			ySubscriptXSize;
	int16_t			ySubscriptYSize;
	int16_t			ySubscriptXOffset;
	int16_t			ySubscriptYOffset;
	int16_t			ySuperscriptXSize;
	int16_t			ySuperscriptYSize;
	int16_t			ySuperscriptXOffset;
	int16_t			ySuperscriptYOffset;
	int16_t			yStrikeoutSize;
	int16_t			yStrikeoutPosition;
	int16_t			sFamilyClass;
	PANOSE			panose;
	uint32_t		ulUnicodeRange1;
	uint32_t		ulUnicodeRange2;
	uint32_t		ulUnicodeRange3;
	uint32_t		ulUnicodeRange4;
	FourCharCode	achVendID;
	uint16_t		fsSelection;
	uint16_t		usFirstCharIndex;
	uint16_t		usLastCharIndex;
	int16_t			sTypoAscender;
	int16_t			sTypoDescender;
	int16_t			sTypoLineGap;
	uint16_t		usWinAscent;
	uint16_t		usWinDescent;
	uint32_t		ulCodePageRange1;
	uint32_t		ulCodePageRange2;
	};

#ifndef __cplusplus
typedef struct OS2TableVersion1 OS2TableVersion1;
#endif

struct OS2TableVersion2
	{
	uint16_t		version;
	int16_t			xAvgCharWidth;
	uint16_t		usWeightClass;
	uint16_t		usWidthClass;
	int16_t			fsType;
	int16_t			ySubscriptXSize;
	int16_t			ySubscriptYSize;
	int16_t			ySubscriptXOffset;
	int16_t			ySubscriptYOffset;
	int16_t			ySuperscriptXSize;
	int16_t			ySuperscriptYSize;
	int16_t			ySuperscriptXOffset;
	int16_t			ySuperscriptYOffset;
	int16_t			yStrikeoutSize;
	int16_t			yStrikeoutPosition;
	int16_t			sFamilyClass;
	PANOSE			panose;
	uint32_t		ulUnicodeRange1;
	uint32_t		ulUnicodeRange2;
	uint32_t		ulUnicodeRange3;
	uint32_t		ulUnicodeRange4;
	FourCharCode	achVendID;
	uint16_t		fsSelection;
	uint16_t		usFirstCharIndex;
	uint16_t		usLastCharIndex;
	int16_t			sTypoAscender;
	int16_t			sTypoDescender;
	int16_t			sTypoLineGap;
	uint16_t		usWinAscent;
	uint16_t		usWinDescent;
	uint32_t		ulCodePageRange1;
	uint32_t		ulCodePageRange2;
	int16_t			sxHeight;
	int16_t			sCapHeight;
	uint16_t		usDefaultChar;
	uint16_t		usBreakChar;
	uint16_t		usMaxContext;
	};

#ifndef __cplusplus
typedef struct OS2TableVersion2 OS2TableVersion2;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_OS_2 : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'OS/2' ),
		
		kOS2TableVersion0				= 0,
		kOS2TableVersion1				= 1,
		kOS2TableVersion2				= 2,
		kOS2TableVersion3				= 3,
		kOS2TableVersion4				= 4,
		kCurrentOTTableVersion			= kOS2TableVersion4,

		kAppleOS2TableSize				= 68,
		kMSVersion0OS2TableSize			= 78,
		kMSVersion1OS2TableSize			= 86,
		kMSVersion2OS2TableSize			= 96,
		
		kFontographerNoEmbeddingMask	= 0x0001U,
		kNoEmbeddingMask				= 0x0002U,
		kPreviewAndPrintEmbeddingMask	= 0x0004U,
		kEditableEmbeddingMask			= 0x0008U,
		kBit4_ReservedMask				= 0x0100U,
		kBit5_ReservedMask				= 0x0200U,
		kBit6_ReservedMask				= 0x0400U,
		kBit7_ReservedMask				= 0x0800U,
		kNoSubsettingMask				= 0x0100U,
		kBitmapEmbedOnlyMask			= 0x0200U,
		kBit10_ReservedMask				= 0x0400U,
		kBit11_ReservedMask				= 0x0800U,
		kBit12_ReservedMask				= 0x1000U,
		kBit13_ReservedMask				= 0x2000U,
		kBit14_ReservedMask				= 0x4000U,
		kBit15_ReservedMask				= 0x8000U,
		kValidEmbeddingBitsMask			= 0x030EU,
		kReservedEmbeddingMask			= 0xFFFFU - kValidEmbeddingBitsMask,
		
		kUnicodeBasicLatin					=	 ( 1 << 0 ),
		kUnicodeLatin1Supplement			=	 ( 1 << 1 ),
		kUnicodeLatinExtendedA				=	 ( 1 << 2 ),
		kUnicodeLatinExtendedB				=	 ( 1 << 3 ),
		kUnicodeIPAExtensions				=	 ( 1 << 4 ),
		kUnicodeSpacingModifierLetters		=	 ( 1 << 5 ),
		kUnicodeCombiningDiacriticalMarks	=	 ( 1 << 6 ),
		kUnicodeGreek						=	 ( 1 << 7 ),
		kUnicodeCoptic						=	 ( 1 << 8 ),
		kUnicodeCyrillic					=	 ( 1 << 9 ),
		kUnicodeArmenian					=	( 1 << 10 ),
		kUnicodeHebrew						=	( 1 << 11 ),
		kUnicodeVai							=	( 1 << 12 ),
		kUnicodeArabic						=	( 1 << 13 ),
		kUnicodeNKo							=	( 1 << 14 ),
		kUnicodeDevanagari					=	( 1 << 15 ),
		kUnicodeBengali						=	( 1 << 16 ),
		kUnicodeGurmukhi					=	( 1 << 17 ),
		kUnicodeGujarati					=	( 1 << 18 ),
		kUnicodeOriya						=	( 1 << 19 ),
		kUnicodeTamil						=	( 1 << 20 ),
		kUnicodeTelugu						=	( 1 << 21 ),
		kUnicodeKannada						=	( 1 << 22 ),
		kUnicodeMalayalam					=	( 1 << 23 ),
		kUnicodeThai						=	( 1 << 24 ),
		kUnicodeLao							=	( 1 << 25 ),
		kUnicodeGeorgian					=	( 1 << 26 ),
		kUnicodeBalinese					=	( 1 << 27 ),
		kUnicodeHangulJamo					=	( 1 << 28 ),
		kUnicodeLatinExtendedAdditional		=	( 1 << 29 ),
		kUnicodeGreekExtended				=	( 1 << 30 ),
		kUnicodeGeneralPunctuation			=	( 1 << 31 ),

		// Yes, this is dorky, but it makes it easier to relate the
		//	bit numbers in the OpenType spec with these constants
		kUnicodeSuperscriptsAndSubscripts	=	( 1 << ( 32 - 32 ) ),
		kUnicodeCurrencySymbols				=	( 1 << ( 33 - 32 ) ),
		kUnicodeCombiningDiacriticalMarksForSymbols	
											=	( 1 << ( 34 - 32 ) ),
		kUnicodeLetterlikeSymbols			=	( 1 << ( 35 - 32 ) ),
		kUnicodeNumberForms					=	( 1 << ( 36 - 32 ) ),
		kUnicodeArrows						=	( 1 << ( 37 - 32 ) ),
		kUnicodeMathematicalOperators		=	( 1 << ( 38 - 32 ) ),
		kUnicodeMiscellaneousTechnical		=	( 1 << ( 39 - 32 ) ),
		kUnicodeControlPictures				=	( 1 << ( 40 - 32 ) ),
		kUnicodeOpticalCharacterRecognition	=	( 1 << ( 41 - 32 ) ),
		kUnicodeEnclosedAlphanumerics		=	( 1 << ( 42 - 32 ) ),
		kUnicodeBoxDrawing					=	( 1 << ( 43 - 32 ) ),
		kUnicodeBlockElements				=	( 1 << ( 44 - 32 ) ),
		kUnicodeGeometricShapes				=	( 1 << ( 45 - 32 ) ),
		kUnicodeMiscellaneousSymbols		=	( 1 << ( 46 - 32 ) ),
		kUnicodeDingbats					=	( 1 << ( 47 - 32 ) ),
		kUnicodeCJKSymbolsAndPunctuation	=	( 1 << ( 48 - 32 ) ),
		kUnicodeHiragana					=	( 1 << ( 49 - 32 ) ),
		kUnicodeKatakana					=	( 1 << ( 50 - 32 ) ),
		kUnicodeBopomofo					=	( 1 << ( 51 - 32 ) ),
		kUnicodeHangulCompatibilityJamo		=	( 1 << ( 52 - 32 ) ),
		kUnicodePhagsPa						=	( 1 << ( 53 - 32 ) ),
		kUnicodeEnclosedCJKLettersAndMonths	=	( 1 << ( 54 - 32 ) ),
		kUnicodeCJKCompatibility			=	( 1 << ( 55 - 32 ) ),
		kUnicodeHangul						=	( 1 << ( 56 - 32 ) ),
		kUnicodeSurrogates					=	( 1 << ( 57 - 32 ) ),
		kUnicodePhonecian					=	( 1 << ( 58 - 32 ) ),
		kUnicodeCJKUnifiedIdeographs		=	( 1 << ( 59 - 32 ) ),
		kUnicodePrivateUseArea				=	( 1 << ( 60 - 32 ) ),
		kUnicodeCJKCompatibilityIdeographs	=	( 1 << ( 61 - 32 ) ),
		kUnicodeAlphabeticPresentationForms	=	( 1 << ( 62 - 32 ) ),
		kUnicodeArabicPresentationFormsA	=	( 1 << ( 63 - 32 ) ),
		
		kUnicodeCombiningHalfMarks			=	( 1 << ( 64 - 64 ) ),
		kUnicodeCJKCompatibilityForms		=	( 1 << ( 65 - 64 ) ),
		kUnicodeSmallFormVariants			=	( 1 << ( 66 - 64 ) ),
		kUnicodeArabicPresentationB			=	( 1 << ( 67 - 64 ) ),
		kUnicodeHalfwidthAndFullwidth		=	( 1 << ( 68 - 64 ) ),
		kUnicodeSpecials					=	( 1 << ( 69 - 64 ) ),
		kUnicodeTibetan						=	( 1 << ( 70 - 64 ) ),
		kUnicodeSyriac						=	( 1 << ( 71 - 64 ) ),
		kUnicodeThaana						=	( 1 << ( 72 - 64 ) ),
		kUnicodeSinhala						=	( 1 << ( 73 - 64 ) ),
		kUnicodeMyanmar						=	( 1 << ( 74 - 64 ) ),
		kUnicodeEthiopic					=	( 1 << ( 75 - 64 ) ),
		kUnicodeCherokee					=	( 1 << ( 76 - 64 ) ),
		kUnicodeUnifiedCanadianAboriginalSyllabics
											=	( 1 << ( 77 - 64 ) ),
		kUnicodeOgham						=	( 1 << ( 78 - 64 ) ),
		kUnicodeRunic						=	( 1 << ( 79 - 64 ) ),
		kUnicodeKhmer						=	( 1 << ( 80 - 64 ) ),
		kUnicodeMongolian					=	( 1 << ( 81 - 64 ) ),
		kUnicodeBraillePatterns				=	( 1 << ( 82 - 64 ) ),
		kUnicodeYi							=	( 1 << ( 83 - 64 ) ),
		kUnicodeFilippino					=	( 1 << ( 84 - 64 ) ),
		kUnicodeOldItalic					=	( 1 << ( 85 - 64 ) ),
		kUnicodeGothic						=	( 1 << ( 86 - 64 ) ),
		kUnicodeDeseret						=	( 1 << ( 87 - 64 ) ),
		kUnicodeMusical						=	( 1 << ( 88 - 64 ) ),
		kUnicodeMathAlphanumeric			=	( 1 << ( 89 - 64 ) ),
		kUnicodePrivateUseAreaPlane15_16	=	( 1 << ( 90 - 64 ) ),
		kUnicodeVariationSelectors			=	( 1 << ( 91 - 64 ) ),
		kUnicodeTags						=	( 1 << ( 92 - 64 ) ),
		kUnicodeLimbu						=	( 1 << ( 93 - 64 ) ),
		kUnicodeTaiLe						=	( 1 << ( 94 - 64 ) ),
		kUnicodeNewTaiLue					=	( 1 << ( 95 - 64 ) ),
		
		kUnicodeBuginese					=	( 1 << ( 96 - 96 ) ),
		kUnicodeGlagolitic					=	( 1 << ( 97 - 96 ) ),
		kUnicodeTifinagh					=	( 1 << ( 98 - 96 ) ),
		kUnicodeYijingHexagramSymbols		=	( 1 << ( 99 - 96 ) ),
		kUnicodeSylotiNagri					=	( 1 << ( 100 - 96 ) ),
		kUnicodeLinearB						=	( 1 << ( 101 - 96 ) ),
		kUnicodeAncientGreekNumbers			=	( 1 << ( 102 - 96 ) ),
		kUnicodeUgaritic					=	( 1 << ( 103 - 96 ) ),
		kUnicodeOldPersian					=	( 1 << ( 104 - 96 ) ),
		kUnicodeShavian						=	( 1 << ( 105 - 96 ) ),
		kUnicodeOsmanya						=	( 1 << ( 106 - 96 ) ),
		kUnicodeCypriotSyllabary			=	( 1 << ( 107 - 96 ) ),
		kUnicodeKharoshthi					=	( 1 << ( 108 - 96 ) ),
		kUnicodeTaiXuanJingSymbols			=	( 1 << ( 109 - 96 ) ),
		kUnicodeCuneiform					=	( 1 << ( 110 - 96 ) ),
		kUnicodeCountingRodNumerals			=	( 1 << ( 111 - 96 ) ),
		kUnicodeSundanese					=	( 1 << ( 112 - 96 ) ),
		kUnicodeLepcha						=	( 1 << ( 113 - 96 ) ),
		kUnicodeOlChiki						=	( 1 << ( 114 - 96 ) ),
		kUnicodeSaurashtra					=	( 1 << ( 115 - 96 ) ),
		kUnicodeKayahLi						=	( 1 << ( 116 - 96 ) ),
		kUnicodeRejang						=	( 1 << ( 117 - 96 ) ),
		kUnicodeCham						=	( 1 << ( 118 - 96 ) ),
		kUnicodeAncientSymbols				=	( 1 << ( 119 - 96 ) ),
		kUnicodePhaistosDisc				=	( 1 << ( 120 - 96 ) ),
		kUnicodeCarian						=	( 1 << ( 121 - 96 ) ),
		kUnicodeDominoTiles					=	( 1 << ( 122 - 96 ) ),
		kUnicodeBit123_Reserved				=	( 1 << ( 123 - 96 ) ),
		kUnicodeBit124_Reserved				=	( 1 << ( 124 - 96 ) ),
		kUnicodeBit125_Reserved				=	( 1 << ( 125 - 96 ) ),
		kUnicodeBit126_Reserved				=	( 1 << ( 126 - 96 ) ),
		kUnicodeBit127_Reserved				=	( 1 << ( 127 - 96 ) ),
		
		kCodepage1252	=	( 1 << 0 ),
		kCodepage1250	=	( 1 << 1 ),
		kCodepage1251	=	( 1 << 2 ),
		kCodepage1253	=	( 1 << 3 ),
		kCodepage1254	=	( 1 << 4 ),
		kCodepage1255	=	( 1 << 5 ),
		kCodepage1256	=	( 1 << 6 ),
		kCodepage1257	=	( 1 << 7 ),
		kCodepage1258	=	( 1 << 8 ),
		kCodepage874	=	( 1 << 16 ),
		kCodepage932	=	( 1 << 17 ),
		kCodepage936	=	( 1 << 18 ),
		kCodepage949	=	( 1 << 19 ),
		kCodepage950	=	( 1 << 20 ),
		kCodepage1361	=	( 1 << 21 ),
		kCodepageMacRoman	=	( 1 << 29 ),
		kCodepageOEMCharset	=	( 1 << 30 ),
		kCodepageSymbolCharset	=	( 1 << 31 ),
		kCodepage869	=	( 1 << ( 48 - 32 ) ),
		kCodepage866	=	( 1 << ( 49 - 32 ) ),
		kCodepage865	=	( 1 << ( 50 - 32 ) ),
		kCodepage864	=	( 1 << ( 51 - 32 ) ),
		kCodepage863	=	( 1 << ( 52 - 32 ) ),
		kCodepage862	=	( 1 << ( 53 - 32 ) ),
		kCodepage861	=	( 1 << ( 54 - 32 ) ),
		kCodepage860	=	( 1 << ( 55 - 32 ) ),
		kCodepage857	=	( 1 << ( 56 - 32 ) ),
		kCodepage855	=	( 1 << ( 57 - 32 ) ),
		kCodepage852	=	( 1 << ( 58 - 32 ) ),
		kCodepage775	=	( 1 << ( 59 - 32 ) ),
		kCodepage737	=	( 1 << ( 60 - 32 ) ),
		kCodepage708	=	( 1 << ( 61 - 32 ) ),
		kCodepage850	=	( 1 << ( 62 - 32 ) ),
		kCodepage437	=	( 1 << ( 63 - 32 ) ),

		kFWidthUltraCondensed		= 1,
		kFWidthExtraCondensed		= 2,
		kFWidthCondensed 			= 3,
		kFWidthSemiCondensed 		= 4,
		kFWidthMedium 				= 5,
		kFWidthSemiExpanded 		= 6,
		kFWidthExpanded 			= 7,
		kFWidthExtraExpanded 		= 8,
		kFWidthUltraExpanded 		= 9,

		kFWeightThin				= 100,
		kFWeightExtraLight			= 200,
		kFWeightLight				= 300,
		kFWeightNormal				= 400,
		kFWeightMedium				= 500,
		kFWeightSemibold			= 600,
		kFWeightBold				= 700,
		kFWeightExtraBold			= 800,
		kFWeightBlack				= 900,
		
		kFSSelectionItalic			=   1,
		kFSSelectionUnderscore		=   2,
		kFSSelectionNegative		=   4,
		kFSSelectionOutlined		=   8,
		kFSSelectionStrikeout		=  16,
		kFSSelectionBold			=  32,
		kFSSelectionRegular			=  64,
		kFSSelectionUseTypoMetrics	= 128,
		kFSSelectionWeightWidthSlope
									= 256,
		kFSSelectionOblique			= 512
		};

    static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML);
    
	FTFontTable_OS_2( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_OS_2( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_OS_2( const FTFontTable& iOther );
	virtual ~FTFontTable_OS_2();
	
	FTFontTable_OS_2& operator=( const FTFontTable_OS_2& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual uint16_t	GetVersion() const { ReadData(); return _fVersion; };
	virtual int16_t		GetFSType() const { ReadData(); return _fFSType; };

protected:

	FTFontTable_OS_2();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	uint16_t		_fVersion;
	int16_t			_fFSType;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_OS_2__ */
