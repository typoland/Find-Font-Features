//: Playground - noun: a place where people can play

import Cocoa
import Foundation
var str = "Hello, playground"

let font = NSFont.boldSystemFontOfSize(12)
let charset  = font.coveredCharacterSet
print (charset )
for var plane : UInt8 in 0...16 {
    if charset.hasMemberInPlane( plane ) {
        var c : UTF32Char;
        
        for var c : UInt32 = UInt32( plane ) << 16; c < (UInt32(plane)+1) << 16; c += 1 {
            if charset.longCharacterIsMember(c) {
                var c1 = c.littleEndian // To make it byte-order safe
                let s = NSString(bytes: &c1, length: 4, encoding: NSUTF32LittleEndianStringEncoding);
                NSLog("Char: \(s)");
            }
        }
    }
}
//-coveredCharacterSet.
