/*
	File:			FTBitmap.cp

	Contains:		C++ class for embedded bitmaps

	Version:		Mac OS X

	Written by:		The Apple Font Group

	Copyright:		© 2009-2015 by Apple Inc. All rights reserved.

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

#ifndef __FTBITMAP__
#define __FTBITMAP__

#ifdef __cplusplus
#include <vector>
#endif

using namespace std;

#include "FTFont_sfnt.h"
#include "FTFontTable_bdat.h"
#include "FTFontTable_bloc.h"
#include "FTString.h"

namespace ftx {
	
	class FTBitmap
	{
	public:
		
		enum {
			kNoBitmaps = 0,
			kAATBitmapType = 1,
			kOpenTypeBitmapType = 2,
			kOpenTypeColorBitmapType = 3,
			
			kUsesSmallMetrics = true,
			kUsesBigMetrics = false
		};
		
		enum EAlignment {
			kBitAligned = 0,
			kByteAligned = 1,
			kCompressed = 2,
		};
		
		FTBitmap( const FTGlyphID iGlyphcode, const BDATBigMetrics& iMetrics, ByteCount iRawBitDataLength, const uint8_t* iRawBitData, EAlignment iAlignment = kByteAligned, bool iUsesSmallMetrics = kUsesBigMetrics );
		FTBitmap( const FTGlyphID iGlyphcode, const BDATBigMetrics& iMetrics, CFDataRef iBitmapData, EAlignment iAlignment );
		FTBitmap( const FTGlyphID iGlyphcode, const BDATSmallMetrics& iMetrics, CFDataRef iBitmapData, EAlignment iAlignment );
		FTBitmap( const FTBitmap& iOther );
		virtual ~FTBitmap();
		
		FTBitmap& operator=( const FTBitmap& iOther );
		virtual bool operator==( const FTBitmap& iOther ) const { return !( operator!=( iOther ) ); };
		virtual bool operator!=( const FTBitmap& iOther ) const;

		bool ImageEqual(const FTBitmap& iOther) const;
		
		const FTGlyphID				GetGlyphcode() const { return _fGlyphcode; };
		operator FTGlyphID() { return _fGlyphcode; };
		
		const void					GetMetrics( BDATBigMetrics& oMetrics ) const { oMetrics = _fMetrics; };
		BDATBigMetrics				GetMetrics() const { return _fMetrics; };
		bool						UsesSmallMetrics() const { return _fUsesSmallMetrics; };
		
		const uint8_t*				GetRawBitData() const { return ::CFDataGetBytePtr( _fBits ); };
		ByteCount					GetRawBitDataLength() const { return ::CFDataGetLength( _fBits ); };
		
		virtual ByteCount			GetBytesNeededCount() const;
		// The ideal number of bytes to hold the bitmap
		//	data, given our alignment and metrics; may
		//	be smaller or bigger than the actual
		//	number of bytes we have.  If it's bigger,
		//	that's bad
		
		virtual ByteCount			GetBytesUsedCount() const;
		// The min of GetRawBitDataLength() and
		//	GetBytesNeededCount()
		
		virtual bool				GetBit( CFIndex iRow, CFIndex iColumn ) const;
		// True iff this bit is in range
		//	of the bytes used and set

		FTString					BitString() const;
		
		EAlignment					GetAlignment() const { return _fAlignment; };
		
		bool						IsEmpty() const;
		bool						CanUseSmallMetrics() const;
		
	private:
		
		FTBitmap();
		static const uint8_t *CreateSanitizedBits( const BDATBigMetrics& iMetrics, ByteCount iRawBitDataLength, const uint8_t* iRawBitData );
		
		FTGlyphID		_fGlyphcode;
		BDATBigMetrics	_fMetrics;
		bool			_fUsesSmallMetrics;
		EAlignment		_fAlignment;
		CFDataRef		_fBits;
		
	};
	
	typedef list<FTBitmap> FTBitmapList;
	
	class FTBitmapRange
	{
		
	public:
		
		FTBitmapRange();
		FTBitmapRange( const FTBitmapRange& iOther );
		FTBitmapRange( const FTBitmapRange& iOther, list<FTBitmap> iGlyphs );
		
		virtual ~FTBitmapRange();
		
		FTBitmapRange& operator=( const FTBitmapRange& iOther );
		
		FTBitmapList& Glyphs() { return _fGlyphs; };
		
		void						AddBitmap( const FTBitmap& iBitmap );
		
		FTBitmap::EAlignment		GetAlignment() { ReadData(); return _fAlignment; };
		FTGlyphID					GetFirstGlyphID() { ReadData(); return _fFirstGlyphID; };
		FTGlyphID					GetLastGlyphID() { ReadData(); return _fLastGlyphID; };
		ItemCount					GlyphCount() { ReadData(); return _fGlyphCount; };
		ByteCount					IndexSubtableSize() { ReadData(); return _fIndexSubtableSize; };
		BDATImageFormat				ImageFormat() { ReadData(); return _fImageFormat; };
		BLOCIndexFormat				IndexFormat() { ReadData(); return _fIndexFormat; };
		bool						IsMonospaced() { ReadData(); return _fIsMonospaced; };
		
	private:
		
		void						ReadData();
		
		list<FTBitmap>				_fGlyphs;
		bool						_fDataRead;
		FTBitmap::EAlignment		_fAlignment;
		FTGlyphID					_fFirstGlyphID;
		FTGlyphID					_fLastGlyphID;
		ItemCount					_fGlyphCount;
		ByteCount					_fIndexSubtableSize;
		BDATImageFormat				_fImageFormat;
		BLOCIndexFormat				_fIndexFormat;
		bool						_fIsMonospaced;
		
	};
	
	
	typedef list<FTBitmapRange> FTBitmapRangeList;
	
	
	class FTBitmapStrike
	{
		
	public:
		
		FTBitmapStrike( const FTBitmapStrikeData& iData );
		FTBitmapStrike( const FTBitmapStrike& iOther );
		
		virtual ~FTBitmapStrike();
		
		FTBitmapStrike& operator=( const FTBitmapStrike& iOther );
		
		FTBitmapRangeList&		Ranges() { return _fRanges; };
		
		void					AddBitmap( const FTBitmap& iBitmap );
		
		CFMutableDataRef		Accumulator() const { return _fAccumulator; };
		ByteCount				GetSwappedPerSizeTable( ItemCount iOffset, BLOCPerSizeTable& oPerSizeTable );
		
		FTBitmapLineMetrics		HorizontalMetrics() const { return _fStrikeData.fHorizontalLineMetrics; };
		void					SetHorizontalMetrics( const FTBitmapLineMetrics& iMetrics ) { _fStrikeData.fHorizontalLineMetrics = iMetrics; };
		FTBitmapLineMetrics		VerticalMetrics() const { return _fStrikeData.fVerticalLineMetrics; };
		void					SetVerticalMetrics( const FTBitmapLineMetrics& iMetrics ) { _fStrikeData.fVerticalLineMetrics = iMetrics; };
		uint8_t					HorizontalPixelsPerEm() const { return _fStrikeData.fHorizontalPixelsPerEm; };
		void					SetHorizontalPixelsPerEm( uint8_t iPixelsPerEm ) { _fStrikeData.fHorizontalPixelsPerEm = iPixelsPerEm; };
		uint8_t					VerticalPixelsPerEm() const { return _fStrikeData.fVerticalPixelsPerEm; };
		void					SetVerticalPixelsPerEm( uint8_t iPixelsPerEm ) { _fStrikeData.fVerticalPixelsPerEm = iPixelsPerEm; };
		uint8_t					Flags() const { return _fStrikeData.fFlags; };
		void					SetFlags( uint8_t iFlags ) { _fStrikeData.fFlags = iFlags; };
		ByteCount				IndexSubtableSize();
		
	private:
		
		FTGlyphID				StartGlyphID();
		FTGlyphID				EndGlyphID();
		
		list<FTBitmapRange>		_fRanges;
		FTBitmapStrikeData		_fStrikeData;
		CFMutableDataRef		_fAccumulator;
		
	};
	
#ifdef __cplusplus
	typedef vector<FTBitmapStrike> FTBitmapStrikeArray;
#else 
	typedef FTBitmapStrike *FTBitmapStrikeArray;
#endif
	
}

#endif /* __FTBITMAP__ */
