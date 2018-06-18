//
//  LDTableCellButton.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

@IBDesignable
class LDTableCellButton: NSTableCellView {
    @IBOutlet weak var checkButton:NSButton!
    override func draw(_ dirtyRect: NSRect) {
        Swift.print("HERE IS A OBJECT", objectValue)
        NSColor.blue.set()
        NSBezierPath(rect: dirtyRect).fill()
    }
}
