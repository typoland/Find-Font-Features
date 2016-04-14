/*
	File:		FTOutputStream.h
 
	Contains:	Declarations for classes encapsulating the destinations for text output
 
	Version:	MacOS X
 
	Copyright:	© 2009-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins
 
*/

#ifndef __FTOUTPUTSTREAM__
#define __FTOUTPUTSTREAM__

/* ----------------------------------------------------------------------------------------- */

/* HEADERS -- ANSI */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* HEADERS -- SYSTEM */

#include <Carbon/Carbon.h>
#include <fstream>

/* HEADERS -- LIBRARY */

#include "FTTypes.h"

using namespace std;

namespace ftx {

	class FTFont_sfnt;
	class FTString;
	
//-----------------------------------------------------------------
//	class FTOutputStream
//-----------------------------------------------------------------

class FTOutputStream 
{
	
public:
	
	/*! \brief Base class for text output objects
	 *
	 *  FTOutputStream provides a standard way to
	 *		output text, either to a FILE, an ostream,
	 *		or an CFStringRef. We use this because
	 *		the long history and haphazard design 
	 *		of the Font Toolbox has left us with 
	 *		a mixture of output based on different
	 *		APIs.
	 *
	 *  Note that it is an abstract class and may
	 *		not be instantiated.
	 */

	enum EStreamType {

		kOutputType_Invalid = -1,
		kOutputType_FILE = 0,
		kOutputType_ostream = 1,
		kOutputType_string = 2,
		kOutputType_url = 3
	};

	FTOutputStream();
	FTOutputStream( const FTOutputStream& iOther );
	virtual ~FTOutputStream();
	
	FTOutputStream& operator=( const FTOutputStream& iOther );
	
	virtual bool Equals( const FTOutputStream *iOther ) const;
	
	virtual EStreamType	GetStreamType() const { return kOutputType_Invalid; };
	virtual void OutputUTF8String( const char *iString, ... ) const;
	virtual void StreamString( const FTString& iString ) const;
	virtual void StreamText( const char *iString, ... ) const;
	virtual void StreamCString( const char *iString ) const { StreamText(iString); };
	virtual void Indent( ItemCount iDepth ) const;

	void	OutputString(const FTString & iString) const;
	
protected:
	
	enum {
		kBufferSize = 65536
	};
	virtual bool EqualsInternal( const FTOutputStream *iOther ) const;

private:
	virtual void StreamText( const char *iString, va_list iList ) const;

};

//-----------------------------------------------------------------
//	class FTOutputStream_FILE
//-----------------------------------------------------------------

class FTOutputStream_FILE : public FTOutputStream
{
	
public:
	
	/*! \brief FTOutputStream class for use with stdio FILEs
	 *
	 *  FTOutputStream_FILE provides a standard way to
	 *		output text to a stdio FILE. The client
	 *		must open and close the FILE.
	 */

	FTOutputStream_FILE( FILE *iStream );
	FTOutputStream_FILE( const FTOutputStream_FILE& iOther );
	virtual ~FTOutputStream_FILE();
	
	FTOutputStream_FILE& operator=( const FTOutputStream_FILE& iOther );
	
	virtual EStreamType	GetStreamType() const { return FTOutputStream::kOutputType_FILE; };
	virtual void StreamText( const char *iString, va_list iList ) const;
	virtual void StreamCString( const char *iString ) const { ::fputs(iString, GetStream()); };

	FILE* GetStream() const { return _fStream; };
	
protected:
	virtual void SetStream(FILE *iStream) { _fStream = iStream; };
	virtual void Close() const { if (_fStream != nullptr) ::fclose(_fStream); };
	virtual bool EqualsInternal( const FTOutputStream *iOther ) const;
	
private:
	
	mutable char*	_fBuffer;
	mutable size_t	_fBufferSize;
		
	FILE *_fStream;
	
};

//-----------------------------------------------------------------
//	class FTOutputStream_URL
//-----------------------------------------------------------------

class FTOutputStream_URL : public FTOutputStream_FILE
{

public:

	/*! \brief FTOutputStream class for use with file URLs
	 *
	 *  FTOutputStream_URL provides a standard way to
	 *		output text to a file with a given URL.
	 *		It manages the creation/opening of the
	 *		file at the given URL.
	 */

	FTOutputStream_URL( CFURLRef iURL );
	FTOutputStream_URL( const FTOutputStream_URL& iOther );
	virtual ~FTOutputStream_URL();

	FTOutputStream_URL& operator=( const FTOutputStream_URL& iOther );

	virtual EStreamType	GetStreamType() const { return FTOutputStream::kOutputType_url; };

	CFURLRef GetURL() const { return _fURL; };

protected:
	virtual bool EqualsInternal( const FTOutputStream *iOther ) const;

private:
	CFURLRef	_fURL;

};

//-----------------------------------------------------------------
//	class FTOutputStream_ostream
//-----------------------------------------------------------------

class FTOutputStream_ostream : public FTOutputStream
{
	
public:
	
	/*! \brief FTOutputStream class for use with C++ output streams
	 *
	 *  FTOutputStream_ostream provides a standard way to
	 *		output text to a file with a given C++ output
	 *		stream. The output stream must be created and 
	 *		deleted by the client.
	 */

	FTOutputStream_ostream( ostream *iStream );
	FTOutputStream_ostream( const FTOutputStream_ostream& iOther );
	virtual ~FTOutputStream_ostream();
	
	FTOutputStream_ostream& operator=( const FTOutputStream_ostream& iOther );
	
	virtual EStreamType	GetStreamType() const { return FTOutputStream::kOutputType_ostream; };
	virtual void StreamText( const char *iString, va_list iList ) const;
	
	ostream* GetStream() const { return _fStream; };
	
protected:
	virtual bool EqualsInternal( const FTOutputStream *iOther ) const;
	
private:
	
	mutable char*	_fBuffer;
	mutable size_t	_fBufferSize;
	
	ostream* _fStream;
	
};

//-----------------------------------------------------------------
//	class FTOutputStream_string
//-----------------------------------------------------------------

class FTOutputStream_string : public FTOutputStream
{
	
public:
	
	/*! \brief FTOutputStream class for use with string objects
	 *
	 *  FTOutputStream_string provides a standard way to
	 *		output text to a string buffer. Heavy use may
	 *		create performance problems. The client is responsible
	 *		for creating and freeing the string object. 
	 *
	 *  If the FTOutputStream_string is created using an FTString,
	 *		the FTString may not be deallocated before 
	 *		the FTOutputStream_string.
	 */

	FTOutputStream_string( FTString& iStream );
	FTOutputStream_string( CFMutableStringRef iStream );
	FTOutputStream_string( const FTOutputStream_string& iOther );
	virtual ~FTOutputStream_string();
	
	FTOutputStream_string& operator=( const FTOutputStream_string& iOther );
	
	virtual EStreamType	GetStreamType() const { return FTOutputStream::kOutputType_string; };
	virtual void StreamText( const char *iString, va_list iList ) const;
	
	CFMutableStringRef GetStream() const { return _fStream; };
	
protected:
	virtual bool EqualsInternal( const FTOutputStream *iOther ) const;
	
private:
	
	CFMutableStringRef _fStream;
	
};

}

#endif /* __FTOUTPUTSTREAM__ */
