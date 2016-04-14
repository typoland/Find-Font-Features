/*
	File:		FTArray.h

	Contains:	Wrapper class for CFArray

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTARRAY__
#define __FTARRAY__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {

    class FTURL;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFArrayRef
	 *
	 *  FTArray is a C++ wrapper around CFArrayRef
	 *      (and therefore NSArray, as well). It simplifies
	 *      creation of arrays.
	 *
	 *  Note that the its contents are CFTypeRefs, and
	 *		*not* subclasses of FTCoreFoundationType.
	 *		Use the Cast() function of FTCoreFoundationType
	 *		instances to add items to an FTArray.
	 *
	 *	Similarly, use cast operators and constructors
	 *		to turn the contents of an FTArray instance
	 *		into other FTCoreFoundationType instances.
	 *
	 *	Note further that NSArrays are inherently mutable.
	 */

	class FTArray : public FTCoreFoundationType {
		
	public:

        static FTArray *Adopt(CFMutableArrayRef iArray);
        static FTArray *Retain(CFMutableArrayRef iArray);
        static FTArray *Copy(CFMutableArrayRef iArray);

		FTArray();
		FTArray( CFArrayRef iArray );
		FTArray( CFMutableArrayRef iArray, bool iAdopt = false );
		FTArray( const FTArray& iOther );
		FTArray( const FTArray *iOther );
		FTArray( const FTURL& iOther );
		virtual ~FTArray();
		
		FTArray& operator=( const FTArray& iOther );
		
		operator CFArrayRef() const { return (CFArrayRef) _fArray; };
		operator CFMutableArrayRef() const { return _fArray; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fArray; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFArrayCreateCopy( kCFAllocatorDefault, _fArray ); };
		
		void Clear() { ::CFArrayRemoveAllValues(_fArray); };
		
		FTArray operator+(const FTArray& iOther) const;
		FTArray& operator+=(const FTArray& iOther);
		
		int64_t Length() const { return ::CFArrayGetCount( _fArray ); };
		CFTypeRef operator[]( int iIndex ) const;
		void AddObject( const FTCoreFoundationType* iObject );
		void AddObject( CFTypeRef iObject );
		void AddObject( int64_t iNumber );
		void AddObject( const char *iString );
		void PrependObject( CFTypeRef iObject ) { ::CFArrayInsertValueAtIndex(_fArray, 0, iObject); };
		void PrependObject( int64_t iNumber );

		/** @name Insertion
		 *  InsertObjectAtIndex() inserts the indicated object at the indicated index;
		 *		iDefaultValue is repeatedly added to the array (if necessary) to make
		 *		sure that iIndex is not out-of-range. Otherwise, this is just a wrapped
		 *		call to CFArrayInsertValueAtIndex()
		 */
		///@{
		void InsertObjectAtIndex(CFTypeRef iObject, CFIndex iIndex, CFTypeRef iDefaultValue);
		///@}

		/** @name Replacement
		 *  SetObjectAtIndex() inserts the object currently at the given index with the new one;
		 *		iDefaultValue is repeatedly added to the array (if necessary) to make
		 *		sure that iIndex is not out-of-range. Otherwise, this is just a wrapped
		 *		call to CFArraySetValueAtIndex()
		 */
		///@{
		void SetObjectAtIndex(CFTypeRef iObject, CFIndex iIndex, CFTypeRef iDefaultValue);
		///@}

		void Sort();
		void RemoveObjectAtIndex(CFIndex iIndex);
		
		CFIndex FirstIndexOfValue( CFTypeRef iValue ) const;
		CFIndex GetCountOfValue( CFTypeRef iValue ) const;
		
		CFIndex FirstIndexOfUncasedValue( CFStringRef iValue ) const;
		CFIndex GetCountOfUncasedValue( CFStringRef iValue ) const;

		friend ostream& operator<<( ostream &iOut, const FTArray& iObject );
		
	private:
		
		CFMutableArrayRef _fArray;
		
	};
}

#endif /* __FTARRAY__ */
