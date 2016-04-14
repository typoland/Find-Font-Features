/*
	 File:		FTDataUtilities.h
	 
	 Contains:	Utility functions to bridge to Objective-C.
	 
	Version:	Mac OS X
 
	Written by:	The Apple Font Group
 
	Copyright:	Copyright © 2011-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins

*/

#ifndef __FTDATAUTILITIES__
#define __FTDATAUTILITIES__

#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>

namespace ftx {

	class FTString;
	
	class FTDataUtilities {
		
	public:
		static int16_t BuildOfTool(const FTString& iToolName);
		static CFArrayRef ArrayWithContentsOfURL( CFURLRef iURL );
        static CFArrayRef ArrayWithNamedPList( CFStringRef iName );
        static void CacheData();
		static CFDataRef CreateDataRef( const FSRef *iFile );
		static CFDictionaryRef DictionaryWithContentsOfURL( CFURLRef iURL );
		static CFDictionaryRef DictionaryWithNamedPList( CFStringRef iName );
        static CFDictionaryRef CreateLocalizedNames(CFStringRef iName);
		static FTString OperatingSystemVersionString();

		static bool			IsAppleInternal();
        static SecKeyRef    PrivateKey();
        static SecKeyRef    PublicKey();

		static CFStringRef	CreatePathForTemporaryFileWithPrefix(CFStringRef iPrefix);

    private:
        static CFURLRef     KeyDictionaryURL();
        static SecKeyRef    KeyForKey(CFStringRef iKeyKey);

	};
}

#endif /* __FTDATAUTILITIES__ */
