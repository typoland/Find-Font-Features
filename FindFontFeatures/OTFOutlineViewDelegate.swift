//
//  OTFOutlineViewDelegate.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

let setSearchNotification = "com.typoland.otf.setSearchNotification"
let setFeatureNotification = "com.typoland.otf.setFeatureNotification"
var otfFeaturesChangedContext = "com.typoland.otf.otffeaturesChanged"
class OTFOutlineViewDelegate:NSObject ,  NSOutlineViewDelegate, NSOutlineViewDataSource {
    
    var otfFeatures:OTFFeatures = OTFFeatures()
    @IBOutlet weak var table:NSOutlineView!
    
    var selectedFonts:[NSFont] = [NSFont]()
    
    override func awakeFromNib() {
        //Remember thousand times will by repeatesd
        
    }
    
    override func observeValueForKeyPath(keyPath: String?, ofObject object: AnyObject?, change: [String : AnyObject]?, context: UnsafeMutablePointer<Void>) {
        print(debugCounter, context, object)
        debugCounter += 1
        switch context {
        case &otfFeaturesChangedContext:
            table.reloadData()
        default:
            ()
        }
    }
    
    func outlineView(outlineView: NSOutlineView, numberOfChildrenOfItem item: AnyObject?) -> Int {
        
        if item is OTFType {
            return (item as! OTFType).typeSelectors.count
        } else if item is OTFeature {
            return 0
        }
        return otfFeatures.types.count
    }
    
    
    func outlineView(outlineView: NSOutlineView, isItemExpandable item: AnyObject) -> Bool {
        //print ("is item expandible", item)
        if  item is OTFType {
            return true
        } else {
            return false
        }
    }
    func outlineView(outlineView: NSOutlineView, objectValueForTableColumn tableColumn: NSTableColumn?, byItem item: AnyObject?) -> AnyObject? {
        //print("Teraz odda dupę, tylko po co?", item, tableColumn?.identifier)
        return item
    }
    func outlineView(outlineView: NSOutlineView, heightOfRowByItem item: AnyObject) -> CGFloat {
        if item is OTFeature {
            return 15
        }
        return 18
    }
    func outlineView(outlineView: NSOutlineView, child index: Int, ofItem item: AnyObject?) -> AnyObject {
        //print("childOfItem", item, index)
        if item == nil {
            return otfFeatures.types[index]
        } else {
            //let keys = (item as! LDOpenTypeFeaturesType).featuresString]
            return (item as! OTFType).typeSelectors[index]
        }
    }
    func checkFeatureInSelectedFonts (item:OTFeature) -> Bool {

        for font in selectedFonts {
            for type in OTFFeatures.fromFont(font).types {
                if (type as! OTFType).typeSelectors.indexOfObject(item) != NSNotFound {
                    print("znalazł")
                    return true
                }
            }
        }
        print ("Łazi tu", selectedFonts)
        return false
    }
    
    func outlineView(outlineView: NSOutlineView, viewForTableColumn tableColumn: NSTableColumn?, item: AnyObject) -> NSView? {
        if let columnIdentifier = tableColumn?.identifier{
            //print(columnIdentifier)
            switch columnIdentifier {
            case "Features" :
                
                if item is OTFeature {
                    
                    let cell:LDTableCellButton
                    if (item as! OTFeature).parent.exclusive != nil {
                        cell = outlineView.makeViewWithIdentifier("OTFOption", owner: self) as! LDTableCellButton

                    } else {
                        cell = outlineView.makeViewWithIdentifier("OTFeature", owner: self) as! LDTableCellButton
                    }
                    //cell.checkButton.enabled = checkFeatureInSelectedFonts(item as! OTFeature)

                    //cell.checkButton.integerValue =  0
                    return cell
                    
                } else if item is OTFType {
                    let cell = outlineView.makeViewWithIdentifier("OTFType", owner: self) as! NSTableCellView
                    return cell
                }
            case "Additional" :
                let cell = outlineView.makeViewWithIdentifier("Identifier", owner: self) as! NSTableCellView
                return cell
                
            default:
                let cell = outlineView.makeViewWithIdentifier("OTFSearch", owner: self) as! LDTableCellButton
                if item is OTFeature {
                    cell.checkButton.integerValue = (item as! OTFeature).search
                    cell.checkButton.enabled = true
                    cell.checkButton.allowsMixedState = false
                    return cell
                } else if item is OTFType {
                    cell.checkButton.integerValue = (item as! OTFType).search
                    
                }
                return cell
                
            }
            
        }
        return nil
        
    }
    
    @IBAction func searchFontWithFeature (sender:AnyObject) {
        print("searchFontWithFeatue", sender)
         print(sender)
        NSNotificationCenter.defaultCenter().postNotificationName(setSearchNotification, object: (sender))
        table.reloadData()
       
    
    }
    
    @IBAction func setOnOf(sender:AnyObject) {
        print("set On/Off", sender)
        NSNotificationCenter.defaultCenter().postNotificationName(setFeatureNotification, object: (sender))
        table.reloadData()
        /*
        let feature = (sender.superview as! NSTableCellView).objectValue as! OTFeature
        feature.selected = Int((sender as! NSButton).intValue)
        print("set on/off", feature.name, feature.selected)
        
 */
    }
    
    @IBAction func selectExclusive(sender:AnyObject) {
        print ("Coś robi")
        
        
        let feature = (sender.superview as! NSTableCellView).objectValue as! OTFeature
        
        let type = feature.parent
        type.selectFeature(feature)
        NSNotificationCenter.defaultCenter().postNotificationName(setFeatureNotification, object: (sender))
        table.reloadData()
    }
}



