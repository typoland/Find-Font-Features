/*
	File:			FTFontTable_morx.h
 
	Contains:		C++ class individual TrueType font 'morx' tables
 
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

#ifndef __FTFONTTABLE_MORX__
#define __FTFONTTABLE_MORX__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(push,2)

/* ----------------------------------------------------------------------------------------- */

/* NAMESPACE */

namespace ftx {

	class FTSet;

/* ----------------------------------------------------------------------------------------- */

/* CONSTANTS */

/* ----------------------------------------------------------------------------------------- */

/* TYPES */

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_morx : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'morx' ),
        kVersion2 = 2,
		kVersion3 = 3,
		kCurrentVersion = kVersion3,

		kVerticalFlag = 0x80000000U,
		kDescendingFlag = 0x40000000U,
		kIgnoreVerticalFlag = 0x20000000U,
		kTypeMask = 0x000000FFU,
		kLogicalOrderFlag = 0x10000000U,
		};

	FTFontTable_morx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_morx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_morx( const FTFontTable& iOther );
	virtual ~FTFontTable_morx();
	
	FTFontTable_morx& operator=( const FTFontTable_morx& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual Fixed			GetVersion() const { ReadData(); return _fVersion; };
	uint16_t				GetIntVersion() const { ReadData(); return FTFixedToInt(_fVersion); };

	virtual uint32_t		CountChains() const;
	const MorxChain*		GetIndChain(uint32_t iChainIndex) const;

	uint32_t				CountSubtables(uint32_t iChainIndex) const;
	const MorxSubtable*		GetIndSubtable(uint32_t iChainIndex, uint32_t iSubtableIndex) const;

	virtual ItemCount		CountDefaultFeatures() const;
	uint32_t				CountFeatures(uint32_t iChainIndex) const;
	const MortFeatureEntry*	GetIndFeature(uint32_t iChainIndex, uint32_t iFeatureIndex) const;
	sfntFontRunFeature		GetFeatureData_Zapf(uint32_t iChainIndex, uint32_t iFeatureIndex, FTSet *oGlyphSet) const;



protected:

	FTFontTable_morx();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	FTSet				ContextualGlyphSet(const MorxContextualSubtable *iSubtable, uint32_t iTableLength) const;
	FTSet				NoncontextualGlyphSet(const MortSwashSubtable *iSubtable) const;
	FTSet				LigatureGlyphSet(const MorxLigatureSubtable *iSubtable, uint32_t iTableLength) const;
	FTSet				InsertionGlyphSet(const MorxInsertionSubtable *iSubtable, uint32_t iTableLength) const;

	Fixed				_fVersion;
	uint32_t			_fNumChains;
	ItemCount			_fNumDefaultFeatures;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_MORX__ */
