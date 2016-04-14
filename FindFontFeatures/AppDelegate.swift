//
//  AppDelegate.swift
//  FindFontFeatures
//
//  Created by Łukasz Dziedzic on 07/04/16.
//  Copyright © 2016 Łukasz Dziedzic. All rights reserved.
//
var debugCounter = 0
import Cocoa






var fontSelectionChangedContext = "FontSelectionChangedContext"

@NSApplicationMain

class AppDelegate: NSObject, NSApplicationDelegate {
    
    @IBOutlet weak var window: NSWindow!
    @IBOutlet weak var featuresView: NSOutlineView!
    @IBOutlet weak var fontsView: NSTableView!
    @IBOutlet weak var fontsController: NSArrayController!
    @IBOutlet weak var featuresTableDelegate:NSObject!
    
    var _tableFontSize:CGFloat = 15
    var fontSize:CGFloat  = 32
    var _allFontsFeatures: OTFFeatures = OTFFeatures()
    var _choosenFeaturesSet: OTFFeatures = OTFFeatures()
    
    var _allFonts:NSMutableOrderedSet = NSMutableOrderedSet()
    var selectedFonts:NSMutableOrderedSet = NSMutableOrderedSet()
    var _selectedFont:NSFont!
    var selectedFont:NSFont!
    
    
    var defaultFont:NSFont!
    
    var onlySelectedFontFeatures:Bool = false
    
    var allFeatures:NSArray {
        get {
            if onlySelectedFontFeatures {
                let result = OTFFeatures()
                for font in selectedFonts {
                    result.types.unionOrderedSet(OTFFeatures.fromFont(font as! NSFont).types)
                }
                return result.types.array.sort({ (A, B) -> Bool in
                    (A as! OTFType).name > (B as! OTFType).name
                })
            }
            return _allFontsFeatures.types.array.sort({ (A, B) -> Bool in
                (A as! OTFType).name > (B as! OTFType).name
            })

        }
    }
    
    
    var allFonts:NSArray {
        get {
            
            if _featuresToSearch.count > 0  {
                
                let filter = NSMutableOrderedSet()
                for feature in _featuresToSearch {
                    filter.addObjectsFromArray(feature.fonts.array)
                }
                return filter.array
            }
            else {return _allFonts.array.sort({ (objectA, objectB) -> Bool in
                (objectA as! NSFont).fontName.lowercaseString < (objectB as! NSFont).fontName.lowercaseString
            })}
        }
    }
    
    var _featuresToSearch = Set<OTFeature>()
    
    
    func applicationDidFinishLaunching(aNotification: NSNotification) {
        _allFontsFeatures = OTFFeatures.fromAllSystemFonts(_tableFontSize);
        
        //fontsController.setSelectedObjects(_allFonts[0] as! [AnyObject])
        self.willChangeValueForKey("allFonts")
        
        for type in _allFontsFeatures.types {
            for feature in (type as! OTFType).typeSelectors {
                for font in (feature as! OTFeature).fonts {
                    _allFonts.addObject(font)
                }
            }
        }
        defaultFont = _allFonts.objectAtIndex(0) as! NSFont
        self.didChangeValueForKey("allFonts")
                featuresView.reloadData()
        fontsView.reloadData()
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(searchFontsWithFeature), name: setSearchNotification, object: nil)
        NSNotificationCenter.defaultCenter().addObserver(self, selector: #selector(changeOTFeaturesInCurrentFont), name: setFeatureNotification, object: nil)
        
        fontsController.addObserver(self, forKeyPath: "selection", options: NSKeyValueObservingOptions.New, context: &fontSelectionChangedContext)
        
        featuresTableDelegate.bind("otfFeatures", toObject: self, withKeyPath: "_choosenFeaturesSet", options: nil)
        featuresTableDelegate.addObserver(featuresTableDelegate, forKeyPath: "otfFeatures", options: NSKeyValueObservingOptions.New, context: &otfFeaturesChangedContext)
        changeFeaturesTable()
        /*
         self.willChangeValueForKey("_choosenFeatures")
         _choosenFeatures = _allFontsFeatures
         self.didChangeValueForKey("_choosenFeatures")
         */
    }
    
