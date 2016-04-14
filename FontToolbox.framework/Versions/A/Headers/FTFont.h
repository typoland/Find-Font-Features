/*
	File:			FTFont.h
 
	Contains:		C++ class individual TrueType fonts
 
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

#ifndef __FTFONT__
#define __FTFONT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFontContainer.h"

namespace ftx {
	
	class FTFont {
		
	public:
		
		enum EFontType {
			kUnspecifiedFontType,
			kFONDFontType,
			kNFNTFontType,
			kTrueTypeFontType,
			kPostScriptFontType,
			kSplicedFontType,
			kType1FontType,
			kPOSTFontType			// Strictly speaking, is only a font piece, not a font
		};
		
		static	const FTFont *FTFontFromResourceHandle( FTFontContainer *iContainer, Handle iResource );
		static	const FTFont *FTFontFromResource( FTFontContainer *iContainer, ResType iType, const uint8_t *iResource, ByteCount iResourceLength, int16_t iResourceID, Str255 iResourceName );
		
		FTFont( FTFontContainer *iContainer, CFDataRef iData );
		FTFont( FTFontContainer *iContainer, const FSRef& iData );
		FTFont( FTFontContainer *iContainer, const uint8_t *iData, ByteCount iLength );
		FTFont( FTFontContainer *iContainer, Handle iData );
		FTFont( const FTFont& iOther );
		
		virtual ~FTFont();
		
		FTFont& operator=( const FTFont& );
		
		// Routines to track whether or not changed data in the font has been saved
		virtual bool					IsDirty() const { return _fIsDirty; };
		virtual void					MakeDirty();
		virtual void					MakeClean() { _fIsDirty = false; };
		
		//	Determines whether or not this font object is even parsable as
		//		an actual font
		virtual void					TestBasicUsability() const;
		
		// Returns a string which (hopefully) is a unique way of specifying a
		//		certain version of the font.  It is currently a concatination
		//		of the font's checkum (in hex) with its unique name for sfnt fonts
		//		and resource type, resource number, resource name for rescource
		//		fonts
		virtual CFStringRef				GetIdentifier() const { return nullptr; };
		
		// Returns the most useful name for the font as a string
		virtual CFStringRef				GetName() const { return GetContainer()->GetName(); };
		
		// Returns the PostScript name for the font as a string
		virtual CFStringRef				GetPostScriptName() const { return nullptr; };
		
		// Returns a constant indicating what kind of font this is
		virtual EFontType				GetType() const { return kUnspecifiedFontType; };
		
		//	Getters
		virtual FTFontContainer*        GetContainer() const { return _fContainer; };
		virtual void					SetContainer( FTFontContainer *iContainer ) { _fContainer = iContainer; };
		virtual CFURLRef				GetURL() const;
		
		virtual const uint8_t			*GetUnswappedDataPtr() const;
		virtual ByteCount				GetUnswappedDataLength() const;
		virtual bool					IsReadOnly() const { return _fContainer->IsReadOnly(); };
		
		virtual void					PrintDiagnostics() const;
		
	protected:
		
		FTFont();
		
		ByteCount						GetRawUnswappedDataLength() const { return _fUnswappedDataLength; };
		virtual void					SetData( CFDataRef iData );
		
	private:
		
		void		CopyUnswappedData( const FTFont& iOther );
		void		DeleteData();
		
		FTFontContainer*        _fContainer;
		
		mutable CFURLRef		_fURL;
		mutable bool			_fURLSet;
		
		CFDataRef				_fUnswappedData;
		const uint8_t			*_fUnswappedDataPtr;
		ByteCount				_fUnswappedDataLength;
		bool					_fDataIsMappedFile;
		
		bool					_fIsDirty;
		
	};
	
}

#endif /* __FTFONT__ */
