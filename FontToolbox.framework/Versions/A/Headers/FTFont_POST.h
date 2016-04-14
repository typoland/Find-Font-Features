/*
	File:			FTFont_POST.h
 
	Contains:		C++ class for 'POST' resources
 
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

#ifndef __FTFONT_POST__
#define __FTFONT_POST__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont_resource.h"

namespace ftx {
	
	class FTFontContainer;
	
	class FTFont_POST : public FTFont_resource {
		
	public:
		
		enum {
			kCommentType = 0,
			kASCIIType = 1,
			kHexType = 2,
			kEndOfFile = 3,
			kDataForkType = 4,
			kEndOfFontProgramType = 5,
			
			kFirstPOSTResource = 501
		};
		
		FTFont_POST( FTFontContainer *iContainer, Handle iPOSTResource );
		FTFont_POST( FTFontContainer *iContainer,
					const uint8_t *iData, ByteCount iLength,
					int16_t iResourceID, const unsigned char *iResourceName );
		FTFont_POST( const FTFont_POST& iOther );
		virtual ~FTFont_POST();
		
		FTFont_POST& operator=( const FTFont_POST& iOther );
		
		// Returns a constant indicating what kind of font this is
		virtual FTFont::EFontType		GetType() const { return FTFont::kPOSTFontType; };
		virtual uint8_t					GetDataType() const { return *( GetUnswappedDataPtr() ); };
		
	protected:
		
		FTFont_POST();
		
		virtual void ReadDataInternal();
		
	private:
		
	};
	
}

#endif /* __FTFONT_POST__ */
