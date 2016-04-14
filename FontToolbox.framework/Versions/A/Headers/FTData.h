/*
	File:		FTData.h

	Contains:	Wrapper class for CFData

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTDATA__
#define __FTDATA__

#include <iostream>

using namespace std;

#include "FTCoreFoundationType.h"

namespace ftx {
	
	class FTString;
	
	/*! \brief Wrapper for CoreFoundation CFDataRef
	 *
	 *  FTData is a C++ wrapper around CFDataRef
	 *      (and therefore NSData, as well). It simplifies
	 *      creation and manipulation of binary data.
	 *
	 *  Note that FTData is inherently mutable.
	 */

	class FTData : public FTCoreFoundationType {
		
	public:
        static FTData *Adopt(CFMutableDataRef iData);
        static FTData *Retain(CFMutableDataRef iData);
        static FTData *Copy(CFMutableDataRef iData);

		static FTData ConvertHexToData( const FTString& iHexString );
        static FTData ConvertBase64ToData(const FTString& iBase64String );
		
		FTData();
		FTData( const void *iData, size_t iSize );
		FTData( CFDataRef iData );
		FTData( CFMutableDataRef iData, bool iAdopt );
		FTData( const FTData& iOther );
		FTData( CFURLRef iURL );
		virtual ~FTData();
		
		FTData& operator=( const FTData& iOther );
		bool operator==( const FTData& iOther ) const { return !operator!=( iOther ); };
		bool operator!=( const FTData& iOther ) const;
		
		FTData& operator+=( const FTData& iOther );
		FTData& operator+=( const FTString& iString );
		FTData& operator+=( const CFDataRef iData ) { FTData tScratch(iData); return operator+=(tScratch); };
		FTData operator+( const FTData& iOther ) const;
		FTData operator+( const CFDataRef iData ) const { FTData tScratch(iData); return operator+(tScratch); };
		
		operator CFDataRef() const { return _fData; };
		operator CFMutableDataRef() const { return _fData; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fData; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFDataCreateCopy( kCFAllocatorDefault, _fData ); };
		
		CFMutableDataRef GetData() const { return _fData; };
		ItemCount Length() const { return (_fData != nullptr ? ::CFDataGetLength( _fData ) : 0); };
		const void *DataPtr() const { return ::CFDataGetBytePtr( _fData ); };
		uint32_t Checksum() const;

		bool IsASCII() const;
		bool IsUTF8() const;
		
		void AppendBytes(void *iData, ByteCount iLength) { CFDataAppendBytes(_fData, (const UInt8*) iData, iLength); };

		void Add1Zero() { Add1(uint8_t(0)); };
		void Add1(uint8_t iValue);
		void Add1(CFNumberRef iValue);
		void Add2(uint16_t iValue);
		void SwapAndAdd2(uint16_t iValue);
		void SwapAndAdd2(CFNumberRef iValue);
		void SwapAndReplace2At(uint16_t iValue, size_t tPosition);
		void Add4(uint32_t iValue);
		void SwapAndAdd4(uint32_t iValue);
		void SwapAndAdd4(CFNumberRef iValue);
		void SwapAndReplace4At(uint32_t iValue, size_t iPosition);
		void PadTo2();
		void PadTo4();
		
		void IncreaseLength(uint32_t iBytesToAdd);
		
		void WriteToFile(CFURLRef iURL) const;

        FTString    Base64() const;
		FTString	HexString() const;

        // These two functions are intended for Apple-internal use only
        //  and won't work for anybody else
        FTData      DecryptedData() const;
        FTData      EncryptedData() const;

		friend ostream& operator<<( ostream &iOut, const FTData& iObject );
		
	private:
		
		CFMutableDataRef _fData;
		
	};
	
}

#endif
