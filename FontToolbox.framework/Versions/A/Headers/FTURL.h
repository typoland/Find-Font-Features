/*
	File:		FTURL.h

	Contains:	Wrapper class for CFURL

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2013 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTURL__
#define __FTURL__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {
	
	class FTData;
	class FTString;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFURLRef
	 *
	 *  FTURL is a C++ wrapper around CFURLRef
	 *      (and therefore NSURL, as well). It simplifies
	 *      creation and handling of URLs.
	 */
	
	class FTURL : public FTCoreFoundationType {
		
	public:
        static FTURL *Adopt(CFURLRef iValue);
        static FTURL *Retain(CFURLRef iValue);
        static FTURL *Copy(CFURLRef iValue);

		static FTURL URLForTemporaryDirectoryWithPrefix(CFStringRef iPrefix);

		FTURL();
		FTURL( CFURLRef iURL, bool iAdopt = false );
		FTURL( const char *iPath );
		FTURL( const FTString& iPath );
		FTURL( CFBundleRef iBundle, const FTString& iName, const FTString& iExtension);
		FTURL( const FTURL& iOther );
		FTURL( const FTURL *iOther );
		virtual ~FTURL();
		
		FTURL& operator=( const FTURL& iOther );
		bool IsDirectory() const;
		bool IsFile() const { return !IsDirectory(); };
		
		CFTypeRef		CopyProperty( CFStringRef iKey, int32_t *oErrorCode = nullptr ) const;
		bool			WriteProperty( CFStringRef iKey, CFTypeRef iValue, int32_t *oErrorCode = nullptr ) const;
		FTData			Data( int32_t *oErrorCode = nullptr ) const;
		bool			WriteData( const FTData& iData, int32_t *oErrorCode = nullptr ) const;
		
		FTString		RootDirectory() const;
		FTString		FileName() const;
		FTString		FileExtension() const;
		
		bool	IsValid() const { return (_fURL != nullptr); };
		operator CFURLRef() const { return (CFURLRef) _fURL; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fURL; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFURLCopyAbsoluteURL( _fURL ); };

		bool GetFSRef(FSRef *oFSRef) const;
		
		operator FTString() const;
		
		friend ostream& operator<<( ostream &iOut, const FTURL& iObject );
		
	private:
		
		CFURLRef _fURL;
		
	};
	
}

#endif /* __FTSET__ */
