//
//  OTFeatures.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

class OTF:NSObject {
    var name:String = ""
    var nameID:Int? = 0
    var identifier:Int = 0
    
    var selected:Int = 0
    var search:Int = 0
    var enabled:Bool {get { return false }}
    
    
    
    var toolTip:String {
        get {
            return "\(name) \(self is OTFeature ?  " from \((self as! OTFeature).parent.name)" : "")\n\tindentifier: \(identifier)\n\tname ID: \(nameID == nil ? String(nameID) : "no" )" + "\n\n\tseleced: \(selected == 1 ? "Yes":"No")\n\tsearch: \(search)" //+ ("\n\tHash:\n\(name.hashValue) \n\(identifier.hashValue)")
        }
    }
    override var hash: Int {
        //print ("hash")
        return self.hashValue // if the only field to determine uniqueness is `identifier`, this hashing method is enough
    }
    override func isEqual(object: AnyObject?) -> Bool {
        if let otf = object as? OTF {
            return otf.hashValue == self.hashValue
        }
        return false
    }
    override var hashValue: Int { get {
        return name.hashValue ^ identifier.hashValue ^ (nameID?.hashValue)!
        }
    }
    
    init(name:String, nameID:Int?, identifier:Int) {
        self.name = name
        self.nameID = nameID
        self.identifier = identifier
        
    }
}

class OTFeature:OTF {
    
    var selDefault:Int?;
    var parent:OTFType!
    var isOn:Int = 1
    
    var fonts:NSMutableOrderedSet = NSMutableOrderedSet()
    var searchResult: String { get {return String(fonts.count)} }
    
    override var enabled: Bool {
        get {
            if let selectedFont = (NSApplication.sharedApplication().delegate as! AppDelegate)._selectedFont {
            return fonts.containsObject(selectedFont)
            }
            return false
                
           
        }
    }
        
    override var toolTip: String {
        get {
            var fontNames = "\n\n\t"
            for font in fonts {
                fontNames += "\((font as! NSFont).fontName)\n\t"
            }
            return super.toolTip + "\n\tselector default: \(selDefault != nil ? String(selDefault!) : "no")" + fontNames
        }
    }
    
    
    init (name:String, parent:OTFType, nameID:Int?, identifier:Int, selDefault:Int?) {
        super.init(name: name, nameID: nameID, identifier: identifier)
        self.selDefault = selDefault
        if selDefault == 1 {
            self.selected = 1
        }
        self.parent = parent
    }
}
class OTFType:OTF {
    
    var exclusive:Int?
    var typeSelectors:NSMutableOrderedSet = NSMutableOrderedSet()
    
    override var search:Int {
        get {
            var n = 0
            for feature in typeSelectors {
                n += feature.search
            }
            //print ("get search", n, typeSelectors.count)
            if n == 0 {
                return 0
            } else if n == typeSelectors.count {
                return 1
            }
            //print("returning -1)")
            return -1
        }
        set (value) {
            //print ("set", value)
            for selector in typeSelectors.array as! [OTFeature] {
                selector.willChangeValueForKey("search")
                selector.search = value
                selector.didChangeValueForKey("search")
            }
        }
    }
    
     var searchResult: String {
        get {
            let fonts = NSMutableSet()
            let inSearch = NSMutableSet()
            for feature in  typeSelectors {
                let new = feature.fonts.array
                if feature.search == 1 {
                    inSearch.addObjectsFromArray(new)
                }
                fonts.addObjectsFromArray(new)
            }
            
            let result = String(format: "\(inSearch.count)/\(fonts.count)")
            return result
        }
    }
   
    
    init(name:String, nameID:Int?, identifier:Int, exclusive:Int?) {
        super.init(name: name, nameID: nameID, identifier: identifier)
        self.exclusive = exclusive
        self.typeSelectors = NSMutableOrderedSet()
    }
    
    
    func selectFeature(feature:OTFeature)  {
        for selector in self.typeSelectors.array as! [OTFeature] {
            if (feature == selector) || (feature.identifier == selector.identifier) {
                selector.selected = 1
            } else {
                selector.selected = 0
            }
        }
    }
}

func == (typeA: OTF, typeB: OTF) -> Bool {
    return  (typeA.name == typeB.name) && (typeA.nameID == typeB.nameID) && (typeA.identifier == typeB.identifier)
}



class OTFFeatures:NSObject  {
    
    var types = NSMutableOrderedSet()
    var typesArray:NSArray {
        get {
            return self.types.array
        }
    }
    
    
    class func fromTypes(types:OTFFeatures) -> OTFFeatures {
        let result = OTFFeatures()
        for type in types.types {
            result.types.addObject(type)
        }
        return result
    }
    

    
    
    
    /*
    override func removeObjectAtIndex(idx: Int) {
        self.types.removeObjectAtIndex(idx)
    }
    */
    class func fromAllSystemFonts(size: CGFloat) -> OTFFeatures {
        let result = OTFFeatures()
        for fontName in NSFontManager.sharedFontManager().availableFonts {
            if let font = NSFont(name: fontName, size: size) {
                result.addFontFeatures(OTFFeatures.fromFont(font), fromFont: font)
            }
        }
        return result
    }
    
    class func fromFont(font : NSFont) -> OTFFeatures {
                return font.openTypeFeatures
    }
    
    func removeAllObjects() {
        self.types.removeAllObjects()
    }
    
    /*
    override var count: Int {
        get {
            //print ("counting")
            return types.count
        }
    }
    */
    
    func addFontFeatures(fontFeatures:OTFFeatures, fromFont font :NSFont ){
        for type in fontFeatures.types {
            self.addOTFType(type as! OTFType, fromFont: font)
            for selector in (type as! OTFType).typeSelectors {
                self.addFeature(selector as! OTFeature, fromFont: font)
            }
        }
    }
    
    func addOTFType(newType:OTFType, fromFont:NSFont) {
        self.types.addObject(newType)
 
    }
    /*
    func addObject(anObject: AnyObject) {
        print ("dont't use this method")
        
    }
    */
    func addFeature(feature:OTFeature, fromFont: NSFont) {
        let index = Int(types.indexOfObject(feature.parent))
        
        if index != NSNotFound {
            let type = types.objectAtIndex(index) as! OTFType
            feature.parent = type
            type.typeSelectors.addObject(feature)
            
            let featureIndex = type.typeSelectors.indexOfObject(feature)
            if featureIndex != NSNotFound {
                let savedFeature = type.typeSelectors.objectAtIndex(featureIndex)
                savedFeature.fonts.addObject(fromFont)
            }
        }
    }
    /*
    func objectAtIndex(index: Int) -> AnyObject {
        assert(index < count, "The index is out of bounds")
        return types.objectAtIndex(index)
    }
    */

    
}











