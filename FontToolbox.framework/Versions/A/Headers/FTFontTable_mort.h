/*
	File:			FTFontTable_mort.h
 
	Contains:		C++ class individual TrueType font 'mort' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_mort.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:06  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/08/01 19:10:46  jenkins
	First checked in.
	
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

#ifndef __FTFONTTABLE_MORT__
#define __FTFONTTABLE_MORT__

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

class FTFontTable_mort : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'mort' ),
		};

	FTFontTable_mort( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_mort( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_mort( const FTFontTable& iOther );
	virtual ~FTFontTable_mort();
	
	FTFontTable_mort& operator=( const FTFontTable_mort& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual Fixed			GetVersion() const;
	virtual uint32_t		CountChains() const;
	virtual ItemCount		CountDefaultFeatures() const;

protected:

	FTFontTable_mort();

	virtual void		ReadDataInternal();
#if 1
	virtual CFDataRef	RebuildDataInternal() const;
#endif

private:

	Fixed				_fVersion;
	uint32_t			_fNumChains;
	ItemCount			_fNumDefaultFeatures;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_MORT__ */
