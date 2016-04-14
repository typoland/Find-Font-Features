/*
	File:			FTResourceFontContainer.h
 
	Contains:		C++ class for TrueType fonts contained in the resource fork of files
 
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

#ifndef __FTRESOURCEFONTCONTAINER__
#define __FTRESOURCEFONTCONTAINER__

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>

#include "FTDiskBasedFontContainer.h"
#include "FTTypes.h"

namespace ftx {
	
	class FTResourceHandler;
	
	class FTResourceFontContainer : public FTDiskBasedFontContainer {
		
	public:
		
		FTResourceFontContainer( const FSRef& iFSRef, bool iIsDataforkSuitcase, bool iIsReadOnly );
		FTResourceFontContainer( const CFURLRef& iURL, bool iIsDataforkSuitcase, bool iIsReadOnly );
		
		FTResourceFontContainer( const FTResourceFontContainer& iOther );
		
		virtual ~FTResourceFontContainer();
		
		FTResourceFontContainer& operator=( const FTResourceFontContainer& iOther );
		
		bool					IsDataforkSuitcase() const { return _fIsDataforkSuitcase; };
		SInt64					MaximumResourceSize() const { return _fMaximumResourceSize; };
		
		virtual void			WriteData();
		virtual void			ReadData();
		
		virtual const FTFont	*GetFont( ResType iType, int16_t iID ) const;
		
		FTResourceFileRef		GetFileRef() const { ((FTResourceFontContainer*)this)->ReadData(); return _fResourceFileRef; };
		
	protected:
		
		enum {
			kTransferBufferSize	= 262144L,
		};
		
		FTResourceFontContainer();
		
		virtual void			ReadDataInternal();
		
		virtual void			AddFontsFromResources( CFMutableArrayRef iFontArray );
		virtual void			AddFontsFromResourceType( ResType iType, CFMutableArrayRef iFontArray );
		
	private:
		
		void                    ValidateResourceData() const;
		
		bool					_fDataRead;
		bool					_fIsDataforkSuitcase;
		FTResourceFileRef		_fResourceFileRef;
		SInt64					_fMaximumResourceSize;
		
		ItemCount				_fResourceCount;
		Handle					*_fResources;
		
	};
	
}

#endif /* __FTRESOURCEFONTCONTAINER__ */
