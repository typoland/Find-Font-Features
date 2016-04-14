/*
	File:		FTXMLGenerator.h
 
	Contains:	A C++ base class for dumping table contents
 
	Version:	MacOS X
 
	Copyright:	© 2002-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#ifndef __FTXMLGENERATOR__
#define __FTXMLGENERATOR__

#include <Carbon/Carbon.h>
#include <fstream>

#include "FTDataStreamer.h"
#include "FTException.h"
#include "FTFont_sfnt.h"
#include "FTTypes.h"

using namespace std;

namespace ftx {
	
	class FTFont_sfnt;
	class FTOutputStream;
	
	class FTXMLGenerator : public FTDataStreamer {
		
	public:
		
		static FTXMLGenerator* CreateGenerator( const FTFont_sfnt* iFont, FourCharCode iTag, FTOutputStream* iStream,
                                                     uint16_t iDiagnosticLevel = 0,
                                                     bool iUseGenericDumpAndFuse = false, bool iDumpExperimentalTables = true,
                                                     bool iIncludeGlyphNames = true, bool iIncludeCharacterNames = true);
		
		FTXMLGenerator( const FTFont_sfnt* iFont, FourCharCode iTableTag );
		FTXMLGenerator( const FTXMLGenerator& iOther );
		
		virtual ~FTXMLGenerator();
		
		FTXMLGenerator& operator=( const FTXMLGenerator& iOther );
		
		bool				DumpTable() const;
		virtual void		DumpDTD() const;
		virtual void		DumpData() const;
		bool				GenerateAndDumpTable() const;
		CFStringRef			CreateDumpedTableString() const;
		
		friend ostream& operator<<( ostream &iOut, const FTXMLGenerator& iDumper );
		
		virtual FourCharCode		GetTag() const { return _fTag; };
		
		const uint8_t*				GetData() const { return _fData != nullptr ? ::CFDataGetBytePtr( _fData ) : nullptr; };
		ByteCount					GetSize() const { return _fData != nullptr ? ::CFDataGetLength( _fData ) : 0; };
		
		ItemCount					GetGlyphCount() const;
		uint16_t					GetUnitsPerEm() const;

	protected:
		
		virtual void			GenerateAndDumpData() const;
		virtual bool			CanGenerateTable() const { return false; };
		bool					GetGlyphName( FTGlyphID iGlyph, char *oName ) const;
		ItemCount				CountFontGlyphs() const { return GetFont()->CountFontGlyphs(); };
		
		uint16_t				PerformGenericLookup( const SFNTLookupTable *iLookupTable, FTGlyphID iGlyph, bool &oFoundIt ) const;
		uint16_t				PerformSwappedLookup( const SFNTLookupTable *iLookupTable, FTGlyphID iGlyph, bool &oFoundIt ) const;
		
		
	private:
		
		enum {
			kBufferSize = 1024,
		};
		
		void				SetUpData();
		void				SetData( CFDataRef iData ) const;
		void				ClearData();
		
		FourCharCode				_fTag;
		mutable CFDataRef			_fData;		
	};
	
	
}

#endif /* __FTXMLGENERATOR__ */
