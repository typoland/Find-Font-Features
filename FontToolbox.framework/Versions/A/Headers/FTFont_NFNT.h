/*
	File:			FTFont_NFNT.h
 
	Contains:		C++ class for 'NFNT' resources
 
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

#ifndef __FTFONT_NFNT__
#define __FTFONT_NFNT__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont_resource.h"

namespace ftx {

	struct FTFontRec {
	  int16_t              fontType;               /*font type*/
	  int16_t              firstChar;              /*ASCII code of first character*/
	  int16_t              lastChar;               /*ASCII code of last character*/
	  int16_t              widMax;                 /*maximum character width*/
	  int16_t              kernMax;                /*negative of maximum character kern*/
	  int16_t              nDescent;               /*negative of descent*/
	  int16_t              fRectWidth;             /*width of font rectangle*/
	  int16_t              fRectHeight;            /*height of font rectangle*/
	  int16_t              owTLoc;                 /*offset to offset/width table*/
	  int16_t              ascent;                 /*ascent*/
	  int16_t              descent;                /*descent*/
	  int16_t              leading;                /*leading*/
	  int16_t              rowWords;               /*row width of bit image / 2 */
	};

	
	class FTFontContainer;
	class FTString;
	
	class FTFont_NFNT : public FTFont_resource {
		
	public:
		
		FTFont_NFNT( FTFontContainer *iContainer, Handle iNFNTResource );
		FTFont_NFNT( FTFontContainer *iContainer,
					const uint8_t *iData, ByteCount iLength,
					int16_t iResourceID, const unsigned char *iResourceName );
		FTFont_NFNT( const FTFont_NFNT& iOther );
		virtual ~FTFont_NFNT();
		
		FTFont_NFNT& operator=( const FTFont_NFNT& iOther );
		
		// Returns a constant indicating what kind of font this is
		virtual FTFont::EFontType		GetType() const { return FTFont::kNFNTFontType; };

		uint16_t	GetStyle() const { ReadData(); return _fStyle; };
		uint16_t	GetPointSize() const { ReadData(); return _fPointSize; };

		FTString GenerateXML() const;
		
	protected:
		
		FTFont_NFNT();
		
		virtual void ReadDataInternal();
		
	private:

		uint16_t	_fStyle;
		uint16_t	_fPointSize;

	};
	
}

#endif /* __FTFONT_NFNT__ */
