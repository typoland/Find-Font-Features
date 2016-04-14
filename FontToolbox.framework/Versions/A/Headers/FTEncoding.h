/*
	File:			FTEncoding.h
 
	Contains:		C++ class for a TrueType font's encoding
 
	Version:			Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		© 2006-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:					John Jenkins
 
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

#ifndef __FTENCODING__
#define __FTENCODING__

#include <Carbon/Carbon.h>
#include <list>

#include "FTFont_sfnt.h"
#include "FTTypes.h"

namespace ftx {
	
	struct FTCharacterGlyphMap {
		UnicodeScalarValue	fCharacter;
		FTGlyphID			fGlyph;
	};
	
	struct Format2CodeInfo {
		ByteCount	fExtraOffset;
		FTGlyphID	fGlyphs[ 256 ];
		uint16_t		fIDDelta;
		uint16_t		fUseReference;
	};
	
	struct Format2Analysis {
		Format2CodeInfo	fCodeInfo[ 256 ];
		ItemCount		fOrderVectorCount;
		uint16_t			fHighestFirstByte;
		uint16_t			fOrderIndices[ 256 ];
		bool				fHasFirstByte[ 256 ];
		uint8_t			fStartSecondByte[ 256 ];
		uint8_t			fEndSecondByte[ 256 ];
	};
	
	class FTMappingSegment;
	class FTString;
	
	class FTEncoding {
		
	public:
		
		enum {
			
			kSmallestFormat =	 -2,
			kNoFormat =          -1,
			
			kFormat0Short =		 0,
			kFormat2Short =		 2,
			kFormat4Short =		 4,
			kFormat6Short =		 6,
			kFormat8Short =		 8,
			kFormat10Short =		10,
			kFormat12Short =		12,
			kFormat13Short =		13,
			kFormat14Short =		14,
			
			kFormat0Fixed = 	 0 * fixed1,
			kFormat2Fixed = 	 2 * fixed1,
			kFormat4Fixed = 	 4 * fixed1,
			kFormat6Fixed = 	 6 * fixed1,
			kFormat8Fixed = 	 8 * fixed1,
			kFormat10Fixed =	10 * fixed1,
			kFormat12Fixed =	12 * fixed1,
			kFormat13Fixed =	13 * fixed1,
			kFormat14Fixed =	14 * fixed1,
			
			kNoUseReferece = 0xFFFFU
		};

        static FTEncoding *CreateEncoding(CFDataRef iEncodingData);
		
		FTEncoding( const uint8_t *iData, CFIndex iLength, FontPlatformCode iPlatform, FontScriptCode iScript );
		FTEncoding( const FTCharacterGlyphMap *iCharacterGlyphMap,
				   ItemCount iCharacterGlyphCount,
				   FontPlatformCode iPlatform,
				   FontScriptCode iScript,
				   FontLanguageCode iLanguage,
				   int16_t iPreferredFormat = kNoFormat );
		FTEncoding( CFDataRef iStreamedData );
		FTEncoding( const FTEncoding& iOther );
		
		virtual ~FTEncoding();
		
		FTEncoding& operator=( const FTEncoding& iOther );
		
		virtual bool operator==( const FTEncoding& iOther ) const;
		virtual bool operator!=( const FTEncoding& iOther ) const;
		
		virtual CFDataRef CreateStreamedData() const;
		// This creates a single data ref with all the data of the encoding
		virtual CFDataRef GenerateSmallestUnswappedSubtableData() const;
		// This creates a single data ref with just the 'cmap' subtable data of the encoding,
		//	suitable for adding to the 'cmap'
		virtual CFDataRef GenerateUnswappedDataInFormat0() const;
		virtual CFDataRef GenerateUnswappedDataInFormat2() const;
		virtual CFDataRef GenerateUnswappedDataInFormat4(bool iReportOutOfRangeCharacters = true) const;
		virtual CFDataRef GenerateUnswappedDataInFormat6() const;
		virtual CFDataRef GenerateUnswappedDataInFormat8() const;
		virtual CFDataRef GenerateUnswappedDataInFormat10() const;
		virtual CFDataRef GenerateUnswappedDataInFormat12() const;
		virtual CFDataRef GenerateUnswappedDataInFormat13() const;
		
		virtual const FTCharacterGlyphMap *GetMapping() const { ((FTEncoding*)this)->GenerateMappingFromUnswappedMappingData(); return _fCharGlyphMapping; };
		virtual FTCharacterGlyphMap *CreateMappingCopy() const;
		virtual ItemCount GetMappingCount() const { ((FTEncoding*)this)->GenerateMappingFromUnswappedMappingData(); return _fMappingCount; };
		virtual const uint8_t *GetUnswappedMappingDataPtr() const { ((FTEncoding*)this)->GenerateUnswappedMappingDataFromMapping(); return _fUnswappedMappingDataPtr; };
		virtual ByteCount GetUnswappedMappingDataLength() const { ((FTEncoding*)this)->GenerateUnswappedMappingDataFromMapping(); return _fUnswappedMappingDataLength; };
		
		virtual Fixed				GetLongFormat() const { return _fFormat; };
		virtual uint16_t			GetShortFormat() const { return ( _fFormat >> 16 ); };
		virtual FontPlatformCode	GetPlatform() const { return _fPlatform; };
		virtual FontScriptCode		GetScript() const { return _fScript; };
		virtual FontLanguageCode	GetLanguage() const { return _fLanguage; };
		FTString					GetSortKey() const;
		
		virtual bool				MapsCharacter( UnicodeScalarValue iCharacter ) const;
		virtual FTGlyphID			CharacterToGlyph( UnicodeScalarValue iCharacter ) const;
		virtual bool				MapsGlyph( int32_t iGlyph ) const;
		virtual UnicodeScalarValue	GlyphToCharacter( int32_t iGlyph ) const;
		
		//	Is this particular encoding raw Unicode?
		virtual bool				IsUnicodeEncoding() const;
		
		//	Can this encoding be converted to Unicode?
		virtual bool				IsUnicodableEncoding() const;
		
		//	The encoding as a CFCharacterSetRef
		virtual CFCharacterSetRef	GetCharacterSet() const;
		
	protected:
		virtual bool IsVariationMapping() const { return false; };
        FTEncoding();

	private:
		
		void	GenerateMappingFromUnswappedMappingData();
		void	GenerateUnswappedMappingDataFromMapping();
		
		// Table readers
		
		bool FillCGFormat0( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat2( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat4( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat6( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat8( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat10( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat12( CFMutableDataRef& oDataRef ) const;
		bool FillCGFormat13( CFMutableDataRef& oDataRef ) const;
		
		bool FillFormat2Analysis( ItemCount& oNumSubheaders, Format2Analysis& oAnalysis ) const;
		std::list<FTMappingSegment> MakeSegmentsFromList() const;
		void DisposeSegmentList( CFDataRef iList ) const;
		bool IsValidFormat8Data( ItemCount iCGCount, FTCharacterGlyphMap iCharGlyph[], uint32_t oFourByteFlags[] ) const;
		bool CanReuseIndex( const Format2Analysis& iAnalysis, ItemCount iIndex, ItemCount& oOtherIndex, uint16_t& oIDDelta ) const;
		
		CFDataRef			_fUnswappedData;
		const uint8_t		*_fUnswappedMappingDataPtr;
		ByteCount			_fUnswappedMappingDataLength;
		bool				_fOwnsUnswappedData;
		
		CFCharacterSetRef	_fCharacterSet;
		FTCharacterGlyphMap	*_fCharGlyphMapping;
		FTCharacterGlyphMap	*_fGlyphCharMapping;
		ItemCount			_fMappingCount;
		Fixed				_fFormat;
		FontPlatformCode	_fPlatform;
		FontScriptCode		_fScript;
		FontLanguageCode	_fLanguage;
		
	};
	
	typedef FTEncoding *FTEncodingPtr;
	
	
	class FTVariationMapping : public FTEncoding
	{

    public:
        FTVariationMapping( const FTData &iData, FontPlatformCode iPlatform, FontScriptCode iScript, FontLanguageCode iLanguage );
        FTVariationMapping( const FTVariationMapping& iOther );

        virtual ~FTVariationMapping();

        FTVariationMapping& operator=( const FTVariationMapping& iOther );

        virtual bool operator==( const FTVariationMapping& iOther ) const;
        virtual bool operator!=( const FTVariationMapping& iOther ) const;

        virtual CFDataRef CreateStreamedData() const;
        // This creates a single data ref with all the data of the encoding
        virtual CFDataRef GenerateSmallestUnswappedSubtableData() const { return (CFDataRef) _fData.Copy(); };
        // This creates a single data ref with just the 'cmap' subtable data of the encoding,
        //	suitable for adding to the 'cmap'
        virtual CFDataRef GenerateUnswappedDataInFormat0() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat2() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat4(bool iReportOutOfRangeCharacters = true) const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat6() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat8() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat10() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat12() const { return nullptr; };
        virtual CFDataRef GenerateUnswappedDataInFormat13() const { return nullptr; };
        
        virtual Fixed				GetLongFormat() const { return FTEncoding::kFormat14Fixed; };
        virtual uint16_t			GetShortFormat() const { return FTEncoding::kFormat14Short; };
        virtual FontPlatformCode	GetPlatform() const { return _fPlatform; };
        virtual FontScriptCode		GetScript() const { return _fScript; };
        virtual FontLanguageCode	GetLanguage() const { return _fLanguage; };

        virtual const FTCharacterGlyphMap *GetMapping() const { return nullptr; };
        virtual FTCharacterGlyphMap *CreateMappingCopy() const { return nullptr; };
        virtual ItemCount GetMappingCount() const { return 0; };
        virtual const uint8_t *GetUnswappedMappingDataPtr() const { return nullptr; };
        virtual ByteCount GetUnswappedMappingDataLength() const { return 0; };
        
        virtual bool				MapsCharacter( UnicodeScalarValue ) const { return false; };
        virtual FTGlyphID			CharacterToGlyph( UnicodeScalarValue ) const { return -1; };
        virtual bool				MapsGlyph( int32_t ) const { return false; };
        virtual UnicodeScalarValue	GlyphToCharacter( int32_t ) const { return kUnicodeNotAChar; };

        //	Is this particular encoding raw Unicode?
        virtual bool				IsUnicodeEncoding() const { return false; };

        //	Can this encoding be converted to Unicode?
        virtual bool				IsUnicodableEncoding() const { return false; };

        //	The encoding as a CFCharacterSetRef
        virtual CFCharacterSetRef	GetCharacterSet() const { return nullptr; };
        
	protected:
		virtual bool IsVariationMapping() const { return true; };

    private:
        FTData              _fData;
        FontPlatformCode    _fPlatform;
        FontScriptCode      _fScript;
        FontLanguageCode    _fLanguage;
		
	};
	
}

#endif /* __FTENCODING__ */
