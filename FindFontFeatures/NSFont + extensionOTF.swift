//
//  NSFont + extensionOTF.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 10/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//

import Foundation
import Cocoa

extension NSFont {
    var openTypeFeaturesCount:Int {
        get {
            return self.openTypeFeatures.types.count
        }
    }
    var openTypeFeatures : OTFFeatures {
        get {
            
            let result = OTFFeatures()
            
            let descriptor = self.fontDescriptor
            if let featureDescriptions = CTFontDescriptorCopyAttribute(descriptor, kCTFontFeaturesAttribute) {
                for type in featureDescriptions  as! [[String:AnyObject]]{
                    
                    let otfType = OTFType(name: type["CTFeatureTypeName"] as! String,
                                          nameID: type["CTFeatureTypeNameID"] as? Int,
                                          identifier: type["CTFeatureTypeIdentifier"]  as! Int,
                                          exclusive: type["CTFeatureTypeExclusive"] as? Int)
                    
                    result.addOTFType(otfType, fromFont:self)
                    
                    for feature in type["CTFeatureTypeSelectors"] as! [[String:AnyObject]] {
                        
                        var name = feature["CTFeatureSelectorName"] as? String
                        if name == nil {
                            
                            name = String(format: "<no name feature>" )
                            
                            
                        }
                        
                        let fea = OTFeature(name:name!,
                                            parent: otfType,
                                            nameID: feature["CTFeatureSelectorNameID"] as? Int,
                                            identifier: feature["CTFeatureSelectorIdentifier"] as! Int,
                                            selDefault: feature["CTFeatureSelectorDefault"] as? Int)
                        result.addFeature(fea, fromFont: self)
                        
                        //print ("added Font")
                        
                    }
                }
                
            }
            return result
        }
    }
    func setOpenTypeFeatures(types:OTFFeatures) {
        
    }
    
    var allChars:String {
        get {
        let charset  = NSMutableCharacterSet(bitmapRepresentation: self.coveredCharacterSet.bitmapRepresentation)
        charset.formIntersectionWithCharacterSet (NSCharacterSet.controlCharacterSet().invertedSet)
        var result = ""
        for plane : UInt8 in 0...16 {
            if charset.hasMemberInPlane( plane ) {
                
                for c : UInt32 in UInt32( plane ) << 16 ..< (UInt32(plane)+1) << 16 {
                    if charset.longCharacterIsMember(c) {
                        var c1 = c.littleEndian // To make it byte-order safe
                        
                        let s = NSString(bytes: &c1, length: 4, encoding: NSUTF32LittleEndianStringEncoding);
                        
                        result += (s != nil ? s! as String : "")
                    }
                }
            }
        }
            return result
        }
        
    }
}
