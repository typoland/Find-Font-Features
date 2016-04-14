//
//  FTUniChar.h
//  ftxanalyzer
//
//  Created by 井作恆 on 1/3/13.
//
//

#ifndef __ftxanalyzer__FTUniChar__
#define __ftxanalyzer__FTUniChar__

#include <iostream>

using namespace std;

#include "FTDictionary.h"
#include "FTNumber.h"

namespace ftx {
	
	class FTString;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for individual Unicode characters
	 *
	 *  FTUniChar is a wrapper class encapsulating an 
	 *		individual Unicode character together with
	 *		its properties. It mainly exists to avoid
	 *		having to make calls down into ICU.
	 */

	class FTUniChar {
		
	public:
		
		enum {
			
			kGeneralOtherTypes			= ('C' << 8) + 'n',
			kUppercaseLetter			= ('L' << 8) + 'u',
			kLowercaseLetter			= ('L' << 8) + 'l',
			kTitlecaseLetter			= ('L' << 8) + 't',
			kModifierLetter				= ('L' << 8) + 'm',
			kOtherLetter				= ('L' << 8) + 'o',
			kNonSpacingMark				= ('M' << 8) + 'n',
			kEnclosingMark				= ('M' << 8) + 'e',
			kCombiningSpacingMark		= ('M' << 8) + 'c',
			kDecimalDigitNumber			= ('N' << 8) + 'd',
			kLetterNumber				= ('N' << 8) + 'l',
			kOtherNumber				= ('N' << 8) + 'o',
			kSpaceSeparator				= ('Z' << 8) + 's',
			kLineSeparator				= ('Z' << 8) + 'l',
			kParagraphSeparator			= ('Z' << 8) + 'p',
			kControlChar				= ('C' << 8) + 'c',
			kFormatChar					= ('C' << 8) + 'f',
			kPrivateUseChar				= ('C' << 8) + 'o',
			kSurrogate					= ('C' << 8) + 's',
			kDashPunctuation			= ('P' << 8) + 'd',
			kStartPunctuation			= ('P' << 8) + 's',
			kEndPunctuation				= ('P' << 8) + 'e',
			kConnectorPunctuation		= ('P' << 8) + 'c',
			kOtherPunctuation			= ('P' << 8) + 'o',
			kMathSymbol					= ('S' << 8) + 'm',
			kCurrencySymbol				= ('S' << 8) + 'c',
			kModifierSymbol				= ('S' << 8) + 'k',
			kOtherSymbol				= ('S' << 8) + 'o',
			kInitialPunctuation			= ('P' << 8) + 'i',
			kFinalPunctuation			= ('P' << 8) + 'f',

			kTab								= 0x0009U,
			
			kCJKExtensionAStart					= 0x03400U,
			kCJKExtensionAStop					= 0x04DB5U,
			kCJKIdeographStart					= 0x04E00U,
			kCJKIdeographStop					= 0x09FCBU,
			kHighSurrogateStart					= 0x0D800U,
			kHighSurrogateStop					= 0x0DBFFU,
			kLowSurrogateStart					= 0x0DC00U,
			kLowSurrogateStop					= 0x0DFFFU,
			kUserZoneStart						= 0x0E000U,
			kUserZoneStop						= 0x0F8FFU,
			kCJKCompatibilityIdeographStart 	= 0x0F900U,
			kCJKCompatibilityIdeographStop		= 0x0FAD9U,
			kHangulStart						= 0x0AC00U,
			kHangulStop 						= 0x0D7A3U,
			kByteOrderMark						= 0x0FFFEU,
			
			kPlane01Start						= 0x00010000U,
			kCJKExtensionBStart					= 0x00020000U,
			kCJKExtensionBStop					= 0x0002A6D6U,
			kCJKExtensionCStart					= 0x0002A700U,
			kCJKExtensionCStop					= 0x0002B734U,
			kCJKExtensionDStart					= 0x0002B740U,
			kCJKExtensionDStop					= 0x0002B81DU,
			kCJKCompatibilityExtensionStart		= 0x0002F800U,
			kCJKCompatibilityExtensionStop		= 0x0002FA1DU,
			kUserPlaneStart						= 0x000F0000U,
			kUnassignableStart					= 0x00110000U,
			
			kNotAChar							= 0x7FFFFFFFU
		};

        static FTUniChar UniCharFromUnicodeID(const FTString& iUnicodeID);
		
		FTUniChar();
		FTUniChar(const FTUniChar& iOther);
		FTUniChar(UnicodeScalarValue iUC);
		FTUniChar(const FTNumber& iUC);
		FTUniChar(const FTString& iGlyphName);
		
		virtual ~FTUniChar();
		
		FTUniChar& operator=(const FTUniChar& iOther);
		operator UnicodeScalarValue() const { return _fUniChar; };
		
		uint16_t Plane() const { return _fUniChar >> 16; };
		
		bool operator!=(const FTUniChar& iOther) const { return _fUniChar != iOther._fUniChar; };
		bool operator==(const FTUniChar& iOther) const { return _fUniChar == iOther._fUniChar; };
		bool operator<(const FTUniChar& iOther) const { return _fUniChar < iOther._fUniChar; };
		bool operator<=(const FTUniChar& iOther) const { return _fUniChar <= iOther._fUniChar; };
		bool operator>(const FTUniChar& iOther) const { return _fUniChar > iOther._fUniChar; };
		bool operator>=(const FTUniChar& iOther) const { return _fUniChar >= iOther._fUniChar; };
		
		FTUniChar operator+(const FTUniChar& iOther) const { return FTUniChar(_fUniChar + iOther._fUniChar); };
		FTUniChar operator-(const FTUniChar& iOther) const { return FTUniChar(_fUniChar - iOther._fUniChar); };
		FTUniChar& operator+=(const FTUniChar& iOther) { _fUniChar += iOther._fUniChar; return *this; };
		FTUniChar& operator-=(const FTUniChar& iOther) { _fUniChar -= iOther._fUniChar; return *this; };
		
		FTString CharacterName() const;
		FTString StandardGlyphName() const;
		uint16_t GeneralCategory() const;
		uint16_t Directionality() const;
		
		bool Mirrors() const;
		FTUniChar MirrorChar() const;
		
		int16_t UnicodeBlock() const;
		bool ContainedByBlock( int16_t iBlockID ) const;
		int16_t	UnicodeScript() const;
		bool ContainedByScript( int16_t iScriptID ) const;
			
		bool IsHan() const;
        bool IsDefined() const;
        bool IsPrintable() const;

		FTDictionary Decomposition() const;

		bool IsValid() const { return _fUniChar != kUnicodeNotAChar && _fUniChar != kNotAChar; };
		
		FTString Identifier() const;
		friend ostream& operator<<( ostream &iOut, const FTUniChar& iObject );
		
	protected:
		
	private:
		UnicodeScalarValue _fUniChar;
		
	};
	
}

#endif /* defined(__ftxanalyzer__FTUniChar__) */
