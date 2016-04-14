/*
	File:			FTFontTable_cvar.h
 
	Contains:		C++ class individual TrueType font 'cvar' tables
 
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

#ifndef __FTFONTTABLE_CVAR__
#define __FTFONTTABLE_CVAR__

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
	
	struct CVARTuple {
		UInt16	fTupleSize;
		UInt16	fTupleIndex;
	};
	
	struct CVARTable {
		Fixed		fVersion;
		UInt16		fTupleCount;
		UInt16		fOffsetToData;
		CVARTuple   fTuples[];
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_cvar : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'cvar' ),
			
			kFlagsMask					= 0xA000,
			kTupleCountMask				= 0x3FFF,
			
			kEmbeddedTupleCoordinate	= 0x8000,
			kIntermediateTuple			= 0x4000,
			kPrivateValueIndices		= 0x2000,
			kReservedTupleIndexFlag		= 0x1000,
			kTupleIndexMask				= 0x0FFF,
			
			kPackedDeltasMask = 0x00C0U,
			kDeltasAreBytes = 0,			/* points are moved by byte deltas */
			kDeltasAreWords = 0x40,			/* points are moved by word deltas */
			kDeltasAreZero = 0x80			/* points are touched */
		};
		
        static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );
        
		FTFontTable_cvar( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_cvar( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_cvar( const FTFontTable& iOther );
		virtual ~FTFontTable_cvar();
		
		FTFontTable_cvar& operator=( const FTFontTable_cvar& iOther );
		
		virtual FourCharCode	GetTag() const;
		
        virtual FTString		TableSchema() const;
        virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
                                             const FTGlyphID *iGlyphReordering) const;
	protected:
		
		FTFontTable_cvar();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
        void                        OutputAxisRefID(ostream &iOutput, int iAxisIndex) const;

        const CVARTuple				*NextTupleVariation( const CVARTuple* iTupleVar, int iAxisCount ) const;
        const UInt8					*UnpackValueNumbers( ItemCount iValueCount, int16_t oValueNumbers[], const UInt8 iPackedData[] ) const;
        const UInt8					*CalculateDeltas( ItemCount iPointCount, const int16_t iPointNumbers[], const UInt8 iPackedData[], int16_t oDeltaArray[] ) const;

	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_CVAR__ */
