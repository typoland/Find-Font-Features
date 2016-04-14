/*
	File:		FTLookupTableBuilder.h
 
	Contains:	Declarations for the a class that can build lookup tables
 
	Version:	MacOS X
 
	Copyright:	© 2009-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Peter Lofting
 
		Technology:			Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins
 
 
	 N.B., to the extent possible, this code observes the following naming conventions
		 for variables
	 Method or function *input* variables all have names beginning with "i"
	 Method or function *output* variables all have names beginning with "o"
	 Local variables all have names beginning with "t"
	 Structure or class members all have names beginning with "f" (public members) or
		 "_f" (private members)
	 Constants all have names beginning with "k"
 */

#ifndef __FTLOOKUPTABLEBUILDER__
#define __FTLOOKUPTABLEBUILDER__

/* ----------------------------------------------------------------------------------------- */

/* HEADERS -- ANSI */

/* HEADERS -- SYSTEM */

/* HEADERS -- LIBRARY */

#include "FTTypes.h"

namespace ftx {

/* ----------------------------------------------------------------------------------------- */

/* TYPES */

struct FTLookupValue {
	uint16_t		fGlyphID;
	SFNTLookupValue	fValue;
};

/* ----------------------------------------------------------------------------------------- */

/* CLASSES -- FTLookupTableBuilder */

class FTLookupTableBuilder {
	
public:
	
	enum {
		kValuesArePreswapped = true,
		kValuesAreUnswapped = false,
	};
	
	enum ELookupType {
		kSimpleArray        = 0,    /* a simple array indexed by glyph code */
		kSegmentSingle      = 2,    /* segment mapping to single value */
		kSegmentArray       = 4,    /* segment mapping to lookup array */
		kSingleTable        = 6,    /* sorted list of glyph, value pairs */
		kTrimmedArray       = 8,    /* a simple trimmed array indexed by glyph code */
		kSmallest			  = 10
	};
	
	FTLookupTableBuilder();
	FTLookupTableBuilder( ItemCount iValueCount, const FTLookupValue *iValues, bool iValuesArePreSwapped = kValuesAreUnswapped );
	FTLookupTableBuilder( const FTLookupTableBuilder& iOther );
	virtual ~FTLookupTableBuilder();
	
	FTLookupTableBuilder& operator=( const FTLookupTableBuilder& iOther );
	
	/* Setters and getters */
	virtual ItemCount			GetValueCount() const { return _fValueCount; };
	virtual const FTLookupValue	*GetValues()  const { return _fValues; };
	virtual FTGlyphID			GetIndGlyphID( ItemCount iIndex ) const;
	virtual SFNTLookupValue		GetIndSwappedValue( ItemCount iIndex ) const;
	virtual SFNTLookupValue		GetIndUnswappedValue( ItemCount iIndex ) const;
	virtual bool				MapGlyphToValue( FTGlyphID iGlyphID, uint16_t& oValue ) const;
	virtual bool				ValuesArePreSwapped() const { return _fValuesArePreSwapped; };
	
	static int32_t FirstBit( uint32_t iBit );
	static const void *DoGenericLookup( const SFNTLookupTable *table, uint32_t glyph );
	
	/* Build the tables */
	/*	Each of these returns an empty data ref and *not* nullptr on failure */
	CFDataRef	BuildType0LookupTable() const;
	CFDataRef	BuildType2LookupTable() const;
	CFDataRef	BuildType4LookupTable() const;
	CFDataRef	BuildType6LookupTable() const;
	CFDataRef	BuildType8LookupTable() const;
	CFDataRef	BuildSmallestLookupTable() const;
	CFDataRef	BuildLookupTable( ELookupType iType ) const;
	
private:
	
	const FTLookupValue	*CopyAndSwap( ItemCount iValueCount, const FTLookupValue *iValues, bool iValuesArePreSwapped ) const;
	void FillInAndSwap( SFNTLookupBinarySearchHeader& iHeader ) const;
	
	static const void *DoGenericBinarySearchLookup( const SFNTLookupTable *table, uint32_t glyph );
	static const SFNTLookupSingle *FindSingle(const SFNTLookupSingleHeader *header, uint32_t glyph);
	static const SFNTLookupSegment *FindSegment(const SFNTLookupSegmentHeader *header, uint32_t glyph);	
	
	ItemCount			_fValueCount;
	bool				_fValuesArePreSwapped;
	const FTLookupValue	*_fValues;
};

}

#endif /* __FTLOOKUPTABLEBUILDER__ */
