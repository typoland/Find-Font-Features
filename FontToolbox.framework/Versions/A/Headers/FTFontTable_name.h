/*
	File:			FTFontTable_name.h
 
	Contains:		C++ class individual TrueType font 'name' tables
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONTTABLE_NAME__
#define __FTFONTTABLE_NAME__

#include <Carbon/Carbon.h>

#include "FTData.h"
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
	
	struct FTRawNameRecord
	{
		uint16_t	fPlatformID;					/* zero-based */
		uint16_t	fPlatformSpecificID;			/* zero-based */
		uint16_t	fLanguageID;					/* zero-based */
		uint16_t	fNameID;						/* zero-based */
		uint16_t	fLength;						/* in bytes */
		uint16_t	fOffset;						/* from start of string base */
	};
	
#ifndef __cplusplus
	typedef struct FTRawNameRecord FTRawNameRecord;
#endif
	
	struct FTRawTableData_name
	{
		uint16_t		fFormat;
		uint16_t		fNumNameRecords;
		uint16_t		fStringBaseOffset;
		FTRawNameRecord	fNameRecords[];
		/*	string base follows the above array */
	};
	
#ifndef __cplusplus
	typedef struct FTRawTableData_name FTRawTableData_name;
#endif
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTNameTableEntry;
	
	class FTFontTable_name : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'name' ),
			kVersion = 0
		};

		static FTData CreateDummyTable(const FTString& iFontName);
		
		FTFontTable_name( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_name( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_name( const FTFontTable& iOther );
		virtual ~FTFontTable_name();
		
		FTFontTable_name& operator=( const FTFontTable_name& iOther );
		
		virtual bool operator==( const FTFontTable_name& iOther ) const;
		virtual bool operator!=( const FTFontTable_name& iOther ) const;
		
		virtual FourCharCode	GetTag() const;
		
		virtual uint16_t		Format() const;
		virtual uint16_t		StringBaseOffset() const;
		virtual CFArrayRef		Names() const;
		virtual CFIndex			NameCount() const;
		
		virtual FTNameTableEntry*		GetIndName( CFIndex iIndex ) const;
		virtual FTNameTableEntry*		FindName( FontNameCode iNameType, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage, CFIndex& oIndex ) const;
		
		virtual void					SetIndName( CFIndex iIndex, CFStringRef iString );
		virtual bool					SetName( FontNameCode iNameType, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage, CFIndex& oIndex, CFStringRef iString );
		
		virtual void					DeleteIndName( CFIndex iIndex );
		virtual bool					DeleteName( FontNameCode iNameType, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage, CFIndex& oIndex );
		
	protected:
		
		FTFontTable_name();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
		virtual void		SetNames( CFArrayRef iNewNames );
		
	private:
		
		void		DeleteData();
		
		uint16_t	_fFormat;
		uint16_t	_fStringBaseOffset;
		CFArrayRef	_fNames;
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_NAME__ */
