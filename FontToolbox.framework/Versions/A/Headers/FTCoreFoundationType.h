/*
	File:		FTCoreFoundationType.h

	Contains:	Abstract superclass for all CFType wrappers

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTCOREFOUNDATIONTYPE__
#define __FTCOREFOUNDATIONTYPE__

#include <CoreFoundation/CoreFoundation.h>

/**
 * \defgroup Wrapper Classes
 * @{
 */


namespace ftx {
	
	class FTCoreFoundationType {
        /*! \brief Base class for CoreFoundation wrappers.
         *
         *  FTCoreFoundationType is an abstract base class for
         *      CoreFoundation wrapper classes (e.g., FTString).
         *      This is an abstract class.
         */
	public:

        enum EMemoryControlType {
            kRetainObject = 0,
            kAdoptObject = 1
        };

		FTCoreFoundationType();
		FTCoreFoundationType( const FTCoreFoundationType& iOther );
		FTCoreFoundationType( const FTCoreFoundationType&& iOther );
		virtual ~FTCoreFoundationType();
		
		FTCoreFoundationType& operator=( const FTCoreFoundationType& iOther );
		FTCoreFoundationType& operator=( const FTCoreFoundationType&& iOther );

		operator CFTypeRef() const { return Cast(); };
		virtual CFTypeRef Cast() const = 0;
		virtual CFTypeRef Copy() const = 0;
		
	private:
		
	};
	
}

/**@}*/

#endif /* __FTCOREFOUNDATIONTYPE__ */
