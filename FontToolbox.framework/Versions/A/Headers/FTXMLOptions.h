/*
	File:		FTXMLOptions.h

	Contains:	A class to hold parameters controlling XML output

	Version:	MacOS X

	Copyright:	© 2013-2015 by Apple Inc., all rights reserved.

	File Ownership:

		DRI:				John Jenkins

		Other Contact:		Julio Gonzalez

		Technology:			Apple Font Tools

	Writers:

		(JHJ)	John Jenkins

 */

#ifndef __FTXMLOPTIONS__
#define __FTXMLOPTIONS__

#include <iostream>

namespace ftx {

	class FTXMLOptions {

	public:
		/*! \brief A class used to control XML output
		 *
		 *  FTXMLOptions provides a mechanism for
		 *		controlling possible output options
		 *		when generating XML using a single
		 *		object. This simplifies the task of
		 *		to minimize the parameters passed
		 *		to XML-generating functions.
		 */
		
		FTXMLOptions();
		FTXMLOptions(const FTXMLOptions& iOther);
		virtual ~FTXMLOptions();
		FTXMLOptions& operator=(const FTXMLOptions& iOther);

		bool operator!=(const FTXMLOptions& iOther) const;
		bool operator==(const FTXMLOptions& iOther) const { return !operator!=(iOther); };

		bool	IncludeGlyphNames() const { return _fIncludeGlyphNames; };
		void	SetIncludeGlyphNames(bool iValue) { _fIncludeGlyphNames = iValue; };

		bool	IncludeCharacterNames() const { return _fIncludeCharacterNames; };
		void	SetIncludeCharacterNames(bool iValue) { _fIncludeCharacterNames = iValue; };

		bool	GenerateCompactOutput() const { return _fGenerateCompactOutput; };
		void	SetGenerateCompactOutput(bool iValue) { _fGenerateCompactOutput = iValue; };

		bool	GenerateMinimalXML() const { return _fGenerateMinimalXML; };
		void	SetGenerateMinimalXML(bool iValue) { _fGenerateMinimalXML = iValue; };

		bool	IncludeNameTableStrings() const { return _fIncludeNameTableStrings; };
		void	SetIncludeNameTableStrings(bool iValue) { _fIncludeNameTableStrings = iValue; };

		bool	CompatibilityMode() const { return _fCompatibilityMode; };
		void	SetCompatibilityMode(bool iValue) { _fCompatibilityMode = iValue; };

		bool	OmitStamp() const { return _fOmitStamp; };
		void	SetOmitStamp(bool iValue) { _fOmitStamp = iValue; };

	protected:

	private:
		bool _fIncludeGlyphNames;
		bool _fIncludeCharacterNames;
		bool _fGenerateCompactOutput;
		bool _fGenerateMinimalXML;
		bool _fIncludeNameTableStrings;
		bool _fCompatibilityMode;
		bool _fOmitStamp;

	};
	
}

#endif /* __FTXMLOPTIONS__ */
