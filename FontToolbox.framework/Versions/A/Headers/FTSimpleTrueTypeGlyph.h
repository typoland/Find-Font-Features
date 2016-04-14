/*
	File:			FTSimpleTrueTypeGlyph.h
 
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

#ifndef __FTSIMPLETRUETYPEGLYPH__
#define __FTSIMPLETRUETYPEGLYPH__

#include <CoreFoundation/CoreFoundation.h>
#include <Carbon/Carbon.h>

#include "FTTrueTypeGlyph.h"

namespace ftx {

class FTFontTable_glyf;
class FTTrueTypeGlyphComponent;

	/*! \brief FTTrueTypeGlyph subclass for non-compound glyphs
	 *
	 *  FTSimpleTrueTypeGlyph is a FTTrueTypeGlyph 
	 *		subclass for TrueType glyphs that 
	 *		have outline data defined by contours,
	 *		not components.
	 *
	 *	FTSimpleTrueTypeGlyph instances will return
	 *		true to IsSimpleGlyph() and false to
	 *		the other Is*Glyph() functions defined
	 *		by its FTTrueTypeGlyph.
	 */

class FTSimpleTrueTypeGlyph : public FTTrueTypeGlyph {

public:
	
	enum {
		kNPUSHB = 0x40U,
		kNPUSHW = 0x41U,
		kPUSHB  = 0xB0U,
		kPUSHW  = 0xB8U,

		kBadInstruction	= 0xFFFFU,
		
		kInstructionStackDepth	= 1024,

	    kDontAppendStack = 0,
		
		kAppendStackPushMask = 1,
		kAppendStackPopMask	= 2,
		
		kAppendDescriptionMask	= 4,
		
		kAppendStackPush = kAppendStackPushMask,
		kAppendStackPop	= kAppendStackPopMask,
		kAppendStackAll	= ( kAppendStackPushMask | kAppendStackPopMask ),
	};

	static CFStringRef		DecodeInstruction( const uint8_t* iInstructionPtr, OptionBits iOptions, ByteCount* oBytesConsumed );
	
	FTSimpleTrueTypeGlyph( const uint8_t *iData, ByteCount iLength, const FTFontTable_glyf *iTable );
	FTSimpleTrueTypeGlyph( const FTSimpleTrueTypeGlyph& iOther );
	
	virtual ~FTSimpleTrueTypeGlyph();
	
	FTSimpleTrueTypeGlyph& operator=( const FTSimpleTrueTypeGlyph& iOther );
	virtual bool operator!=( const FTSimpleTrueTypeGlyph& iOther ) const;
	virtual bool operator==( const FTSimpleTrueTypeGlyph& iOther ) const;
		
	virtual bool			IsSimpleGlyph() const { return true; };
	virtual bool			IsEmptyGlyph() const { return false; };
	
	virtual uint16_t		GetContourCount() const;

	virtual uint16_t		GetPointCount() const;
	virtual Point			GetPoint( uint16_t iIndex ) const;
	virtual uint8_t			GetPointFlags( uint16_t iIndex ) const;
	virtual uint16_t		GetContourPointCount( uint16_t iContourIndex ) const;
	virtual Point			GetContourPoint( uint16_t iContourIndex, uint16_t iPointIndex ) const;
	virtual uint8_t			GetContourPointFlags( uint16_t iContourIndex, uint16_t iPointIndex ) const;
	
	virtual Rect			ComputeBoundingBox() const;

	virtual uint16_t		GetInstructionByteCount() const;

	virtual const uint16_t	*GetUnswappedEndPoints() const;
	virtual const uint8_t	*GetInstructionData() const;
	virtual const uint8_t	*GetFlagData() const;

protected:

	virtual void					CountPartsInternal( ItemCount *oNumPoints,
													   ItemCount* oNumContours, 
													   ItemCount iCurrentDepth, 
													   ItemCount *oMaxDepth ) const;
	
	virtual void		ReadDataInternal() const;
	const uint8_t		*UnzipFlags( const uint8_t *iData, const uint8_t *iDataLimit ) const;
	const uint8_t		*UnzipXCoordinates( const uint8_t *iData, const uint8_t *iDataLimit ) const;
	const uint8_t		*UnzipYCoordinates( const uint8_t *iData, const uint8_t *iDataLimit ) const;
	virtual void		WriteData();

	virtual FTString	GenerateXMLInternal(FTGlyphID iGlyphID, const FTArray* iGlyphsToRetain) const;

private:

	FTSimpleTrueTypeGlyph();
	void ClearData();

	static uint16_t		_fgInstructionStack[ kInstructionStackDepth ];
	static ItemCount	_fgStackDepth;

	static void PushOnStack( uint16_t iValue );
	static uint16_t PopFromStack();
	static void NumToBin( uint16_t iNum, uint16_t iNumDigits, char *oString );
	
	uint16_t				_fContourCount;
	uint16_t				_fInstructionByteCount;
	uint16_t				_fPointCount;
	uint8_t					*_fFlags;
	int16_t					*_fXCoordinates;
	int16_t					*_fYCoordinates;
};
	
}

#endif /* __FTSIMPLETRUETYPEGLYPH__ */
