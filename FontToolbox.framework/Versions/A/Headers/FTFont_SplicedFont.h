/*
	File:			FTFont_SplicedFont.h
 
	Contains:		C++ class individual TrueType fonts
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTFont_SplicedFont.h,v $
	Revision 1.2  2007/01/15 23:28:02  kurita
	<rdar://problem/4916090> updated copyright.

	Revision 1.1  2006/11/03 19:03:15  jenkins
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

#ifndef __FTFONT_SPLICEDFONT__
#define __FTFONT_SPLICEDFONT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTEncoding.h"
#include "FTFont.h"
#include "FTFontTable_feat.h"

namespace ftx {
	
	class FTEncoding;
	class FTFontContainer;
	class FTFontTable;
	class FTNameTableEntry;
	
	class FTFont_SplicedFont : public FTFont {
		
	public:
		
		enum {
			kInvalidGlyphID = 0xFFFFU
		};
		
		FTFont_SplicedFont( FTFontContainer *iContainer, CFDataRef iData );
		FTFont_SplicedFont( FTFontContainer *iContainer, const FSRef& iFileRef );
		FTFont_SplicedFont( FTFontContainer *iContainer, const uint8_t *iData, ByteCount iLength );
		FTFont_SplicedFont( FTFontContainer *iContainer, Handle iData );
		FTFont_SplicedFont( const FTFont_SplicedFont& iOther );
		
		virtual ~FTFont_SplicedFont();
		
		FTFont_SplicedFont& operator=( const FTFont_SplicedFont& );
		
		// Returns a string which (hopefully) is a unique way of specifying a
		//		certain version of the font.
		virtual CFStringRef				GetIdentifier() const;
		
		// Returns the most useful name for the font as a string
		virtual CFStringRef				GetName() const;
		
		// Returns a constant indicating what kind of font this is
		virtual FTFont::EFontType		GetType() const { return FTFont::kSplicedFontType; };
		
	protected:
		
		FTFont_SplicedFont();
		
	private:
		
		void Validate() const;
		//	Perform basic validation functions to make sure
		//		this is a valid spliced font
		//	This function throws an exception if something is wrong
		
		void DeleteAllCachedData();
		
		CFStringRef _fIdentifier;
		
	};
	
}

#endif /* __FTFONT_SPLICEDFONT__ */
