//
//  FTFeatureSelectorPair.h
//  FontToolbox
//
//  Created by 井作恆 on 2/10/13.
//  Copyright (c) 2013年 Apple Inc. All rights reserved.
//

#ifndef __FontToolbox__FTFeatureSelectorPair__
#define __FontToolbox__FTFeatureSelectorPair__

#include <iostream>

namespace ftx {

	class FTNumber;
	class FTString;

class FTFeatureSelectorPair {

public:

	enum {
		kInvalidFeatureType = 0xFFFFU,
		kInvalidSelectorType = 0xFFFFU
	};

	FTFeatureSelectorPair(uint16_t iFeatureType = kInvalidFeatureType, uint16_t iSelectorType = kInvalidSelectorType);
	FTFeatureSelectorPair(const FTFeatureSelectorPair& iOther);
	FTFeatureSelectorPair(sfntFontRunFeature iFontRunFeature);
	FTFeatureSelectorPair(const FTNumber& iNumber);

	virtual ~FTFeatureSelectorPair();

	const FTFeatureSelectorPair& operator=(const FTFeatureSelectorPair& iOther);
	const bool operator!=(const FTFeatureSelectorPair& iOther) const;
	const bool operator==(const FTFeatureSelectorPair& iOther) const { return !operator!=(iOther); };
	operator sfntFontRunFeature() const;
	operator FTNumber() const;

	uint16_t	GetFeature() const { return _fFeature; };
	void		SetFeature(uint16_t iValue) { _fFeature = iValue; };
	uint16_t	GetSelector() const { return _fSelector; };
	void		SetSelector(uint16_t iValue) { _fSelector = iValue; };
	uint16_t	GetSetting() const { return _fSelector; };
	void		SetSetting(uint16_t iValue) { _fSelector = iValue; };

	static FTString StandardFeatureName(uint16_t iFeatureType);
	static FTString StandardSelectorName(const sfntFontRunFeature& iEntry);

protected:

private:
	uint16_t _fFeature;
	uint16_t _fSelector;

};

}

#endif /* defined(__FontToolbox__FTFeatureSelectorPair__) */
