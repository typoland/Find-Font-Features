/*
	File:			FTException.h
 
	Contains:		Exception class for font table manipulation
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: not supported by cvs2svn $
	Revision 1.1  2006/07/07 17:35:45  jenkins
	First checked in.
	

	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTEXCEPTION__
#define __FTEXCEPTION__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

namespace ftx {
	
	class FTFont;
	
	class FTException {
		
	public:
		
		static void			ReportCatch( const FTException* iException, FILE *iStream, const char *iFunctionName, const FTFont* iFont );
		
		FTException();
		FTException( const char *iAssertion, int32_t iErrorCode, const char *iMessage, const char *iFile, UInt32 iLine );
		FTException( const char *iAssertion, int32_t iErrorCode, const char *iFile = nullptr, UInt32 iLine = 0 );
		FTException( const FTException& iOther );
		
		virtual ~FTException();
		
		FTException& operator=( const FTException& iOther );
		
		virtual const char	*GetAssertion() const { return _fAssertion; };
		virtual int32_t		GetErrorCode() const { return _fErrorCode; };
		virtual const char	*GetFile() const { return _fFile; };
		virtual UInt32		GetLine() const { return _fLine; };
		virtual CFStringRef	GetUIMessageString() const;
		
		virtual void		PrintReport( FILE *iStream = stderr ) const;
		virtual void		ReportCatch( FILE *iStream, const char *iFunctionName, const FTFont* iFont ) const;
		
		virtual const char	*GetDetailedMessage() const { return _fDetailedMessage; };
		
	protected:
		
	private:
		
		enum {
			kMaxFileLength = PATH_MAX,
			kMaxMessageLength = 2048
		};
		
		static CFBundleRef	GetBundle();
		
		char		_fAssertion[ kMaxMessageLength ];
		int32_t		_fErrorCode;
		char		_fFile[ kMaxFileLength ];
		UInt32		_fLine;
		char		_fDetailedMessage[ kMaxMessageLength ];
		CFStringRef	_fMessageString;
		
	};
	
	
#define THROW_IF(a,b) do { if(a) throw FTException(#a,b,__FILE__,__LINE__); } while(0)
#define THROW_IF_NOT(a,b)  do { if(!(a)) throw FTException(#a,b,__FILE__,__LINE__); } while(0)
	
#define THROW_IF_MESSAGE(a,b) do { if(a) throw FTException(#a,-1,b,__FILE__,__LINE__); } while(0)
#define THROW_IF_NOT_MESSAGE(a,b)  do { if(!(a)) throw FTException(#a,-1,b,__FILE__,__LINE__); } while(0)
	
#define ThrowIf(a)  do { if(a) throw FTException(#a,-1,__FILE__,__LINE__); } while(0)
#define ThrowIfNot(a)  do { if(!(a)) throw FTException(#a,-1,__FILE__,__LINE__); } while(0)
#define ThrowIfOSError(a)  do { if((a)!=noErr) { char tErrorScratch[256]; ::sprintf( tErrorScratch, "A system call returned %d", (int) (a) ); throw FTException(#a,a,tErrorScratch,__FILE__,__LINE__); } } while(0)
#define ThrowIfResError(a)  do { OSStatus resError = ::ResError(); if(resError!=noErr) { char tErrorScratch[256]; ::sprintf( tErrorScratch, "ResError() returned %d after %s was called", (int) resError, (a) ); throw FTException("ResError()",resError,tErrorScratch,__FILE__,__LINE__); } } while(0)
#define ThrowIfNULL(a)  do { if(a==nullptr) throw FTException(#a,-1,"A memory allocation failed",__FILE__,__LINE__); } while(0)
#define ThrowIfNULLParameter(a)  do { if(a==nullptr) throw FTException(#a,-1,"nullptr was incorrectly passed as a function parameter",__FILE__,__LINE__); } while(0)
	
}

#endif /* __FTEXCEPTION__ */
