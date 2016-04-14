/*
	File:			FTFontTable_vhea.h
 
	Contains:		C++ class individual TrueType font 'vhea' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2007-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_vhea.h,v $
	Revision 1.2  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.1  2007/01/31 21:23:50  jenkins
	Fix problems with 'vmtx' and 'name' tests <rdar://problems/4402454&4780973&4834838&4853298&4853332&4925234&4928520>
	
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_VHEA__
#define __FTFONTTABLE_VHEA__

#include <Carbon/Carbon.h>
#include "FTFontTable_hhea.h"

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

struct VHEATable {
		Fixed		fVersion;
		int16_t		fAscender;
		int16_t		fDescender;
		int16_t		fLineGap;
		uint16_t	fAdvanceMax;
		int16_t		fSideBearingMin;
		int16_t		fOtherSideBearingMin;
		int16_t		fExtentMax;
		int16_t		fCaretSlopeRise;
		int16_t		fCaretSlopeRun;
		int16_t		fCaretOffset;
		uint16_t	fFiller[ 4 ];
		int16_t		fMetricDataFormat;
		uint16_t	fNumberLongMetrics;
	};

#ifndef __cplusplus
typedef struct VHEATable VHEATable;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_vhea : public FTFontTable_hhea {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'vhea' ),
		kVersion = 0x00011000U
		};

	FTFontTable_vhea( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_vhea( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_vhea( const FTFontTable& iOther );
	virtual ~FTFontTable_vhea();
	
	FTFontTable_vhea& operator=( const FTFontTable_vhea& iOther );

	virtual FourCharCode	GetTag() const;

protected:

	FTFontTable_vhea();

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_VHEA__ */
