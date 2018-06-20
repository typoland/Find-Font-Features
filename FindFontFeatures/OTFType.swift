//
//  OTFType.swift
//  Find Font Features
//
//  Created by Łukasz Dziedzic on 19/06/2018.
//  Copyright © 2018 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import AppKit

@objc class OTFType:OTFBaseObject {
    
    var exclusive:Int?
    var features: Set<OTFeature> = []
    
    
    override var search:Int {
        get {
            var n = 0
            for feature in features {
                n += feature.search
            }
            //print ("get search", n, typefeatures.count)
            if n == 0 {
                return 0
            } else if n == features.count {
                return 1
            }
            //print("returning -1)")
            return -1
        }
        set (value) {
            for feature in features {
                feature.willChangeValue(forKey: "search")
                feature.search = value
                feature.didChangeValue(forKey: "search")
            }
        }
    }
    
    @objc var searchResult: String {
        get {
            var fonts:Set<NSFont> = []
            var inSearch:Set<NSFont> = []
            
            for feature in features {
                if feature.search == 1 {
                    inSearch = inSearch.union(feature.fonts)
                }
                fonts = fonts.union(inSearch)
            }
            
            let result = String(format: "\(inSearch.count)/\(fonts.count)")
            return result
        }
    }
    
    
    init(name:String, nameID:Int?, identifier:Int, exclusive:Int?) {
        super.init(name: name, nameID: nameID, identifier: identifier)
        self.exclusive = exclusive
        //self.typefeatures = NSMutableOrderedSet()
        self.name = name
    }
    
    
    func selectFeature(_ feature:OTFeature)  {
        for feature in features {
            if (feature == feature) || (feature.identifier == feature.identifier) {
                feature.selected = 1
            } else {
                feature.selected = 0
            }
        }
    }
}

func == (typeA: OTFBaseObject, typeB: OTFBaseObject) -> Bool {
    return  (typeA.name == typeB.name) && (typeA.nameID == typeB.nameID) && (typeA.identifier == typeB.identifier)
}

