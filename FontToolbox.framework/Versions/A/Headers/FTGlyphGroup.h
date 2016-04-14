/*
	File:			FTGlyphGroup.h

	Contains:		C++ class for individual 'Zapf' table glyph groups

	Version:		Mac OS X

	Written by:		The Apple Font Group

	Copyright:		© 2011-2015 by Apple Inc. All rights reserved.

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

#ifndef __FTGLYPHGROUP__
#define __FTGLYPHGROUP__

#include "FTFontTable_Zapf.h"
#include "FTNamedGroup.h"

namespace ftx {

class FTGlyphGroup {
	
public:
	
	FTGlyphGroup( const uint8_t *iData = nullptr );
	FTGlyphGroup( const FTGlyphGroup& iOther );
	virtual ~FTGlyphGroup();
	
	FTGlyphGroup& operator=( const FTGlyphGroup& iOther );
	
	bool operator==( const FTGlyphGroup& iOther ) const;
	bool operator!=( const FTGlyphGroup& iOther ) const;
	
	size_t	SubgroupCount() const { return _fSubgroupCount; };
	const FTNamedGroup *GetIndSubgroup( size_t iIndex ) const;
	const FTNamedGroup& operator[]( size_t iIndex ) const;
	FTNamedGroup& operator[]( size_t iIndex );
	
private:
	
	size_t _fSubgroupCount;
	FTNamedGroupPtr *_fSubgroups;
	
};

}

#endif /* __FTGLYPHGROUP__ */
