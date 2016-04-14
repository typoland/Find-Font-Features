/*
	File:		FTString.h

	Contains:	A wrapper class for CFString

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTSTRING__
#define __FTSTRING__

#include <iostream>
#include <vector>

using namespace std;

#include "FTCoreFoundationType.h"
#include "FTReporter.h"
#include "FTTypes.h"

#define FTSTR(a)    (*FTString::Retain(CFSTR(a)))

namespace ftx {
	
	class FTArray;
	class FTData;
	class FTNumber;
	class FTOutputStream;

	/**
     * \ingroup Wrapper Classes
     * @{
     */
    
	/*! \brief Wrapper for CoreFoundation CFStringRef
	 *
	 *  FTString is a C++ wrapper around CFStringRef
	 *      (and therefore NSString, as well). It simplifies
	 *      creation of formatted strings, comparison,
	 *      searching, concatenation, and so on.
	 *
	 *  Note that the constructors using other string
	 *      objects (const char * and CFStringRef) all
	 *      variadic. This can entail some unwanted
	 *      overhead for string constants.
	 *
	 *  Clients who wish to create FTStrings from string
	 *      constants should therefore use the
	 *      static Adopt(), Retain(), or Copy() functions,
	 *      e.g., FTString::Retain(CFSTR("FooBarBaz")).
	 *
	 *  Note that FTStrings are inherently mutable.
	 */

	class FTString : public FTCoreFoundationType {

	public:

		enum ENormalizationType {
			kNFD = kCFStringNormalizationFormD,		// 0
			kNFKD = kCFStringNormalizationFormKD,	// 1
			kNFC = kCFStringNormalizationFormC,		// 2
			kNFKC = kCFStringNormalizationFormKC,	// 3
			kInvalidNormalizationType
		};
		
		enum ECaseSensitivity {
			kCaseSensitive = 0,
			kCaseInsensitive = 1,
			
			kInvalidFourCharCode = FOUR_CHAR_CODE('\?\?\?\?')
		};

        /** @name Static Functions
         *  FTString static functions
         */
        ///@{
        static FTString *Adopt(CFStringRef iValue);
        static FTString *Retain(CFStringRef iValue);
        static FTString *Copy(CFStringRef iValue);
        ///@}

		static FTString StringFromFourCharCode( FourCharCode iFourCharCode );
		static FTString StringFromFixed( FTFixed iFixed );
		static CFStringRef CreateStringFromUnicodeScalarValue( UnicodeScalarValue iUC );
		static ECaseSensitivity DefaultCaseSensitivity() { return _fgDefaultCaseSensitivity; };
		static void SetDefaultCaseSensitivity(ECaseSensitivity iValue) { _fgDefaultCaseSensitivity = iValue; };
		
        /** @name Constructors
         *  FTString constructors; note the presence of the move constructor
         */
        ///@{
        FTString();
		FTString( const ostringstream& iStream );
		FTString( CFStringRef iString, ... );
		FTString( CFStringRef iString, va_list iArguments );
		FTString( const char *iString, ... );
		FTString( const char *iString, va_list iList );
		FTString( UnicodeScalarValue iUnicode );
		FTString( const FTData& iData, bool iIsExternalRepresentation = false );
		FTString(const FTArray& iComponents, CFStringRef iJoiner );
		FTString( const FTString& iOther );
		FTString( FTString&& iOther ) noexcept;
        FTString(EMemoryControlType iControlType, CFStringRef iString);
        ///@}
        
        /** @name Destructor
         *  FTString destructor
         */
		///@{
		virtual ~FTString();
		 ///@}

        /** @name operator=
         *  Copy operators; note the presence of the move operator
         */
        ///@{
		FTString& operator=( const FTString& iOther );
		FTString& operator=( FTString&& iOther );
		FTString& operator=( const ostringstream& iStream );
		FTString& operator=( CFStringRef iOther );
		FTString& operator=( const char *iOther );
		FTString& operator=( UnicodeScalarValue iUnicode );
		///@}

        /** @name Comparison operators
         *  FTString comparison operators. EqualsWithOptions() is the only one
         *      which offers full control over the comparison options and the
         *      only way to do, for example, a diacritic-insensitive comparison.
		 *
         *  The other comparison operators can only be either case-sensitive or
         *      not. This is determined by the value of CaseSensitivity(), which
         *      is equal to the value of FTString::DefaultCaseSensitivity()
         *      at the time of the string's creation.  (This is bad design, yes.)
         */
        ///@{
		bool operator==( const FTString& iOther ) const;
		bool operator!=( const FTString& iOther ) const;
		bool operator==( CFStringRef iOther ) const { return operator==(*FTString::Retain(iOther)); };
		bool operator!=( CFStringRef iOther ) const { return operator!=(*FTString::Retain(iOther)); };
		bool operator==( const char *iOther ) const { FTString tScratch; tScratch = iOther; return operator==(tScratch); };
		bool operator!=( const char *iOther ) const { FTString tScratch; tScratch = iOther; return operator!=(tScratch); };
		
		bool EqualsWithOptions(const FTString& iOther, CFStringCompareFlags iOptions = 0) const;
		
		bool operator<(const FTString& iOther) const;
		bool operator<=(const FTString& iOther) const { return operator<(iOther) || operator==(iOther); };
		bool operator>(const FTString& iOther) const { return iOther.operator<(*this); };
		bool operator>=(const FTString& iOther) const { return iOther.operator<=(*this); };
		
		ECaseSensitivity	CaseSensitivity() const { return _fCaseSensitivity; };
		void SetCaseSensitivity(ECaseSensitivity iValue) { _fCaseSensitivity = iValue; };
        ///@}

        /** @name Concatenation
         *  FTString concatenation functions
		 *
		 *  AppendString() is equivalent to operator+=()
         */
        ///@{
		void PrependString( CFStringRef iString );
		void AppendString( CFStringRef iString );
		FTString& operator+=( const FTString& iOther );
		FTString operator+( const FTString& iOther );
        ///@}

		void Normalize(ENormalizationType iType);
		
		FTNumber		DecimalValue() const;
		FTNumber		HexValue() const;
		FTFixed			FixedValue() const;
		double			DoubleValue() const { return ::CFStringGetDoubleValue(_fString); };
		FourCharCode	FourCharCodeValue() const;
		FTData			DataFromText() const;
		FTData			DataFromHex() const;
		
		operator CFStringRef() const { return _fString; };
		virtual CFTypeRef Cast() const { return _fString; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFStringCreateCopy( kCFAllocatorDefault, _fString ); };
		bool CopyToCString(char *oString, size_t iBufferSize=PATH_MAX) const;
		FTData CopyToData() const;
		FTArray SplitToArray(const FTString& iSplitString) const;
		
		void FindAndReplace(const FTString& iStringToReplace, const FTString& iReplacementString, bool iCaseSensitive = kCaseSensitive);
		CFRange Find(const FTString& iStringToFind, bool iCaseSensitive = kCaseSensitive) const;
		bool StartsWithSubstring(const FTString& iStringToFind, bool iCaseSensitive = kCaseSensitive) const;
		bool ContainsSubstring(const FTString& iStringToFind, bool iCaseSensitive = kCaseSensitive) const;
		bool EndsWithSubstring(const FTString& iStringToFind, bool iCaseSensitive = kCaseSensitive) const;
		FTString CopySubstring(CFRange iSubstringRange) const;
		void DeleteSubstring(CFRange iSubstringRange);
		void DeleteSubstring(const FTString& iSubstring, bool iCaseSensitive = kCaseSensitive);
		void RetainSubstring(CFRange iSubstringRange);
		void RetainSubstring(const FTString& iSubstring, bool iCaseSensitive = kCaseSensitive);
		
		void TrimWhitespace();
		void TrimQuotes();
		
		static void TurnXMLSafeOutputOn();
		static void TurnXMLSafeOutputOff();
		static bool XMLSafeOutputIsOn();

		void MakeFullyXMLSafe();
			// Replaces the five standard entities
			// Replaces anything that doesn't really work in plain text (e.g., combining diacritics) with numerical entities
        void MakeFullyXMLUnsafe();

		bool Transform(CFStringRef iTransform, bool iReverse = false);

		void MakeXMLSafe() { FindAndReplace(FTString("&"), FTString("&amp;")); FindAndReplace(FTString("<"), FTString("&lt;")); FindAndReplace(FTString(">"), FTString("&gt;")); };
		void MakeXMLUnsafe() { FindAndReplace(FTString("&gt;"), FTString(">")); FindAndReplace(FTString("&lt;"), FTString("<")); FindAndReplace(FTString("&amp;"), FTString("&")); };
		void MakeQuotesXMLSafe() { FindAndReplace(FTString("\""), FTString("&quot;")); };
		void MakeQuotesXMLUnsafe() { FindAndReplace(FTString("&quot;"), FTString("\"")); };
		void EscapeQuotes() { FindAndReplace(FTString("\""), FTString("\\\"")); };
		void UnescapeQuotes() { FindAndReplace(FTString("\\\""), FTString("\"")); };

		ItemCount Length() const { ConvertToUTF32(); return _fUTF32.size(); };
		UnicodeScalarValue operator[]( ItemCount iIndex ) const { return CharacterAt(iIndex); };
		UnicodeScalarValue CharacterAt( ItemCount iIndex ) const;
		
		void OutputToStream(FTOutputStream *iStream) const;
		friend ostream& operator<<( ostream& iOut, const FTString &iString );
		
	private:
		
		static ECaseSensitivity _fgDefaultCaseSensitivity;
		
		void ConvertToUTF32() const;
		void ClearUTF32() const;
		CFRange StringRange() const { return ::CFRangeMake(0,::CFStringGetLength(_fString)); }
		CFRange ValidateRange(CFRange iRange) const;
		void _OutputToStream(FTOutputStream *iStream) const;
		
		CFStringRef _fString;
		ECaseSensitivity _fCaseSensitivity;
        mutable bool _fUTF32Generated;
        mutable vector<UnicodeScalarValue> _fUTF32;

        static CFStringRef EmptyString();
        static CFStringRef fgEmptyString;
		
	};
    /**@}*/

}

#endif /* __FTSTRING__ */
