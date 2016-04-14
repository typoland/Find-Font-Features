/*
	File:		FTXMLParser.h

	Contains:	A C++ wrapper around the NSXMLParser class

	Version:	MacOS X

	Copyright:	© 2011-2015 by Apple Inc., all rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Julio Gonzalez

		Technology:			Apple Font Tools

*/

#ifndef __FTXMLPARSER__
#define __FTXMLPARSER__

#include <Carbon/Carbon.h>

#include "FTDictionary.h"
#include "FTFont_sfnt.h"
#include "FTString.h"

namespace ftx {
	
	/** The basic Font Toolbox class for parsing XML
	 *
	 *  Subclasses need to override at least InternalParserDidStartElement() and
	 *		InternalParserDidEndElement().   Overriding InternalParserDidStartDocument()
	 *		and InternalParserDidEndDocument() is usually not necessary.
	 *
	 *	The copy constructor and assignment operator are public. Subclasses may therefore
	 *		be copyable and assignable.
	 *
	 *	Other methods cannot be overriden.
	 */

	class FTXMLParser {
		
	public:
		
		enum {
			kInvalidTag = FOUR_CHAR_CODE( '\?\?\?\?' )
		};
		
		static FTXMLParser *CreateParser( FTFont_sfnt* iFont, FourCharCode iTag, bool iUseGenericFuser = false, void *ioUserData = nullptr );
		FTXMLParser(const FTFont_sfnt *iFont = nullptr, FourCharCode iTag = kInvalidTag);
		FTXMLParser( const FTXMLParser& iOther );
		virtual ~FTXMLParser();
		
		FTXMLParser& operator=( const FTXMLParser& iOther );
		
		FTDictionary ParseXML(CFStringRef iXML, void *ioUserData);
		
		// Here follows the C++ wrappers around the NSXMLParserDelegate
		//	methods
		void ParserDidStartDocument();
		void ParserDidEndDocument();
		// Only called if we succeed in parsing, so this should usually be
		//	where we save the table in the font
		
		void ParserDidStartElement( CFStringRef iElementName,
								   CFStringRef iNamespaceURI,
								   CFStringRef iQualifiedName,
								   CFDictionaryRef iAttributes );
		void ParserDidEndElement( CFStringRef elementName,
								 CFStringRef namespaceURI,
								 CFStringRef qName );
		
		void ParserFoundCharacters( CFStringRef iString );
		
		const FTFont_sfnt *GetFont() const { return _fFont; };
		void SetFont(const FTFont_sfnt* iFont) { _fFont = iFont; };
		FourCharCode GetTag() const { return _fTag; };
		void SetTag(FourCharCode iTag) { _fTag = iTag; };
		
		bool GiveGlyphNamesPrecedence() const { return _fGiveGlyphNamesPrecedence; };
		void SetGlyphNamePrecedence(bool iValue) { _fGiveGlyphNamesPrecedence = iValue; };
		
	protected:
		
		ItemCount CountFontGlyphs() const { return GetFont()->CountFontGlyphs(); };
		
		// Here follows the C++ wrappers around the NSXMLParserDelegate
		//	methods
		virtual void InternalParserDidStartDocument();
		virtual void InternalParserDidEndDocument();
		// Only called if we succeed in parsing, so this should usually be
		//	where we save the table in the font
		
		virtual void InternalParserDidStartElement( CFStringRef iElementName,
												   CFStringRef iNamespaceURI,
												   CFStringRef iQualifiedName,
												   CFDictionaryRef iAttributes );
		virtual void InternalParserDidEndElement( CFStringRef iElementName,
												 CFStringRef iNamespaceURI,
												 CFStringRef iQualifiedName );
		
		// Data fetchers
		
		// Number-ish things
		bool			BoolFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString,
										   bool iDefaultValue = false ) const;
		Fixed			FixedFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		float			FloatFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		FourCharCode	FourCharCodeFromAttributes( CFDictionaryRef iAttributes,
												   CFStringRef iString ) const;
		
		// Decimal integers; note that the unswapped ones can always be cast
		
