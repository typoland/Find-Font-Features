/*
	File:			FTFontContainer.h
 
	Contains:		C++ base class for TrueType fonts
 
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

#ifndef __FTFONTCONTAINER__
#define __FTFONTCONTAINER__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTURL.h"

namespace ftx {
	
	class FTFont;
	class FTURL;
	
	class FTFontContainer {
		
	public:
		
		enum {
			kReadOnly = true,
			kReadWrite = false,
			
			kResourceType_sfnt	= FOUR_CHAR_CODE( 'sfnt' ),
			kResourceType_FOND	= FOUR_CHAR_CODE( 'FOND' ),
			kResourceType_NFNT	= FOUR_CHAR_CODE( 'NFNT' ),
			kResourceType_POST	= FOUR_CHAR_CODE( 'POST' ),
		};
		
		enum {
			kOriginalTTScaler	= fixed1,
			kTTFScaler			= FOUR_CHAR_CODE( 'true' ),
			kOTFScaler			= FOUR_CHAR_CODE( 'OTTO' ),
			kType1Scaler		= FOUR_CHAR_CODE( 'typ1' ),
			kTTCScaler			= FOUR_CHAR_CODE( 'ttcf' ),
			kPFBScaler			= 0x8001U,
		};
		
		static FTFontContainer *FontContainerFromFSRef( const FSRef& iFSRef, bool iIsReadOnly );
		static FTFontContainer *FontContainerFromCFURLRef( const CFURLRef& iURL, bool iIsReadOnly );
		static FTFontContainer *FontContainerFromURL( const FTURL& iURL, bool iIsReadOnly );
		static bool CreateMinimalFontContainer(const FTURL& iURL, const FTString& iFontName, size_t iGlyphCount);
		
		FTFontContainer();
		FTFontContainer( bool iIsReadOnly );
		
		FTFontContainer( const FTFontContainer& iOther );
		
		virtual ~FTFontContainer();
		
		FTFontContainer& operator=( const FTFontContainer& iOther );
		
		virtual CFStringRef				GetName() const = 0;
		virtual CFURLRef				GetURL() const = 0;
		FTURL							URL() const { return FTURL(GetURL()); };
		virtual ItemCount				GetFontCount() const;
		virtual FTFont					*GetIndFont( ItemCount iFont ) const;
		
		virtual bool					IsReadOnly() const { return _fIsReadOnly; };
		virtual bool					IsDirty() const;
		virtual void					MakeClean();
		virtual void					WriteData() = 0;
		
		virtual void					ReadData() = 0;
		
	protected:
		
		static bool						HasFontsInResourceFork( const FSRef& iFSRef, bool& oIsDataFork, bool& oIsType1Data );
		static bool						HasFontsInDataFork( const FSRef& iFSRef );
		static bool						HasFontsInResourceFork( CFURLRef iURL, bool& oIsDataFork, bool& oIsType1Data );
		static bool						HasFontsInDataFork( CFURLRef iURL );
		virtual CFArrayRef				Fonts() const;
		
		enum {
			kKeyboardScaler		= FOUR_CHAR_CODE( '\xa5kbd' ),
			kLastResortScaler	= FOUR_CHAR_CODE( '\xa5lst' ),
		};
		
		virtual void		SetFonts( CFArrayRef iFonts );
		
	private:
        
        static void         Initialize();
		
		void				DeleteData();
		void				CopyData( const FTFontContainer& iOther );
		
		enum {
			kDefaultIsReadOnly = kReadOnly
		};
		
		bool				_fIsReadOnly;
		CFArrayRef			_fFonts;
		
	};
	
}

#endif /* __FTFONTCONTAINER__ */
