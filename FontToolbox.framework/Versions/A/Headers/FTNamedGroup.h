/*
	File:			FTNamedGroup.h

	Contains:		C++ class for individual 'Zapf' table named groups

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

#ifndef __FTNAMEDGROUP__
#define __FTNAMEDGROUP__

#include "FTFontTable_Zapf.h"

namespace ftx {
	
	class FTNamedGroup {
		
	public:
		
		FTNamedGroup( const ZAPFNamedGroup* iNamedGroup, uint16_t iFlags = 0 );
		FTNamedGroup( const FTNamedGroup& iOther );
		virtual ~FTNamedGroup();
		
		FTNamedGroup& operator=( const FTNamedGroup& iOther );
		virtual bool operator==( const FTNamedGroup& iOther ) const;
		virtual bool operator!=( const FTNamedGroup& iOther ) const;
		
		uint16_t		GetFlags() const { return _fFlags; };
		FontNameCode	GetNameCode() const { return ::CFSwapInt16BigToHost( _fNamedGroup->fNameIndex ); };
		ItemCount		GetGlyphCount() const { return ::CFSwapInt16BigToHost( _fNamedGroup->fNumGlyphs ); };
		FTGlyphID		GetIndGlyph( ItemCount iIndex ) const;

	private:
		
		FTNamedGroup();
		const ZAPFNamedGroup *_fNamedGroup;
		uint16_t			_fFlags;
		
	};
	
	typedef FTNamedGroup *FTNamedGroupPtr;
	
}

#endif /* __FTNAMEDGROUP__ */
