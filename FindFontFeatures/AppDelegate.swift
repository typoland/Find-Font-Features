//
//  AppDelegate.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//
var debugCounter = 0
import Cocoa
import AppKit






var fontSelectionChangedContext = "FontSelectionChangedContext"

@NSApplicationMain
@objc class AppDelegate: NSObject, NSApplicationDelegate {
    
    @IBOutlet weak var window: NSWindow!
    @IBOutlet weak var featuresView: NSOutlineView!
    @IBOutlet weak var fontsView: NSTableView!
    @IBOutlet weak var fontsController: NSArrayController!
    @IBOutlet weak var axesController:NSArrayController!
    
    @IBOutlet weak var featuresTableDelegate:NSObject!
    @IBOutlet weak var axesMenu:NSPopUpButton!
    
    var _tableFontSize:CGFloat = 15
    @objc var fontSize:CGFloat  = 32
    var _allFontsFeatures: OTFFeatures = OTFFeatures()
    @objc var _choosenFeaturesSet: OTFFeatures = OTFFeatures()
    
    var _allFonts:NSMutableOrderedSet = NSMutableOrderedSet()
    @objc var selectedFonts:NSMutableOrderedSet = NSMutableOrderedSet()
    
    var _selectedFont:NSFont!
    @objc var selectedFont:NSFont!
    
    
    @objc var defaultFont:NSFont!
    
    @objc var onlySelectedFontFeatures:Bool = false
    /*
     @objc var selectedFontsAxes:[Axis] {
     return selectedFont.axes
     }
     */
    
    func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool {
        return true
    }
    
    @objc var allFeatures:NSArray {
        get {
            if onlySelectedFontFeatures {
                let result = OTFFeatures()
                for font in selectedFonts {
                    result.types.union(OTFFeatures.fromFont(font as! NSFont).types)
                }
                return result.types.array.sorted(by: { (A, B) -> Bool in
                    (A as! OTFType).name > (B as! OTFType).name
                }) as NSArray
            }
            return _allFontsFeatures.types.array.sorted(by: { (A, B) -> Bool in
                (A as! OTFType).name > (B as! OTFType).name
            }) as NSArray
            
        }
    }
    
    
    @objc var allFonts:NSArray {
        get {
            
            if _featuresToSearch.count > 0  {
                
                let filter = NSMutableOrderedSet()
                for feature in _featuresToSearch {
                    filter.addObjects(from: feature.fonts.array)
                }
                return filter.array as NSArray
            }
            else {return _allFonts.array.sorted(by: { (objectA, objectB) -> Bool in
                (objectA as! NSFont).fontName.lowercased() < (objectB as! NSFont).fontName.lowercased()
            }) as NSArray}
        }
    }
    
    @objc func setAllFonts (_ sender:Any) {
        Swift.print ("set all fonts", sender)
    }
    
    var _featuresToSearch = Set<OTFeature>()
    
