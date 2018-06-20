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
    var typeSelectors: Set<OTFeature> = []
    
    
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
            for selector in typeSelectors {
                selector.willChangeValue(forKey: "search")
                selector.search = value
                selector.didChangeValue(forKey: "search")
            }
        }
    }
    
    @objc var searchResult: String {
        get {
            var fonts:Set<NSFont> = []
            var inSearch:Set<NSFont> = []
            
            for feature in  typeSelectors {
                if (feature ).search == 1 {
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
        //self.typeSelectors = NSMutableOrderedSet()
        self.name = name
    }
    
    
    func selectFeature(_ feature:OTFeature)  {
        for selector in typeSelectors {
            if (feature == selector) || (feature.identifier == selector.identifier) {
                selector.selected = 1
            } else {
                selector.selected = 0
            }
        }
    }
}

func == (typeA: OTFBaseObject, typeB: OTFBaseObject) -> Bool {
    return  (typeA.name == typeB.name) && (typeA.nameID == typeB.nameID) && (typeA.identifier == typeB.identifier)
}

