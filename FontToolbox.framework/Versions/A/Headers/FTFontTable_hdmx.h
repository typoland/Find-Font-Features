/*
	File:			FTFontTable_hdmx.h
 
	Contains:		C++ class individual TrueType font 'hdmx' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_hdmx.h,v $
	Revision 1.3  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.2  2007/01/15 23:28:04  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.1  2006/09/22 16:21:29  jenkins
	Port glyph- and metrics-related ftxvalidator tests; fix a crashing bug <rdar://problems/4555344&4555348&4742072&4742084&4745142>.
	
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTFONTTABLE_HDMX__
#define __FTFONTTABLE_HDMX__

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

struct HDMXDeviceRecord {
		uint8_t	fPixelsPerEm;
		uint8_t	fMaxWidth;
		uint8_t	fWidths[];
	};

#ifndef __cplusplus
typedef struct HDMXDeviceRecord HDMXDeviceRecord;
#endif

struct HDMXTable {
		uint16_t	fVersion;
		uint16_t	fDeviceRecordCount;
		uint32_t	fDeviceRecordSize;
		HDMXDeviceRecord	fDeviceRecords[];
	};

#ifndef __cplusplus
typedef struct HDMXTable HDMXTable;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_hdmx : public FTFontTable {

public:

	enum {
		kVersion = 0,
		
		kTag = FOUR_CHAR_CODE( 'hdmx' )
		};

	FTFontTable_hdmx( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_hdmx( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_hdmx( const FTFontTable_hdmx& iOther );
	virtual ~FTFontTable_hdmx();
	
	FTFontTable_hdmx& operator=( const FTFontTable_hdmx& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual uint16_t				GetVersion() const;
	virtual uint16_t				GetDeviceRecordCount() const;
	virtual uint32_t				GetDeviceRecordSize() const;
	virtual const HDMXDeviceRecord	*GetDeviceRecords() const;
	virtual const HDMXDeviceRecord	*GetDeviceRecord( ItemCount iIndex ) const;

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
	virtual bool CanGenerateTrimmedData() const { return true; };
	virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;
protected:

	FTFontTable_hdmx();

	virtual void		ReadDataInternal();
#if 1
	virtual CFDataRef	RebuildDataInternal() const;
#endif

private:

	uint16_t				_fVersion;
	uint16_t				_fDeviceRecordCount;
	uint32_t				_fDeviceRecordSize;
	const HDMXDeviceRecord	*_fDeviceRecords;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_HDMX__ */
