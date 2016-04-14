/*
	File:			FTFeatureInfo.h

	Contains:		C++ class for individual 'Zapf' table feature info structures

	Version:		Mac OS X

	Written by:		The Apple Font Group

	Copyright:		© 2009-2015 by Apple Inc. All rights reserved.

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


#ifndef __FTFEATUREINFO__
#define __FTFEATUREINFO__

#include "FTFontTable_Zapf.h"

namespace ftx {

class FTFeatureInfo {
	
public:
	
	static const FTFeatureInfo* CreateFeatureInfo( const ZAPFFeatureInfo *iFeatureInfo );

	FTFeatureInfo( const ZAPFFeatureInfo *iFeatureInfo );
	virtual ~FTFeatureInfo();
	
	virtual bool operator==( const FTFeatureInfo& iOther ) const;
	virtual bool operator!=( const FTFeatureInfo& iOther ) const;
	
	virtual uint16_t GetContext() const;
	virtual ItemCount GetNumAATFeatures() const;
	virtual sfntFontRunFeature GetIndAATFeature( ItemCount iFeatureIndex ) const;
	virtual ItemCount GetNumOTTags() const;
	virtual FourCharCode GetIndOTTag( ItemCount iTagIndex ) const;
	
	
private:
	
	FTFeatureInfo();
	FTFeatureInfo( const FTFeatureInfo& iOther );
	FTFeatureInfo& operator=( const FTFeatureInfo& iOther );
	
	const ZAPFFeatureInfo *_fFeatureInfo;
	
};


typedef FTFeatureInfo *FTFeatureInfoPtr;

}

#endif /* __FTFEATUREINFO__ */
