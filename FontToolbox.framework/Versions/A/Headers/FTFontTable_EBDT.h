/*
	File:			FTFontTable_EBDT.h
 
	Contains:		C++ class individual TrueType font 'EBDT' tables
 
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

#ifndef __FTFONTTABLE_EBDT__
#define __FTFONTTABLE_EBDT__

#include <Carbon/Carbon.h>
#include "FTFontTable_bdat.h"

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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_EBDT : public FTFontTable_bdat {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'EBDT' ),
		};

	FTFontTable_EBDT( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_EBDT( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_EBDT( const FTFontTable& iOther );
	virtual ~FTFontTable_EBDT();
	
	FTFontTable_EBDT& operator=( const FTFontTable_EBDT& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_EBDT();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

};

class FTFontTable_CBDT : public FTFontTable_EBDT {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'CBDT' ),
	};

	FTFontTable_CBDT( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_CBDT( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_CBDT( const FTFontTable& iOther );
	virtual ~FTFontTable_CBDT();

	FTFontTable_CBDT& operator=( const FTFontTable_CBDT& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_CBDT();

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_EBDT__ */
