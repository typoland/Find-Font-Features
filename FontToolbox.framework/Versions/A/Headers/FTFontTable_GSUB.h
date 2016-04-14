/*
	File:			FTFontTable_GSUB.h
 
	Contains:		C++ class individual TrueType font 'GSUB' tables
 
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

#ifndef __FTFONTTABLE_GSUB__
#define __FTFONTTABLE_GSUB__

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
	
	typedef uint16_t GSUBOffset;
	
	/* The SubstLookupRecord */
	
	struct SubstLookupRecord {
		uint16_t	sequenceIndex;
		uint16_t	lookupListIndex;
	};
	
#ifndef __cplusplus
	typedef struct SubstLookupRecord SubstLookupRecord;
#endif
	
	/* The SequenceTable */
	
	struct SequenceTable {
		uint16_t			glyphCount;
		FTFontTableGlyphID	substitute[];
	};
	
#ifndef __cplusplus
	typedef struct SequenceTable SequenceTable;
#endif
	
	/* The AlternateSetTable */
	
	struct AlternateSetTable {
		uint16_t			glyphCount;
		FTFontTableGlyphID	alternate[];
	};
	
#ifndef __cplusplus
	typedef struct AlternateSetTable AlternateSetTable;
#endif
	
	/* The GSUBRangeRecord */
	
	struct GSUBRangeRecord {
		FTFontTableGlyphID	start;
		FTFontTableGlyphID	end;
		uint16_t			startCoverageIndex;
	};
	
#ifndef __cplusplus
	typedef struct GSUBRangeRecord GSUBRangeRecord;
#endif
	
	/* The CoverageFormat1 */
	
	struct CoverageFormat1 {
		uint16_t coverageFormat;
		uint16_t glyphCount;
		FTFontTableGlyphID glyphArray[];
	};
	
#ifndef __cplusplus
	typedef struct CoverageFormat1 CoverageFormat1;
#endif
	
	/* The CoverageFormat2 */
	
	struct CoverageFormat2 {
		uint16_t coverageFormat;
		uint16_t rangeCount;
		GSUBRangeRecord ranges[];
	};
	
#ifndef __cplusplus
	typedef struct CoverageFormat2 CoverageFormat2;
#endif
	
	/* The ClassRangeRecord */
	
	struct ClassRangeRecord {
		FTFontTableGlyphID	start;
		FTFontTableGlyphID	end;
		uint16_t			classValue;
	};
	
#ifndef __cplusplus
	typedef struct ClassRangeRecord ClassRangeRecord;
#endif
	
	
	/* The ClassDefFormat1 */
	
	struct ClassDefFormat1 {
		uint16_t			classFormat;
		FTFontTableGlyphID	startGlyph;
		uint16_t			glyphCount;
		uint16_t			classValueArray[];
	};
	
#ifndef __cplusplus
	typedef struct ClassDefFormat1 ClassDefFormat1;
#endif
	
	/* The ClassDefFormat2 */
	
	struct ClassDefFormat2 {
		uint16_t			classFormat;
		uint16_t			classRangeCount;
		ClassRangeRecord	classRangeRecords[];
	};
	
#ifndef __cplusplus
	typedef struct ClassDefFormat2 ClassDefFormat2;
#endif
	
	
	/* The GSUBHeader */
	
	struct GSUBHeader {
		Fixed version;
		GSUBOffset scriptListOffset;
		GSUBOffset featureListOffset;
		GSUBOffset lookupListOffset;
	};
	
#ifndef __cplusplus
	typedef struct GSUBHeader GSUBHeader;
#endif
	
	/* The ScriptRecord */
	
	struct ScriptRecord {
		FourCharCode tag;
		GSUBOffset	scriptOffset;
	};
	
#ifndef __cplusplus
	typedef struct ScriptRecord ScriptRecord;
#endif
	
	/* The ScriptListTable. */
	
	struct ScriptListTable {
		uint16_t	scriptCount;
		ScriptRecord scripts[];
	};
	
#ifndef __cplusplus
	typedef struct ScriptListTable ScriptListTable;
#endif
	
	/* The LangSysRecord. */
	
	struct LangSysRecord {
		FourCharCode	tag;
		GSUBOffset	langSys; 	/*	From beginning of script table */
	};
	
#ifndef __cplusplus
	typedef struct LangSysRecord LangSysRecord;
