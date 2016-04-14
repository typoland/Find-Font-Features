/*
	File:			FTFontTable_vdmx.h
 
	Contains:		C++ class individual TrueType font 'vdmx' tables
 
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

#ifndef __FTFONTTABLE_VDMX__
#define __FTFONTTABLE_VDMX__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTFontTable_hdmx.h"

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

typedef HDMXDeviceRecord VDMXDeviceRecord;
typedef HDMXTable VDMXTable;

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_vdmx : public FTFontTable_hdmx {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'vdmx' )
		};

	FTFontTable_vdmx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_vdmx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_vdmx( const FTFontTable_vdmx& iOther );
	virtual ~FTFontTable_vdmx();
	
	FTFontTable_vdmx& operator=( const FTFontTable_vdmx& iOther );

	virtual FourCharCode	GetTag() const;
	
protected:

	FTFontTable_vdmx();

private:

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_VDMX__ */
