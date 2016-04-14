/*
	File:			FTNameTableEntry.h
 
	Contains:		C++ class for individual 'name' table entries
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	$Log: FTNameTableEntry.h,v $
	Revision 1.3  2007/01/15 23:28:00  kurita
	<rdar://problem/4916090> updated copyright.

	Revision 1.2  2006/08/01 19:49:03  jenkins
	Refactored to have encoding-fetching code in only one place
	
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

#ifndef __FTNAMETABLEENTRY__
#define __FTNAMETABLEENTRY__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>
#include <fstream>

using namespace std;

namespace ftx {

class FTNameTableEntry {

public:
	
	static CFStringRef CreateStringFromNameCode( FontNameCode iCode );
	static CFStringRef CreateStringFromPlatformCode( FontPlatformCode iPlatform );
	static CFStringRef CreateStringFromScriptCode( FontPlatformCode iPlatform, FontScriptCode iScript );
	static CFStringRef CreateStringFromLanguageCode( FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage );

	FTNameTableEntry( CFStringRef iString, FontNameCode iNameType, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage );
	FTNameTableEntry( const uint8_t *iData, ByteCount iLength, FontNameCode iNameType, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage );
	FTNameTableEntry( const FTNameTableEntry& iOther );
	
	virtual ~FTNameTableEntry();
	
	FTNameTableEntry& operator=( const FTNameTableEntry& iOther );
	
	virtual bool operator==( const FTNameTableEntry& iOther ) const;
	virtual bool operator!=( const FTNameTableEntry& iOther ) const;
    bool operator==( CFStringRef iString ) const;
    bool operator!=( CFStringRef iString ) const;
    
    friend ostream& operator<<( ostream &iOut, const FTNameTableEntry& iEncoding );
	
	virtual CFStringRef GetNameString() const { return _fNameString; };
	virtual const uint8_t *GetUnswappedNameData() const { return _fUnswappedNameData; };
	virtual ByteCount GetUnswappedNameDataLength() const { return _fUnswappedNameDataLength; };
	virtual FontNameCode GetNameCode() const { return _fNameCode; };
	virtual FontPlatformCode GetPlatform() const { return _fPlatform; };
	virtual FontScriptCode GetScript() const { return _fScript; };
	virtual FontLanguageCode GetLanguage() const { return _fLanguage; };
	
	virtual void SetNameString( CFStringRef iNameString );
	virtual void SetUnswappedNameData( CFDataRef iUnswappedNameData );
	virtual void SetNameCode( FontNameCode iCode );
	virtual void SetPlatform( FontNameCode iCode );
	virtual void SetScript( FontNameCode iCode );
	virtual void SetLanguage( FontNameCode iCode );
	
	virtual bool IsDirty() const { return _fIsDirty; };
	virtual void Clean() { _fIsDirty = false; };
	virtual void Dirty() { _fIsDirty = true; };

private:

	enum {
		kInvalidEncoding = 0x7FFFFFFFU
		};

	FTNameTableEntry();
	
	CFStringEncoding	GetEncoding() const;
	
	static CFStringRef	CreateStringFromUnicodeScript( FontScriptCode iScript );
	static CFStringRef	CreateStringFromMacintoshScript( FontScriptCode iScript );
	static CFStringRef	CreateStringFromMicrosoftScript( FontScriptCode iScript );
	
	void				ReplaceNameStringFromUnswappedNameData();
	void				ReplaceUnswappedNameDataFromNameString();

	CFStringRef			_fNameString;
	const uint8_t		*_fUnswappedNameData;
	ByteCount			_fUnswappedNameDataLength;
	FontNameCode		_fNameCode;
	FontPlatformCode	_fPlatform;
	FontScriptCode		_fScript;
	FontLanguageCode	_fLanguage;
	bool				_fIsDirty;
};

}
	
#endif /* __FTNAMETABLEENTRY__ */
