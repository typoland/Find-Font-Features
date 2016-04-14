/*
	File:			FTFont_Type1.h
 
	Contains:		C++ class for Type 1 fonts
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2007-2015 by Apple Inc. All rights reserved.
 
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

#ifndef __FTFONT_TYPE1__
#define __FTFONT_TYPE1__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont.h"

namespace ftx {
	
	class FTFontContainer;
	
	class FTFont_Type1 : public FTFont {
		
	public:
		
		FTFont_Type1( FTFontContainer *iContainer, CFDataRef iData );
		FTFont_Type1( FTFontContainer *iContainer, const FSRef& iData );
		FTFont_Type1( const FTFont_Type1& iOther );
		virtual ~FTFont_Type1();
		
		FTFont_Type1& operator=( const FTFont_Type1& iOther );
		
		//	Determines whether or not this font object is even parsable as
		//		an actual font
		virtual void					TestBasicUsability() const;
		
		// Returns a constant indicating what kind of font this is
		virtual FTFont::EFontType		GetType() const { return FTFont::kType1FontType; };
		
	protected:
		
		FTFont_Type1();
		
		virtual void ReadDataInternal();
		
	private:
		
	};
	
}

#endif /* __FTFONT_TYPE1__ */
