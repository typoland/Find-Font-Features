//: Playground - noun: a place where people can play

import Cocoa
import CoreText

let font = CTFontCreateWithName("ClanText-News-", 16, nil)
let name = CTFontCopyDisplayName(font)
let familyName = CTFontCopyFamilyName(font)
let characterSet = CTFontCopyCharacterSet(font)
let encoding = CTFontGetGlyphCount(font)
print (characterSet)