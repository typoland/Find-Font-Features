/*
	File:			FTFontTable_fvar.h
 
	Contains:		C++ class individual TrueType font 'fvar' tables
 
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

#ifndef __FTFONTTABLE_FVAR__
#define __FTFONTTABLE_FVAR__

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

class FTFontTable_fvar : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'fvar' )
		};

	FTFontTable_fvar( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_fvar( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_fvar( const FTFontTable& iOther );
	virtual ~FTFontTable_fvar();
	
	FTFontTable_fvar& operator=( const FTFontTable_fvar& iOther );

	virtual FourCharCode	GetTag() const;
	
	virtual Fixed			GetVersion() const { ReadData(); return _fVersion; };
	virtual uint16_t		GetOffsetToData() const { ReadData(); return _fOffsetToData; };
	virtual uint16_t		GetCountSizePairs() const { ReadData(); return _fCountSizePairs; };
	virtual uint16_t		GetAxisCount() const { ReadData(); return _fAxisCount; };
	virtual uint16_t		GetAxisSize() const { ReadData(); return _fAxisSize; };
	virtual uint16_t		GetInstanceCount() const { ReadData(); return _fInstanceCount; };
	virtual uint16_t		GetInstanceSize() const { ReadData(); return _fInstanceSize; };
	
	virtual bool			FindFontVariation( ItemCount iAxis, sfntVariationAxis &oAxis ) const;
	virtual FourCharCode	GetIndAxisTag( ItemCount iAxis ) const;
	
	virtual const sfntInstance *GetIndInstance( ItemCount iInstance ) const;
	virtual int16_t			GetIndInstanceNameCode( ItemCount iInstance ) const;
	virtual int16_t			GetIndInstanceFlags( ItemCount iInstance ) const;
	virtual Fixed			GetIndInstanceAxisValue( ItemCount iInstance, ItemCount iAxis ) const;
	
protected:

	FTFontTable_fvar();

	virtual void		ReadDataInternal();
	virtual CFDataRef	RebuildDataInternal() const;

private:
	
	
	Fixed		_fVersion;                /* 1.0 Fixed */
	uint16_t	_fOffsetToData;           /* to first axis = 16*/
	uint16_t	_fCountSizePairs;         /* axis+inst = 2 */
	uint16_t	_fAxisCount;
	uint16_t	_fAxisSize;
	uint16_t	_fInstanceCount;
	uint16_t	_fInstanceSize;
	
};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_FVAR__ */
