/*
	File:		FTDataStreamer.h
 
	Contains:	Definitions for the class that can output text data
 
	Version:	MacOS X
 
	Copyright:	© 2009-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins
 
*/

#ifndef __TDATASTREAMER__
#define __TDATASTREAMER__

/* ----------------------------------------------------------------------------------------- */

/* HEADERS -- ANSI */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* HEADERS -- SYSTEM */

#include <Carbon/Carbon.h>
#include <fstream>

/* HEADERS -- APPLICATION */

#include "FTOutputStream.h"
#include "FTTypes.h"
#include "FTFontTable_head.h"
#include "FTFontTable_xref.h"

using namespace std;

#define FAIL_IF_MESSAGE(a,b) do { if(a) { FTReporter::ReportError(b); return false; }; } while(0)
#define FAIL_IF_NOT_MESSAGE(a,b) do { if(!(a)) { FTReporter::ReportError(b); return false; }; } while(0)

namespace ftx {
	
	enum {
		kFTXMLGeneratorInternalError = -1,
		kFTXMLGeneratorMissingTableError = -2
	};
	
	/* ----------------------------------------------------------------------------------------- */
	
	/* CLASSES -- FTDataStreamer */
	
	
	class FTDataStreamer {
		
	public:
		
		FTDataStreamer( const FTFont_sfnt* iFont, FTOutputStream* iStream = nullptr );
		FTDataStreamer( const FTDataStreamer& iOther );
		virtual ~FTDataStreamer();
		
		FTDataStreamer& operator=( const FTDataStreamer& iOther );
		
		/* Setters and getters */
		FTOutputStream*	GetStream() const { return _fStream; };
		void			SetStream( FTOutputStream* iStream ) const { _fStream = iStream; }
		
		const FTFont_sfnt*	GetFont() const { return _fFont; }
		void			SetFont( const FTFont_sfnt* iFont ) { _fFont = iFont; };
		
		void			OutputUTF8String( const char *iString, ... ) const;
		void			OutputString( CFStringRef iString, const char *iLabel ) const;
		void			OutputString( const FTString& iString, const char *iLabel ) const;
		void			OutputString( const FTString& iString ) const;
        void            OutputString( const char *iString ) const { _OutputString(iString); };
		void			OutputCrossreferencedName( int16_t iTableType, int16_t iTableIndex ) const;
		void			Indent( int iIndent  ) const;
		void			OutputFixed( Fixed iFixed, const char *iLabel ) const;
		void			OutputSwappedFixed( Fixed iFixed, const char *iLabel ) const;
		void			OutputGlyphRefID( FTGlyphID iGlyph, const char *iPrefix = nullptr ) const;
		void			OutputUnswappedGlyphRefID( FTGlyphID iGlyph, const char *iPrefix = nullptr ) const;
		void			OutputNameRefID( FontNameCode iName, const char *iNameIDTag = nullptr, const char *iNameTag = nullptr ) const;
		void			OutputAxisRefID( ItemCount iAxis ) const;
		void			OutputTag( FourCharCode iTag, const char *iLabel = nullptr ) const;
		void			OutputSwappedTag( FourCharCode iTag, const char *iLabel = nullptr ) const;
		void			OutputUnlabeledTag( FourCharCode iTag ) const;
		void			OutputCharacterName( UnicodeScalarValue iUnicode, const char *iPrompt ) const;
		void			OutputDate( const BigDate& iDate ) const;
		void			OutputBit( uint32_t iBitField, uint32_t iBit, const char *iLabel, ItemCount& oBitCount ) const;
		void			OutputOTCoverage( int iIndent, const void *iCoverage, const char *iLabel = nullptr ) const;
		void			OutputFlag( bool iValue, const char *iLabel ) const;
		void			OutputBits( uint8_t iBits ) const;
		
		void			OutputFilteredChar( char iChar ) const;
		void			OutputFilteredString( const char *iString ) const;
		void			OutputFontLanguage( FontPlatformCode iPlatform, FontLanguageCode iLanguage ) const;
		void			OutputFontNameType( FontNameCode iNameType ) const;
		void			OutputFontPlatform( FontPlatformCode iPlatform ) const;
		void			OutputFontScript( FontPlatformCode iPlatform, FontScriptCode iScript ) const;
		void			OutputLanguageTag( CFIndex iIndex, const char *iNameIDTag, const char *iNameTag ) const;
		
