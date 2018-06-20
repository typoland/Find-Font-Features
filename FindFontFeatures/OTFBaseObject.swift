//
//  OTFBaseObject.swift
//  Find Font Features
//
//  Created by Łukasz Dziedzic on 19/06/2018.
//  Copyright © 2018 Łukasz Dziedzic. All rights reserved.
//

import Foundation
@objc class OTFBaseObject:NSObject {
    @objc var name:String = ""
    var nameID:Int? = 0
    @objc var identifier:Int = 0
    
    @objc var selected:Int = 0
    @objc var search:Int = 0
    @objc var enabled: Bool { get { return false }}
    
    
    
    @objc var toolTip:String {
        get {
            return "\(name) \(self is OTFeature ?  " from \((self as! OTFeature).parent.name)" : "")\n\tindentifier: \(identifier)\n\tname ID: \(nameID == nil ? String(describing: nameID) : "no" )" + "\n\n\tseleced: \(selected == 1 ? "Yes":"No")\n\tsearch: \(search)" 
        }
    }
    
    override func isEqual(_ object: Any?) -> Bool {
        if let otf = object as? OTFBaseObject {
            return otf.hashValue == self.hashValue
        }
        return false
    }
    
    override var hashValue: Int {
        return name.hashValue //^ (nameID?.hashValue ?? 0)
    }
    
    init(name:String, nameID:Int?, identifier:Int) {
        self.name = name
        self.nameID = nameID
        self.identifier = identifier
        
    }
}
