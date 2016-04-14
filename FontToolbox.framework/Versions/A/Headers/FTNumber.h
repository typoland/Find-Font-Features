/*
	File:		FTNumber.h

	Contains:	A wrapper class for CFNumber

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTNUMBER__
#define __FTNUMBER__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFNumberRef
	 *
	 *  FTNumber is a C++ wrapper around CFNumberRef
	 *      (and therefore NSNumber, as well). It simplifies
	 *      creation and handling of number objects.
	 *
	 *  The current SPI for FTNumber is geared toward
	 *		using it for integers.
	 */

	class FTNumber : public FTCoreFoundationType {
		
	public:
        static FTNumber *Adopt(CFNumberRef iValue);
        static FTNumber *Retain(CFNumberRef iValue);
        static FTNumber *Copy(CFNumberRef iValue);

		FTNumber();
		FTNumber( int64_t iNumber );
		FTNumber( const FTNumber& iOther );
		FTNumber( const CFTypeRef iOther );
		FTNumber( const CFNumberRef iOther, bool iRetain = false );
		virtual ~FTNumber();
		
		FTNumber& operator=( const FTNumber& iOther );
		FTNumber& operator=( int64_t iNumber );
		
		bool operator==( const FTNumber& iOther ) const;
		bool operator==( int64_t iNumber ) const;
		bool operator!=( const FTNumber& iOther ) const;
		bool operator!=( int64_t iNumber ) const;
		bool operator<(const FTNumber& iOther) const { return int64_t(*this) < int64_t(iOther); };
		bool operator<=(const FTNumber& iOther) const { return int64_t(*this) <= int64_t(iOther); };
		bool operator>(const FTNumber& iOther) const { return int64_t(*this) > int64_t(iOther); };
		bool operator>=(const FTNumber& iOther) const { return int64_t(*this) >= int64_t(iOther); };

		operator int64_t() const;
		operator CFNumberRef() const { return _fNumber; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fNumber; };
		virtual CFTypeRef Copy() const { int64_t tScratch = int64_t( *this ); return ::CFNumberCreate( kCFAllocatorDefault, kCFNumberSInt64Type, &tScratch ); }

		static CFNumberRef Zero();
		
		friend ostream& operator<<( ostream& iOut, const FTNumber &iNumber );
		
	private:
		
		CFNumberRef _fNumber;
		
	};
	
}

#endif /* __FTNUMBER__ */
