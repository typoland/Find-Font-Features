/*
	File:			FTFontTable_EBSC.h
 
	Contains:		C++ class individual TrueType font 'EBSC' tables
 
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

#ifndef __FTFONTTABLE_EBSC__
#define __FTFONTTABLE_EBSC__

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

/* The EBSCScaleTable describes the index entries for a single pointsize. */

struct TScaleTable_EBSC {
	BLOCLineMetrics	fHori;
	BLOCLineMetrics	fVert;
	uint8_t			fPpemX;
	uint8_t			fPpemY;
	uint8_t			fSubstitutePpemX;
	uint8_t			fSubstitutePpemY;
};

#ifndef __cplusplus
typedef struct TScaleTable_EBSC TScaleTable_EBSC;
#endif

/* The EBSCTable defines the top-level structure of a 'EBSC' table. */

struct TTable_EBSC {
	Fixed				fVersion;
	uint32_t			fNumSizes;
	TScaleTable_EBSC	fScaleTables[];
};

#ifndef __cplusplus
typedef struct TTable_EBSC TTable_EBSC;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_EBSC : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'EBSC' ),
		};

	FTFontTable_EBSC( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_EBSC( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_EBSC( const FTFontTable& iOther );
	virtual ~FTFontTable_EBSC();
	
	FTFontTable_EBSC& operator=( const FTFontTable_EBSC& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_EBSC();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_EBSC__ */
