/*
	File:			FTFontTable_GPOS.h
 
	Contains:		C++ class individual TrueType font 'GPOS' tables
 
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

#ifndef __FTFONTTABLE_GPOS__
#define __FTFONTTABLE_GPOS__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTFontTable_GSUB.h"

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

typedef uint16_t GPOSOffset;

/* The GPOSRangeRecord */

struct GPOSRangeRecord {
	uint16_t	start;
	uint16_t	end;
	uint16_t	startCoverageIndex;
};

/* The GPOSHeader */

struct GPOSHeader {
	Fixed version;
	GPOSOffset scriptListOffset;
	GPOSOffset featureListOffset;
	GPOSOffset lookupListOffset;
};

/* The GPOSValueRecord */

struct GPOSValueRecord {
	int16_t fXPlacement;
	int16_t fYPlacement;
	int16_t fXAdvance;
	int16_t fYAdvance;
	GPOSOffset fXPlaDevice;
	GPOSOffset fYPlaDevice;
	GPOSOffset fXAdvDevice;
	GPOSOffset fYAdvDevice;
};

/* The GPOSPairValueRecord */

struct GPOSPairValueRecord {
	uint16_t			fSecondGlyph;
	GPOSValueRecord		fValue1;
	GPOSValueRecord		fValue2;
};

/* The GPOSPairSet */

struct GPOSPairSet {
	uint16_t				fPairValueCount;
	GPOSPairValueRecord		fPairValueRecords[];
};

/* The GPOSPairPosFormat1 */

struct GPOSPairPosFormat1 {
	uint16_t				fPosFormat;
	GPOSOffset				fCoverageOffset;
	uint16_t				fValueFormat1;
	uint16_t				fValueFormat2;
	uint16_t				fPairSetCount;
	GPOSOffset				fPairSetOffset[];
};

/* The GPOSSinglePosFormat1 */

struct GPOSSinglePosFormat1 {
	uint16_t			fPosFormat;
	GPOSOffset			fCoverageOffset;
	uint16_t			fValueFormat;
	GPOSValueRecord		fValue;
};

/* GPOSClass2Record */
struct GPOSClass2Record {
	GPOSValueRecord		fValue1;
	GPOSValueRecord		fValue2;
};

/* GPOSClass1Record */
typedef GPOSClass2Record *GPOSClass1Record;

/* GPOSPairPosFormat2 */
struct GPOSPairPosFormat2 {
	uint16_t				fPosFormat;
	GPOSOffset				fCoverageOffset;
	uint16_t				fValueFormat1;
	uint16_t				fValueFormat2;
	GPOSOffset				fClassDef1;
	GPOSOffset				fClassDef2;
	uint16_t				fClass1Count;
	uint16_t				fClass2Count;
	GPOSClass1Record		fClass1Records[];
};

    /* GPOSMarkToBaseAttachment */
    struct GPOSMarkToBaseAttachment {
        uint16_t            fPosFormat;     // == 1
        GPOSOffset          fMarkCoverageOffset;
        GPOSOffset          fBaseCoverageOffset;
        uint16_t            fClassCount;
        GPOSOffset          fMarkArrayOffset;
        GPOSOffset          fBaseArrayOffset;
    };

    struct GPOSMarkRecord {
        uint16_t    fMarkClass;
        GPOSOffset  fAnchorOffset;
    };

    struct GPOSMarkArray {
        uint16_t        fMarkCount;
        GPOSMarkRecord  fMarkRecords[];
    };

    struct GPOSBaseRecord {
        GPOSOffset      fOffsets[];
    };

    struct GPOSBaseArray {
        uint16_t        fBaseCount;
        GPOSBaseRecord  fBaseRecords[];
    };

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_GPOS : public FTFontTable {

public:

	enum {
		kTag									= FOUR_CHAR_CODE( 'GPOS' ),
		
		kNoRequiredFeature						= 0xFFFFU,
		
		kCoverageFormat1						= 1,
		kCoverageFormat2						= 2,
		
		kSingleAdjustmentLookup					= 1,
		kPairAdjustmentLookup					= 2,
		kCursiveAttachmentLookup				= 3,
		kMarkToBaseAttachmentLookup				= 4,
		kMarkToLigatureAttachmentLookup			= 5,
		kMarkToMarkAttachmentLookup				= 6,
		kContextPositioningLookup				= 7,
		kChainedContextPositioningLookup		= 8,
		kExtensionPositioningLookup				= 9,

		kSingleAdjustmentPositioningFormat1		= 1,
		kSingleAdjustmentPositioningFormat2		= 2,
		
		kPairAdjustmentPositioningFormat1		= 1,
		kPairAdjustmentPositioningFormat2		= 2,
		
		kRightToLeftBit							= 0,
		kRightToLeftMask						= 0x0001U,
		kIgnoreBaseGlyphsBit					= 1,
		kIgnoreBaseGlyphsMask					= 0x0002U,
		kIgnoreLigaturesBit						= 2,
		kIgnoreLigaturesMask					= 0x0004U,
		kIgnoreMarksBit							= 3,
		kIgnoreMarksMask						= 0x0008U,
		kMarkAttachmentTypeBit					= 8,
		kMarkAttachmentTypeMask					= 0xFF00U,
		
		kXPlacementBit							= 0,
		kXPlacementMask							= 0x0001U,
		kYPlacementBit							= 1,
		kYPlacementMask							= 0x0002U,
		kXAdvanceBit							= 2,
		kXAdvanceMask							= 0x0004U,
		kYAdvanceBit							= 3,
		kYAdvanceMask							= 0x0008U,
		kXPlaDeviceBit							= 4,
		kXPlaDeviceMask							= 0x0010U,
		kYPlaDeviceBit							= 5,
		kYPlaDeviceMask							= 0x0020U,
		kXAdvDeviceBit							= 6,
		kXAdvDeviceMask							= 0x0040U,
		kYAdvDeviceBit							= 7,
		kYAdvDeviceMask							= 0x0080U,
		
		kValueRecordReservedMask				= 0xFF00U
		};

	FTFontTable_GPOS( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_GPOS( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_GPOS( const FTFontTable& iOther );
	virtual ~FTFontTable_GPOS();
	
	FTFontTable_GPOS& operator=( const FTFontTable_GPOS& iOther );

	virtual FourCharCode	GetTag() const;
	
	const FeatureListTable *GetFeatureListTable() const;
	const FeatureRecord *GetFeatureRecord( int iIndex ) const;
	
protected:

	FTFontTable_GPOS();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_GPOS__ */