    @IBAction func changeAxis(_ sender:NSSlider) {
        if let varAxes = axesController.arrangedObjects as? [Axis], let oldFont  = CGFont(_selectedFont.fontName as CFString) {
            var variations : [CFString:CFNumber] = [ : ] //Error in documentation
            for axis in varAxes {
                variations[axis.name as CFString] = axis.currentValue as CFNumber
            }
            
             if let newFont = oldFont.copy(withVariations: variations as CFDictionary) {
             willChangeValue(forKey: "selectedFont")
             selectedFont = CTFontCreateWithGraphicsFont(newFont, fontSize, nil, _selectedFont.fontDescriptor)
             didChangeValue(forKey: "selectedFont")
             }
            
        }
    }
    
    
    func applicationDidFinishLaunching(_ aNotification: Notification) {
        
        _allFontsFeatures = OTFFeatures.fromAllSystemFonts(_tableFontSize);
        
        //fontsController.setSelectedObjects(_allFonts[0] as! [AnyObject])
        self.willChangeValue(forKey: "allFonts")
        
        for type in _allFontsFeatures.types {
            for feature in (type as! OTFType).typeSelectors {
                for font in (feature as! OTFeature).fonts {
                    _allFonts.add(font)
                }
            }
        }
        defaultFont = _allFonts.object(at: 0) as! NSFont
        self.didChangeValue(forKey: "allFonts")
        featuresView.reloadData()
        fontsView.reloadData()
        
        NotificationCenter.default.addObserver(self, selector: #selector(searchFontsWithFeature), name: NSNotification.Name(rawValue: setSearchNotification), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(changeOTFeaturesInCurrentFont), name: NSNotification.Name(rawValue: setFeatureNotification), object: nil)
        
        fontsController.addObserver(self, forKeyPath: "selection", options: NSKeyValueObservingOptions.new, context: &fontSelectionChangedContext)
        
        featuresTableDelegate.bind(NSBindingName(rawValue: "otfFeatures"), to: self, withKeyPath: "_choosenFeaturesSet", options: nil)
        featuresTableDelegate.addObserver(featuresTableDelegate, forKeyPath: "otfFeatures", options: NSKeyValueObservingOptions.new, context: &otfFeaturesChangedContext)
        changeFeaturesTable()
        /*
         self.willChangeValueForKey("_choosenFeatures")
         _choosenFeatures = _allFontsFeatures
         self.didChangeValueForKey("_choosenFeatures")
         */
    }
    
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        print("observing value")
        
        if context == &fontSelectionChangedContext {
            self.willChangeValue(forKey: "allFeatures")
            self.willChangeValue(forKey: "selectedFont")
            selectedFonts = NSMutableOrderedSet(array: fontsController.selectedObjects as! [NSFont])
            
            if fontsController.selectedObjects.count != 1 {
                _selectedFont = defaultFont
            } else {
                _selectedFont = (fontsController.selectedObjects as! [NSFont]) [0]
            }
            selectedFont = NSFont(name: _selectedFont.fontName , size: fontSize)
            self.didChangeValue(forKey: "allFeatures")
            self.didChangeValue(forKey: "selectedFont")
            
            self.willChangeValue(forKey: "_choosenFeaturesSet")
            changeFeaturesTable()
            self.didChangeValue(forKey: "_choosenFeaturesSet")
            
            
            
        }
    }
    
    
    func applicationWillTerminate(_ aNotification: Notification) {
        // Insert code here to tear down your application
    }
    
    
    @objc func searchFontsWithFeature(_ notification:Notification) {
        
        if let button = notification.object as? NSButton {
            func setSearchFeature (_ feature:OTFeature) {
                
                feature.willChangeValue(forKey: "search")
                feature.willChangeValue(forKey: "toolTip")
                feature.parent.willChangeValue(forKey: "searchResult")
                feature.parent.willChangeValue(forKey: "search")
                print(feature.search)
                feature.search = Int(button.intValue)
                print(feature.search)
                feature.didChangeValue(forKey: "search")
                feature.didChangeValue(forKey: "toolTip")
                feature.parent.didChangeValue(forKey: "searchResult")
                feature.parent.didChangeValue(forKey: "search")
                
                if feature.search == 1 {
                    _featuresToSearch.insert(feature)
                    if onlySelectedFontFeatures {
                        fontsController.addSelectedObjects([feature.fonts])
                    }
                } else {
                    _featuresToSearch.remove(feature)
                    if onlySelectedFontFeatures {
                        fontsController.removeSelectedObjects([feature.fonts])
                    }
                }
            }
            
            self.willChangeValue(forKey: "allFonts")
            self.willChangeValue(forKey: "selectedFontsAxesNames")
            
            let object = (button.superview as! NSTableCellView).objectValue
            
            if let feature = object as? OTFeature {
                setSearchFeature(feature)
                
                
            }   else if let type = object as? OTFType {
                for feature in type.typeSelectors {
                    setSearchFeature(feature as! OTFeature)
                }
            }
            self.didChangeValue(forKey: "selectedFontsAxesNames")
            self.didChangeValue(forKey: "allFonts")
            
        }
    }
    
