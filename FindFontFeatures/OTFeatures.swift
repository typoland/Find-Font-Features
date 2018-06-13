//
//  OTFeatures.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

@objc class OTF:NSObject {
    @objc var name:String = ""
    var nameID:Int? = 0
   @objc var identifier:Int = 0
    
    @objc var selected:Int = 0
    @objc var search:Int = 0
    @objc var enabled:Bool {get { return false }}
    
    
    
    @objc var toolTip:String {
        get {
            return "\(name) \(self is OTFeature ?  " from \((self as! OTFeature).parent.name)" : "")\n\tindentifier: \(identifier)\n\tname ID: \(nameID == nil ? String(describing: nameID) : "no" )" + "\n\n\tseleced: \(selected == 1 ? "Yes":"No")\n\tsearch: \(search)" //+ ("\n\tHash:\n\(name.hashValue) \n\(identifier.hashValue)")
        }
    }
    override var hash: Int {
        //print ("hash")
        return self.hashValue // if the only field to determine uniqueness is `identifier`, this hashing method is enough
    }
    override func isEqual(_ object: Any?) -> Bool {
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
    
    @objc var fonts:NSMutableOrderedSet = NSMutableOrderedSet()
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

@objc class OTFType:OTF {
    
    var exclusive:Int?
    var typeSelectors:NSMutableOrderedSet = NSMutableOrderedSet()
    
    override var search:Int {
        get {
            var n = 0
            for feature in typeSelectors {
                n += (feature as! OTFeature).search
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
                selector.willChangeValue(forKey: "search")
                selector.search = value
                selector.didChangeValue(forKey: "search")
            }
        }
    }
    
     @objc var searchResult: String {
        get {
            let fonts = NSMutableSet()
            let inSearch = NSMutableSet()
            for feature in  typeSelectors {
                let new = (feature as AnyObject).fonts.array
                if (feature as! OTFeature).search == 1 {
                    inSearch.addObjects(from: new)
                }
                fonts.addObjects(from: new)
            }
            
            let result = String(format: "\(inSearch.count)/\(fonts.count)")
            return result
        }
    }
   
    
    init(name:String, nameID:Int?, identifier:Int, exclusive:Int?) {
        super.init(name: name, nameID: nameID, identifier: identifier)
        self.exclusive = exclusive
        self.typeSelectors = NSMutableOrderedSet()
        self.name = name
    }
    
    
    func selectFeature(_ feature:OTFeature)  {
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
            return self.types.array as NSArray
        }
    }
    
    
    class func fromTypes(_ types:OTFFeatures) -> OTFFeatures {
        let result = OTFFeatures()
        for type in types.types {
            result.types.add(type)
        }
        return result
    }
    

    
    
    
    /*
    override func removeObjectAtIndex(idx: Int) {
        self.types.removeObjectAtIndex(idx)
    }
    */
    class func fromAllSystemFonts(_ size: CGFloat) -> OTFFeatures {
        let result = OTFFeatures()
        for fontName in NSFontManager.shared.availableFonts {
            if let font = NSFont(name: fontName, size: size) {
                result.addFontFeatures(OTFFeatures.fromFont(font), fromFont: font)
            }
        }
        return result
    }
    
    class func fromFont(_ font : NSFont) -> OTFFeatures {
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
    
    func addFontFeatures(_ fontFeatures:OTFFeatures, fromFont font :NSFont ){
        for type in fontFeatures.types {
            self.addOTFType(type as! OTFType, fromFont: font)
            for selector in (type as! OTFType).typeSelectors {
                self.addFeature(selector as! OTFeature, fromFont: font)
            }
        }
    }
    
    func addOTFType(_ newType:OTFType, fromFont:NSFont) {
        self.types.add(newType)
 
    }
    /*
    func addObject(anObject: AnyObject) {
        print ("dont't use this method")
        
    }
    */
    func addFeature(_ feature:OTFeature, fromFont: NSFont) {
        let index = Int(types.index(of: feature.parent))
        
        if index != NSNotFound {
            let type = types.object(at: index) as! OTFType
            feature.parent = type
            type.typeSelectors.add(feature)
            
            let featureIndex = type.typeSelectors.index(of: feature)
            if featureIndex != NSNotFound {
                let savedFeature = type.typeSelectors.object(at: featureIndex)
                (savedFeature as AnyObject).fonts.add(fromFont)
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











