//
//  OTFeatures.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa



class OTFFeatures:NSObject  {
    
    var types:Set<OTFType> = []
    
    var typesArray:NSArray {
        get {
            return [OTFType](self.types) as NSArray
        }
    }
    
    /*
    class func fromFeatures(_ features:OTFFeatures) -> OTFFeatures {
        let result = OTFFeatures()
        for feature in features.types {
            result.types.insert(feature)
        }
        return result
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
        self.types.removeAll()
    }
    
    
    func addFontFeatures(_ fontFeatures:OTFFeatures, fromFont font :NSFont ){
        for type in fontFeatures.types {
            self.types.insert(type)
            for selector in type.typeSelectors {
                self.addFeature(selector , fromFont: font)
            }
        }
    }

    
    func addFeature(_ feature:OTFeature, fromFont: NSFont) {
        if types.contains(feature.parent) {
            let type = feature.parent
            feature.parent.typeSelectors.insert(feature)
           
            if type.typeSelectors.contains(feature) {
                feature.fonts.insert(fromFont)
            }
        }
    }
}

