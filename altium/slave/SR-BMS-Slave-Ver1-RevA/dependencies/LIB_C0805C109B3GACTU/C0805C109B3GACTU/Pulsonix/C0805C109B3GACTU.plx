PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//14702150/1251284/2.50/2/2/Capacitor

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r145_115"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 1.15) (shapeHeight 1.45))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "C0805" (originalName "C0805")
		(multiLayer
			(pad (padNum 1) (padStyleRef r145_115) (pt -0.9, 0) (rotation 0))
			(pad (padNum 2) (padStyleRef r145_115) (pt 0.9, 0) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 0.625) (pt 1 0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 0.625) (pt 1 -0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 -0.625) (pt -1 -0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 -0.625) (pt -1 0.625) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -1.75, 0) (radius 0.05) (startAngle 0.0) (sweepAngle 0.0) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(arc (pt -1.75, 0) (radius 0.05) (startAngle 180.0) (sweepAngle 180.0) (width 0.2))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -2.275 1.625) (pt 2.275 1.625) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 2.275 1.625) (pt 2.275 -1.625) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 2.275 -1.625) (pt -2.275 -1.625) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -2.275 -1.625) (pt -2.275 1.625) (width 0.05))
		)
	)
	(symbolDef "C0805C109B3GACTU" (originalName "C0805C109B3GACTU")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 0 mils -35 mils) (rotation 0]) (justify "UpperLeft") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 500 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 500 mils -35 mils) (rotation 0]) (justify "UpperRight") (textStyleRef "Normal"))
		))
		(line (pt 220 mils 100 mils) (pt 220 mils -100 mils) (width 6 mils))
		(line (pt 280 mils 100 mils) (pt 280 mils -100 mils) (width 6 mils))
		(line (pt 200 mils 0 mils) (pt 220 mils 0 mils) (width 6 mils))
		(line (pt 280 mils 0 mils) (pt 300 mils 0 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 350 mils 250 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 350 mils 150 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "C0805C109B3GACTU" (originalName "C0805C109B3GACTU") (compHeader (numPins 2) (numParts 1) (refDesPrefix C)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "C0805C109B3GACTU"))
		(attachedPattern (patternNum 1) (patternName "C0805")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "80-C0805C109B3GACTU")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/KEMET/C0805C109B3GACTU?qs=%252BdQmOuGyFcGvMtB75B23qg%3D%3D")
		(attr "Manufacturer_Name" "KEMET")
		(attr "Manufacturer_Part_Number" "C0805C109B3GACTU")
		(attr "Description" "SMD Comm C0G, Ceramic, 1 pF, +/-0.1 pF, 25 VDC, 62.5 VDC, 125C, -55C, C0G, SMD, MLCC, Ultra-Stable, Low Loss, Class I, 0.1 % , 100 GOhms, 11 mg, 0805, 2mm, 1.25mm, 0.78mm, 0.75mm, 0.5mm, 4000, 78  Weeks, 120")
		(attr "<Hyperlink>" "https://content.kemet.com/datasheets/KEM_C1003_C0G_SMD.pdf")
		(attr "<Component Height>" "1.1")
		(attr "<STEP Filename>" "C0805C109B3GACTU.stp")
		(attr "<STEP Offsets>" "X=-1.1;Y=-0.73;Z=0")
		(attr "<STEP Rotation>" "X=90;Y=0;Z=0")
	)

)