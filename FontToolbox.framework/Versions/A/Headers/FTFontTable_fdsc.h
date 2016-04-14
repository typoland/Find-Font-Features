/*
	File:			FTFontTable_fdsc.h
 
	Contains:		C++ class individual TrueType font 'fdsc' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_fdsc.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:04  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/08/28 00:19:08  jenkins
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

#ifndef __FTFONTTABLE_FDSC__
#define __FTFONTTABLE_FDSC__

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

struct FTFontDescriptor {
		FourCharCode	fTag;
		Fixed			fValue;
	};

#ifndef __cplusplus
typedef struct FTFontDescriptor FTFontDescriptor;
#endif

struct FDSCTable {
		Fixed				fVersion;
		uint32_t			fDescriptorCount;
		FTFontDescriptor	fDescriptors[];
	};

#ifndef __cplusplus
typedef struct FDSCTable FDSCTable;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_fdsc : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'fdsc' ),

		kStandardDescriptorCount	= 5,

		kWeightTag				= FOUR_CHAR_CODE( 'wght' ),
		kWidthTag				= FOUR_CHAR_CODE( 'wdth' ),
		kSlantTag				= FOUR_CHAR_CODE( 'slnt' ),
		kOpticalSizeTag			= FOUR_CHAR_CODE( 'opsz' ),
		kNonAlphaCodeTag		= FOUR_CHAR_CODE( 'nalf' )
		};

	FTFontTable_fdsc( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_fdsc( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_fdsc( const FTFontTable& iOther );
	virtual ~FTFontTable_fdsc();
	
	FTFontTable_fdsc& operator=( const FTFontTable_fdsc& iOther );

	virtual FourCharCode		GetTag() const;
	
	virtual Fixed				GetAngle() const;
	
	virtual uint32_t			GetDescriptorCount() const;
	virtual bool				HasTaggedDescriptor( FourCharCode iTag ) const;
	virtual const FTFontDescriptor	*GetTaggedDescriptor( FourCharCode iTag ) const;
	virtual const FTFontDescriptor	*GetDescriptor( ItemCount iIndex ) const;

protected:

	FTFontTable_fdsc();

	virtual void		ReadDataInternal();
#if 1
	virtual CFDataRef	RebuildDataInternal() const;
#endif

private:

	CFArrayRef	GetDescriptors();
	void		DeleteData();

	const FTFontDescriptor	*_fDescriptors;

	Fixed				_fVersion;
	ItemCount			_fDescriptorCount;
	Fixed				_fAngle;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_FDSC__ */
