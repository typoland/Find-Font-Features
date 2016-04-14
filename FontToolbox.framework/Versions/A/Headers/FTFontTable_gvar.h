/*
	File:			FTFontTable_gvar.h
 
	Contains:		C++ class individual TrueType font 'gvar' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_gvar.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:04  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/10/06 01:11:57  jenkins
	Remove dependencies on high-level frameworks, rename dylib, add tests for 'mort', 'just', and 'kern' <rdar://problems/4759963&4765869&4769556>.
	
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_GVAR__
#define __FTFONTTABLE_GVAR__

#include <iostream>
#include <sstream>

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

/*	The table header */

struct FTTableHeader_gvar {
		uint16_t	fVersion;
        uint16_t    fReserved;
		uint16_t	fAxisCount;
		uint16_t	fGlobalCoordCount;
		uint32_t	fOffsetToCoord;
		uint16_t	fGlyphCount;
		uint16_t	fFlags;
		uint32_t	fOffsetToData;
		uint32_t	fOffsets[];
	};

#ifndef __cplusplus
typedef struct FTTableHeader_gvar FTTableHeader_gvar;
#endif

typedef FTTableHeader_gvar GVARTableHeader;

/* The glyph variation array header */

struct FTGlyphVariationData {
		uint16_t	fTupleCount;
		uint16_t	fOffsetToData;
	};

#ifndef __cplusplus
typedef struct FTGlyphVariationData FTGlyphVariationData;
#endif

typedef FTGlyphVariationData GVARVariationTable;

/* The tuple variation array header */

struct FTTupleHeader_gvar {
		uint16_t	fTupleSize;
		uint16_t	fTupleIndex;
	};

#ifndef __cplusplus
typedef struct FTTupleHeader_gvar FTTupleHeader_gvar;
#endif

typedef FTTupleHeader_gvar GVARTupleVariation;

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

    class FTTuple {

    public:
        FTTuple(const FTFont_sfnt *iFont, FTGlyphID iGlyph, CFIndex iTupleIndex);
        FTTuple(const FTTuple& iOther);

        virtual ~FTTuple();

        FTTuple& operator=(const FTTuple& iOther);

        float GetTaggedAxisCoordinate(FourCharCode iAxisTag) const;
        float GetIndexedAxisCoordinate(CFIndex iAxisIndex) const;

        ItemCount   GetIntermediateCoordinateCount() const;
        void        GetIndIntermediateCoordinate(CFIndex iCoordinateIndex, float& oFrom, float& oTo);

        ItemCount   GetPointCount() const;
        FTPoint     GetIndDelta(CFIndex iPointIndex);

        const FTFont_sfnt*  GetFont() const { return _fFont; };
        FTGlyphID           GetGlyphID() const { return _fGlyphID; };
        CFIndex             GetTupleIndex() const { return _fTupleIndex; };

    protected:

    private:
        FTTuple();

        void                        ReadData() const;
        const FTTupleHeader_gvar	*NextTupleVariation(const FTTupleHeader_gvar* iTupleVar) const;
        const uint8_t				*UnpackPointNumbers(ItemCount& oTuplePointCount, FTArray& oPointNumbers, const uint8_t *iPackedData ) const;
        const uint8_t				*UnpackDeltas(ItemCount iTuplePointCount, FTArray& oDeltas, const uint8_t* iPackedData) const;
        const uint8_t               *ReadPackedShort(const uint8_t *iData, uint16_t& oResult) const;

        mutable bool                _fDataRead;
        const FTFont_sfnt*          _fFont;
        FTGlyphID                   _fGlyphID;
        CFIndex                     _fTupleIndex;
        mutable vector<float>       _fCoordinates;
        mutable vector<float>       _fIntermediateCoordinatesFrom;
        mutable vector<float>       _fIntermediateCoordinatesTo;
        mutable vector<FTPoint>     _fDeltas;

    };

