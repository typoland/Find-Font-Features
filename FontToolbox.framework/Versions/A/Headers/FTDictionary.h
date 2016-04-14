/*
	File:		FTFeatureOptionList.h

	Contains:	Wrapper classes for CFDictionary

	Version:	Mac OS X

	Written by:	The Apple Font Group

	Copyright:	© 2012-2015 by Apple Inc. All rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Peter Lofting

		Technology:			Apple Font Tools

*/

#ifndef __FTDICTIONARY__
#define __FTDICTIONARY__

#include "FTArray.h"
#include "FTCoreFoundationType.h"
#include "FTNumber.h"
#include "FTString.h"

namespace ftx {
	
	class FTURL;
	
	/**
	 * \ingroup Wrapper Classes
	 * @{
	 */

	/*! \brief Wrapper for CoreFoundation CFDictionaryRef
	 *
	 *  FTDictionary is a C++ wrapper around CFDictionaryRef
	 *      (and therefore NSDictionaryRef, as well). It simplifies
	 *      creation of dictionaries.
	 *
	 *  Note that the its keys and values are CFTypeRefs, and
	 *		*not* subclasses of FTCoreFoundationType.
	 *		Use the Cast() function of FTCoreFoundationType
	 *		instances to add items to an FTDictionary.
	 *
	 *	Similarly, use cast operators and constructors
	 *		to turn the contents of an FTDictionary instance
	 *		into other FTCoreFoundationType instances.
	 *
	 *	Some convenience functions are included to avoid
	 *		this necessity in some cases.
	 *
	 *  Note further that FTDictionarys are inherently mutable.
	 */
	
	class FTDictionary : public FTCoreFoundationType {
		
	public:
		
        static FTDictionary *Adopt(CFMutableDictionaryRef iValue);
        static FTDictionary *Retain(CFMutableDictionaryRef iValue);
        static FTDictionary *Copy(CFMutableDictionaryRef iValue);

		FTDictionary();
		FTDictionary( CFMutableDictionaryRef iDictionary, bool iAdopt = false );
		FTDictionary( CFDictionaryRef iDictionary );
		FTDictionary( const FTDictionary& iOther );
		FTDictionary( const FTDictionary* iOther );
		FTDictionary( const FTURL& iURL );
		virtual ~FTDictionary();
		
		void Clear();
		
		FTDictionary operator+( const FTDictionary& iAddend );
		FTDictionary& operator=( const FTDictionary& iOther );
		FTDictionary& operator+=( const FTDictionary& iOther );
		FTDictionary& operator+=( const FTDictionary* iOther );
		
		virtual FTArray	Keys() const;
		
		virtual CFTypeRef operator[](const FTString& iKey) const { return ::CFDictionaryGetValue( _fDictionary, iKey.Cast() ); };
		
		virtual bool HasValueForKey( CFTypeRef iKey ) const;
		virtual bool HasValueForKey( const FTString& iKey ) const { return HasValueForKey(iKey.Cast()); };
		virtual bool HasValueForKey( int64_t iKey ) const { return HasValueForKey(FTNumber(iKey).Cast()); };
		virtual bool HasValueForKey( const char *iKey ) const { return HasValueForKey(FTString(iKey).Cast()); };

		virtual void RemoveValueForKey( CFTypeRef iKey );
		virtual void RemoveValueForKey( const FTString& iKey ) { RemoveValueForKey(iKey.Cast()); };
		virtual void RemoveValueForKey( int64_t iKey ) { RemoveValueForKey(FTNumber(iKey).Cast()); };
		virtual void RemoveValueForKey( const char *iKey ) { RemoveValueForKey(FTString(iKey).Cast()); };

		virtual CFTypeRef ValueForKey( CFTypeRef iKey ) const { return ::CFDictionaryGetValue( _fDictionary, iKey ); };
		virtual CFTypeRef ValueForKey( const FTString& iKey ) const { return ::CFDictionaryGetValue( _fDictionary, iKey.Cast() ); };
		virtual CFTypeRef ValueForKey( int64_t iKey ) const{ return ::CFDictionaryGetValue( _fDictionary, FTNumber(iKey).Cast() ); };
		virtual CFTypeRef ValueForKey( const char *iKey ) const { return ::CFDictionaryGetValue( _fDictionary, FTString(iKey).Cast() ); };
		
		virtual CFStringRef StringForKey( CFStringRef iKey ) const;
		virtual int64_t IntForKey( CFStringRef iKey ) const;
		virtual bool BooleanForKey( CFStringRef iKey ) const;
		
		virtual void SetValueForKey( CFTypeRef iKey, const FTCoreFoundationType* iValue );
		virtual void SetValueForKey( CFTypeRef iKey, CFTypeRef iValue );
		virtual void SetValueForKey( CFTypeRef iKey, const char *iValue );
		virtual void SetValueForKey( CFTypeRef iKey, int64_t iValue );
		virtual void SetValueForKey( int64_t iKey, CFTypeRef iValue );
		virtual void SetIntegerForKey( CFTypeRef iKey, int64_t iValue );
		virtual void SetBooleanForKey( CFTypeRef iKey, bool iValue );
		
		FTString StringForStringKey(const FTString& iKey) const { return FTString(StringForKey(CFStringRef(iKey))); }
		void SetStringForStringKey(const FTString& iKey, const FTString& iValue) { SetValueForKey(iKey.Cast(), iValue.Cast()); };
		
