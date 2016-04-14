/*
	File:			FTKindName.h

	Contains:		C++ class for individual 'Zapf' table glyph kind names

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

#ifndef __FTKINDNAME__
#define __FTKINDNAME__

namespace ftx {

class FTKindName {
	
public:
	
	static const FTKindName *CreateKindName( const uint8_t *iData );
	
	FTKindName( uint16_t iNameKind, CFTypeRef iName );
	
	virtual ~FTKindName();
	
	virtual bool operator==( const FTKindName& iOther ) const;
	virtual bool operator!=( const FTKindName& iOther ) const;
	
	virtual uint16_t	GetNameKind() const { return _fNameKind; };
	virtual CFTypeRef	GetName() const { return _fName; };

protected:
	
private:
	
	uint16_t	_fNameKind;
	CFTypeRef	_fName;
	
	FTKindName();
	FTKindName( const FTKindName& iOther );
	virtual FTKindName& operator=( const FTKindName& iOther );

};
	
	
}

#endif /* __FTKINDNAME__ */
