/*
	File:			FTDatabase.h
 
	Contains:		Functions to access cached databases (glyph and Unicode names).
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		Copyright © 2009-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Peter Lofting
 
		Technology:			Apple Font Tools
 
*/

#ifndef __FTDATABASE__
#define __FTDATABASE__

#include <Carbon/Carbon.h>

#include "FTFont_sfnt.h"

/* ----------------------------------------------------------------------------------------- */
/* ALIGNMENT PRAGMA */
/* ----------------------------------------------------------------------------------------- */

namespace ftx {
	
	/* ----------------------------------------------------------------------------------------- */
	/* CONSTANTS */
	/* ----------------------------------------------------------------------------------------- */
	
	enum {
		kFTMaximumGlyphStringLength = 16
		//  Assuming one character for a glyph name and one
		//      character for the '_' separator, a compound
		//      glyph name with sixteen components will be
		//      thirty-one characters long, which is the maximum
		//      glyph length defined by Adobe
	};
	
	/* ----------------------------------------------------------------------------------------- */
	/* TYPES */
	/* ----------------------------------------------------------------------------------------- */
	
	struct FTGlyphLookupResult {
		Boolean				fWasFound;
		Boolean             fIsCompoundString;
		UnicodeScalarValue	fUnicode;
		UInt16				fProperties;
		int32_t				fVChar;
		UnicodeScalarValue	fString[ kFTMaximumGlyphStringLength ];
	};

	/* ----------------------------------------------------------------------------------------- */
	/* PROTOTYPES */
	/* ----------------------------------------------------------------------------------------- */

	class FTDatabase {
		
	public:
		
		enum EAdobeCID {
			kAdobeCNS1 = 0,
			kAdobeGB1,
			kAdobeJapan1,
			kAdobeKorean1,
			kInvalidCID
		};

		enum EROSOrder {
			kJapanOrder			= 0,
			kSimpChineseOrder	= 1,
			kTradChineseOrder	= 2,
			kKoreanOrder		= 3,
			kInvalidOrder		= 0xFFFF
		};
		

		static int					UnicodeToAdobeCID(UnicodeScalarValue iUC, EAdobeCID iAdobeCID);
		
		static uint32_t				SupportedUnicodeVersion();
		
		static void					DoNameLookup( const char *iToken, FTGlyphLookupResult *oLookupResult );
		static void					DoTruncatedNameLookup( const char *iToken, FTGlyphLookupResult *oLookupResult );
		static void					DoUnicodeLookup( UnicodeScalarValue iUnicode, FTGlyphLookupResult *oLookupResult );
		static FTString				UnicodeScalarName( UInt32 iUnicode );
		static void					GetUnicodeScalarName( UInt32 iUnicode, char *oName );
		static Boolean				StandardGlyphNameForUnicode( UnicodeScalarValue iUnicode, char *oName );
		static FTString				StandardGlyphNameStringForUnicode( UnicodeScalarValue iUnicode );
		static CFStringRef			CreateStringForGlyphName( char *iGlyphName );
		static FTString				StringForGlyphName( char *iGlyphName );
		static UnicodeScalarValue	UnicodeForGlyphName( char *iGlyphName );
		static uint16_t				GetUnicodeGeneralCategory( UnicodeScalarValue iUnicode );

		static uint16_t             GetUnicodeDirectionality( UnicodeScalarValue iUnicode );
        static bool                 IsDefinedCharacter( UnicodeScalarValue iUnicode );
        static bool                 IsPrintableCharacter( UnicodeScalarValue iUnicode );

		static bool					GetUnicodeMirrors( UnicodeScalarValue iUnicode );
		static UnicodeScalarValue	GetUnicodeMirrorCharacter( UnicodeScalarValue iUnicode );

		// Unicode block support
		// Block IDs are arbitrary and not guaranteed to be consistent across
		//	Unicode releases (or even FontToolbox.framework builds)
		//	-1 is used for an invalid ID
		static int16_t				GetUnicodeBlockIDFromName( const char *iBlockName );
		static const char*			GetUnicodeBlockName( int16_t iBlockID );
		static ItemCount			GetUnicodeBlockCount();
		static void					GetUnicodeBlockRange( int16_t iBlockID, UnicodeScalarValue& oBlockStart, UnicodeScalarValue& oBlockEnd );
		static int16_t				GetUnicodeBlockOfCharacter( UnicodeScalarValue iUnicode );
		static bool					UnicodeBlockContainsCharacter( int16_t iBlockID, UnicodeScalarValue iUnicode );
		
		// Unicode script support
		// Script IDs are arbitrary and not guaranteed to be consistent across
		//	Unicode releases (or even FontToolbox.framework builds)
		//	-1 is used for an invalid ID
		static int16_t				GetUnicodeScriptIDFromName( const char *iScriptName );
		static const char*			GetUnicodeScriptName( int16_t iScriptID );
		static ItemCount			GetUnicodeScriptCount();
		static int16_t				GetUnicodeScriptOfCharacter( UnicodeScalarValue iUnicode );
		static bool					UnicodeScriptContainsCharacter( int16_t iScriptID, UnicodeScalarValue iUnicode );
		
		static CFDictionaryRef		DecompositionForCharacter( UnicodeScalarValue iUnicode );
		
	private:

		static bool CaselessStringEqual( const char *iString1, const char *iString2 );
		static void DoUnicodeLookup( const char	*iUnicode4, FTGlyphLookupResult *oLookupResult );
		static void LoadDatabase();
		static void LoadUnicodeDatabases();
		static void ParseBlockNameText( const void *iValue, void *iContext );
		static uint16_t PropUCharDirectionToDirectionality( uint16_t iUCharDirection );
		static size_t UTF32StringLength( const UnicodeScalarValue *iString );
		
	};
		
}

#endif /* __FTDATABASE__ */
