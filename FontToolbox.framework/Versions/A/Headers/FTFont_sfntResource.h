/*
	File:			FTFont_sfntResource.h
 
	Contains:		C++ class for 'sfnt'-housed fonts contained in resources
 
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

#ifndef __FTFONT_SFNTRESOURCE__
#define __FTFONT_SFNTRESOURCE__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont_sfnt.h"

namespace ftx {
	
	class FTFontContainer;
	
	class FTFont_sfntResource : public FTFont_sfnt {
		
	public:
		
		FTFont_sfntResource( FTFontContainer *iContainer, Handle iResource );
		FTFont_sfntResource( FTFontContainer *iContainer,
							const uint8_t *iData, ByteCount iLength,
							int16_t iResourceID, const unsigned char *iResourceName );
		FTFont_sfntResource( const FTFont_sfntResource& iOther );
		virtual ~FTFont_sfntResource();
		
		FTFont_sfntResource& operator=( const FTFont_sfntResource& iOther );
		
		// Returns the *first* 'FOND' resouce (if any) associated with this font
		virtual const FTFont_FOND		*GetFOND() const;
		virtual CFStringRef				GetFONDName() const;

		virtual int16_t					GetResourceID() const { return _fResourceID; };
		virtual ResType					GetResourceType() const { return FTFontContainer::kResourceType_sfnt; };
		virtual const unsigned char		*GetResourceName() const { return _fResourceName; };
		
	protected:
		
		FTFont_sfntResource();
		
	private:

		mutable CFStringRef		_fFONDName;
		int16_t					_fResourceID;
		unsigned char			_fResourceName[ 256 ];
		
	};
	
}

#endif /* __FTFONT_SFNTRESOURCE__ */
