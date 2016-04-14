/*
	File:		BOFFontTable.h
 
	Contains:	Class representing a TrueType font table; individual 
					table types are represented via subclasses

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

@class BOFFontTableContainer;
@class BOFXMLOptions;

@interface BOFFontTable : NSObject

+(BOFFontTable*)fontTableWithFont:(BOFFont_sfnt*)font index:(ItemCount)index;

@property(assign,readonly) BOFFont_sfnt *font;

@property(assign,readonly) BOOL isDirty;
@property(strong,readonly) NSString *tag;
@property(assign,readonly) NSUInteger offset;
@property(assign,readonly) uint32_t checksum;

@property(assign,readonly) void *dataPtr;
@property(assign,readonly) NSUInteger dataLength;

- (NSData*)copyData;
- (NSString*)copyToXMLWithOptions:(BOFXMLOptions*)options;

- (void)makeDirty;
- (void)makeClean;

- (void)printDiagnostics;

@end

