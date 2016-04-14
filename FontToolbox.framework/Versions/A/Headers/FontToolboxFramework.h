/*
	File:		FontToolboxFramework.h
 
	Contains:	Umbrella include file for the Font Toolbox
 
	Version:	Mac OS X
 
	Written by:	The Apple Font Group
 
	Copyright:	Copyright © 2008-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:			John Jenkins
 
		Other Contact:	Peter Lofting
 
		Technology:		Apple Font Tools
 
*/

#ifndef __FONTTOOLBOXFRAMEWORK__
#define __FONTTOOLBOXFRAMEWORK__

#include "FTTypes.h"

// Container classes
#include "FTFontContainer.h"
#include "FTCoreTextFontContainer.h"
#include "FTDiskBasedFontContainer.h"
#include "FTResourceFontContainer.h"

// Font classes
#include "FTFont.h"
#include "FTFont_FOND.h"
#include "FTFont_NFNT.h"
#include "FTFont_POST.h"
#include "FTFont_SplicedFont.h"
#include "FTFont_Type1.h"
#include "FTFont_resource.h"
#include "FTFont_sfnt.h"
#include "FTFont_sfntResource.h"
#include "FTCoreTextFont.h"

// TrueType font table classes
#include "FTFontTable.h"
#include "FTFontTable_CFF_.h"
#include "FTFontTable_CID_.h"
#include "FTFontTable_EBDT.h"
#include "FTFontTable_EBLC.h"
#include "FTFontTable_EBSC.h"
#include "FTFontTable_GDEF.h"
#include "FTFontTable_GPOS.h"
#include "FTFontTable_GSUB.h"
#include "FTFontTable_OS_2.h"
#include "FTFontTable_TYP1.h"
#include "FTFontTable_Zapf.h"
#include "FTFontTable_addg.h"
#include "FTFontTable_ankr.h"
#include "FTFontTable_avar.h"
#include "FTFontTable_bdat.h"
#include "FTFontTable_bhed.h"
#include "FTFontTable_bloc.h"
#include "FTFontTable_bsln.h"
#include "FTFontTable_clas.h"
#include "FTFontTable_cmap.h"
#include "FTFontTable_cvar.h"
#include "FTFontTable_cvt_.h"
#include "FTFontTable_dsig.h"
#include "FTFontTable_fdsc.h"
#include "FTFontTable_feat.h"
#include "FTFontTable_fmtx.h"
#include "FTFontTable_fond.h"
#include "FTFontTable_fpgm.h"
#include "FTFontTable_fvar.h"
#include "FTFontTable_gasp.h"
#include "FTFontTable_gcid.h"
#include "FTFontTable_glyf.h"
#include "FTFontTable_gvar.h"
#include "FTFontTable_hdmx.h"
#include "FTFontTable_head.h"
#include "FTFontTable_hhea.h"
#include "FTFontTable_hmtx.h"
#include "FTFontTable_hsty.h"
#include "FTFontTable_just.h"
#include "FTFontTable_kern.h"
#include "FTFontTable_kerx.h"
#include "FTFontTable_loca.h"
#include "FTFontTable_ltag.h"
#include "FTFontTable_maxp.h"
#include "FTFontTable_meta.h"
#include "FTFontTable_mort.h"
#include "FTFontTable_morx.h"
#include "FTFontTable_name.h"
#include "FTFontTable_opbd.h"
#include "FTFontTable_post.h"
#include "FTFontTable_prep.h"
#include "FTFontTable_prop.h"
#include "FTFontTable_sbix.h"
#include "FTFontTable_trak.h"
#include "FTFontTable_umif.h"
#include "FTFontTable_vdmx.h"
#include "FTFontTable_vhea.h"
#include "FTFontTable_vmtx.h"
#include "FTFontTable_xref.h"

// Glyph classes
#include "FTTrueTypeGlyph.h"
#include "FTSimpleTrueTypeGlyph.h"
#include "FTCompoundTrueTypeGlyph.h"

// Miscellaneous TrueType-related classes
#include "FTGlyphGroup.h"
#include "FTKindName.h"
#include "FTLWFNFontContainer.h"
#include "FTNamedGroup.h"
#include "FTNameTableEntry.h"
#include "FTBitmap.h"
#include "FTEncoding.h"
#include "FTFeatureInfo.h"

// Utility classes
#include "FTDatabase.h"
#include "FTDataUtilities.h"
#include "FTException.h"
#include "FTFeatureSelectorPair.h"
#include "FTGlyphPieceDatabase.h"
#include "FTLookupTableBuilder.h"
#include "FTOutputStream.h"
#include "FTReporter.h"

// XML classes
#include "FTXMLGenerator.h"
#include "FTXMLParser.h"
#include "FTATIFGenerator.h"
#include "FTXMLOptions.h"

// Wrapper classes
#include "FTArray.h"
#include "FTCharacterSet.h"
#include "FTCoreFoundationType.h"
#include "FTData.h"
#include "FTDictionary.h"
#include "FTNumber.h"
#include "FTSet.h"
#include "FTString.h"
#include "FTUniChar.h"
#include "FTURL.h"

// Non-class stuff
#include "WindowsLanguages.h"

#endif /* __FONTTOOLBOXFRAMEWORK__ */