    override func observeValueForKeyPath(keyPath: String?, ofObject object: AnyObject?, change: [String : AnyObject]?, context: UnsafeMutablePointer<Void>) {
        print("observing value")
        
        if context == &fontSelectionChangedContext {
            self.willChangeValueForKey("allFeatures")
            self.willChangeValueForKey("selectedFont")
            selectedFonts = NSMutableOrderedSet(array: fontsController.selectedObjects as! [NSFont])
            
            if fontsController.selectedObjects.count != 1 {
                _selectedFont = defaultFont
            } else {
                _selectedFont = (fontsController.selectedObjects as! [NSFont]) [0]
            }
            selectedFont = NSFont(name: _selectedFont.fontName , size: fontSize)
            self.didChangeValueForKey("allFeatures")
            self.didChangeValueForKey("selectedFont")
            
            self.willChangeValueForKey("_choosenFeaturesSet")
            changeFeaturesTable()
            self.didChangeValueForKey("_choosenFeaturesSet")
            
           
            
        }
    }
    
    
    func applicationWillTerminate(aNotification: NSNotification) {
        // Insert code here to tear down your application
    }
    
    
    func searchFontsWithFeature(notification:NSNotification) {
        
        if let button = notification.object as? NSButton {
        func setSearchFeature (feature:OTFeature) {
            
            feature.willChangeValueForKey("search")
            feature.willChangeValueForKey("toolTip")
            feature.parent.willChangeValueForKey("searchResult")
            feature.parent.willChangeValueForKey("search")
            print(feature.search)
            feature.search = Int(button.intValue)
            print(feature.search)
            feature.didChangeValueForKey("search")
            feature.didChangeValueForKey("toolTip")
            feature.parent.didChangeValueForKey("searchResult")
            feature.parent.didChangeValueForKey("search")
            
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
            
        self.willChangeValueForKey("allFonts")
            
        let object = (button.superview as! NSTableCellView).objectValue
            
        if let feature = object as? OTFeature {
            setSearchFeature(feature)
            
            
        }   else if let type = object as? OTFType {
            for feature in type.typeSelectors {
                setSearchFeature(feature as! OTFeature)
            }
        }
        self.didChangeValueForKey("allFonts")
        }
    }
    
    
    func changeOTFeaturesInCurrentFont(notification:NSNotification) {
        print ("zmienia fjuczery",   ((notification.object as! NSButton).superview as! NSTableCellView).objectValue)
        if let feature = ((notification.object as! NSButton).superview as! NSTableCellView).objectValue as? OTFeature {
            print("OK")
            self.willChangeValueForKey("selectedFont")
            print ("identifiers", feature.parent.identifier, feature.identifier)
            
            let fontDescriptor = _selectedFont.fontDescriptor.fontDescriptorByAddingAttributes([
                NSFontFeatureSettingsAttribute: [
                    [
                        NSFontFeatureTypeIdentifierKey: feature.parent.identifier,
                        NSFontFeatureSelectorIdentifierKey: feature.identifier
                    ]
                ]
                ])
            
            selectedFont = NSFont(descriptor: fontDescriptor, size: fontSize)
            if let fea = _selectedFont.fontDescriptor.objectForKey(NSFontFeatureSettingsAttribute) {
            
                print ("feature \(fea)")
                print ("NSFontFeatureTypeIdentifierKey =", NSFontFeatureTypeIdentifierKey)
                print ("NSFontFeatureSelectorIdentifierKey =", NSFontFeatureSelectorIdentifierKey)
                
            }
            print ("Fonts:", _allFonts.count, selectedFonts.count)
            self.didChangeValueForKey("selectedFont")
            }
        }
        
            
    
    
    func changeFeaturesTable () {
        print("changing Feature Table")
        // Tu nie może bo się pętli self.willChangeValueForKey("allFonts")
        self.willChangeValueForKey("_choosenFeaturesSet")
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
        self.didChangeValueForKey("_choosenFeaturesSet")
        // Tu nie może bo się pętli self.didChangeValueForKey("allFonts")
       print ("All fonts:", _allFonts.count, allFonts.count, _featuresToSearch.count)
        
    }
    
    @IBAction func fontSize (sender: AnyObject) {
        print ("works")
        fontsController.willChangeValueForKey("selection")
        fontSize = CGFloat((sender as! NSControl).floatValue)
        changeFeaturesTable()
        fontsController.didChangeValueForKey("selection")
    }
    
    @IBAction func filterFontFeatures (sender:AnyObject) {

        self.willChangeValueForKey("onlySelectedFontFeatures")
        onlySelectedFontFeatures = sender.intValue == 1
        self.didChangeValueForKey("onlySelectedFontFeatures")
        self.willChangeValueForKey("_choosenFeaturesSet")
        changeFeaturesTable()
        self.didChangeValueForKey("_choosenFeaturesSet")
        self.willChangeValueForKey("allFonts")
        self.didChangeValueForKey("allFonts")
        
    }
}

