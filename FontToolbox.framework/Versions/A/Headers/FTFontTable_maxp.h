/*
	File:			FTFontTable_maxp.h
 
	Contains:		C++ class individual TrueType font 'fMaxp' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFontTable_maxp.h,v $
	Revision 1.5  2007/02/13 19:35:17  jenkins
	Improve 'name' table and 'FOND' resource tests; fix alignment problems; introduce an intermediate-sized report <rdar://problems/4910015&4943089&4968188&4981883>

	Revision 1.4  2007/01/15 23:28:06  kurita
	<rdar://problem/4916090> updated copyright.
	
	Revision 1.3  2006/11/03 19:10:05  jenkins
	Extensive changes to fix various problems, mainly crashes and false fatal error reports <rdar://problems/4451915&4606617&4703492&4780973&4799113&4799150&4801545&4804608>
	
	Revision 1.2  2006/08/28 00:20:53  jenkins
	Do initial integration into ATS <rdar://problems/4546011>.
	
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

#ifndef __FTFONTTABLE_MAXP__
#define __FTFONTTABLE_MAXP__

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

struct MAXPTable {
		Fixed		fVersion;
		uint16_t	fNumGlyphs;
		uint16_t	fMaxPoints;
		uint16_t	fMaxContours;
		uint16_t	fMaxComponentPoints;
		uint16_t	fMaxComponentContours;
		uint16_t	fMaxZones;
		uint16_t	fMaxTwilightPoints;
		uint16_t	fMaxStorage;
		uint16_t	fMaxFunctionDefs;
		uint16_t	fMaxInstructionDefs;
		uint16_t	fMaxStackElements;
		uint16_t	fMaxSizeOfInstructions;
		uint16_t	fMaxComponentElements;
		uint16_t	fMaxComponentDepth;
	};

#ifndef __cplusplus
typedef struct MAXPTable MAXPTable;
#endif

struct FTMinimalTable_maxp {
	Fixed		fVersion;
	uint16_t	fNumGlyphs;
};

#ifndef __cplusplus
typedef struct FTMinimalTable_maxp FTMinimalTable_maxp  ;
#endif

class FTFontTable_maxp : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'maxp' ),
		
		kVersion_glyf = 0x00010000,
		kVersion_CFF_ = 0x00005000,
		
		};

	static FTData CreateDummyTable(size_t iGlyphCount);

	FTFontTable_maxp( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_maxp( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_maxp( const FTFontTable& iOther );
	virtual ~FTFontTable_maxp();
	
	FTFontTable_maxp& operator=( const FTFontTable_maxp& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual Fixed		Version() const;
	virtual uint16_t	NumGlyphs() const;
	virtual uint16_t	MaxPoints() const;
	virtual uint16_t	MaxContours() const;
	virtual uint16_t	MaxComponentPoints() const;
	virtual uint16_t	MaxComponentContours() const;
	virtual uint16_t	MaxZones() const;
	virtual uint16_t	MaxTwilightPoints() const;
	virtual uint16_t	MaxStorage() const;
	virtual uint16_t	MaxFunctionDefs() const;
	virtual uint16_t	MaxInstructionDefs() const;
	virtual uint16_t	MaxStackElements() const;
	virtual uint16_t	MaxSizeOfInstructions() const;
	virtual uint16_t	MaxComponentElements() const;
	virtual uint16_t	MaxComponentDepth() const;

	virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
										 const FTArray& iGlyphsToRetain) const;
	virtual bool CanGenerateTrimmedData() const { return true; };
	virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

protected:

	FTFontTable_maxp();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;


private:

	Fixed		_fVersion;
	uint16_t	_fNumGlyphs;
	uint16_t	_fMaxPoints;
	uint16_t	_fMaxContours;
	uint16_t	_fMaxComponentPoints;
	uint16_t	_fMaxComponentContours;
	uint16_t	_fMaxZones;
	uint16_t	_fMaxTwilightPoints;
	uint16_t	_fMaxStorage;
	uint16_t	_fMaxFunctionDefs;
	uint16_t	_fMaxInstructionDefs;
	uint16_t	_fMaxStackElements;
	uint16_t	_fMaxSizeOfInstructions;
	uint16_t	_fMaxComponentElements;
	uint16_t	_fMaxComponentDepth;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_MAXP__ */
