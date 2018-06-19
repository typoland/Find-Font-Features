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
    
    override func viewWillDraw() {
        if objectValue is OTFType{
            checkButton.allowsMixedState = false
        }
        //Swift.print ("viewWill Draw", objectValue)
    }
    
}
