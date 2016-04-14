/*
	File:			FTDiskBasedFontContainer.h
 
	Contains:		C++ class for TrueType fonts contained in the data fork of files
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzales
 
		Technology:			Apple Font Tools
 
	N.B., to the extent possible, this code observes the following naming conventions
		for variables
	Method or function *input* variables all have names beginning with "i"
	Method or function *output* variables all have names beginning with "o"
	Local variables all have names beginning with "t"
	Structure or class members all have names beginning with "f" (public members) or
		"_f" (private members)
	Constants all have names beginning with "k"
*/

#ifndef __FTDISKBASEDFONTCONTAINER__
#define __FTDISKBASEDFONTCONTAINER__

#include <Carbon/Carbon.h>

#include "FTFontContainer.h"

namespace ftx {
	
	class FTDiskBasedFontContainer : public FTFontContainer {
		
	public:
		
		FTDiskBasedFontContainer( const FSRef& iFSRef, bool iIsReadOnly = kReadOnly );
		FTDiskBasedFontContainer( const CFURLRef& iURL, bool iIsReadOnly = kReadOnly );
		FTDiskBasedFontContainer( const FTDiskBasedFontContainer& iOther );
		
		virtual ~FTDiskBasedFontContainer();
		
		FTDiskBasedFontContainer& operator=( const FTDiskBasedFontContainer& iOther );
		
		virtual CFStringRef				GetName() const;
		virtual CFStringRef				CopyPath() const;
		
		virtual const FSRef&			GetFile() const { return _fFile; };
		virtual const CFURLRef			GetFileURL() const;
		virtual CFURLRef				GetURL() const { return GetFileURL(); };
		
		virtual void					SetFile( const FSRef& iFSRef );
		virtual void					WriteData();
		virtual void					ReadData();
		
	protected:
		
		FTDiskBasedFontContainer();
		
	private:
		
		void			WriteTTFData();		// This includes .otf, since they're both single sfnt-based fonts
		void			WriteTTCData();
		CFDataRef		CreateOutputFontData( CFSetRef iTagSet );
		CFDictionaryRef	CreateCommonData( CFSetRef iTagSet );
		static void		MakeCommonDataForTag( const void *iValue, void *oContext );
		static void		PadTo4( CFMutableDataRef iData );
		static void		WriteCommonTableData( const void *iKey, const void *iValue, void *oContext );
		bool			WriteTTCFile() const;
		static int		TableEntryAlphabeticalOrderCompareFunction( const void *arg1, const void *arg2 );
		
		FSRef			_fFile;
		CFURLRef		_fFileURL;
		CFStringRef		_fName;
		
	};
	
}

#endif /* __FTDISKBASEDFONTCONTAINER__ */
