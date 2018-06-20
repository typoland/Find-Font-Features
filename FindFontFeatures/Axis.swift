//
//  Axis.swift
//  Find Font Features
//
//  Created by Łukasz Dziedzic on 20/06/2018.
//  Copyright © 2018 Łukasz Dziedzic. All rights reserved.
//

import Foundation
@objc class Axis:NSObject {
    enum Keys:String {
        case id = "NSCTVariationAxisIdentifier"
        case name = "NSCTVariationAxisName"
        case minValue = "NSCTVariationAxisMinimumValue"
        case defaultValue = "NSCTVariationAxisDefaultValue"
        case maxValue = "NSCTVariationAxisMaximumValue"
        
    }
    @objc var name:String
    @objc var identifier:Int
    @objc var minValue:Double
    @objc var maxValue:Double
    @objc var defaultValue:Double
    @objc var currentValue:Double
    
    init(identifier:Int, name: String, min:Double, default:Double, max:Double) {
        self.identifier = identifier
        self.name = name
        self.minValue = min
        self.defaultValue = `default`
        self.currentValue = `default`
        self.maxValue = max
    }
}

extension Axis {
    var dict:[String:Any] {
        return [Keys.id.rawValue:identifier as CFNumber as Any,
                Keys.name.rawValue: name as  Any,
                Keys.minValue.rawValue: minValue as CFNumber as Any,
                Keys.defaultValue.rawValue: currentValue as CFNumber as Any,
                Keys.maxValue.rawValue: maxValue as CFNumber as Any
        ]
    }
}

extension Axis {
    override var description: String {
        return "id: \(identifier), name: \(name) \(minValue)...\(defaultValue)...\(maxValue) [\(currentValue)] "
    }
}
