/*
	File:			FTFontTable_sbix.h
 
	Contains:		C++ class individual TrueType font 'sbix' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2010-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_SBIX__
#define __FTFONTTABLE_SBIX__

#include <Carbon/Carbon.h>
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

/* NB, we don't use Points below because they are (v, h) instead of (h, v) <rdar://problem/11648218> */

	struct TGlyphData_sbix {
		int16_t		fOriginOffsetX;
		int16_t		fOriginOffsetY;
		char		fPathString[];
	};

	struct TMaskedGlyphData_sbix {
		uint32_t		fMaskOffset;
		FourCharCode	fGraphicsType;
		uint8_t			fGraphicsData[];
	};

	struct TMaskData_sbix {
		uint32_t		fLength;			// including the header
		uint16_t		fReserved;
		uint16_t		fBlendMode;
		int16_t			fOriginOffsetX;
		int16_t			fOriginOffsetY;
		FourCharCode	fGraphicsType;
		uint8_t			fGraphicsData[];
	};

	struct TGlyphEmbeddedGraphicsData_sbix {
		int16_t			fOriginOffsetX;
		int16_t			fOriginOffsetY;
		FourCharCode	fGraphicsType;
		uint8_t			fGraphicsData[];
	};

	struct TStrike_sbix {
		uint16_t	fPointSize;
		uint16_t	fResolution;
		uint32_t	fGlyphDataOffsets[];
		// There are numGlyphs + 1 of these
	};

	struct THeader_sbix {
		uint16_t		fVersion;
		uint16_t		fFlags;
		uint32_t		fNumStrikes;
		uint32_t		fStrikeOffsets[];
	};

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_sbix : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'sbix' ),
		kVersion = 1,
		
		kEmbeddedDataFlag = 1,
		kDrawBitmapsAndOutlines = 2,

		kBlendModeMultiply = 0,
		kBlendModeDarken = 1,
		kBlendModeHardLight = 2,
		kBlendModeSourceAtop = 3,
		kBlendModeXOR = 4,
		
		kGraphicsType_jpg = FOUR_CHAR_CODE( 'jpg ' ),
		kGraphicsType_pdf = FOUR_CHAR_CODE( 'pdf ' ),
		kGraphicsType_png = FOUR_CHAR_CODE( 'png ' ),
		kGraphicsType_tiff = FOUR_CHAR_CODE( 'tiff' ),

		kDuplicateDataTag = FOUR_CHAR_CODE( 'dupe' ),
		kMaskDataTag = FOUR_CHAR_CODE( 'mask' ),
		kBlendDataTag = FOUR_CHAR_CODE( 'blen' ),

		kCARDataTag = FOUR_CHAR_CODE('card'),

		kMaskHeaderSize = sizeof(uint32_t) + 2 * sizeof(uint16_t) + 2 * sizeof(int16_t) + sizeof(FourCharCode),

		kInvalidIndex = -1,

		};

	FTFontTable_sbix( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_sbix( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_sbix( const FTFontTable& iOther );
	virtual ~FTFontTable_sbix();
	
	FTFontTable_sbix& operator=( const FTFontTable_sbix& iOther );

	virtual FourCharCode	GetTag() const;
	
	bool		GlyphDataEmbedded() const;
	CFIndex		StrikeCount() const;
	uint16_t	GetIndStrikePointSize( CFIndex iStrikeIndex ) const;
	uint16_t	GetIndStrikeResolution( CFIndex iStrikeIndex ) const;
	bool		StrikeHasDataForGlyph( CFIndex iStrikeIndex, FTGlyphID iGlyphID ) const;
	FTData		RawGlyphData( CFIndex iStrikeIndex, FTGlyphID iGlyphID,
							 Point& oGlyphOrigin, FourCharCode &oGraphicDataType,
							 int16_t& oMaskIndex, int16_t& oBlendIndex ) const;

	CFIndex		MaskCount() const { ReadData(); return _fMasks.Length(); };
	FTData		GetIndMask( CFIndex iIndex, uint16_t& oFlags, uint16_t& oBlendMode, Point& oGlyphOrigin, FourCharCode& oMaskDataType) const;
	CFIndex		MaskOffsetToIndex(uint32_t iMaskOffset) const;
	uint32_t	MaskIndexToOffset(CFIndex iMaskIndex) const;

	CFIndex		BlendCount() const { ReadData(); return _fBlends.Length(); };
	FTData		GetIndBlend( CFIndex iIndex, uint16_t& oFlags, uint16_t& oBlendMode, Point& oGlyphOrigin, FourCharCode& oMaskDataType) const;
	CFIndex		BlendOffsetToIndex(uint32_t iMaskOffset) const;
	uint32_t	BlendIndexToOffset(CFIndex iBlendIndex) const;

	virtual FTString		TableSchema() const;
	virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
                                         const FTGlyphID *iGlyphReordering) const;
	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;

	FTData		CARCatalogue() const { ReadData(); return _fCARCatalogue; };

protected:

	FTFontTable_sbix();
	virtual void		ReadDataInternal();

private:

	FTString BasicGlyphData(FTGlyphID iGlyphID, bool iIncludeGlyphNames, Point tGlyphOrigin) const;
	FTString GlyphDataAsXML(const FTXMLOptions& iOptions,
							int iStrikeIndex,
							FTGlyphID iGlyphID,
							const FTArray* iGlyphsToRetain = nullptr) const;
	FTString MaskDataAsXML() const;
	FTString BlendDataAsXML() const;
	FTString CARCatalogueAsXML() const;

	uint16_t _fFlags;
	FTArray _fMasks;
	FTArray _fBlends;
	mutable FTData _fCARCatalogue;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_SBIX__ */
