/*
	File:		FTCharacterSet.h

	Contains:	Wrapper class for CFCharacterSet

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTCHARACTERSET__
#define __FTCHARACTERSET__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {
	
	class FTString;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFCharacterSetRef
	 *
	 *  FTCharacterSet is a C++ wrapper around CFCharacterSetRef
	 *      (and therefore NSCharacterSet, as well). It simplifies
	 *      creation and querying of character sets. In particular,
	 *		it is less UTF-16-centric.
	 */

	class FTCharacterSet : public FTCoreFoundationType {
		
	public:
		
        static FTCharacterSet *Adopt(CFMutableCharacterSetRef iCharacterSet);
        static FTCharacterSet *Retain(CFMutableCharacterSetRef iArray);
        static FTCharacterSet *Copy(CFMutableCharacterSetRef iArray);

		static FTCharacterSet StandardCharacterSet(CFCharacterSetPredefinedSet iSetID);
		
		FTCharacterSet();
		FTCharacterSet( CFCharacterSetRef iCharacterSet );
		FTCharacterSet( CFMutableCharacterSetRef iCharacterSet, bool iAdopt = false );
		FTCharacterSet( const FTCharacterSet& iOther );
		FTCharacterSet( const FTString& iString );
		FTCharacterSet( CFRange iRange );
		FTCharacterSet( const FTCharacterSet *iOther );
		virtual ~FTCharacterSet();
		
		FTCharacterSet& operator=( const FTCharacterSet& iOther );
		FTCharacterSet& operator-=(const FTCharacterSet& iOther) { ::CFCharacterSetIntersect(_fCharacterSet,iOther._fCharacterSet); return *this; };
		FTCharacterSet& operator+=(const FTCharacterSet& iOther) { ::CFCharacterSetUnion(_fCharacterSet,iOther._fCharacterSet); return *this; };
		FTCharacterSet operator+(const FTCharacterSet& iOther) const { FTCharacterSet tReturnValue(*this); tReturnValue += iOther; return tReturnValue; };
		FTCharacterSet operator-(const FTCharacterSet& iOther) const { FTCharacterSet tReturnValue(*this); tReturnValue -= iOther; return tReturnValue; };
		
		
		operator CFCharacterSetRef() const { return (CFCharacterSetRef) _fCharacterSet; };
		operator CFMutableCharacterSetRef() { return _fCharacterSet; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fCharacterSet; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFCharacterSetCreateMutableCopy( kCFAllocatorDefault, _fCharacterSet ); };
		
		
		bool CoversCharacter( UnicodeScalarValue iUC ) const;
		UnicodeScalarValue FirstCharacter() const;
		UnicodeScalarValue CharacterFollowing( UnicodeScalarValue iUC ) const;
		UnicodeScalarValue CharacterPreceding( UnicodeScalarValue iUC ) const;
		UnicodeScalarValue LastCharacter() const;
		
		friend ostream& operator<<( ostream &iOut, const FTCharacterSet& iObject );
		
	private:
		
		CFMutableCharacterSetRef _fCharacterSet;
		
	};
	
}

#endif /* __FTCHARACTERSET__ */
