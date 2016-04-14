/*
	File:			FTFontTable_gcid.h
 
	Contains:		C++ class individual TrueType font 'gcid' tables
 
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

#ifndef __FTFONTTABLE_gcid__
#define __FTFONTTABLE_gcid__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTFontTable_bloc.h"

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

struct TableHeader_gcid {
	uint16_t	fVersion;
	uint16_t	fFormat;
	uint32_t	fSize;
	uint16_t	fRegistry;
	int8_t		fRegistryName[64 /* == kRosNameSize_gcid*/];//nullptr terminated
	uint16_t	fOrder;
	int8_t		fOrderName[64 /* == kRosNameSize_gcid*/]; //nullptr terminated
	uint16_t	fSupplementVersion;
	uint16_t	fCount;
	uint16_t	fCID[];
	
};

#ifndef __cplusplus
typedef struct TableHeader_gcid TableHeader_gcid;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_gcid : public FTFontTable {

public:

	enum {
		kCurrentVersion			= 0,
		kFormat0				= 0,
		kRosNameSize			= 64,
		kHeaderBinarySize		= 2 * kRosNameSize + 6 * sizeof(uint16_t) + sizeof(uint32_t),
		kInvalidCID				= 65535,

		kTag = FOUR_CHAR_CODE( 'gcid' ),
		};

	FTFontTable_gcid( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_gcid( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_gcid( const FTFontTable& iOther );
	virtual ~FTFontTable_gcid();
	
	FTFontTable_gcid& operator=( const FTFontTable_gcid& iOther );

	uint16_t GetCount() const { return _fCount; };

	uint16_t CIDFromGlyphID(FTGlyphID iGlyph) const;

	virtual FourCharCode	GetTag() const;

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
protected:

	FTFontTable_gcid();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

	uint16_t _fCount;
	const uint16_t *_fUnswappedCID;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_gcid__ */
