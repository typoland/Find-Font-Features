/*
	File:		FTATIFGenerator.h
 
	Contains:	A C++ base class for dumping table contents as ATIFs
 
	Version:	MacOS X
 
	Copyright:	© 2012-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#ifndef __FTATIFGENERATOR__
#define __FTATIFGENERATOR__

#include <Carbon/Carbon.h>
#include <fstream>

#include "FTDataStreamer.h"
#include "FTDictionary.h"
#include "FTException.h"
#include "FTLookupTableBuilder.h"
#include "FTFont_sfnt.h"
#include "FTString.h"

using namespace std;

namespace ftx {

class FTATIFGenerator : public FTDataStreamer {

public:

	static const FTATIFGenerator*	CreateGenerator( const FTFont_sfnt* iFont, FourCharCode iTag, FTOutputStream* iStream );

	virtual ~FTATIFGenerator();
	
	FTATIFGenerator& operator=( const FTATIFGenerator& iOther );
	
	bool				DumpATIF() const;
	FTString			CreateDumpedTableString() const;
	
	friend ostream& operator<<( ostream &iOut, const FTATIFGenerator& iDumper );
	
	virtual FourCharCode		GetTag() const { return _fTag; };
	
	uint16_t					GetUnitsPerEm() const;
	
	uint16_t					GetDiagnosticLevel() const { return _fDiagnosticLevel; };
	
	void						DoStamp( const FTFont_sfnt *iFont ) const;
	
protected:

	FTATIFGenerator( const FTFont_sfnt* iFont, FourCharCode iTableTag );
	FTATIFGenerator( const FTATIFGenerator& iOther );
	
	virtual void			DumpData() const = 0;
	ItemCount				CountFontGlyphs() const { return GetFont()->CountFontGlyphs(); };
	bool					GetGlyphName( FTGlyphID iGlyphID, char *oName ) const;

	uint16_t				PerformGenericLookup( const SFNTLookupTable *iLookupTable, FTGlyphID iGlyph, bool &oFoundIt ) const;
	uint16_t				PerformSwappedLookup( const SFNTLookupTable *iLookupTable, FTGlyphID iGlyph, bool &oFoundIt ) const;
	void EndSubtable() const { OutputUTF8String( "}\n\n//-----------------------------------------------------------------------------------------------------------\n\n"); };
	void AddInterpieceGap() const { OutputUTF8String( "\n\t//---------------------------------------------\n\n"); };
	void AddInterpieceGap2() const { OutputUTF8String( "\n\t\t//-----------------------------------------\n\n"); };
		
private:
	
	enum {
		kBufferSize = 1024,
	};

	void				SetDiagnosticLevel( uint16_t iNewLevel ) const { _fDiagnosticLevel = iNewLevel; };

	FourCharCode				_fTag;
	mutable FTData				_fData;
	mutable uint16_t			_fDiagnosticLevel;

};


}

#endif /* __FTATIFGENERATOR__ */
