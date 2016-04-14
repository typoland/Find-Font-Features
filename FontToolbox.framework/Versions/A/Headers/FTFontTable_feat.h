/*
	File:			FTFontTable_feat.h
 
	Contains:		C++ class individual TrueType font 'feat' tables
 
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

#ifndef __FTFONTTABLE_FEAT__
#define __FTFONTTABLE_FEAT__

#include <Carbon/Carbon.h>
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

	struct FTFeatureSelector {
		uint16_t	fFeatureSelector;
		int16_t		fNameIndex;
	};
	
	struct FTFeatureName {
		uint16_t	fFeatureType;
		uint16_t	fSelectorCount;
		uint32_t	fSelectorArrayOffset;
		uint16_t	fFeatureFlags;
		uint16_t	fNameIndex;
	};
	
	struct FTTable_feat {
		Fixed			fVersion;
		uint16_t		fNameCount;
		uint16_t		fReserved1;
		uint32_t		fReserved2;
		FTFeatureName	fNames[];
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* PROTOTYPES */
	
	class FTFontTable_feat : public FTFontTable {
		
	public:
		
		enum {
			kTag = FOUR_CHAR_CODE( 'feat' ),
			
			kIsExclusive 				= 0x8000U,
			kDefaultSettingSpecified	= 0x4000U,
			kDefaultSettingMask 		= 0x00FFU,
			
			kValidFlags					= kIsExclusive | kDefaultSettingMask | kDefaultSettingSpecified,
			
			kHeaderSize = sizeof( Fixed ) + 2 * sizeof( uint16_t ) + sizeof( uint32_t ),
			
			kVersion = fixed1,
			
		};
		
		FTFontTable_feat( FTFont_sfnt *iFont, FourCharCode iTag, ByteCount iOffset, ByteCount iLength, uint32_t iChecksum );
		FTFontTable_feat( FTFont_sfnt *iFont, FourCharCode iTag, CFDataRef iData, uint32_t iChecksum = FTFontTable::kInvalidChecksum );
		FTFontTable_feat( const FTFontTable& iOther );
		virtual ~FTFontTable_feat();
		
		FTFontTable_feat& operator=( const FTFontTable_feat& iOther );
		
		virtual FourCharCode		GetTag() const;
		
		virtual Fixed				GetVersion() const { ReadData(); return _fVersion; };
		virtual uint16_t			GetNameCount() const { ReadData(); return _fNameCount; };
		virtual bool				GetIndNameData( ItemCount iIndex, FTFeatureName &oNameData ) const;
		virtual bool				GetIndSelectorData( ItemCount iNameIndex, ItemCount iSelectorIndex, FTFeatureSelector &oSelectorData ) const;
		
	protected:
		
		FTFontTable_feat();
		
		virtual void		ReadDataInternal();
		virtual CFDataRef	RebuildDataInternal() const;
		
	private:
		
		void			DeleteData();
		
		Fixed			_fVersion;
		uint16_t		_fNameCount;
		
	};

}

#pragma pack(pop)

#endif /* __FTFONTTABLE_FEAT__ */
