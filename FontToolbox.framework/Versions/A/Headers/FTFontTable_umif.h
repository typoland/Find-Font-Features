/*
	File:			FTFontTable_umif.h
 
	Contains:		C++ class individual TrueType font 'umif' tables
 
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

#ifndef __FTFONTTABLE_umif__
#define __FTFONTTABLE_umif__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTFontTable_bloc.h"

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
	
	class FTFontTable_umif : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'umif' ),
		};
		
		FTFontTable_umif( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_umif( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_umif( const FTFontTable& iOther );
		virtual ~FTFontTable_umif();
		
		FTFontTable_umif& operator=( const FTFontTable_umif& iOther );
		
		virtual FourCharCode	GetTag() const;
		
	protected:
		
		FTFontTable_umif();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_umif__ */
