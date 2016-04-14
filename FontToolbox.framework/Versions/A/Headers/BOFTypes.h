/*
	File:		BOFTypes.h
 
	Contains:	General types used by the framework

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

typedef int32_t		BOFGlyphID;
	// We make this a four-byte signed int so that we can use -1 as a flag value
	//	but still include glyphs from 0 through 65534

typedef uint16_t	BOFFontTableGlyphID;
	// This is the value stored in font tables

typedef int32_t		BOFResourceFileRef;
typedef int16_t		BOFShortFrac;
typedef uint16_t	BOFOpenTypeOffset;

typedef int32_t     BOFFixed;

enum {
	kBOFInvalidGlyphID = 0xFFFFU,
};
