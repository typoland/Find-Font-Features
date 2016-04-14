/*
	File:			FTTrueTypeGlyph.h
 
	Contains:		C++ class for individual 'glyf' table entries
 
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

#ifndef __FTTRUETYPEGLYPH__
#define __FTTRUETYPEGLYPH__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTDictionary.h"
#include "FTFont_sfnt.h"
#include "FTFontTable_glyf.h"

namespace ftx {
	
	class FTFont_sfnt;
	class FTTrueTypeGlyphComponent;
	
	/*! \brief Base class for all TrueType glyphs
	 *
	 *  FTTrueTypeGlyph is a base class for all 
	 *		TrueType glyphs. It has two subclasses:
	 *		FTSimpleTrueTypeGlyph and FTCompoundTrueTypeGlyph.
	 *
	 *	The type for a specific FTTrueTypeGlyph instance
	 *		can be determined either by calling one
	 *		of the Is*Glyph() functions or by using
	 *		a dynamic cast. Empty TrueType glyphs (that
	 *		is, glyphs with no outline data) will
	 *		return true to IsEmptyGlyph() and cannot
	 *		be dynamically cast to any other glyph class.
	 */

	class FTTrueTypeGlyph {
		
	public:
		
		enum {
			kArgs1And2AreWordsFlag	= 0x0001,
			kArgsAreXYValuesFlag	= 0x0002,
			kRoundXYToGridFlag		= 0x0004,
			kWeHaveAScaleFlag		= 0x0008,
			kObsoleteFlag			= 0x0010,
			kMoreComponentsFlag		= 0x0020,
			kWeHaveXAndYScaleFlag	= 0x0040,
			kWeHaveTwoByTwoFlag		= 0x0080,
			kWeHaveHintsFlag		= 0x0100,
			kUseMyMetricsFlag		= 0x0200,
			kOverlapCompoundFlag	= 0x0400,
			
			kOnCurveFlag			= 0x01,
			kXShortFlag				= 0x02,
			kYShortFlag				= 0x04,
			kRepeatFlag				= 0x08,
			kThisXSameFlag			= 0x10,
			kThisYSameFlag			= 0x20,
			
			kMaximumValidGlyphNameLength = 31,
		};
		
		static const FTTrueTypeGlyph *CreateGlyph( const uint8_t *iData,
												  ByteCount iLength,
												  const FTFontTable_glyf *iTable,
                                                  FTGlyphID iGlyphID = FTFont_sfnt::kInvalidGlyphID );
		
		FTTrueTypeGlyph( const uint8_t *iData, ByteCount iLength, const FTFontTable_glyf *iTable );
		FTTrueTypeGlyph( const FTTrueTypeGlyph& iOther );
		
		virtual ~FTTrueTypeGlyph();
		
		FTTrueTypeGlyph& operator=( const FTTrueTypeGlyph& iOther );
		
		virtual bool operator!=( const FTTrueTypeGlyph& iOther ) const;
		virtual bool operator==( const FTTrueTypeGlyph& iOther ) const;
		
		virtual const uint8_t *GetUnswappedData() const { return _fUnswappedData; };
		virtual ByteCount GetUnswappedDataLength() const { return _fUnswappedDataLength; };

		FTData	CopyGlyphData() const { return FTData(_fUnswappedData, _fUnswappedDataLength); };
		
		virtual bool		IsCompoundGlyph() const { return false; };
		virtual bool		IsSimpleGlyph() const { return false; };
		virtual bool		IsEmptyGlyph() const { return true; };
		
		virtual Rect GetBounds() const { ReadData(); return _fBounds; };
		
		ItemCount CountParts( ItemCount *oNumPoints, ItemCount* oNumContours ) const;
		// returns the glyph's depth (level of recursion)
		
		virtual bool IsDirty() const { return _fIsDirty; };
		virtual void Clean() { _fIsDirty = false; };
		virtual void Dirty() { _fIsDirty = true; };
		
		FTGlyphID GlyphID() const { return _fGlyphID; };
		void SetGlyphID(FTGlyphID iValue) { _fGlyphID = iValue; };
		
		virtual const FTFontTable_glyf *GetTable() const { return _fTable_glyf; };
		const FTFont_sfnt *				GetFont() const { return _fTable_glyf->GetFont(); };

		FTString						GenerateXML(const FTArray* iGlyphsToRetain = nullptr) const;

	protected:
		virtual void					CountPartsInternal( ItemCount *oNumPoints,
														   ItemCount* oNumContours,
														   ItemCount iCurrentDepth,
														   ItemCount *oMaxDepth ) const;
		
		virtual uint16_t				RawComponentCount() const { ReadData(); return _fRawComponentCount; };
		
		virtual bool					ReadingData() const { return _fReadingData; };
		virtual void					MarkReadingData() { _fReadingData = true; };
		virtual bool					DataRead() const { return _fDataRead; };
		virtual void					MarkDataRead() { _fDataRead = true; _fReadingData = false; };
		
		virtual void					ReadData() const;
		virtual void					ReadDataInternal() const;
		virtual void					WriteData();
		
		FTDictionary					UnicodeDecomposition() const;

		virtual FTString				GenerateXMLInternal(FTGlyphID iGlyphID, const FTArray* iGlyphsToRetain) const { return FTString(); };
		
		FTTrueTypeGlyph();
		
	private:
		
		const FTFontTable_glyf *_fTable_glyf;
		
		const uint8_t			*_fUnswappedData;
		ByteCount				_fUnswappedDataLength;
		
		uint16_t				_fRawComponentCount;
		
		Rect					_fBounds;
		
		bool					_fDataRead;
		bool					_fReadingData;
		
		FTGlyphID				_fGlyphID;
		
		bool					_fIsDirty;
	};
	
}

#endif /* __FTTRUETYPEGLYPH__ */