		bool CanMerge( const FTDictionary &iOther ) const;
		bool CanMerge( const FTDictionary *iOther ) const { return CanMerge( *iOther ); };
		
		operator CFDictionaryRef() const { return _fDictionary; };
		operator CFMutableDictionaryRef() const { return _fDictionary; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fDictionary; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFDictionaryCreateCopy( kCFAllocatorDefault, _fDictionary ); };
		
		void ApplyFunction( CFDictionaryApplierFunction iApplier, void *ioContext ) const;
		
	protected:
		CFMutableDictionaryRef Dictionary() const { return _fDictionary; };
		
	private:
		
		CFMutableDictionaryRef _fDictionary;
		
	};
	
	/*! \brief Wrapper for CoreFoundation CFDictionaryRef
	 *
	 *  FTNormalizingDictionary is a C++ wrapper around CFDictionaryRef
	 *      (and therefore NSDictionaryRef, as well). It simplifies
	 *      creation of dictionaries. The difference between this 
	 *		class and FTDictionary is that keys are case-insensitive.
	 *
	 *  Note that it is *not* a subclass of FTDictionary. This is to
	 *		avoid accidentally mistaking one for the other.
	 *
	 *  Note further that the its keys and values are CFTypeRefs, and
	 *		*not* subclasses of FTCoreFoundationType.
	 *		Use the Cast() function of FTCoreFoundationType
	 *		instances to add items to an FTNormalizingDictionary.
	 *
	 *	Similarly, use cast operators and constructors
	 *		to turn the contents of an FTNormalizingDictionary instance
	 *		into other FTCoreFoundationType instances.
	 *
	 *	Some convenience functions are included to avoid
	 *		this necessity in some cases.
	 *
	 *  Note finally that FTNormalizingDictionarys are inherently mutable.
	 */

	class FTNormalizingDictionary : public FTCoreFoundationType
	{
	public:
		FTNormalizingDictionary();
		FTNormalizingDictionary( const FTNormalizingDictionary& iOther );
		FTNormalizingDictionary( const FTNormalizingDictionary *iOther );
		virtual ~FTNormalizingDictionary();
		
		void Clear();
		
		FTNormalizingDictionary& operator=(const FTNormalizingDictionary& iOther );
		FTNormalizingDictionary operator+( const FTNormalizingDictionary& iAddend );
		FTNormalizingDictionary& operator+=( const FTNormalizingDictionary& iOther );
		FTNormalizingDictionary& operator+=( const FTNormalizingDictionary* iOther );
		
		bool CanMerge( const FTNormalizingDictionary &iOther ) const;
		bool CanMerge( const FTNormalizingDictionary *iOther ) const { return CanMerge( *iOther ); };
		
		virtual FTArray	Keys() const;
		
		CFStringRef CanonicalFormForKey(CFStringRef iKey) const;
		CFStringRef CanonicalFormForKey(const FTString& iKey) const;
		
		virtual bool HasValueForKey( CFTypeRef iKey ) const;
		virtual bool HasValueForKey( const char *iKey ) const{ return HasValueForKey(FTString(iKey).Cast()); };
		virtual CFTypeRef ValueForKey( CFTypeRef iKey ) const;
		virtual CFTypeRef ValueForKey( int64_t iKey ) const;
		virtual CFTypeRef ValueForKey( const char *iKey ) const;
		virtual void SetValueForKey( CFTypeRef iKey, const FTCoreFoundationType* iValue );
		virtual void SetValueForKey( CFTypeRef iKey, CFTypeRef iValue );
		virtual void SetValueForKey( CFTypeRef iKey, const char *iValue );
		virtual void SetValueForKey( CFTypeRef iKey, int64_t iValue );
		virtual void SetValueForKey( int64_t iKey, CFTypeRef iValue );
		virtual void SetValueForKey( const char *iKey, const CFTypeRef iValue );
		virtual void SetValueForKey( const char *iKey, int64_t iValue );
		
		void ApplyFunction( CFDictionaryApplierFunction iApplier, void *ioContext ) const;
		void ApplyFunctionToKeys( CFDictionaryApplierFunction iApplier, void *ioContext ) const;
		void ApplyFunctionToValues( CFDictionaryApplierFunction iApplier, void *ioContext ) const;
		
		operator CFDictionaryRef() { return _fDictionary; };
		virtual CFTypeRef Cast() const { return (CFTypeRef) _fDictionary; };
		virtual CFTypeRef Copy() const { return (CFTypeRef) ::CFDictionaryCreateCopy( kCFAllocatorDefault, _fDictionary ); };
		
		friend ostream& operator<<( ostream &iOut, const FTNormalizingDictionary& iObject );
		
	protected:
		CFMutableDictionaryRef Dictionary() const { return _fDictionary; };
		
	private:
		CFMutableDictionaryRef KeyDictionary() const;
		CFMutableDictionaryRef ValueDictionary() const;
		
		CFStringRef CreateNormalizedKey( CFStringRef iString ) const;
		CFStringRef CreateNormalizedKey( const char *iString ) const;
		
		bool HasNormalizedValueForKey( CFStringRef iString ) const;
		void SetNormalizedValueForKey( CFStringRef iKey, CFTypeRef iValue );
		
		CFMutableDictionaryRef _fDictionary;
	};
	
}

#endif /* __FTDICTIONARY__ */
