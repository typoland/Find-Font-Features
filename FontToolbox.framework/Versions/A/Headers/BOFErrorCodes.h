/*
 File:		BOFErrorCodes.h

	Contains:	Error codes used in NSError objects with the "FontToolbox" domain

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	Copyright © 2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:			John Jenkins

		Other Contact:	Julio Gonzalez

		Technology:		Apple Font Tools

 */
#ifndef FontToolbox_BOFErrorCodes_h
#define FontToolbox_BOFErrorCodes_h

#define BOFErrorDomain @"FontToolbox"

enum {
	kBOFStringConversionError = 0,
	kBOFTableCreationError,

	kBOFInvalidErrorCode,
	kBOFMaxErrorCodes = kBOFInvalidErrorCode-1
};

#endif
