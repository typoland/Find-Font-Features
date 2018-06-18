//
//  LDSwitchButton.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

@IBDesignable
class LDSwitchButton :NSButton {
    /*
    override func mouseUp(theEvent: NSEvent) {
        //super.mouseDown(theEvent)
        //self.willChangeValueForKey("intValue")
        Swift.print ("Bin", self.intValue)
        if self.state != NSMixedState {
            if self.state == NSOnState {self.state = NSOffState}
            else {self.state = NSOnState }
        } else {
            self.state = NSOffState
        }
        Swift.print( self.intValue)
        Swift.print ("BOut", self.intValue)
        //self.didChangeValueForKey("intValue")
        self.needsDisplay = true
    }
    */
    @IBInspectable var switchGap:CGFloat = 1.5
    @IBInspectable var outlineWidth:CGFloat = 1
    @IBInspectable var margin:CGFloat = 2
    
    override func draw(_ dirtyRect: NSRect) {
        
        NSColor.lightGray.set()
        NSBezierPath.defaultLineWidth = outlineWidth
        let shape = NSBezierPath(roundedRect: NSMakeRect(outlineWidth/2, outlineWidth/2, dirtyRect.width-outlineWidth, dirtyRect.height-outlineWidth), xRadius: dirtyRect.height/2-outlineWidth, yRadius: dirtyRect.height/2-outlineWidth)
        if self.intValue == 1{
            NSColor.white.set()
            
        } else {
            NSColor.windowBackgroundColor.set()
        }
        shape.fill()
        NSColor.lightGray.set()

        shape.stroke()
        
        let offset:CGFloat
        let height = dirtyRect.height-(switchGap*2)-(outlineWidth*2)
        switch (self.intValue, self.isEnabled) {
        case (1, true): ()
            
        default: ()
        }
        
        if self.intValue == 0 {
            offset = switchGap+outlineWidth
            NSColor.white.set()
        } else {
            offset = dirtyRect.width-(height + switchGap + outlineWidth)
            NSColor.gray.set()
        }
        
        let label:NSMutableAttributedString
        let font:NSFont = NSFont.menuFont(ofSize: dirtyRect.height - 2*switchGap - 2*outlineWidth)
        let labelRect:NSRect
        switch self.intValue {
        case 1:
            label = NSMutableAttributedString(string: title, attributes: [NSAttributedStringKey.font : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+margin,
                                              dirtyRect.origin.y,
                                              dirtyRect.width-switchGap*2 - outlineWidth*2 - margin - height,
                                              dirtyRect.height)
        case -1:
            label = NSMutableAttributedString(string: title, attributes: [NSAttributedStringKey.font : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+margin/2,
                                   dirtyRect.origin.y,
                                   dirtyRect.width-switchGap*2 - outlineWidth*2 - margin/2 - height,
                                   dirtyRect.height)
        default:
            label = NSMutableAttributedString(string: alternateTitle, attributes: [NSAttributedStringKey.font : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+height,
                                dirtyRect.origin.y,
                                dirtyRect.width-switchGap*2 - outlineWidth*2 - margin*2-height,
                                dirtyRect.height)
            
        }
        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.alignment = NSTextAlignment.center
        label.addAttribute(NSAttributedStringKey.paragraphStyle, value: paragraphStyle, range: NSRange(location: 0,length: label.length))
        
        label.draw(in: labelRect)
        
        
        if intValue != -1 {
        NSColor.gray.set()
        NSBezierPath(ovalIn: NSMakeRect(offset,  switchGap+outlineWidth , height, height)).fill()
        }
    }
}
