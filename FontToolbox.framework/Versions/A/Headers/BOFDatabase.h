/*
	File:		BOFDatabase.h
 
	Contains:	Class providing access to the framework's glyph property database

	Version:	Mac OS X
 
	Copyright:	© 2014-2015 by Apple Inc., all rights reserved.
 
	File Ownership:
 
		DRI:				John Jenkins
 
		Other Contact:		Julio Gonzalez
 
		Technology:			Apple Font Tools
 
*/

#import <Foundation/Foundation.h>

/* ----------------------------------------------------------------------------------------- */
/* CONSTANTS */
/* ----------------------------------------------------------------------------------------- */

enum {
	kBOFMaximumGlyphStringLength = 16
	//  Assuming one character for a glyph name and one
	//      character for the '_' separator, a compound
	//      glyph name with sixteen components will be
	//      thirty-one characters long, which is the maximum
	//      glyph length defined by Adobe
};

/* ----------------------------------------------------------------------------------------- */
/* TYPES */
/* ----------------------------------------------------------------------------------------- */

struct BOFGlyphLookupResult {
	BOOL				fWasFound;
	BOOL				fIsCompoundString;
	UnicodeScalarValue	fUnicode;
	uint16_t 			fProperties;
	int32_t				fVChar;
	UnicodeScalarValue	fString[kBOFMaximumGlyphStringLength];
};

typedef struct BOFGlyphLookupResult BOFGlyphLookupResult;

enum BOFAdobeCID {
	kBOFAdobeCNS1 = 0,
	kBOFAdobeGB1,
	kBOFAdobeJapan1,
	kBOFAdobeKorean1,
	kBOFInvalidCID
};

typedef enum BOFAdobeCID BOFAdobeCID;

enum BOFROSOrder {
	kBOFJapanOrder			= 0,
	kBOFSimpChineseOrder	= 1,
	kBOFTradChineseOrder	= 2,
	kBOFKoreanOrder			= 3,
	kBOFInvalidOrder		= 0xFFFF
};

typedef enum BOFROSOrder BOFROSOrder;

@interface BOFDatabase : NSObject

+ (int)unicode:(UnicodeScalarValue)iUC toAdobeCID:(BOFAdobeCID)iAdobeCID;

+ (uint32_t)supportedUnicodeVersion;

+ (BOOL)doNameLookup:(NSString *)iToken result:(BOFGlyphLookupResult *)oLookupResult;
+ (BOOL)doTruncatedNameLookup:(NSString *)iToken result:(BOFGlyphLookupResult *)oLookupResult;
+ (BOOL)doUnicodeLookup:(UnicodeScalarValue)iUnicode result:(BOFGlyphLookupResult *)oLookupResult;
+ (NSString *)unicodeScalarName:(UnicodeScalarValue)iUnicode;
+ (NSString *)standardGlyphNameStringForUnicode:(UnicodeScalarValue)iUnicode;
+ (NSString *)stringForGlyphName:(NSString *)iGlyphName;
+ (UnicodeScalarValue)unicodeForGlyphName:(NSString *)iGlyphName;

+ (uint16_t)unicodeGeneralCategory:(UnicodeScalarValue)iUnicode;
+ (uint16_t)unicodeDirectionality:(UnicodeScalarValue)iUnicode;
+ (BOOL)isDefinedCharacter:(UnicodeScalarValue)iUnicode;
+ (BOOL)isPrintableCharacter:(UnicodeScalarValue)iUnicode;

+ (BOOL)unicodeCharacterMirrors:(UnicodeScalarValue)iUnicode;
+ (UnicodeScalarValue)unicodeMirrorCharacter:(UnicodeScalarValue)iUnicode;

// Unicode block support
// Block IDs are arbitrary and not guaranteed to be consistent across
//	Unicode releases (or even FontToolbox.framework builds)
//	-1 is used for an invalid ID
+ (int16_t)unicodeBlockIDWithName:(NSString *)iBlockName;
+ (NSString *)unicodeBlockNameWithID:(int16_t)iBlockID;
+ (ItemCount)unicodeBlockCount;
+ (NSRange)unicodeBlockRange:(int16_t)iBlockID;
+ (int16_t)unicodeBlockOfCharacter:(UnicodeScalarValue)iUnicode;
+ (BOOL)unicodeBlock:(int16_t)iBlockID containsCharacter:(UnicodeScalarValue)iUnicode;

// Unicode script support
// Script IDs are arbitrary and not guaranteed to be consistent across
//	Unicode releases (or even FontToolbox.framework builds)
//	-1 is used for an invalid ID
+ (int16_t)unicodeScriptIDFromName:(NSString *)iScriptName;
+ (NSString *)unicodeScriptName:(int16_t)iScriptID;
+ (ItemCount)unicodeScriptCount;
+ (int16_t)unicodeScriptOfCharacter:(UnicodeScalarValue)iUnicode;
+ (BOOL)unicodeScript:(int16_t)iScriptID containsCharacter:(UnicodeScalarValue)iUnicode;

+ (NSDictionary*)decompositionForCharacter:(UnicodeScalarValue)iUnicode;

@end
