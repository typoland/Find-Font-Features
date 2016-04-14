/*
	File:			FTFontTable_meta.h

	Contains:		C++ class individual TrueType font 'meta' tables

	Version:		Mac OS X

	Written by:		The Apple Font Group

	Copyright:		© 2013 by Apple Inc. All rights reserved.

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

#ifndef __FTFONTTABLE_META__
#define __FTFONTTABLE_META__

#include <Carbon/Carbon.h>
#include <vector>

#include "FTFontTable.h"

using namespace std;

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

struct FTDataMap_meta {
	FourCharCode	fDataTag;
	uint32_t		fDataOffset;
	uint32_t		fDataLength;
};

struct FTHeader_meta {
	uint32_t			fVersion;
	uint32_t			fFlags;
	uint32_t			fDataOffset;	// Not really needed, but it makes things simpler
	uint32_t			fNumDatMaps;
	FTDataMap_meta		fDataMaps[];
};

class FTFontTable_meta : public FTFontTable {
	
public:
	
	enum {
		kCurrentVersion = 1,
		kTag = FOUR_CHAR_CODE('meta'),
        kAppleStandardMetadata = FOUR_CHAR_CODE('appl'),
		
		kDesignLanguages = FOUR_CHAR_CODE('dlng'),
		kSupportedLanguages = FOUR_CHAR_CODE('slng'),
		kToolVersion = FOUR_CHAR_CODE('bild'),
		
		kInvalidDataTag = FOUR_CHAR_CODE('\?\?\?\?')
	};

    static FTString TaggedDataToString(FourCharCode iTag, const FTData& iData);
    static FTData TaggedStringToData(FourCharCode iTag, const FTString& iData);
	
	static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );

	static bool AddStringToMetadata(FTFont_sfnt *iFont, const FTString& iString, FourCharCode iTag);
	static bool AddDataToMetadata(FTFont_sfnt *iFont, const FTData& iData, FourCharCode iTag);

	FTFontTable_meta( FTFont_sfnt *iFont, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
	FTFontTable_meta( FTFont_sfnt *iFont, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_meta( FTFont_sfnt *iFont, const FTData& iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
	FTFontTable_meta( const FTFontTable_meta& iOther );
	virtual ~FTFontTable_meta();
	
	FTFontTable_meta& operator=( const FTFontTable_meta& iOther );
	
	virtual FourCharCode	GetTag() const;
	
	uint32_t			GetVersion() const { return kCurrentVersion; };
	
	uint32_t			GetFlags() const { ReadData(); return _fFlags; };
	void				SetFlags(uint32_t iFlags) { _fFlags = iFlags; MakeDirty(); };
	CFIndex				GetTaggedDataCount() const { ReadData(); return _fDataMap.size(); };
	FourCharCode		GetIndDataTag(CFIndex iIndex) const;
	FTData				GetIndData(CFIndex iIndex) const;

	bool				HasTaggedData(FourCharCode iTag) const;
	FTData				GetTaggedData(FourCharCode iTag) const;
	
	void				SetData(vector<FourCharCode> iTags, const FTData& iData);
	
	virtual FTString		TableSchema() const;
	virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
                                         const FTGlyphID *iGlyphReordering) const;

protected:
	
	FTFontTable_meta();
	
	virtual void		ReadDataInternal();
	
	
private:

	static bool IsTextMetadata(FourCharCode iTag);
	
	uint32_t					_fFlags;
	uint32_t					_fDataOffset;
	vector<FTDataMap_meta>		_fDataMap;
	
};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_META__ */