#endif
	
	/* The LangSysTable */
	
	struct LangSysTable {
		GSUBOffset	lookupOrder; 		/*	Should be 0 for now */
		uint16_t	reqFeatureIndex; 	/*	Index of a feature required for	*/
		/*		this language system; if	*/
		/*		no required features, 		*/
		/*		= kGSUBNoRequiredFeature	*/
		uint16_t	featureCount; 		/*	Number of FeatureIndex values	*/
		/*		for this language system;	*/
		/*		excludes the required		*/
		/*		feature						*/
		uint16_t	featureIndices[];
		/*	Array of indices into the 		*/
		/*		FeatureList, in arbitrary	*/
		/*		order						*/
	};
	
#ifndef __cplusplus
	typedef struct LangSysTable LangSysTable;
#endif
	
	/* The ScriptTable. */
	
	struct ScriptTable {
		GSUBOffset	defaultLangSys;
		uint16_t	langSysCount;
		LangSysRecord	langSysRecords[];
	};
	
#ifndef __cplusplus
	typedef struct ScriptTable ScriptTable;
#endif
	
	
	/* The FeatureRecord */
	
	struct FeatureRecord {
		FourCharCode tag;
		GSUBOffset	featureOffset;
	};
	
#ifndef __cplusplus
	typedef struct FeatureRecord FeatureRecord;
#endif
	
	
	/* The FeatureListTable */
	
	struct FeatureListTable {
		uint16_t	featureCount;
		FeatureRecord featureRecords[];
	};
	
#ifndef __cplusplus
	typedef struct FeatureListTable FeatureListTable;
#endif
	
	/* The FeatureTable */
	
	struct FeatureTable {
		GSUBOffset	featureParams;
		uint16_t	lookupCount;
		uint16_t	lookupListIndices[];
	};
	
#ifndef __cplusplus
	typedef struct FeatureTable FeatureTable;