		int32_t	IntFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int32_t	IntFromAttributesWithAlternateName( CFDictionaryRef iAttributes, CFStringRef iString, CFStringRef iAlternateName ) const;
		int32_t	SwappedInt32FromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int16_t	SwappedInt16FromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int32_t	OptionalIntFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString,
										  int32_t iDefaultValue ) const;
		int32_t	SwappedOptionalInt32FromAttributes( CFDictionaryRef iAttributes,
												   CFStringRef iString, int32_t iDefaultValue ) const;
		int16_t	SwappedOptionalInt16FromAttributes( CFDictionaryRef iAttributes,
												   CFStringRef iString, int16_t iDefaultValue ) const;
		
		// The same in hex
        UnicodeScalarValue UnicodeFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
        int32_t	HexFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int32_t	SwappedHex32FromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int16_t	SwappedHex16FromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;
		int32_t	OptionalHexFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString,
										  int32_t iDefaultValue ) const;
		int32_t	SwappedOptionalHex32FromAttributes( CFDictionaryRef iAttributes,
												   CFStringRef iString, int32_t iDefaultValue ) const;
		int16_t	SwappedOptionalHex16FromAttributes( CFDictionaryRef iAttributes,
												   CFStringRef iString, int16_t iDefaultValue  ) const;
		
		// Glyph IDs
		FTGlyphID	GlyphcodeFromAttributes( CFDictionaryRef iAttributes,
											CFStringRef iPrefix = nullptr ) const;

        /** Fetches a variation axis index from the attributes to use in connection with the 'gvar' and related tables
         *		Both the iIndexString and iTagString are treated as optional.
         *
         *		If neither is found or the result is out-of-range for our font, 0 is returned.
         *
         *		If the iIndexString present, it is used to fetch an integer value for the axis index.
         *
         *		If the iTagString is present, the 'fvar' table is checked to see if it has an
         *		axis with the given tag. The index of the first such entry is used. A warning
         *		is issued and 0 returned if there is none.
         *
         *		If both iIndexString and iTagString are used, the two results are compared
         *      and a warning issued if they differ. The value derived from the iIndexString is returned.
         *
         *		@param iAttributes the attributes dictionary to use
         *		@param iIndexString the tag for the axis index attribute -- may be nullptr
         *		@param iTagString the tag for the four-character axis tag attribute -- may be nullptr
         *		@return The appropriate variation axis, or 0 if none or the index is out-of-range
         */
        uint16_t    VariationAxisFromAttributes( CFDictionaryRef iAttributes, CFStringRef iIndexString, CFStringRef iTagString ) const;

        /** Fetches a name code from the attributes to use in connection with the 'name' table
		  *		Both the iNameCodeTag and iNameStringTag are treated as optional.
		  *
		  *		If neither is found, kFontNoName is returned.
		  *
		  *		If the iNameCodeTag present, the 'name' table is checked to see if it has an entry
		  *		with the given name code. A warning is issued and kFontNoName returned if there is none.
		  *
		  *		If the iNameStringTag is present, the 'name' table is checked to see if it has an
		  *		entry with the given string. The name code of the first such entry is used. A warning
		  *		is issued and kFontNoName returned if there is none.
		  *
		  *		If both iNameCodeTag and iNameStringTag are used, only 'name' table entries with
		  *		the given code are checked and a warning issued if there is no match. The value of
		  *		iNameCodeTag is returned if available.
		  *
		  *		@param iAttributes the attributes dictionary to use
		  *		@param iNameCodeTag the tag for the name code attribute -- do not use nullptr
		  *		@param iNameStringTag the tag for the name string -- do not use nullptr
		  *		@return The appropriate name code, or kFontNoName if none
		  *
		  */
		FontNameCode	NamecodeFromAttributes( CFDictionaryRef iAttributes,
											   CFStringRef iNameCodeTag = CFSTR("nameCode"),
											   CFStringRef iNameStringTag = CFSTR("name")) const;
		
        /** Fetches a FTShortFrac from the attributes; iString must not be nullptr and the attribute must exist
         *
         *		@param iAttributes the attributes dictionary to use
         *		@param iString the tag for the FTShortFrac attribute -- do not use nullptr
         *		@return The FTShortFrac attribute; 0 if there is an error
         *
         */
        FTShortFrac                FTShortFracFromAttributes( CFDictionaryRef iAttributes, CFStringRef iString ) const;

        // Type conversions
        static FTShortFrac         FloatToFrac(float iValue);
        static float               FracToFloat(FTShortFrac iValue);

		// Strings
		FTString	StringFromAttributes( CFDictionaryRef iAttributes, CFStringRef iLabel ) const;
		FTString	OptionalStringFromAttributes( CFDictionaryRef iAttributes, CFStringRef iLabel ) const;

		// Files
		FTData		DataFromURL( CFDictionaryRef iAttributes, CFStringRef iLabel ) const;
		
		// Our parsed data
		FTDictionary	GetParsedData() const { return _fParsedData; };
		void SetParsedData(const FTDictionary& iData) const { _fParsedData = iData; };
		void SetParsedData(const FTData& iData) const;
            // Strictly speaking, SetParsedData() should not be const (it is a setter, after all),
            //  but it's called by some const functions; making the function const and _fParsedData
            //  mutable is the simplest way of dealing with what would otherwise be a *very* complicated
            //  mess
        void StoreParsedData(FourCharCode iTag, CFDataRef iData);

		FTString AccumulatedString() const { return _fStringAccumulator; };
		
	private:
		
		void StartAccumulatingString() const;
		void StopAccumulatingString() const;
		
		const FTFont_sfnt*		_fFont;
		FourCharCode			_fTag;
		bool					_fGiveGlyphNamesPrecedence;
		mutable FTString		_fStringAccumulator;
		mutable FTDictionary	_fParsedData;
		
	};
	
}

#endif /* __FTXMLPARSER__ */
