//
//  LDSwitchButton.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

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
    override func drawRect(dirtyRect: NSRect) {
        //Swift.print(dirtyRect)
        let switchGap:CGFloat = 1.5
        let outlineWidth:CGFloat = 1
        let margin:CGFloat = 2
        /*
        struct Colors {
            let background:NSColor
            let outline:NSColor
            let `switch`: NSColor
            init (background:NSColor, outline:NSColor, `switch`:NSColor) {
            self.background = background
                self.outline = outline
                self.`switch` = `switch`
            }
        
        }
        
        let ButtonColors = (
            enabledOn:Colors = Colors(background:NSColor.whiteColor(), outline:NSColor.lightGrayColor(), switch:NSColor.darkGrayColor())
            let enabledOff:Colors = Colors(background:NSColor.windowBackgroundColor(), outline:NSColor.lightGrayColor(),switch:NSColor.darkGrayColor())
            let enabledMix:Colors

            let disabledOn:Colors
            let disabledOff:Colors
            let disabledMix:Colors
        )
        */
        NSColor.lightGrayColor().set()
        NSBezierPath.setDefaultLineWidth(outlineWidth)
        let shape = NSBezierPath(roundedRect: NSMakeRect(outlineWidth/2, outlineWidth/2, dirtyRect.width-outlineWidth, dirtyRect.height-outlineWidth), xRadius: dirtyRect.height/2-outlineWidth, yRadius: dirtyRect.height/2-outlineWidth)
        if self.intValue == 1{
            NSColor.whiteColor().set()
            
        } else {
            NSColor.windowBackgroundColor().set()
        }
        shape.fill()
        NSColor.lightGrayColor().set()

        shape.stroke()
        
        let offset:CGFloat
        let height = dirtyRect.height-(switchGap*2)-(outlineWidth*2)
        switch (self.intValue, self.enabled) {
        case (1, true): ()
            
        default: ()
        }
        
        if self.intValue == 0 {
            offset = switchGap+outlineWidth
            NSColor.whiteColor().set()
        } else {
            offset = dirtyRect.width-(height + switchGap + outlineWidth)
            NSColor.grayColor().set()
        }
        
        let label:NSMutableAttributedString
        let font:NSFont = NSFont.menuFontOfSize(dirtyRect.height - 2*switchGap - 2*outlineWidth)
        let labelRect:NSRect
        switch self.intValue {
        case 1:
            label = NSMutableAttributedString(string: title, attributes: [NSFontAttributeName : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+margin,
                                              dirtyRect.origin.y,
                                              dirtyRect.width-switchGap*2 - outlineWidth*2 - margin - height,
                                              dirtyRect.height)
        case -1:
            label = NSMutableAttributedString(string: title, attributes: [NSFontAttributeName : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+margin/2,
                                   dirtyRect.origin.y,
                                   dirtyRect.width-switchGap*2 - outlineWidth*2 - margin/2 - height,
                                   dirtyRect.height)
        default:
            label = NSMutableAttributedString(string: alternateTitle, attributes: [NSFontAttributeName : font])
            labelRect = NSMakeRect(dirtyRect.origin.x+switchGap+outlineWidth+height,
                                dirtyRect.origin.y,
                                dirtyRect.width-switchGap*2 - outlineWidth*2 - margin*2-height,
                                dirtyRect.height)
            
        }
        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.alignment = NSTextAlignment.Center
        label.addAttribute(NSParagraphStyleAttributeName, value: paragraphStyle, range: NSRange(location: 0,length: label.length))
        
        //let labelRect:NSRect = dirtyRect
        label.drawInRect(labelRect)
        
        
        if intValue != -1 {
        NSColor.grayColor().set()
        NSBezierPath(ovalInRect: NSMakeRect(offset,  switchGap+outlineWidth , height, height)).fill()
        }
    }
}