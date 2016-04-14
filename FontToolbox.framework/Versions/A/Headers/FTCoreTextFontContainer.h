/*
	File:			FTCoreTextFontContainer.h
 
	Contains:		C++ base class for TrueType fonts represented by CTFontRefs
 
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

#ifndef __FTCORETEXTFONTCONTAINER__
#define __FTCORETEXTFONTCONTAINER__

#include "FTCoreTextFont.h"
#include "FTFontContainer.h"

namespace ftx {
	
	class FTCoreTextFontContainer : public FTFontContainer {
		
	public:
		
		FTCoreTextFontContainer( CTFontRef iFont );
		
		FTCoreTextFontContainer( const FTCoreTextFontContainer& iOther );
		
		virtual ~FTCoreTextFontContainer();
		
		FTCoreTextFontContainer& operator=( const FTCoreTextFontContainer& iOther );
		
		virtual CFStringRef				GetName() const { return _fCoreTextFont.GetPostScriptName(); };
		virtual CFURLRef				GetURL() const { return nullptr; };
		virtual ItemCount				GetFontCount() const { return 1; };
		virtual FTFont					*GetIndFont( ItemCount iFont ) const;
		
		virtual void					WriteData() { /* Don't do anything */ };
		virtual void					ReadData() { /* Don't do anything */ };
		
		virtual bool					IsReadOnly() const { return true; };
		virtual bool					IsDirty() const { return false; };
		
	protected:
		
	private:
		
		FTCoreTextFont	_fCoreTextFont;
		
	};
	
}

#endif /* __FTCORETEXTFONTCONTAINER__ */
