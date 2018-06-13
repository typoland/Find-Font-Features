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
    @objc var openTypeFeaturesCount:Int {
        get {
            return self.openTypeFeatures.types.count
        }
    }
    @objc var openTypeFeatures : OTFFeatures {
        get {
            
            let result = OTFFeatures()
            
            let descriptor = self.fontDescriptor
            if let featureDescriptions = CTFontDescriptorCopyAttribute(descriptor, kCTFontFeaturesAttribute) {
                for featureType in featureDescriptions  as! [[String:AnyObject]]{
                    let name = featureType["CTFeatureTypeName"] as? String ?? "No Name"
                    let nameID = featureType["CTFeatureTypeNameID"] as? Int ?? 0
                    let identifier = featureType["CTFeatureTypeIdentifier"]  as? Int ?? 0
                    let exclusive = featureType["CTFeatureTypeExclusive"] as? Int ?? 0
                    //Swift.print ("\(name), \(nameID), \(identifier), \(exclusive)")
                    let otfType = OTFType(name:name,
                                          nameID: nameID,
                                          identifier: identifier,
                                          exclusive: exclusive)
                    
                    result.addOTFType(otfType, fromFont:self)
                    
                    for feature in featureType["CTFeatureTypeSelectors"] as! [[String:AnyObject]] {
                        
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
        } set {
            print ("set OTFeatures \(newValue)")
        }
    }
    /*
     func setOpenTypeFeatures(_ types:OTFFeatures) {
     
     }
     */
    @objc var allChars:String {
        get {
            print("getting AllChars")
            let allFontChars = self.coveredCharacterSet.intersection(CharacterSet.controlCharacters.inverted)
            //let charset = NSMutableCharacterSet(bitmapRepresentation:  (allFontChars as NSCharacterSet).bitmapRepresentation)
            
            //print("charset", allFontChars, charset)
            //charset.formIntersection (with: CharacterSet.controlCharacters.inverted)
            var result = ""
            for plane : UInt8 in 0...16 {
                if allFontChars.hasMember(inPlane: plane) {
                    
                    for c : UInt32 in UInt32( plane ) << 16 ..< (UInt32(plane)+1) << 16 {
                        if let scalar = UnicodeScalar(c)  {
                            if allFontChars.contains(scalar) {
                                var c1 = c.littleEndian // To make it byte-order safe
                                
                                let s = NSString(bytes: &c1, length: 4, encoding: String.Encoding.utf32LittleEndian.rawValue);
                                
                                result += (s != nil ? s! as String : "")
                            }
                        }
                    }
                }
            }
            print(result)
            return result
        }
    
    }
    @objc func setAllChars (_ sender:Any) {
        print ("setting allchars")
    }
}
