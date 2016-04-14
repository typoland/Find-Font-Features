/*
	File:			FTFontTable_Zapf.h
 
	Contains:		C++ class individual TrueType font 'Zapf' tables
 
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

#ifndef __FTFONTTABLE_ZAPF__
#define __FTFONTTABLE_ZAPF__

#include <Carbon/Carbon.h>
#include "FTFontTable.h"
#include "FTTypes.h"

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
	
	typedef uint16_t	ZAPFGroupFlags;
	
	struct ZAPFNamedGroup
	{
		uint16_t	fNameIndex;
		uint16_t	fNumGlyphs;
		uint16_t	fGlyphs[];
	};
	
#ifndef __cplusplus
	typedef struct ZAPFNamedGroup ZAPFNamedGroup;
#endif
	
	typedef ZAPFNamedGroup *ZAPFNamedGroupPtr;
	
	struct ZAPFGroupInfoGroup
	{
		uint16_t			fNumGroups;
		uint16_t			fPadding;
		uint32_t			fOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct ZAPFGroupInfoGroup ZAPFGroupInfoGroup;
#endif
	
	typedef ZAPFGroupInfoGroup *ZAPFGroupInfoGroupPtr;
	
	struct ZAPFFlaggedGroup
	{
		ZAPFGroupFlags	fFlags;
		ZAPFNamedGroup	fGroup;
	};
	
#ifndef __cplusplus
	typedef struct ZAPFFlaggedGroup ZAPFFlaggedGroup;
#endif
	
	typedef ZAPFFlaggedGroup *ZAPFFlaggedGroupPtr;
	
	struct ZAPFGroupOffsetInfo
	{
		uint16_t				fNumGroups;
		uint16_t				fPadding;
		uint32_t				fOffsets[];
	};
	
	
#ifndef __cplusplus
	typedef struct ZAPFGroupOffsetInfo ZAPFGroupOffsetInfo;
#endif
	
	typedef ZAPFGroupOffsetInfo *ZAPFGroupOffsetInfoPtr;
	
	struct ZAPFGroupInfo
	{
		uint16_t				fNumGroups;
		union ZAPFGroupUnion {
			ZAPFFlaggedGroup	fFlaggedGroup;
			ZAPFNamedGroup		fNamedGroup;
		}				fGroup;
	};
	
#ifndef __cplusplus
	typedef struct ZAPFGroupInfo ZAPFGroupInfo;
#endif
	
	typedef ZAPFGroupInfo *ZAPFGroupInfoPtr;
	
	struct ZAPFFeatureInfo
	{
		uint16_t				fContext;
		uint16_t				fNumAATFeatures;
		sfntFontRunFeature		fFeatures[];
		/*	uint16_t				fNumOTTags;	*/
		/*	FourCharCode			fOTTags[];	*/
	};
	
#ifndef __cplusplus
	typedef struct ZAPFFeatureInfo ZAPFFeatureInfo;
#endif
	
	struct ZAPFKindName
	{
		uint8_t	fNameType;
		uint8_t	fData[];
	};
	
#ifndef __cplusplus
	typedef struct ZAPFKindName ZAPFKindName;
#endif
	
	typedef ZAPFKindName *ZAPFKindNamePtr;
	
	struct ZAPFGlyphInfo
	{
		uint32_t			fGroupOffset;
		uint32_t			fFeatOffset;
		uint16_t			fNum16BitUnicodes;
		uint16_t			fUnicodes[];
		/*	uint16_t			fNumNames;		*/
		/*	ZAPFKindName		fKindNames[];	*/
		/*	uint8_t				fPadding[];		*/
	};
	
#ifndef __cplusplus
	typedef struct ZAPFGlyphInfo ZAPFGlyphInfo;
#endif
	
	typedef ZAPFGlyphInfo *ZAPFGlyphInfoPtr;
	typedef ZAPFGlyphInfo **ZAPFGlyphInfoHandle;
	
	/* For convenience, we also define the last part of the ZAPFGlyphInfo separately */
	
	struct ZAPFGlyphInfoKindNames
	{
		uint16_t			fNumNames;
		ZAPFKindName		fKindNames[];
		/*	uint8_t				fPadding[];		*/
	};
	
