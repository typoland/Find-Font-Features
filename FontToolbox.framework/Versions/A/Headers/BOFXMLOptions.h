/*
	File:		BOFXMLOptions.h
 
	Contains:	Class holding the options to pass to an XML parser

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

@interface BOFXMLOptions : NSObject

@property(nonatomic,readwrite) BOOL includeGlyphNames;
@property(nonatomic,readwrite) BOOL includeCharacterNames;
@property(nonatomic,readwrite) BOOL generateCompactOutput;
@property(nonatomic,readwrite) BOOL generateMinimalXML;
@property(nonatomic,readwrite) BOOL includeNameTableStrings;
@property(nonatomic,readwrite) BOOL compatibilityMode;
@property(nonatomic,readwrite) BOOL omitStamp;

@end
