#
#	Generates useful lldb summaries for ftx classes
#	To use this, add the following line to your ~/.lldbinit
#		command script import "/AppleInternal/Library/Application Support/Apple/Font Tools/FTSummaries.py"
#

import lldb;

def ftstring_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fString').GetSummary()

def ftset_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fSet').GetSummary()

def ftarray_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fArray').GetSummary()

def ftdictionary_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fDictionary').GetSummary()

def ftdata_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fData').GetSummary()

def ftnumber_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fNumber').GetSummary()

def fturl_summary(value_object,dictionary):
	return value_object.GetChildMemberWithName('_fURL').GetSummary()

def ftunichar_summary(value_object,dictionary):
	return "U+{0:0>4x}".format(value_object.GetChildMemberWithName('_fURL')).upper()

def __lldb_init_module(debugger,dict):
	debugger.HandleCommand('type summary add ftx::FTString --python-function FTSummaries.ftstring_summary')
	debugger.HandleCommand('type summary add ftx::FTSet --python-function FTSummaries.ftset_summary')
	debugger.HandleCommand('type summary add ftx::FTArray --python-function FTSummaries.ftarray_summary')
	debugger.HandleCommand('type summary add ftx::FTDictionary --python-function FTSummaries.ftdictionary_summary')
	debugger.HandleCommand('type summary add ftx::FTData --python-function FTSummaries.ftdata_summary')
	debugger.HandleCommand('type summary add ftx::FTNumber --python-function FTSummaries.ftnumber_summary')
	debugger.HandleCommand('type summary add ftx::FTURL --python-function FTSummaries.fturl_summary')
	debugger.HandleCommand('type summary add ftx::FTUniChar --python-function FTSummaries.ftunichar_summary')

