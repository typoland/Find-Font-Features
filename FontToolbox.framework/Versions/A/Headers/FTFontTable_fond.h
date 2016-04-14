/*
	File:			FTFontTable_fond.h
 
	Contains:		C++ class individual TrueType font 'fond' tables
 
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

#ifndef __FTFONTTABLE_FOND__
#define __FTFONTTABLE_FOND__

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

#if PRAGMA_STRUCT_ALIGN
#pragma options align = mac68k
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack( push, 2 )
#elif PRAGMA_STRUCT_PACK
#pragma pack( 2 )
#endif

struct FTTableEntry_fond {
	int16_t		fResourceID;
	int16_t		fFamilyID;
	uint16_t	fFlags;
	uint16_t	fStyle;
	int16_t		fScript;
	int16_t		fLanguage;
	uint32_t	fOffset;
	uint32_t	fLength;
	uint8_t		fNameLength;
	uint8_t		fName[ 255 ];	// The resource name as a C-string.  
	// This consists of the raw bytes from 
	//	the 'FOND' resource name, simply 
	//	converted from a Pascal string to a C-string.
};

struct FTHeader_nfnt {
	int16_t		fFontType;			/* font type */
	uint16_t	fFirstChar;			/* character code of first character */
	uint16_t	fLastChar;			/* character code of last character */
	int16_t		fMaxWidth;			/* maximum character width */
	int16_t		fKernMax;			/* negative of maximum character kern */
	int16_t		fNegatedDescent;	/* negative of descent */
	int16_t		fRectWidth;			/* width of font rectangle */
	int16_t		fRectHeight;		/* height of font rectangle */
	uint16_t	fOffsetWidthOffset;	/* offset to offset/width table in NFNT resources */
	int16_t		fAscent;			/* ascent */
	int16_t		fDescent;			/* descent */
	int16_t		fLeading;			/* leading */
	uint16_t	fUnused1;			/* not used in the 'fond' table; row width of bit image / 2 in NFNT resources */
	uint16_t	fUnused2;			/* pad to four-byte boundary */
};

struct FTTableEntry_nfnt {
	int16_t		fResourceID;
	uint16_t	fFlags;
	uint16_t	fStyle;
	int16_t		fScript;
	int16_t		fLanguage;
	uint16_t	fPointSize;
	uint32_t	fOffset;
	uint32_t	fLength;
	uint8_t		fNameLength;
	uint8_t		fName[ 255 ];	// The resource name as a C-string.  
	// This consists of the raw bytes from 
	//	the 'FOND' resource name, simply 
	//	converted from a Pascal string to a C-string.
};

struct FTOffsetWidth_nfnt {
	int8_t fOffset;
	int8_t fWidth;
};

struct FTTableHeader_fond {
	uint16_t			fVersion;
	uint16_t			fCount_fond;
	uint16_t			fCount_nfnt;
	uint16_t			fUnused;
	FTTableEntry_fond	fEntries[];
};

struct FTResourceMapping {
	int32_t 	fResourceID;
	uint8_t		fPostScriptName[ 62 /* == FTFontTable_fond::kPostScriptNameLength */ ];
	// The PostScript name of the font 
	// corresponding to this font resource
	// in ASCII (zero-terminated)
};

struct FTResource_fond {
	uint32_t			fNumFonts;
	FTResourceMapping	fEntries[];
};

struct FTBBoxEntry
{
	int16_t	fStyle;
	int16_t	fLeft;
	int16_t	fBottom;
	int16_t	fRight;
	int16_t	fTop;
};

struct FTBBoxTable
{
	int16_t		fNumEntriesMinusOne;
	FTBBoxEntry	fEntries[];
};

