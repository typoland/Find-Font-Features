/*
	File:			FTFontTable_hsty.h
 
	Contains:		C++ class individual TrueType font 'hsty' tables
 
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

#ifndef __FTFONTTABLE_HSTY__
#define __FTFONTTABLE_HSTY__

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
	
	/* The TTable_hsty defines the complete structure of a 'hsty' table. */
	
	struct TTable_hsty {
		Fixed		fVersion;
		int16_t		fExtraPlain;
		int16_t		fExtraBold;
		int16_t		fExtraItalic;
		int16_t		fExtraUnderline;
		int16_t		fExtraOutline;
		int16_t		fExtraShadow;
		int16_t		fExtraCondensed;
		int16_t		fExtraExtended;
		int16_t		fExtraUnused;
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_hsty : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'hsty' )
		};
		
		FTFontTable_hsty( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_hsty( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_hsty( const FTFontTable& iOther );
		virtual ~FTFontTable_hsty();
		
		FTFontTable_hsty& operator=( const FTFontTable_hsty& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		virtual Fixed		GetVersion() const { ReadData(); return _fSwappedTable.fVersion; };
		virtual int16_t		GetExtraPlain() const { ReadData(); return _fSwappedTable.fExtraPlain; };
		virtual int16_t		GetExtraBold() const { ReadData(); return _fSwappedTable.fExtraBold; };
		virtual int16_t		GetExtraItalic() const { ReadData(); return _fSwappedTable.fExtraItalic; };
		virtual int16_t		GetExtraUnderline() const { ReadData(); return _fSwappedTable.fExtraUnderline; };
		virtual int16_t		GetExtraOutline() const { ReadData(); return _fSwappedTable.fExtraOutline; };
		virtual int16_t		GetExtraShadow() const { ReadData(); return _fSwappedTable.fExtraShadow; };
		virtual int16_t		GetExtraCondensed() const { ReadData(); return _fSwappedTable.fExtraCondensed; };
		virtual int16_t		GetExtraExtended() const { ReadData(); return _fSwappedTable.fExtraExtended; };
		virtual int16_t		GetExtraUnused() const { ReadData(); return _fSwappedTable.fExtraUnused; };
		
	protected:
		
		FTFontTable_hsty();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		TTable_hsty		_fSwappedTable;
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_HSTY__ */
