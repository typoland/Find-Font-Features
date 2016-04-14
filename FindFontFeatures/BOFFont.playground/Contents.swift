//: Playground - noun: a place where people can play

import Cocoa
import FontToolbox

var str = "Hello, playground"
let url  = NSURL(fileURLWithPath: "/Users/lukasz/Library/Fonts/ClanSerif/ClanHeaBlaCom.otf")
let container = BOFFontContainer(URL: url, isReadOnly: true)
let bofFont = BOFFont(fontContainer: container, index: 0 )
print (bofFont)
