/*
	File:			FTLWFNFontContainer.h
 
	Contains:		C++ class for PostScript Type 1 fonts stored in an LWFN file
 
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

#ifndef __FTLWFNFONTCONTAINER__
#define __FTLWFNFONTCONTAINER__

#include <Carbon/Carbon.h>

#include "FTResourceFontContainer.h"

namespace ftx {

class FTFont_POST;
class FTFont_Type1;

class FTLWFNFontContainer : public FTResourceFontContainer {

public:

	enum {
		kFileType_LWFN = FOUR_CHAR_CODE( 'LWFN' )
		};

	FTLWFNFontContainer( const FSRef& iFSRef, bool iIsDataforkSuitcase, bool iIsReadOnly );
	FTLWFNFontContainer( const CFURLRef& iURL, bool iIsDataforkSuitcase, bool iIsReadOnly );
	
	FTLWFNFontContainer( const FTLWFNFontContainer& iOther );
	
	virtual ~FTLWFNFontContainer();
	
	FTLWFNFontContainer& operator=( const FTLWFNFontContainer& iOther );
	
	virtual const FTFont_POST	*GetPOST( int16_t iID ) const;
	virtual const FTFont_Type1	*GetType1Font() const;
	
	virtual void				WriteData();

protected:

	FTLWFNFontContainer();
	virtual void		AddFontsFromResources( CFMutableArrayRef iFontArray );

private:

	void				ClearData();

	CFDataRef                   _fData;
	mutable const FTFont_Type1	*_fType1Font;

};

}

#endif /* __FTLWFNFONTCONTAINER__ */
