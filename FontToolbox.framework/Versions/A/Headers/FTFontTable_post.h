/*
	File:			FTFontTable_post.h
 
	Contains:		C++ class individual TrueType font 'post' tables
 
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

#ifndef __FTFONTTABLE_POST__
#define __FTFONTTABLE_POST__

#include <Carbon/Carbon.h>

#include "FTArray.h"
#include "FTData.h"
#include "FTDictionary.h"
#include "FTFontTable.h"

/* ----------------------------------------------------------------------------------------- */

/* ALIGNMENT PRAGMA */

#pragma pack(push,2)

/* ----------------------------------------------------------------------------------------- */

/* NAMESPACE */

namespace ftx {
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* CONSTANTS */
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* TYPES */
	
	struct PostTable
	{
		Fixed		fFormat;
		Fixed		fItalicAngle;
		int16_t		fUnderlinePosition;
		uint16_t	fUnderlineThickness;
		uint32_t	fIsFixedPitch;
		uint32_t	fMinMemType42;
		uint32_t	fMaxMemType42;
		uint32_t	fMinMemType1;
		uint32_t	fMaxMemType1;
		int32_t		fFormatSpecificStart;
	};
	
	typedef PostTable POSTTable;
	typedef PostTable **PostTableHandle;
	typedef const PostTable **ConstPostTableHandle;
	
	struct Post2Subtable
	{
		uint16_t	fNumGlyphs;
		uint16_t	fGlyphNameIndex[];
		/*	array of Pascal strings follows here */
	};
	
	struct Post25Subtable
	{
		uint16_t	fNumGlyphs;
		int8_t		fDelta[];
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_post : public FTFontTable {
		
	public:
		
		static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML );
		static FTData CreateDummyTable();

		static CFStringRef	CreateStringWithStandard258IndexName( ItemCount iIndex );
		static const char*	Standard258IndexName( ItemCount iIndex ) { return fgStandard258Names[iIndex]; };
		static FTData		CreateNameDataForNames( const FTFont_sfnt* iFont, const FTArray& iGlyphNames, Fixed& oFormat );
		static FTData		GenerateTableFromNameList(const FTFont_sfnt* iFont,
													  Fixed iItalicAngle,
													  int16_t iUnderlinePosition,
													  uint16_t iUnderlineThickness,
													  uint32_t iIsFixedPitch,
													  uint32_t iMinMemType42,
													  uint32_t iMaxMemType42,
													  uint32_t iMinMemType1,
													  uint32_t iMaxMemType1,
													  const FTArray &iNames);

		enum {
			kTag = FOUR_CHAR_CODE( 'post' ),
			
			kFormat10		= 0x00010000L,
			kFormat20		= 0x00020000L,
			kFormat25		= 0x00028000L,
			kFormat30		= 0x00030000L,
			kFormat40		= 0x00040000L,
			
			kHeaderSize		= sizeof( PostTable ) - sizeof( int32_t ),
			
			kStd258Count	= 258
		};
		
		FTFontTable_post( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_post( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_post( const FTFontTable& iOther );
		virtual ~FTFontTable_post();
		
		FTFontTable_post& operator=( const FTFontTable_post& iOther );
		
		virtual bool operator==( const FTFontTable_post& iOther ) const;
		virtual bool operator!=( const FTFontTable_post& iOther ) const;
		
		virtual FourCharCode	GetTag() const { return kTag; };
		
		virtual Fixed			GetFormat() const;
		virtual Fixed			GetItalicAngle() const;
		virtual int16_t			GetUnderlinePosition() const;
		virtual uint16_t		GetUnderlineThickness() const;
		virtual uint32_t		GetIsFixedPitch() const;
		virtual uint32_t		GetMinMemType42() const;
		virtual uint32_t		GetMaxMemType42() const;
		virtual uint32_t		GetMinMemType1() const;
		virtual uint32_t		GetMaxMemType1() const;
		
		virtual ItemCount		CountFontGlyphs() const;
		virtual CFStringRef		CreateGlyphName( CFIndex iIndex ) const;
		FTString				GlyphName(CFIndex iIndex) const { return FTString(FTCoreFoundationType::kAdoptObject, CreateGlyphName(iIndex)); };
		virtual void			GetGlyphName( ItemCount iIndex, char *oName ) const;
		virtual bool			HasGlyphNames() const { return GetFormat() != kFormat30; };
        FTDictionary            GlyphNameDictionary() const;
		
		virtual FTString		TableSchema() const;
        virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
                                             const FTGlyphID *iGlyphReordering) const;
		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;
		virtual bool CanGenerateTrimmedData() const { return true; };
		virtual FTDictionary GenerateTrimmedData(const FTFont_sfnt& iTargetFont, const FTArray& iGlyphsToRetain, bool iRemoveGlyphs) const;

	protected:
		
		FTFontTable_post();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;

		virtual bool		NotEqualsInternal(const FTFontTable *iOther) const;

	private:
		
		static const char *fgStandard258Names[];
		
		void		DeleteData();
		
		void		GetName20( const Post2Subtable *iSubtable, ItemCount iIndex, char *oName ) const;
		void		GetName25( const Post25Subtable *iSubtable, ItemCount iIndex, char *oName ) const;
		void		GetName40( ItemCount iIndex, char *oName ) const;
		
		static bool FitsFormat1( const FTFont_sfnt* iFont, CFArrayRef iGlyphNames );
		static bool FitsFormat4( const FTFont_sfnt* iFont, CFArrayRef iGlyphNames );
		static void GenerateFormat2Names( const FTFont_sfnt* iFont, CFArrayRef iGlyphNames, CFMutableDataRef iAccumulator );
		static void GenerateFormat4Names( const FTFont_sfnt* iFont, CFArrayRef iGlyphNames, CFMutableDataRef iAccumulator );
		
		Fixed           _fFormat;
		Fixed           _fItalicAngle;
		int16_t         _fUnderlinePosition;
		uint16_t        _fUnderlineThickness;
		uint32_t        _fIsFixedPitch;
		uint32_t        _fMinMemType42;
		uint32_t        _fMaxMemType42;
		uint32_t        _fMinMemType1;
		uint32_t        _fMaxMemType1;
		
		ItemCount       _fGlyphCount;
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_POST__ */
