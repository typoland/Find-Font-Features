/*
	File:		BOFFontContainer.h
 
	Contains:	Class representing file containing one or more fonts

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

#import "BOFTypes.h"

@class BOFFont_POST;
@class BOFFont_Type1;

@interface BOFFontContainer : NSObject

+ (BOOL)createMinimalFontContainerWithURL:(NSURL*)url fontName:(NSString*)fontName glyphCount:(NSUInteger)glyphCount;
+ (BOFFontContainer*)fontContainerWithURL:(NSURL*)url isReadOnly:(BOOL)isReadOnly;

- (id)initWithURL:(NSURL*)url isReadOnly:(BOOL)isReadOnly;

@property(strong,readonly) NSString *name;
@property(strong,readonly) NSURL *url;
@property(strong,readonly) NSArray *fonts;
@property(assign,readonly) BOOL isReadOnly;
@property(assign,readonly) BOOL isDirty;
@property(assign,readonly) void *containerPtr;

- (void)makeClean;
- (void)readData;
- (void)writeData;

@end

@interface BOFDiskBasedFontContainer : BOFFontContainer

- (id)initWithURL:(NSURL *)url isReadOnly:(BOOL)isReadOnly;

- (NSString*)copyPath;

@property(strong,readonly) NSURL *fileURL;

@end

@interface BOFCoreTextFontContainer : BOFFontContainer

- (id)initWithURL:(NSURL*)url isReadOnly:(BOOL)isReadOnly;
- (id)initWithFont:(NSFont*)font;

@end

@interface BOFResourceFontContainer : BOFDiskBasedFontContainer

- (id)initWithURL:(NSURL*)url isReadOnly:(BOOL)isReadOnly;

@property(assign,readonly) BOOL isDataforkSuitcase;
@property(assign,readonly) int64_t maximumResourceSize;
@property(assign,readonly) BOFResourceFileRef fileRef;

@end

@interface BOFLWFNFontContainer : BOFResourceFontContainer

- (id)initWithURL:(NSURL *)url isReadOnly:(BOOL)isReadOnly;

@property(strong,readonly) BOFFont_POST	*postFont;
@property(strong,readonly) BOFFont_Type1 *type1Font;

@end
