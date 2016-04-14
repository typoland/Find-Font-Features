/*
	File:			FTFontTable_EBLC.h
 
	Contains:		C++ class individual TrueType font 'EBLC' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_EBLC.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:03  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/07/07 17:44:02  jenkins
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

#ifndef __FTFONTTABLE_EBLC__
#define __FTFONTTABLE_EBLC__

#include <Carbon/Carbon.h>
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

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_EBLC : public FTFontTable_bloc {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'EBLC' ),
		};

	FTFontTable_EBLC( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_EBLC( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_EBLC( const FTFontTable& iOther );
	virtual ~FTFontTable_EBLC();
	
	FTFontTable_EBLC& operator=( const FTFontTable_EBLC& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_EBLC();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:

};

	class FTFontTable_CBLC : public FTFontTable_EBLC {

	public:

		enum {
			kTag = FOUR_CHAR_CODE( 'CBLC' ),
		};

		FTFontTable_CBLC( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_CBLC( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_CBLC( const FTFontTable& iOther );
		virtual ~FTFontTable_CBLC();

		FTFontTable_CBLC& operator=( const FTFontTable_CBLC& iOther );

		virtual FourCharCode	GetTag() const;

	protected:

		FTFontTable_CBLC();

	private:
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_EBLC__ */
