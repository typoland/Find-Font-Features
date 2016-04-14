/*
	File:			FTReporter.h
 
	Contains:		Utility functions for Font Toolbox clients
 
	Version:		Mac OS X
 
	Written by:		The Apple Font Group
 
	Copyright:		Copyright © 2008-2015 by Apple Inc. All rights reserved.
 
	File Ownership:
 
		DRI:			John Jenkins
 
		Other Contact:	Peter Lofting
 
		Technology:		Apple Font Tools
 
	Writers:
 
		(JHJ)	John Jenkins
 
*/

#ifndef __FTUTILITIES__
#define __FTUTILITIES__

#include <Carbon/Carbon.h>

namespace ftx {

    class FTFont_sfnt;
	class FTOutputStream;
	class FTString;
	
	class FTReporter {
		
	public:
        static FTString         XMLStamp(const FTFont_sfnt *iFont);
		static CFStringRef		GetBuildNumber();
		static uint16_t			GetBuildNumberAsInteger();
		static CFRange			RangeIntersect(CFRange iRange1, CFRange iRange2);
		
		static void				ReportError( const char *iFormatString,... );
		static void				IssueWarning( const char *iFormatString,... );
		static void				OutputDebugString( CFStringRef iTag, const char *iFormatString,... );
		static void				Printf( const char *iFormatString,... );
		
		static void				ReportError( const char *iFormatString, va_list iList );
		static void				IssueWarning( const char *iFormatString, va_list iList );
		static void				OutputDebugString( CFStringRef iTag, const char *iFormatString, va_list iList );
		static void				Printf( const char *iFormatString, va_list iList );
		
		static void				SetErrorStream( FTOutputStream *iStream );
		static FTOutputStream*	GetErrorStream();
		static void				SetWarningStream( FTOutputStream *iStream );
		static FTOutputStream*	GetWarningStream();
		static void				SetOutputStream( FTOutputStream *iStream );
		static FTOutputStream*	GetOutputStream();
		static void				SetDebugStream( FTOutputStream *iStream );
		static FTOutputStream*	GetDebugStream();

        static void             SetToolName(const FTString& iToolName, int iToolBuild);
        static FTString         ToolName();
        static int              ToolBuild() { return fgToolBuild; };
		
		static void				SuppressWarnings();
		static void				UnsuppressWarnings();
		static bool				WarningsSuppressed();
		
		static void				SetDebuggingTag(CFStringRef iTag);
		static void				ClearDebuggingTag(CFStringRef iTag);
		static bool				DebuggingTagSet(CFStringRef iTag);

	private:
		static void				OutputString( FTOutputStream *iStream, CFStringRef iFormat, CFStringRef iPrepend, va_list iList );

        static FTString         fgToolName;
        static int              fgToolBuild;
	};
			
	
	
	//===========================================================
	//	Stolen from CarbonCore/FixMath.h
	//	We have it here to eliminate deprecation warnings
	//===========================================================
	
#define FTFixed1              ((FTFixed) 0x00010000L)
	
	/*  The _FTIntSaturate macro converts a float to an int with saturation:
	 If x <= -2**31, the result is 0x80000000.
	 If -2**31 < x < 2**31, the result is x truncated to an integer.
	 If 2**31 <= x, the result is 0x7fffffff.
	 */
#if (defined (__i386__) || defined(__x86_64__)) && __GNUC__
    // For comments, see the annotated version below.
#define _FTIntSaturate(x)     ({                  \
int _FTResult = (int) (x);                    \
__asm__("                                   \
ucomisd %[LimitFloat], %[xx]    \n  \
cmovae  %[LimitInt], %[_FTResult] "   \
:   [_FTResult] "+r" (_FTResult)            \
:   [LimitFloat] "mx" (0x1p31),     \
[LimitInt] "mr" (0x7fffffff),       \
[xx] "x" ((double)(x))          \
:   "cc"                                \
);                                      \
_FTResult; })
    /*
	 // Assume result will be x.
	 int _FTResult = (x);
	 __asm__("
	 // Compare x to the floating-point limit.
	 ucomisd %[LimitFloat], %[xx]    \n
	 // If xx is too large, set _FTResult to the integer limit.
	 cmovae  %[LimitInt], %[_FTResult]
	 // _FTResult is input and output, in a general register.
	 :   [_FTResult] "+r" (_FTResult)
	 // LimitFloat is 0x1p31f and may be in memory or an XMM
	 // register.
	 :   [LimitFloat] "mx" (0x1p31f),
	 // LimitInt is 0x7fffffff and may be in memory or a general
	 // register.
	 [LimitInt] "mr" (0x7fffffff),
	 // xx is x and must be in an XMM register.
	 [xx] "x" ((double)(x))
	 // The condition code is changed.
	 :   "cc"
	 );
	 // Return _FTResult.
	 _FTResult;
	 */
#elif defined __ppc__ || __ppc64__
#define _FTIntSaturate(x) ((int) (x))
#else
    // #error "Unknown architecture."
    // To use unoptimized standard C code, remove above line.
#define _FTIntSaturate(x) ((x) <= -0x1p31f ? (int) -0x80000000 : \
0x1p31f <= (x) ? (int) 0x7fffffff : (int) (x))
#endif
#define FTFloatToFixed(a) (_FTIntSaturate((a) * FTFixed1))
#define FTFixedToInt(a)       ((short)(((Fixed)(a) + FTFixed1/2) >> 16))
#define FTIntToFixed(a)       ((Fixed)(a) << 16)
#define FTFixedToFloat(a)     ((float)(a) / FTFixed1)
	
}

#endif /* __FTUTILITIES__ */
