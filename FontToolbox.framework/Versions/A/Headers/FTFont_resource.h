/*
	File:			FTFont.h
 
	Contains:		C++ class individual TrueType fonts
 
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

#ifndef __FTRESOURCEFONT__
#define __FTRESOURCEFONT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont.h"

namespace ftx {
	
	class FTFont_resource : public FTFont {
		
	public:
		
		FTFont_resource( FTFontContainer *iContainer, Handle iFontData );
		FTFont_resource( FTFontContainer *iContainer,
						const uint8_t *iData, ByteCount iLength,
						ResType iResType, int16_t iResourceID, const unsigned char *iResourceName );
		FTFont_resource( const FTFont_resource& iOther );
		
		virtual ~FTFont_resource();
		
		FTFont_resource& operator=( const FTFont_resource& iOther );
		
		// Returns a string which (hopefully) is a unique way of specifying a
		//		certain version of the font.  It is currently a concatination
		//		of resource type, resource number, resource name for rescource
		//		fonts
		virtual CFStringRef				GetIdentifier() const;
		
		// Returns the most useful name for the font as a string
		virtual CFStringRef				GetName() const;
		
		// Returns the PostScript name for the font as a string
		virtual CFStringRef				GetPostScriptName() const { return GetName(); };
		
		virtual uint16_t				GetResourceID() const { return _fResourceID; };
		virtual ResType					GetResourceType() const { return _fResourceType; };
		virtual const unsigned char		*GetResourceName() const { return _fResourceName; };

		int16_t							GetResourceFlags() const { return _fResourceFlags; };

		CFStringEncoding				GetScript() const;
		
		virtual void					CheckIntegrity() const;
		
	protected:
		
		FTFont_resource();
		
		virtual void			ReadData() const;
		virtual void			ReadDataInternal() = 0;
		
	private:
		
		bool					_fDataRead;
		
		int16_t					_fResourceID;
		int16_t					_fResourceFlags;
		ResType					_fResourceType;
		unsigned char			_fResourceName[ 256 ];
		
		CFStringRef				_fIdentifier;
		CFStringRef				_fName;
		
	};
	
}

#endif /* __FTRESOURCEFONT__ */