#endif
	
	
	/* The LookupTable */
	
	struct LookupTable {
		uint16_t lookupType;
		uint16_t lookupFlag;
		uint16_t subtableCount;
		GSUBOffset	subTableOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct LookupTable LookupTable;
#endif
	
	
	/* The LookupListTable */
	
	struct LookupListTable {
		uint16_t	lookupCount;
		GSUBOffset lookupTables[];
	};
	
#ifndef __cplusplus
	typedef struct LookupListTable LookupListTable;
#endif
	
	
	/* The SingleSubstFormat1 */
	
	struct SingleSubstFormat1 {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		int16_t	deltaGlyphID;
	};
	
#ifndef __cplusplus
	typedef struct SingleSubstFormat1 SingleSubstFormat1;
#endif
	
	
	/* The SingleSubstFormat2 */
	
	struct SingleSubstFormat2 {
		uint16_t			substFormat;
		GSUBOffset			coverageOffset;
		uint16_t			glyphCount;
		FTFontTableGlyphID	substitute[];
	};
	
#ifndef __cplusplus
	typedef struct SingleSubstFormat2 SingleSubstFormat2;
#endif
	
	
	
	/* The MultipleSubstFormat1 */
	
	struct MultipleSubstFormat1 {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	sequenceCount;
		GSUBOffset	sequenceOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct MultipleSubstFormat1 MultipleSubstFormat1;
#endif
	
	
	
	/* The AlternateSubstFormat1 */
	
	struct AlternateSetSubstFormat1 {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	alternateSetCount;
		GSUBOffset	alternateSetOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct AlternateSetSubstFormat1 AlternateSetSubstFormat1;
#endif
	
	
	/* The LigatureSubstFormat1Subtable */
	
	struct LigatureSubstFormat1Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	ligSetCount;
		GSUBOffset	ligatureSetOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct LigatureSubstFormat1Subtable LigatureSubstFormat1Subtable;
#endif
	
	
	/* The LigatureSetTable */
	
	struct LigatureSetTable {
		uint16_t	ligatureCount;
		GSUBOffset	ligatureOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct LigatureSetTable LigatureSetTable;
#endif
	
	
	/* The LigatureTable */
	
	struct LigatureTable {
		FTFontTableGlyphID	ligGlyph;
		uint16_t			compCount;
		FTFontTableGlyphID	components[];
	};
	
#ifndef __cplusplus
	typedef struct LigatureTable LigatureTable;
#endif
	
	
	/* The ContextSubstFormat1Subtable */
	
	struct ContextSubstFormat1Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	subRuleSetCount;
		GSUBOffset	subRuleSetOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct ContextSubstFormat1Subtable ContextSubstFormat1Subtable;
#endif
	
	
	/* The SubRuleSetTable */
	
	struct SubRuleSetTable {
		uint16_t	subRuleCount;
		GSUBOffset	subRuleOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct SubRuleSetTable SubRuleSetTable;
#endif
	
	
	/* The SubRuleTable */
	
	struct SubRuleTable {
		uint16_t	glyphCount;
		uint16_t	substCount;
		FTFontTableGlyphID	input[];
		//	SubstLookupRecord	substLookupRecords[];
	};
	
#ifndef __cplusplus
	typedef struct SubRuleTable SubRuleTable;
#endif
	
	/* The ContextSubstFormat2Subtable */
	
	struct ContextSubstFormat2Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		GSUBOffset	classDefOffset;
		uint16_t	subClassSetCount;
		GSUBOffset	subClassSetOffsets[];
	};
	
#ifndef __cplusplus
	typdef struct ContextSubstFormat2Subtable ContextSubstFormat2Subtable;
#endif
	
	/* The SubClassSetTable */
	
	struct SubClassSetTable {
		uint16_t	subClassRuleCount;
		GSUBOffset	subClassRuleOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct SubClassSetTable SubClassSetTable;
#endif
	
	/* The SubClassRuletTable */
	
	struct SubClassRuleTable {
		uint16_t	glyphCount;
		uint16_t	substCount;
		uint16_t	glyphClasses[]; /* [glyphCount - 1] */
		//	SubstLookupRecord	substLookupRecords[ ]; /* [substCount] */
	};
	
#ifdef __cplusplus
	typedef struct SubClassRuleTable SubClassRuleTable;
#endif
	
	/* The ContextSubstFormat3Subtable */
	
	struct ContextSubstFormat3Subtable {
		uint16_t	substFormat;
		uint16_t	glyphCount;
		uint16_t	substCount;
		GSUBOffset	Coverage[]; /* [glyphCount - 1] */
		//	SubstLookupRecord	substLookupRecords[]; /* [substCount] */
	};
	
#ifndef __cplusplus
	typedef struct ContextSubstFormat3Subtable ContextSubstFormat3Subtable;
#endif
	
	/* The ChainingContextSubstFormat1Subtable */
	
	struct ChainingContextSubstFormat1Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	chainSubRuleSetCount;
		GSUBOffset	chainSubRuleSetOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct ChainingContextSubstFormat1Subtable ChainingContextSubstFormat1Subtable;
#endif
	
	/* The ChainSubRuleSetTable */
	
	struct ChainSubRuleSetTable {
		uint16_t	chainSubRuleCount;
		GSUBOffset	chainSubRuleOffsets[];
	};
	
#ifdef __cplusplus
	typedef struct ChainSubRuleSetTable ChainSubRuleSetTable;
#endif
	
	/* The ChainSubRuleTable */
	
	struct ChainSubRuleTable {
		uint16_t			backtrackGlyphCount;
		FTFontTableGlyphID	backtrackGlyphs[];
		//	uint16_t			inputGlyphCount;
		//	FTFontTableGlyphID	inputGlyphs[];
		//	uint16_t			lookAheadGlyphCount;
		//	FTFontTableGlyphID	lookAheadGlyphs[];
		//	uint16_t			substCount;
		//	SubstLookupRecord	substLookupRecords[];
	};
	
	/* The ChainingContextSubstFormat2Subtable */
	
	struct ChainingContextSubstFormat2Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		GSUBOffset	backtrackClassDefOffset;
		GSUBOffset	inputClassDefOffset;
		GSUBOffset	lookAheadClassDefOffset;
		uint16_t	chainSubClassSetCount;
		GSUBOffset	chainSubClassSetOffsets[];
	};
	
#ifdef __cplusplus
	typedef struct ChainingContextSubstFormat2Subtable ChainingContextSubstFormat2Subtable;
#endif
	
	/* The ChainSubClassSetTable */
	
	struct ChainSubClassSetTable {
		uint16_t	chainSubClassRuleCount;
		GSUBOffset	chainSubClassRuleOffsets[];
	};
	
#ifndef __cplusplus
	typedef struct ChainSubClassSetTable ChainSubClassSetTable;
#endif
	
	/* The ChainSubClassRuleTable */
	
	struct ChainSubClassRuleTable {
		uint16_t	backtrackGlyphCount;
		uint16_t	backtrackClasses[]; /* [backtrackGlyphCount] */
		//	uint16_t	inputGlyphCount;
		//	uint16_t	inputClasses[]; /* [inputGlyphCount - 1] */
		//	uint16_t	lookAheadGlyphCount;
		//	uint16_t	lookAheadClasses[]; /* [lookAheadGlyphCount] */
		//	uint16_t	substCount;
		//	SubstLookupRecord substLookupRecords[]; /* [substCount] */
	};
	
#ifndef __cplusplus
	typedef struct ChainSubClassRuleTable ChainSubClassRuleTable;
#endif
	
	/* The ChainingContextSubstFormat3Subtable */
	
	struct ChainingContextSubstFormat3Subtable {
		uint16_t	substFormat;
		uint16_t	backtrackGlyphCount;
		GSUBOffset	backtrackCoverageTables[]; /* [backtrackGlyphCount] */
		//	uint16_t	inputGlyphCount;
		//	GSUBOffset	inputCoverageTables[]; /* [inputGlyphCount] */
		//	uint16_t	lookAheadGlyhCount;
		//	GSUBOffset	lookAheadCoverageTables[]; /* [lookAheadGlyphCount] */
		//	uint16_t	substCount;
		//	SubstLookupRecord substLookupRecords[]; /* [substCount] */
	};
	
#ifndef __cplusplus
	typedef struct ChainingContextSubstFormat3Subtable ChainingContextSubstFormat3Subtable;
#endif
	
	/* The ExtensionSubstFormat1Subtable */
	
	struct ExtensionSubstFormat1Subtable {
		uint16_t	substFormat;
		uint16_t	extensionLookupType;
		uint32_t	extensionOffset;
	};
	
#ifndef __cplusplus
	typedef struct ExtensionSubstFormat1Subtable ExtensionSubstFormat1Subtable;
#endif
	
	/* The ReverseChainingContextSubstFormat1Subtable */
	
	struct ReverseChainingContextSubstFormat1Subtable {
		uint16_t	substFormat;
		GSUBOffset	coverageOffset;
		uint16_t	backtrackGlyphCount;
		GSUBOffset	backtrackGlyphCoverage[]; /* [backtrackGlyphCount] */
		//	uint16_t	lookAheadGlyphCount;
		//	GSUBOffset	lookAheadGlyphCoverage[]; /* [lookAheadGlyphCount] */
		//	uint16_t	glyphCount;
		//	FTFontTableGlyphID substituteGlyphs[]; /* [glyphCount] */
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_GSUB : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'GSUB' ),
			kNoRequiredFeature	= 0xFFFFU,
			
			kSingleSubstitution				= 1,
			kMultipleSubstitution			= 2,
			kAlternateSetSubstitution		= 3,
			kLigatureSubstitution			= 4,
			kContextSubstitution			= 5,
			kChainingContextSubstitution	= 6,
			kExtensionSubstitution			= 7,
			kReverseChainingContextSubstitution = 8,
			
			kSingleSubstFormat1				= 1,
			kSingleSubstFormat2				= 2,
			
			kMultipleSubstFormat1			= 1,
			
			kAlternateSetSubstFormat1		= 1,
			
			kGUSBLigatureSubstFormat1		= 1,
			
			kContextSubstFormat1			= 1,
			kContextSubstFormat2			= 2,
			kContextSubstFormat3			= 3,
			
			kChainingContextSubstFormat1	= 1,
			KChainingContextSubstFormat2	= 2,
			kChainingContextSubstFormat3	= 3,
			
			kExtensionSubstFormat1			= 1,
			
			kReverseChainingContextSubstFormat1 = 1,
			
			kCoverageFormat1				= 1,
			kCoverageFormat2				= 2,
			
			kClassDefFormat1				= 1,
			kClassDefFormat2				= 2,
			
			kRightToLeftBit					= 0,
			kRightToLeftMask				= 0x0001U,
			kIgnoreBaseGlyphsBit			= 1,
			kIgnoreBaseGlyphsMask			= 0x0002U,
			kIgnoreLigaturesBit				= 2,
			kIgnoreLigaturesMask			= 0x0004U,
			kIgnoreMarksBit					= 3,
			kIgnoreMarksMask				= 0x0008U,
			kMarkAttachmentTypeBit			= 8,
			kMarkAttachmentTypeMask			= 0xFF00U
		};
		
		FTFontTable_GSUB( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_GSUB( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_GSUB( const FTFontTable& iOther );
		virtual ~FTFontTable_GSUB();
		
		FTFontTable_GSUB& operator=( const FTFontTable_GSUB& iOther );
		
		virtual FourCharCode	GetTag() const;
		
		const FeatureListTable *GetFeatureListTable() const;
		const FeatureRecord *GetFeatureRecord( int iIndex ) const;
		
	protected:
		
		FTFontTable_GSUB();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
	};
	
}

#pragma pack(pop)

#endif /* __FTFONTTABLE_GSUB__ */
