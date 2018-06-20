//
//  OTFeature.swift
//  Find Font Features
//
//  Created by Łukasz Dziedzic on 19/06/2018.
//  Copyright © 2018 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import AppKit

class OTFeature:OTFBaseObject {
    
    var selDefault:Int?;
    var parent:OTFType
    var isOn:Int = 1
    
    override var hashValue: Int {
        return super.hashValue
    }
    
    @objc var fonts:Set<NSFont> = []
    @objc var searchResult: String { get {return String(fonts.count)} }
    
    override var enabled: Bool {
        get {
            if let selectedFont = (NSApplication.shared.delegate as! AppDelegate)._selectedFont {
                return fonts.contains(selectedFont)
            }
            return false
        }
    }
    
    override var toolTip: String {
        get {
            var fontNames = "\n\n\t"
            for font in fonts {
                fontNames += "\(font.fontName)\n\t"
            }
            return super.toolTip + "\n\tselector default: \(selDefault != nil ? String(selDefault!) : "no")" + fontNames
        }
    }
    
    
    init (name:String, parent:OTFType, nameID:Int, identifier:Int, selDefault:Int) {
        self.parent = parent
        super.init(name: name, nameID: nameID, identifier: identifier)
        self.selDefault = selDefault
        if selDefault == 1 {
            self.selected = 1
        }
        
    }
}
