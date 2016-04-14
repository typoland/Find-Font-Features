/*
	File:			FTFontTable_kern.h
 
	Contains:		C++ class individual TrueType font 'kern' tables
 
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

#ifndef __FTFONTTABLE_KERN__
#define __FTFONTTABLE_KERN__

#include <Carbon/Carbon.h>
#include <vector>

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

#if 0
	typedef struct {
		uint16_t	fFormat;
		bool		fVertical;
		bool		fCrossStream;
		bool		fVariation;
		uint16_t	fTupleIndex;
		FTData		fSubtableData;
	} FTSubtable_kern;
#endif

/* ----------------------------------------------------------------------------------------- */

/* PROTOTYPES */

	class FTSubtable_kern {
	public:

		enum {
			kInvalidSubtableFormat = -1
		};

		FTSubtable_kern();
		FTSubtable_kern(const KernVersion0SubtableHeader* iSubtable0);
		FTSubtable_kern(const KernSubtableHeader* iSubtable);
		FTSubtable_kern(const FTSubtable_kern& iOther);

		virtual ~FTSubtable_kern();
		FTSubtable_kern& operator=(const FTSubtable_kern& iOther);

		const uint8_t*	GetUnswappedDataPtr() const { return (const uint8_t*) _fSubtableData.DataPtr(); };
		uint32_t		GetUnswappedDataLength() const { return (uint32_t) _fSubtableData.Length(); };
		uint16_t		GetCoverage() const;
		int16_t			GetFormat() const{ return _fFormat; };
		bool			GetVertical() const { return _fVertical; };
		bool			GetCrossStream() const { return _fCrossStream; };
		bool			GetVariation() const { return _fVariation; };
		uint16_t		GetTupleIndex() const { return _fTupleIndex; };

	private:
		int16_t			_fFormat;
		bool			_fVertical;
		bool			_fCrossStream;
		bool			_fVariation;
		uint16_t		_fTupleIndex;
		FTData			_fSubtableData;
	};

	class FTFontTable_kern : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'kern' ),
			kOTVerticalFlag =		( 1 << 0 ),
			kOTMinimumFlag =		( 1 << 1 ),
			kOTCrossStreamFlag =	( 1 << 2 ),
			kOTOverrideFlag =		( 1 << 3 ),
			kOTFormatMask =			0xF0,
			kOTFormatShift =		8,
		};
		
		FTFontTable_kern( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_kern( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_kern( const FTFontTable_kern& iOther );
		virtual ~FTFontTable_kern();
		
		FTFontTable_kern& operator=( const FTFontTable_kern& iOther );
		
		virtual FourCharCode	GetTag() const;
		virtual Fixed			GetVersion() const { ReadData(); return _fVersion; };
		uint16_t				GetSubtableCount() const { ReadData(); return _fSubtableCount; };
		void					GetIndSubtable(uint16_t iSubtableIndex, FTSubtable_kern& oSubtable) const;
		virtual bool			IsOTCompatible() const { return GetVersion() == 0; };
		
		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
	protected:
		
		FTFontTable_kern();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:

		FTString ConvertOrderedListToTrimmedXML(const FTXMLOptions& iOptions,
												const FTArray& iGlyphsToRetain,
												const KernOrderedListHeader* iSubtableHeader) const;
		FTString ConvertIndexArrayToTrimmedXML(const FTXMLOptions& iOptions,
												const FTArray& iGlyphsToRetain,
												const KernIndexArrayHeader* iSubtableHeader) const;

		Fixed						_fVersion;
		uint16_t					_fSubtableCount;
		vector<FTSubtable_kern>		_fSubtables;
		
	};
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_KERN__ */
