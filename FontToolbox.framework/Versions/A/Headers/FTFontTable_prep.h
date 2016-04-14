/*
	File:			FTFontTable_prep.h
 
	Contains:		C++ class individual TrueType font 'prep' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_prep.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:06  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/07/07 17:44:03  jenkins
	First checked in.
	

	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_PREP__
#define __FTFONTTABLE_PREP__

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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_prep : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'prep' ),
		};

	FTFontTable_prep( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_prep( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_prep( const FTFontTable& iOther );
	virtual ~FTFontTable_prep();
	
	FTFontTable_prep& operator=( const FTFontTable_prep& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_prep();

	virtual void		ReadDataInternal();
#if 1
	virtual CFDataRef	RebuildDataInternal() const;
#endif

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_prep__ */
