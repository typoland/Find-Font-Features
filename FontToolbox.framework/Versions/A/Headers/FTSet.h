/*
	File:		FTSet.h

	Contains:	Wrapper class for CFSet

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTSET__
#define __FTSET__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {
	
	class FTArray;
	class FTString;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFSetRef
	 *
	 *  FTSet is a C++ wrapper around CFSetRef
	 *      (and therefore NSSet, as well). It simplifies
	 *      creation and manipulation of sets.
	 *
	 *  Note that the its contents are CFTypeRefs, and
	 *		*not* subclasses of FTCoreFoundationType.
	 *		Use the Cast() function of FTCoreFoundationType
	 *		instances to add items to an FTSet.
	 *
	 *	Note further that FTSets are inherently mutable.
	 */
	
	class FTSet : public FTCoreFoundationType {
		
	public:
        static FTSet *Adopt(CFMutableSetRef iValue);
        static FTSet *Retain(CFMutableSetRef iValue);
        static FTSet *Copy(CFMutableSetRef iValue);

		FTSet();
		FTSet( CFSetRef iSet );
		FTSet( CFMutableSetRef iSet, bool iAdopt = false );
		FTSet( const FTSet& iOther );
		FTSet( const FTArray& iArray );
		FTSet( const FTSet *iOther );
		virtual ~FTSet();
		
		FTSet& operator=( const FTSet& iOther );
		FTSet& operator-=(const FTSet& iOther);
		FTSet& operator+=(const FTSet& iOther);
		FTSet& operator&=(const FTSet& iOther);
		FTSet& operator|=(const FTSet& iOther) { return operator+=(iOther); };

		FTSet operator-(const FTSet& iOther) const { FTSet tReturnValue(*this); tReturnValue -= iOther; return tReturnValue; };
		FTSet operator+(const FTSet& iOther) const { FTSet tReturnValue(*this); tReturnValue += iOther; return tReturnValue; };
		FTSet operator&(const FTSet& iOther) const { FTSet tReturnValue(*this); tReturnValue &= iOther; return tReturnValue; };
		FTSet operator|(const FTSet& iOther) const { FTSet tReturnValue(*this); tReturnValue += iOther; return tReturnValue; };

		void AddToSet(CFMutableSetRef iOther) const;

		bool operator!=(const FTSet& iOther) const;
		bool operator==(const FTSet& iOther) const { return !operator!=(iOther); };
		
		operator CFSetRef() const { return (CFSetRef) _fSet; };
		operator CFMutableSetRef() { return _fSet; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fSet; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFSetCreateCopy( kCFAllocatorDefault, _fSet ); };
		
		operator FTArray() const;
		
		void Clear() { ::CFSetRemoveAllValues(_fSet); };
		
		int64_t Length() const { return ::CFSetGetCount( _fSet ); };
		
		void AddObject( const FTCoreFoundationType* iObject );
		void AddObject( CFTypeRef iObject );
		void AddObject( int64_t iNumber );
		void AddObject( const char *iString );
		
		void RemoveObject( const FTCoreFoundationType* iObject );
		void RemoveObject( CFTypeRef iObject );
		void RemoveObject( int64_t iNumber );
		void RemoveObject( const char *iString );
		
		bool ContainsValue( CFTypeRef iValue ) const;
		bool ContainsValue( const char *iValue ) const;
		bool ContainsValue( int64_t iValue ) const;

		FTString Contents() const;
		
		friend ostream& operator<<( ostream &iOut, const FTSet& iObject );
		
	private:
		
		CFMutableSetRef _fSet;
		
	};
	
}

#endif /* __FTSET__ */
