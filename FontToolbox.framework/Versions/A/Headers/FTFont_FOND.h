/*
	File:			FTFont_FOND.h
 
	Contains:		C++ class for 'FOND' resources
 
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

#ifndef __FTFONT_FOND__
#define __FTFONT_FOND__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTFont_resource.h"

namespace ftx {

	// These are versions of types which are defined in Snow Leopard headers
	//		but not in Barolo ones.  They're very, very old stuff.

	struct FTWidEntry {
		SInt16 widStyle;               /*style entry applies to*/
	};

	struct FTWidTable {
		SInt16 numWidths;              /*number of entries - 1*/
	};
	
	class FTString;
	
	// Types that aren't defined in system headers anywhere
	
	struct FONDBoundingBoxEntry
	{
		int16_t		fStyle;
		int16_t		fLeft;
		int16_t		fBottom;
		int16_t		fRight;
		int16_t		fTop;
	};
	
	struct FONDBoundingBoxTable
	{
		int16_t					fNumEntriesMinusOne;
		FONDBoundingBoxEntry	fEntries[];
	};
	
	class FTFontContainer;
	class FTLWFNFontContainer;
	
	class FTFont_FOND : public FTFont_resource {
		
	public:

		enum {
			kNormal                        = 0,
			kBold                          = 1,
			kItalic                        = 2,
			kUnderline                     = 4,
			kOutline                       = 8,
			kShadow                        = 0x10,
			kCondense                      = 0x20,
			kExtend                        = 0x40,

			kPostScriptNameCount			= 48,

			kIsFixedWidth					= 0x8000,
			kWidthTableUsed					= 0x4000,
			kUseIntegerWidths				= 0x2000,
			kIgnoreFracEnable				= 0x1000,

			kNameNeedsCoordinating			= 0x0001,
			kMacVectorReencoding			= 0x0002,
			kOutlinableBySettingPaintType	= 0x0004,
			kNoSmearAndWhiteout				= 0x0008,
			kNoSmearBolding					= 0x0010,
			kBoldByIncreasingPointsize		= 0x0020,
			kNoObliquingForItalic			= 0x0040,
			kNoSimulationOfCondensed		= 0x0080,
			kNoSimulationOfExpanded			= 0x0100,
			kNonMacReencoding				= 0x0200,
			kNoAdditionalIntercharSpacing	= 0x0400

		};

		FTFont_FOND( FTFontContainer *iContainer, Handle iFONDResource );
		FTFont_FOND( FTFontContainer *iContainer,
					const uint8_t *iData, ByteCount iLength,
					int16_t iResourceID, const unsigned char *iResourceName );
		FTFont_FOND( const FTFont_FOND& iOther );
		virtual ~FTFont_FOND();
		
		FTFont_FOND& operator=( const FTFont_FOND& iOther );
		
		// Returns a constant indicating what kind of font this is
		virtual EFontType		GetType() const { return FTFont::kFONDFontType; };
		
		// Gettters

		const FamRec *			GetFamilyRecord() const { return &_fFamRec; };

		// Returns the PostScript name for the font as a string
		virtual CFStringRef						GetPostScriptName() const { return GetIndPostScriptName( 0 ); };
		
		virtual ItemCount						GetFATEntryCount() const;
		virtual const AsscEntry					*GetFAT() const;
		bool									GetIndFATEntry(ItemCount iIndex, AsscEntry& oEntry) const;
		
		virtual const StyleTable				*GetStyleMappingTable() const;
		uint16_t								GetFontClass() const { return ::CFSwapInt16BigToHost(GetStyleMappingTable()->fontClass); };

		static FTString							CreateStyleString(uint16_t iStyle);
		static FTString							CreateStyleStringNoU(uint16_t iStyle);
		static FTString							MakePSNameString(const StyleTable *styleTable, const NameTable *nameTable, ItemCount index );
		static const unsigned char *			FindIthString( const NameTable *iNameTable, ItemCount iIndex );

		virtual const NameTable					*GetNameTable() const;
		
		virtual const KernTable					*GetKernTable() const;
		virtual ItemCount						GetKernEntryCount() const;
		virtual const KernEntry					*GetKernEntries() const;
		virtual const KernEntry					*GetIndKernEntry( ItemCount iEntryIndex ) const;
		virtual ItemCount						GetIndKernPairCount( ItemCount iEntryIndex ) const;
		virtual const KernPair					*GetIndKernPair( ItemCount iEntryIndex, ItemCount iPairIndex ) const;
		
		virtual const uint8_t					*GetWidthTable() const;
		
		virtual ItemCount						GetOffsetCount() const;
		virtual const uint32_t					*GetOffsets() const;
		
		virtual ItemCount						GetBoundingBoxCount() const;
		virtual const FONDBoundingBoxEntry		*GetBoundingBoxes() const;
		
		virtual ItemCount						GetType1FontCount() const;
		virtual const FTLWFNFontContainer		*GetIndType1Font( ItemCount iFontIndex ) const;
		
		virtual void CheckIntegrity() const;
		
		virtual ItemCount						GetPostScriptNameCount() const;
		virtual CFStringRef						GetIndPostScriptName( ItemCount iNameIndex ) const;
		virtual CFStringRef						GetStylePostScriptName( int16_t iStyle ) const;
		
		virtual bool							HasOutlines_sfnt() const;
		virtual bool							HasOutlines_LWFN() const;

		FTString								GenerateString(bool iOutputXML) const;
		
	protected:
		
		FTFont_FOND();
		
		virtual void ReadDataInternal();
		
	private:

		CFArrayRef					GetPostScriptNames() const;
		void						ClearType1Fonts();
		void						LookForType1Fonts();
		const FTLWFNFontContainer	*Type1FontContainerFromName( CFStringRef iName ) const;
		void						Make533NameFromFullNameUC( ItemCount iLength, const UniChar *fullName, HFSUniStr255    *shortName) const;
		bool						StyleTableIsBad( const StyleTable *iStyleTable ) const;
		// This function is used to identify cases where the FOND
		//	is sufficiently corrupt that the style table cannot be used

		void						AppendStyleMappingTable(ostream& iStream) const;
		void						AppendStyleMappingFlag(ostream& iStream, uint16_t iFlag, const char *iLabel) const;
		void						AppendGlyphWidthTable(ostream& iStream) const;
		void						AppendBoundingBoxTable(ostream& iStream) const;

		FTString					GenerateNonXMLString() const;
		FTString					GenerateXMLString() const;

		FamRec						_fFamRec;
		
		ItemCount					_fFATEntryCount;
		const AsscEntry				*_fFAT;
		
		const StyleTable			*_fStyleMappingTable;

		const NameTable				*_fNameTable;
		
		const KernTable				*_fKernTable;
		int16_t						_fKernEntryCount;
		const KernEntry				*_fKernEntries;
		
		const uint8_t				*_fWidthTable;
		
		ItemCount					_fOffsetCount;
		const uint32_t				*_fOffsets;
		
		int16_t							_fBoundingBoxCount;
		const FONDBoundingBoxEntry		*_fBoundingBoxes;
		
		ItemCount						_fType1FontCount;
		const FTLWFNFontContainer		*_fType1Fonts[ 48 ];
		
		CFArrayRef						_fPostScriptNames;
		
		static CFMutableArrayRef			_fgType1Fonts;
		static const FTLWFNFontContainer	*ContainerForFile( const FSRef& iFile, bool iIsReadOnly );
		static void							ReleaseContainer( const FTLWFNFontContainer *iContainer );
	};
	
}

#endif /* __FTFONT_FOND__ */