struct FTFamilyRecord_fond {
	int16_t		fFlags;					/* flags for family */
	int16_t		fFamilyID;				/* family ID number */
	uint16_t	fFirstChar;				/* character code of 1st character */
	uint16_t	fLastChar;				/* character code of last character */
	int16_t		fAscent;				/* maximum ascent for 1pt font */
	int16_t		fDescent;				/* maximum descent for 1pt font */
	int16_t		fLeading;				/* maximum leading for 1pt font */
	int16_t		fMaximumWidth;			/* maximum widMax for 1pt font */
	int32_t		fWidthTableOffset;		/* offset to width table */
	int32_t		fKerningTableOffset;	/* offset to kerning table */
	int32_t		fStyleTableOffset;		/* offset to style mapping table */
	int16_t		fProperty[8];			/* style property info */
	int16_t		fLanguage;				/* language field for version 4 'FOND' resources, 0 otherwise */
	int16_t		fInternational[2];		/* for international use */
	int16_t		fVersion;				/* version number */
};

struct FTAssociationEntry_fond {
	int16_t	fFontSize;
	int16_t	fFontStyle;
	int16_t	fFontID;
};

struct FTFontAssociationTable {
	int16_t					fNumEntriesMinusOne;	/*number of entries - 1*/
	FTAssociationEntry_fond	fEntries[];
};

struct FTStyleTable_fond {
	int16_t		fFontClass;
	int32_t		fOffset;
	int32_t		fReserved;
	int8_t		fIndexes[48];
};

struct FTNameTable_fond {
	int16_t		fStringCount;
	Str255		fBaseFontName;
};

struct FTKernPair_fond {
	uint8_t		fKernFirst;              /* 1st char of kerned pair */
	uint8_t		fKernSecond;             /* 2nd char of kerned pair */
	int16_t 	fKernWidth;              /* kerning in 1pt fixed format */
};

struct FTKernEntry_fond {
	int16_t			fKernStyle;			/* style the entry applies to */
	int16_t			fKernPairCount;		/* number of pairs */
	FTKernPair_fond	fEntries[];
};

struct FTKernTable_fond {
	int16_t				fNumEntries;		/* number of kerning entries */
	FTKernEntry_fond	fEntries[];
};

#if PRAGMA_STRUCT_ALIGN
#pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
#pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
#pragma pack()
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTFontTable_fond : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'fond' ),
		kPostScriptNameLength = 62,

	    kTableVersion0	 			= 0,
		kTableVersion1	 			= 1,
		kTableVersion2	 			= 2,
		kTableCurrentVersion 		= kTableVersion2,
		
	};
	
	static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );

	static Handle CreateTableFromFONDsForFont( const FTFont_sfnt *iFont );
	static CFDataRef ProcessFONDFile( const FSRef *iFile );

	FTFontTable_fond( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_fond( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_fond( const FTFontTable& iOther );
	virtual ~FTFontTable_fond();
	
	FTFontTable_fond& operator=( const FTFontTable_fond& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual uint16_t	GetVersion() const { ReadData(); return _fVersion; };
	virtual uint16_t	GetNumEntries_fond() const { ReadData(); return _fCount_fond; };
	virtual uint16_t	GetNumEntries_nfnt() const { ReadData(); return _fCount_nfnt; };
	
	virtual uint32_t	GetIndNumResourceMappings( uint16_t tIndex ) const;
	virtual void		GetIndResourceMapping( uint16_t iIndex_fond, uint16_t iIndex_mapping, FTResourceMapping& oMapping ) const;
	
	virtual void		GetIndEntry_fond( uint16_t iIndex, FTTableEntry_fond& oEntry ) const;
	virtual void		GetIndFamilyRecord( uint16_t iIndex, FTFamilyRecord_fond& oEntry ) const;
	
	virtual void		GetIndEntry_nfnt( uint16_t, FTTableEntry_nfnt& oEntry ) const;

protected:

	FTFontTable_fond();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	
	uint16_t			_fVersion;
	uint16_t			_fCount_fond;
	uint16_t			_fCount_nfnt;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_fond__ */
