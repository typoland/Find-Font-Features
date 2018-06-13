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
var otfFeaturesChangedContext = "com.typoland.otf.FeaturesChangedContext"
class OTFOutlineViewDelegate:NSObject ,  NSOutlineViewDelegate, NSOutlineViewDataSource {
    
    @objc var otfFeatures:OTFFeatures = OTFFeatures()
    @IBOutlet weak var table:NSOutlineView!
    
    var selectedFonts:[NSFont] = [NSFont]()
    
    override func awakeFromNib() {
        //Remember thousand times will by repeatesd
        
    }
    
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        print ("observeValue", debugCounter, context as Any, object!)
        debugCounter += 1
        switch context! {
        case &otfFeaturesChangedContext:
            table.reloadData()
        default:
            ()
        }
    }
    
    func outlineView(_ outlineView: NSOutlineView, numberOfChildrenOfItem item: Any?) -> Int {
        
        if item is OTFType {
            return (item as! OTFType).typeSelectors.count
        } else if item is OTFeature {
            return 0
        }
        return otfFeatures.types.count
    }
    
    
    func outlineView(_ outlineView: NSOutlineView, isItemExpandable item: Any) -> Bool {
        //print ("is item expandible", item)
        if  item is OTFType {
            return true
        } else {
            return false
        }
    }
    func outlineView(_ outlineView: NSOutlineView, objectValueFor tableColumn: NSTableColumn?, byItem item: Any?) -> Any? {
        //print("Teraz odda dupę, tylko po co?", item, tableColumn?.identifier)
        return item
    }
    func outlineView(_ outlineView: NSOutlineView, heightOfRowByItem item: Any) -> CGFloat {
        if item is OTFeature {
            return 15
        }
        return 18
    }
    func outlineView(_ outlineView: NSOutlineView, child index: Int, ofItem item: Any?) -> Any {
        //print("childOfItem", item, index)
        if item == nil {
            return otfFeatures.types[index]
        } else {
            //let keys = (item as! LDOpenTypeFeaturesType).featuresString]
            return (item as! OTFType).typeSelectors[index]
        }
    }
    func checkFeatureInSelectedFonts (_ item:OTFeature) -> Bool {

        for font in selectedFonts {
            for type in OTFFeatures.fromFont(font).types {
                if (type as! OTFType).typeSelectors.index(of: item) != NSNotFound {
                    print("znalazł")
                    return true
                }
            }
        }
        print ("Łazi tu", selectedFonts)
        return false
    }
    
    func outlineView(_ outlineView: NSOutlineView, viewFor tableColumn: NSTableColumn?, item: Any) -> NSView? {
        if let columnIdentifier = tableColumn?.identifier{
            //print(columnIdentifier)
            switch columnIdentifier.rawValue {
            case "Features" :
                
                if item is OTFeature {
                    
                    let cell:LDTableCellButton
                    if (item as! OTFeature).parent.exclusive != nil {
                        cell = outlineView.makeView(withIdentifier: NSUserInterfaceItemIdentifier(rawValue: "OTFOption"), owner: self) as! LDTableCellButton

                    } else {
                        cell = outlineView.makeView(withIdentifier: NSUserInterfaceItemIdentifier(rawValue: "OTFeature"), owner: self) as! LDTableCellButton
                    }
                    //cell.checkButton.enabled = checkFeatureInSelectedFonts(item as! OTFeature)

                    //cell.checkButton.integerValue =  0
                    return cell
                    
                } else if item is OTFType {
                    let cell = outlineView.makeView(withIdentifier: NSUserInterfaceItemIdentifier(rawValue: "OTFType"), owner: self) as! NSTableCellView
                    return cell
                }
            case "Additional" :
                let cell = outlineView.makeView(withIdentifier: NSUserInterfaceItemIdentifier(rawValue: "Identifier"), owner: self) as! NSTableCellView
                return cell
                
            default:
                let cell = outlineView.makeView(withIdentifier: NSUserInterfaceItemIdentifier(rawValue: "OTFSearch"), owner: self) as! LDTableCellButton
                if item is OTFeature {
                    cell.checkButton.integerValue = (item as! OTFeature).search
                    cell.checkButton.isEnabled = true
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
    
    @IBAction func searchFontWithFeature (_ sender:AnyObject) {
        print("searchFontWithFeatue", sender)
         print(sender)
        NotificationCenter.default.post(name: Notification.Name(rawValue: setSearchNotification), object: (sender))
        table.reloadData()
       
    
    }
    
    @IBAction func setOnOf(_ sender:AnyObject) {
        print("set On/Off", sender)
        NotificationCenter.default.post(name: Notification.Name(rawValue: setFeatureNotification), object: (sender))
        table.reloadData()
        /*
        let feature = (sender.superview as! NSTableCellView).objectValue as! OTFeature
        feature.selected = Int((sender as! NSButton).intValue)
        print("set on/off", feature.name, feature.selected)
        
 */
    }
    
    @IBAction func selectExclusive(_ sender:AnyObject) {
        print ("Coś robi")
        
        
        let feature = (sender.superview as! NSTableCellView).objectValue as! OTFeature
        
        let type = feature.parent
        type?.selectFeature(feature)
        NotificationCenter.default.post(name: Notification.Name(rawValue: setFeatureNotification), object: (sender))
        table.reloadData()
    }
}



