/*
	File:			FTCoreTextFont.h
 
	Contains:		C++ class individual CoreText fonts
 
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

#ifndef __FTCORETEXTFONT__
#define __FTCORETEXTFONT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont_sfnt.h"

namespace ftx {

class FTCoreTextFont : public FTFont_sfnt {

public:

	FTCoreTextFont( CTFontRef iFont );
	FTCoreTextFont( const FTCoreTextFont& iOther );

	virtual ~FTCoreTextFont();
	
	FTCoreTextFont& operator=( const FTCoreTextFont& );
	
	CTFontRef	GetCTFont() const { return _fCTFontRef; };

	virtual void					Rebuild();

	//	Determines whether or not this font object is even parsable as 
	//		an actual font
	virtual void					TestBasicUsability() const;
	
	// Returns the *first* 'FOND' resouce (if any) associated with this font
	virtual const FTFont_FOND		*GetFOND() const { return nullptr; };

	//	Table functions
	virtual void					SetTable( FourCharCode iTag, const FTFontTable& iTable );
	virtual void					CreateAndAddTable( FourCharCode iTag, CFDataRef iData );
	virtual void					PrintDiagnostics() const;
	
	//	Getters
	virtual Fixed					GetScaler() const { return 0; };
	virtual CFArrayRef				GetTables() const;
	virtual bool					DeleteFontName( CFIndex iIndex );

	virtual bool					DeleteFontName(
										FontNameCode		iName,
										FontPlatformCode	iPlatform,
										FontScriptCode		iScript,
										FontLanguageCode	iLanguage );

	virtual bool					DeleteFontTable(
										ItemCount iIndex );
	
	virtual bool					DeleteTaggedFontTable(
										FourCharCode iTag );

protected:

private:
	
	void	DeleteTables();
	
	
	CTFontRef			_fCTFontRef;
	mutable CFArrayRef	_fTables;
	
};

}

#endif /* __FTCORETEXTFONT__ */