#ifndef __cplusplus
	typedef struct ZAPFGlyphInfoKindNames ZAPFGlyphInfoKindNames;
#endif
	
	struct ZAPFTable
	{
		Fixed			fVersion;
		uint32_t		fExtraInfo;
		uint32_t		fOffsets[];
		/*	ZAPFGlyphInfo	fGlyphInfo[]; */
	};
	
#ifndef __cplusplus
	typedef struct ZAPFTable ZAPFTable;
#endif
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTGlyphGroup;
	class FTKindName;
	class FTFeatureInfo;
	class FTNamedGroup;
	
	typedef void *FTVoidPtr;
	
	class FTFontTable_Zapf : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'Zapf' ),
			
			kInitialVersion = fixed1,
			kCurrentVersion = kInitialVersion,
			
			kNoGroupOffset				= 0xFFFFFFFFU,
			kNoFeatOffset				= 0xFFFFFFFFU,
			
			/* Values used for the flags "kind name" */
			kIsCanonicalGlyph			= 0x8000U,
			
			/* Values used for flags for ZAPFGroupInfo.fNumGroups */
			
			kGroupsHaveFlagsBit			= 0x8000U,
			kGroupsAreOffsetsBit		= 0x4000U,
			kGroupCountMask				= 0x3FFFU,
			
			/* Values used for flags for ZAPFFlaggedGroup.fFlags */
			
			kIsOffsetBit				= 0x8000U,
			kIsSubdivisionBit			= 0x4000U,
			
			/* Values for the ZAPFFeatureInfo.fContext		*/
			
			kNoContext					= 0x0000U,
			kLineIitialBit				= 0x0001U,
			kLineMedialBit				= 0x0002U,
			kLineFinalBit				= 0x0004U,
			kWordIitialBit				= 0x0008U,
			kWordMedialBit				= 0x0010U,
			kWordFinalBit				= 0x0020U,
			kAutoFractionNumeratorBit	= 0x0040U,
			kAutoFractionDenominatorBit	= 0x0080U,
			
			/* Values for the ZAPFKindName.fNameType 		*/
			/*	 These values are used for Pascal string data */
			
			kUniversalName				= 0,
			kAppleName					= 1,
			kAdobeName					= 2,
			kAFIIName					= 3,
			kUnicodeName				= 4,
			
			kLastPascalStringNameType	= 63,
			
			/* 	These values are used for two-byte integer data */
			
			kJapaneseCID				= 64,
			kTradChineseCID				= 65,
			kSimpChineseCID				= 66,
			kKoreanCID					= 67,
			
			/* 	These values are used for indices in the 'name' table */
			
			kVersionHistory				= 68,
			kDesignerShortName			= 69,
			kDesignerLongName			= 70,
			kDesignerUsageNotes			= 71,
			kDesignerHistoricalNotes	= 72,
			
			/*	This value gets around the lack of a flags field	*/
			/*	in the ZAPFGlyphInfo structure						*/
			kFlagsKindName				= 127,
			
			kLastValidKindNameType		= kFlagsKindName,
			kInvalidKindNameType		= kLastValidKindNameType+1,

			kLineInitialContext				= 0,
			kLineMedialContext				= 1,
			kLineFinalContext				= 2,
			kWordInitialContext				= 3,
			kWordMedialContext				= 4,
			kWordFinalContext				= 5,
			kAutoFractionNumeratorContext	= 6,
			kAutoFractionDenominatorContext	= 7,
			kInvalidFeatureInfoContext		= kAutoFractionDenominatorContext+1,
			
		};
		
		FTFontTable_Zapf( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_Zapf( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_Zapf( const FTFontTable& iOther );
		virtual ~FTFontTable_Zapf();
		
		FTFontTable_Zapf& operator=( const FTFontTable_Zapf& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		Fixed			GetVersion() const { ReadData(); return _fVersion; };
		uint32_t		GetExtraInfo() const { ReadData(); return _fExtraInfo; };
		bool			GetGlyphInfo( ItemCount iGlyphIndex, ZAPFGlyphInfo &oGlyphInfo, ZAPFGlyphInfoKindNames &oGlyphNames ) const;
		UnicodeScalarValue		GetSingleUnicode( ItemCount iGlyphIndex ) const;
		// If the glyph represents exactly one Unicode character, return it
		// Otherwise, return kUnicodeNotAChar
		
		// The Unicode string this character represents; may be empty or nullptr
		FTString				GlyphString(ItemCount iGlyphIndex) const;
		CFStringRef				CreateGlyphString( ItemCount iGlyphIndex ) const;

		ItemCount				GetGlyphKindNameCount( ItemCount iGlyphIndex ) const;
		const FTKindName*		CreateGlyphKindName( ItemCount iGlyphIndex, ItemCount iKindNameIndex ) const;
		bool					IsTwoByteKindName( ItemCount iGlyphIndex, ItemCount iKindNameIndex ) const;
		uint16_t				TwoByteKindNameValue( ItemCount iGlyphIndex, ItemCount iKindNameIndex ) const;
		bool					IsPascalStringKindName( ItemCount iGlyphIndex , ItemCount iKindNameIndex) const;
		CFStringRef				CreatePascalStringKindName( ItemCount iGlyphIndex, ItemCount iKindNameIndex ) const;
		uint16_t				GlyphFlags( ItemCount iGlyphIndex ) const;
		
		ItemCount				GetFeatureInfoCount() const { ReadData(); return _fFeatureInfoCount; };
		const FTFeatureInfo*	GetIndFeatureInfo( ItemCount iFeatureInfoIndex ) const;
		const FTFeatureInfo*	GetFeatureInfoForGlyph( FTGlyphID iGlyph ) const;
		uint32_t				GetFeatureInfoIndexForGlyph( ItemCount iGlyphIndex ) const;
		
		ItemCount				GetGroupCount() const  { ReadData(); return _fGroupCount; };
		ItemCount				GetNamedGroupForGroupCount( ItemCount iGroupIndex ) const;
		FTNamedGroup*			CreateIndNamedGroupForGroup( ItemCount iGroupIndex, ItemCount iNamedGroupIndex ) const;
		bool					NamedGroupForGroupIsAlternatesGroup( ItemCount iGroupIndex, ItemCount iNamedGroupIndex ) const;
		
		ItemCount				GroupCountForGlyph( FTGlyphID iGlyphIndex ) const;
		const ItemCount			*CreateGroupInfoIndicesForGlyph( FTGlyphID iGlyphIndex ) const;
		const FTGlyphGroup&		CreateIndGroupForGlyph( FTGlyphID iGlyphIndex, size_t iGroupIndex ) const;
		
		static FTDictionary CreateFromXML(FTFont_sfnt *iFont, const FTString& iXML, void *ioUserData );
		
		virtual FTString		TableSchema() const;
		virtual	FTString		ConvertToXML(const FTXMLOptions& iOptions,
											 const FTGlyphID *iGlyphReordering) const;

		virtual	FTString ConvertToTrimmedXML(const FTXMLOptions& iOptions,
											 const FTArray& iGlyphsToRetain) const;

	protected:

		FTFontTable_Zapf();

		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:

		FTString			GlyphInfoXMLString(bool iIncludeGlyphNames) const;
		FTString			SingleGlyphInfoXMLString(FTGlyphID iSourceGID, FTGlyphID iTargetGlyphID, bool iIncludeGlyphNames) const;
		FTString			GroupInfoXMLString(bool iIncludeGlyphNames, bool iIncludeNameTableEntries, const FTArray* iGlyphsToRetain = nullptr) const;
		FTString			FeatureInfoXMLString(bool iIncludeGlyphNames, const FTArray* iGlyphsToRetain = nullptr) const;

		CFIndex				FlagNameIndex( ItemCount iGlyphIndex ) const;
		uint32_t			GroupOffsetToIndex( ByteCount iOffset ) const;
		
		Fixed				_fVersion;
		uint32_t			_fExtraInfo;
		
		ItemCount			_fFeatureInfoCount;
		ByteCount			*_fFeatureInfoOffsets;
		FTVoidPtr			*_fFeatureInfo;
		
		// These are offsets to GroupInfo structures only
		ItemCount			_fGroupCount;
		ByteCount			*_fGroupOffsets;
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_ZAPF__ */