    @objc func changeOTFeaturesInCurrentFont(_ notification:Notification) {
        print ("zmienia fjuczery",   ((notification.object as! NSButton).superview as! NSTableCellView).objectValue!)
        if let feature = ((notification.object as! NSButton).superview as! NSTableCellView).objectValue as? OTFeature {
            print("OK")
            self.willChangeValue(forKey: "selectedFont")
            print ("identifiers", feature.parent.identifier, feature.identifier)
            
            let fontDescriptor = _selectedFont.fontDescriptor.addingAttributes([
                NSFontDescriptor.AttributeName.featureSettings: [
                    [
                        NSFontDescriptor.FeatureKey.typeIdentifier: feature.parent.identifier,
                        NSFontDescriptor.FeatureKey.selectorIdentifier: feature.identifier
                    ]
                ]
                
                
                ])
            
            selectedFont = NSFont(descriptor: fontDescriptor, size: fontSize)
            if let fea = _selectedFont.fontDescriptor.object(forKey: NSFontDescriptor.AttributeName.featureSettings) {
                
                print ("feature \(fea)")
                print ("NSFontFeatureTypeIdentifierKey =", NSFontDescriptor.FeatureKey.typeIdentifier)
                print ("NSFontFeatureSelectorIdentifierKey =", NSFontDescriptor.FeatureKey.selectorIdentifier)
                
            }
            print ("Fonts:", _allFonts.count, selectedFonts.count)
            self.didChangeValue(forKey: "selectedFont")
        }
    }
    
    
    
    
    func changeFeaturesTable () {
        print("changing Feature Table")
        // Tu nie może bo się pętli self.willChangeValueForKey("allFonts")
        self.willChangeValue(forKey: "selectedFontsAxesNames")
        self.willChangeValue(forKey: "_choosenFeaturesSet")
        if onlySelectedFontFeatures {
            _choosenFeaturesSet = OTFFeatures()
            for font in selectedFonts {
                _choosenFeaturesSet.addFontFeatures((font as! NSFont).openTypeFeatures, fromFont: font as! NSFont)
            }
        } else {
            _choosenFeaturesSet = OTFFeatures.fromTypes( _allFontsFeatures)
            //= OTFFeatures.( _allFontsFeatures
        }
        
        //featuresView.reloadData()
        print ("Features: ",_choosenFeaturesSet.types.count, _allFontsFeatures.types.count)
        debugCounter = 0
        self.didChangeValue(forKey: "_choosenFeaturesSet")
        self.didChangeValue(forKey: "selectedFontsAxesNames")
        // Tu nie może bo się pętli self.didChangeValueForKey("allFonts")
        print ("All fonts:", _allFonts.count, allFonts.count, _featuresToSearch.count)
        
    }
    
    @IBAction func fontSize (_ sender: AnyObject) {
        print ("works")
        fontsController.willChangeValue(forKey: "selection")
        fontSize = CGFloat((sender as! NSControl).floatValue)
        changeFeaturesTable()
        fontsController.didChangeValue(forKey: "selection")
    }
    
    @IBAction func filterFontFeatures (_ sender:AnyObject) {
        self.willChangeValue(forKey: "selectedFontsAxes")
        self.willChangeValue(forKey: "onlySelectedFontFeatures")
        onlySelectedFontFeatures = ((sender as! NSControl).intValue  == 1)
        self.didChangeValue(forKey: "onlySelectedFontFeatures")
        self.willChangeValue(forKey: "_choosenFeaturesSet")
        changeFeaturesTable()
        self.didChangeValue(forKey: "_choosenFeaturesSet")
        self.willChangeValue(forKey: "allFonts")
        self.didChangeValue(forKey: "allFonts")
        self.didChangeValue(forKey: "selectedFontsAxes")
        
    }
}