class FTFontTable_gvar : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'gvar' ),

        kCurrentVersion = 1,

		kOffsetsAreLongFlag = 1,
		kTuplesSharePointNumbersFlag = 0x8000,
		kReservedTupleCountFlags = 0x7000,
		kTupleCountMask = 0x0FFF,

		kEmbeddedTupleCoordinate = 0x8000,
		kIntermediateTuple = 0x4000,
		kPrivatePointNumbers = 0x2000,
		kReservedTupleIndexFlag = 0x1000,
		kTupleIndexMask = 0x0FFF,
		
		kPackedDeltasMask = 0x00C0U,
		kDeltasAreBytes = 0,			/* points are moved by byte deltas */
		kDeltasAreWords = 0x40,			/* points are moved by word deltas */
		kDeltasAreZero = 0x80,			/* points are touched */
        kDeltaRunCountMask = 0x3F,

        kPointsAreWords = 0x80,
        kPointRunCountMask = 0x7F

		};

	static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );

	FTFontTable_gvar( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_gvar( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_gvar( const FTFontTable_gvar& iOther );
	virtual ~FTFontTable_gvar();
	
	FTFontTable_gvar& operator=( const FTFontTable_gvar& iOther );

	virtual FourCharCode	GetTag() const;
	
	uint16_t                GetVersion() const { ReadData(); return _fVersion; };
	ItemCount               GetAxisCount() const { ReadData(); return (ItemCount) _fAxisCount; };
	ItemCount               GetGlobalCoordinateCount() const { ReadData(); return (ItemCount) _fGlobalCoordCount; };
	ItemCount               GetGlyphCount() const { ReadData(); return (ItemCount) _fGlyphCount; };
	uint16_t                GetFlags() const { ReadData(); return _fFlags; };
	uint32_t                GetOffsetToCoordinates() const { ReadData(); return _fOffsetToCoordinates; };
	uint32_t                GetOffsetToData() const { ReadData(); return _fOffsetToData; };
	float                   GetGlobalCoordinate( ItemCount iCoordinateIndex, ItemCount iAxisIndex ) const;
	ByteCount               GlyphOffset( FTGlyphID iGlyph ) const;
	ByteCount               GlyphDataSize( FTGlyphID iGlyph ) const;
    FTData                  GlyphData( FTGlyphID iGlyph ) const;

    ItemCount               GetTupleCount(FTGlyphID iGlyphID) const;
    FTTuple*                GetIndTuple(FTGlyphID iGlyphID, CFIndex iTupleIndex);

	virtual FTString		TableSchema() const;
	virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
                                         const FTGlyphID *iGlyphReordering) const;
protected:

	FTFontTable_gvar();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

    void                        DumpGlobalCoordinates(ostream &iOutput) const;
    void                        DumpGlyphData(ostream &iOutput) const;
	const FTTupleHeader_gvar	*NextTupleVariation( const FTTupleHeader_gvar* iTupleVar, int iAxisCount ) const;
	const uint8_t				*UnpackPointNumbers( ItemCount iTuplePointCount, int16_t oPointNumbers[],
                                                    const uint8_t *iPackedData, ItemCount iGlyphPointCount ) const;
	const uint8_t				*UnpackDeltas( const uint8_t *iPackedData, int16_t oDeltaArray[], ItemCount iGlyphPointCount ) const;
    void                        OutputAxisRefID(ostream &iOutput, int iAxisIndex) const;
    const uint8_t               *ReadPackedShort(const uint8_t *iData, uint16_t& oResult) const;

    /* Type conversions */
    static FTShortFrac         FloatToFrac(float iValue);
    static float               FracToFloat(FTShortFrac iValue);

	uint16_t	_fVersion;
	uint16_t	_fAxisCount;
	uint16_t	_fGlobalCoordCount;
	uint16_t	_fGlyphCount;
	uint16_t	_fFlags;
	uint32_t	_fOffsetToCoordinates;
	uint32_t	_fOffsetToData;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_gvar__ */