		void 			WriteStringToLog( FSIORefNum iRefNum, char *iString, ByteCount length ) const;
		virtual void	DoStamp( const FTFont_sfnt *iFont ) const;

		void						CopyOutputOptions(const FTDataStreamer& iOther);
		
		uint16_t					GetDiagnosticLevel() const { return _fDiagnosticLevel; };
		void						SetDiagnosticLevel(uint16_t iValue) { _fDiagnosticLevel = iValue; };
		
		bool						CompactData() const { return _fCompactData; };
		void						SetCompactData(bool iValue) { _fCompactData = iValue; };
		
		bool						MinimalDump() const { return _fMinimalDump; };
		void						SetMinimalDump(bool iValue) { _fMinimalDump = iValue; };
		
		bool						IncludeUnicodeNames() const { return _fIncludeUnicodeNames; };
		void						SetIncludeUnicodeNames(bool iValue) { _fIncludeUnicodeNames = iValue; };
		
		bool						IncludeGlyphNames() const { return _fIncludeGlyphNames; };
		void						SetIncludeGlyphNames(bool iValue) { _fIncludeGlyphNames = iValue; };
		
		bool						DumpNameTableEntries() const { return _fDumpNameTableEntries; };
		void						SetDumpNameTableEntries(bool iValue) { _fDumpNameTableEntries = iValue; };

		bool						OmitStamp() const { return _fOmitStamp; };
		void						SetOmitStamp(bool iValue) { _fOmitStamp = iValue; };
		
		const char*					CmapSpecifier() const { return _fCmapSpecifier; };
		void						SetCmapSpecifier(const char* iValue) { _fCmapSpecifier = iValue; };

        const FTGlyphID*            GlyphReordering() const { return _fGlyphReordering; };
        void                        AdoptGlyphReordering(const FTGlyphID* iGlyphReordering) { if ( _fGlyphReordering != nullptr ) delete [] _fGlyphReordering; _fGlyphReordering = iGlyphReordering; };
		
		const FTString&				ToolName() const { return _fToolName; };
		void						SetToolName(const FTString& iValue) { _fToolName = iValue; };
		
		uint16_t					ToolBuild() const { return _fToolBuild; };
		void						SetToolBuild(uint16_t iValue) { _fToolBuild = iValue; };
		
	protected:		
		const FTFontTable_xref *GetTable_xref() const;
		FTEntry_xref GetEntry_xref() const { return _fEntry_xref; };
		void SetEntry_xref( const FTEntry_xref& iEntry_xref ) const { _fEntry_xref = iEntry_xref; };
		FTString GetName( int16_t iTableType, int16_t iTableIndex ) const;
		
		uint32_t GetSubtableIndex() const { return _fEntry_xref.fSubtableIndex; };
		void	 SetSubtableIndex(uint32_t iValue) const { _fEntry_xref.fSubtableIndex = iValue; };
		void	 IncrementSubtableIndex() const { _fEntry_xref.fSubtableIndex++; };
		
		FTString	FixedAsString(Fixed iValue) const;
		
		const char				*StandardBreakString() const { return "//-----------------------------------------------------------------------------------------------------------"; };
		const char				*ShortBreakString() const { return "//----------------------------------------------------"; };
		
	private:
		
		void _OutputString(const char *iString) const;
		void _OutputString(CFStringRef iString) const;
		void _OutputString(const FTString& iString) const;
		
		const FTFont_sfnt*				_fFont;
		mutable uint16_t				_fDiagnosticLevel;
		bool							_fCompactData;
		bool							_fMinimalDump;
		bool							_fIncludeUnicodeNames;
		bool							_fIncludeGlyphNames;
		bool							_fOmitStamp;
		bool							_fDumpNameTableEntries;
		const char*						_fCmapSpecifier;
        const FTGlyphID*                _fGlyphReordering;
		FTString						_fToolName;
		uint16_t						_fToolBuild;
		mutable FTOutputStream*			_fStream;
		mutable char*					_fBuffer;
		mutable ByteCount				_fBufferSize;
		mutable const FTFontTable_xref	*_fTable_xref;
		mutable FTEntry_xref			_fEntry_xref;
		
	};
	
	
}

#endif /* __TDATASTREAMER__ */
