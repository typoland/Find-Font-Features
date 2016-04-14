/*
	File:			FTCompoundTrueTypeGlyph.h
 
	Contains:		C++ class for individual 'glyf' table entries
 
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

#ifndef __FTCOMPOUNDTRUETYPEGLYPH__
#define __FTCOMPOUNDTRUETYPEGLYPH__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTArray.h"
#include "FTTrueTypeGlyph.h"

namespace ftx {

struct FTGlyphComponent {
	uint16_t		fFlags;
	int16_t			fGlyphIndex;
	uint16_t		fRest;
};

struct FTComponentTransform {
	int16_t	a;
	int16_t	b;
	int16_t	c;
	int16_t	d;
	int16_t xShift;
	int16_t yShift;
};

class FTFontTable_glyf;
class FTTrueTypeGlyphComponent;
class FTSimpleTrueTypeGlyph;

class FTCompoundTrueTypeGlyph : public FTTrueTypeGlyph {

public:
	
	FTCompoundTrueTypeGlyph( const uint8_t *iData, ByteCount iLength, const FTFontTable_glyf *iTable );
	FTCompoundTrueTypeGlyph( const FTCompoundTrueTypeGlyph& iOther );
	
	virtual ~FTCompoundTrueTypeGlyph();
	
	FTCompoundTrueTypeGlyph& operator=( const FTCompoundTrueTypeGlyph& iOther );
	virtual bool operator!=( const FTCompoundTrueTypeGlyph& iOther ) const;
	virtual bool operator==( const FTCompoundTrueTypeGlyph& iOther ) const;

	virtual bool		IsCompoundGlyph() const { return true; };
	virtual bool		IsEmptyGlyph() const { return false; };
	
	virtual uint16_t	GetComponentCount() const;
	virtual uint16_t	GetComponentID( uint16_t iIndex ) const;
	virtual uint16_t	GetComponentFlags( uint16_t iIndex ) const;
	virtual FTComponentTransform
						GetComponentTransform( uint16_t iIndex ) const;
	virtual uint16_t	GetSubcomponentCount() const;
	virtual uint16_t	GetComponentPointCount() const;
	virtual uint16_t	GetComponentContourCount() const;
	virtual uint16_t	GetComponentDepth() const;
	FTArray				SortedComponents() const;

	FTSimpleTrueTypeGlyph* CreateFlattenedCopy() const { FTReporter::ReportError("FTCompoundTrueTypeGlyph::CreateFlattenedCopy() is unimplemented"); return nullptr; };

protected:

	virtual void					CountPartsInternal( ItemCount *oNumPoints,
													   ItemCount* oNumContours, 
													   ItemCount iCurrentDepth, 
													   ItemCount *oMaxDepth ) const;
	
	virtual void		ReadDataInternal() const;
	virtual void		ReadComponentIDs() const;
	virtual void		WriteData();

	virtual FTString	GenerateXMLInternal(FTGlyphID iGlyphID, const FTArray* iGlyphsToRetain) const;
	
private:

	FTCompoundTrueTypeGlyph();
	
	static int32_t UnicodeToCanonicalCombiningClass( int32_t iUC );
	
	CFArrayRef				GenerateComponentIDs() const;
	CFArrayRef				GenerateComponentFlags() const;
	CFArrayRef				GenerateComponentTransforms() const;
	ByteCount				GetComponentSizeFromFlags( UInt16 iFlags, const FTGlyphComponent* iGlyphData, FTComponentTransform& oTransform ) const;
	CFArrayRef				GetComponentGlyphIDs() const;
	CFArrayRef				GetComponentGlyphFlags() const;
	CFArrayRef				GetComponentGlyphTransforms() const;
	FTComponentTransform	DefaultTransform() const;
	FTGlyphID				MapGlyphID(FTGlyphID iOldGlyphID, const FTArray *iGlyphsToRetain) const;

	uint16_t				_fSubcomponentCount;
	uint16_t				_fComponentPoints;
	uint16_t				_fComponentContourCount;
	uint16_t				_fComponentDepth;
	
	CFArrayRef				_fComponentIDs;
	CFArrayRef				_fComponentFlags;
	CFArrayRef				_fComponentTransforms;
	
};
	
}

#endif /* __FTCOMPOUNDTRUETYPEGLYPH__ */
