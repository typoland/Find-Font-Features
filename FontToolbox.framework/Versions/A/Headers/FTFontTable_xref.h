/*
	File:			FTFontTable_xref.h
 
	Contains:		C++ class individual TrueType font 'xref' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2012-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_xref__
#define __FTFONTTABLE_xref__

#include <vector>

using namespace std;

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTString.h"

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

struct FTHeader_xref {
	uint32_t	fVersion;
	uint32_t	fFlags;
	uint32_t	fNumEntries;
	uint32_t	fStringOffset;
};

struct FTEntry_xref {
	FourCharCode	fTableTag;
	int16_t			fChainIndex;
	int16_t			fSubtableIndex;
	int16_t			fTableType;
	int16_t			fTableIndex;
	uint16_t		fStringOffset;
	uint16_t		fStringLength;
};

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

class FTData_xref {

public:
	FTData_xref();
	FTData_xref( const FTEntry_xref& iEntry, const uint8_t *iUnswappedData );
	FTData_xref( const FTEntry_xref& iEntry, CFStringRef iName );
	FTData_xref( const FTData_xref& iOther );
	
	virtual ~FTData_xref();
	
	FTData_xref& operator=( const FTData_xref& iOther );
	bool Matches( const FTData_xref& iOther ) const;
	bool operator!=( const FTData_xref& iOther ) const { return !(operator==(iOther)); };
	bool operator==( const FTData_xref& iOther ) const;
	
	bool operator<( const FTData_xref& iOther ) const;
	bool operator<=( const FTData_xref& iOther ) const { return operator<(iOther) || operator==(iOther); };
	bool operator>( const FTData_xref& iOther ) const { return iOther.operator<( *this ); };
	bool operator>=( const FTData_xref& iOther ) const { return operator>(iOther) || operator==(iOther); };
	
	FourCharCode	GetTableTag() const { return _fEntry.fTableTag; };
	int16_t			GetChainIndex() const { return _fEntry.fChainIndex; };
	int16_t			GetSubtableIndex() const { return _fEntry.fSubtableIndex; };
	int16_t			GetTableType() const { return _fEntry.fTableType; };
	int16_t			GetTableIndex() const { return _fEntry.fTableIndex; };
	
	friend ostream& operator<<( ostream& iOut, const FTData_xref &iData_xref );

	CFStringRef		GetString() const { return _fString; };
	FTString		String() const { return FTString(_fString); };

private:

	FTEntry_xref	_fEntry;
	CFStringRef		_fString;

};

class FTFontTable_xref : public FTFontTable {

public:

	enum {
		kTag = FOUR_CHAR_CODE( 'xref' ),
		
		kDontCare = -1,
		
		kClassTableName = 0,
		kStateTableName = 1,
		kEntryTableName = 2,
		kActionTableName = 3,
		kColumnClassName = 4,
		kRowClassName = 5,
		
		kOriginalVersion = 1,
		kCurrentVersion = kOriginalVersion
		
		};

	FTFontTable_xref( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_xref( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_xref( FTFont_sfnt *iFont, const FTData& iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_xref( FTFont_sfnt *iFont );
	FTFontTable_xref( const FTFontTable_xref& iOther );
	virtual ~FTFontTable_xref();
	
	FTFontTable_xref& operator=( const FTFontTable_xref& iOther );

	virtual FourCharCode	GetTag() const;
	
	CFStringRef				CopyStringData( const FTEntry_xref& iEntry ) const;
	bool					CopyStringData( const FTEntry_xref& iEntry, char *oName, size_t iBufferSize ) const;
	
	size_t					EntryCount() const { ReadData(); return _fData.size(); };
	const FTData_xref&		GetIndEntry( size_t iIndex ) const;
	
	vector<FTData_xref>		CopyMatchingNames( const FTEntry_xref& iMatchCriterion ) const;
	FTString				NameForEntry(const FTEntry_xref& iEntry) const;
	
	bool					SetEntry( const FTEntry_xref& iEntry, CFStringRef iString );
	CFDataRef				CopyTableAsData() const;
	
	friend ostream& operator<<( ostream& iOut, const FTFontTable_xref &iTable_xref );

protected:

	FTFontTable_xref();

	virtual void		ReadDataInternal();

private:

	mutable vector<FTData_xref>	_fData;

};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_xref__ */
