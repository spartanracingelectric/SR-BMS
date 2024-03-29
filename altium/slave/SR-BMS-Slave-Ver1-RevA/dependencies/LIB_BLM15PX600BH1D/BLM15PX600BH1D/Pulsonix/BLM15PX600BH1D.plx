PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//18491250/1251284/2.50/2/5/Ferrite Bead

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r50_40"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.400) (shapeHeight 0.500))
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
	(patternDef "NFZ15SG152SN10B" (originalName "NFZ15SG152SN10B")
		(multiLayer
			(pad (padNum 1) (padStyleRef r50_40) (pt -0.400, 0.000) (rotation 0))
			(pad (padNum 2) (padStyleRef r50_40) (pt 0.400, 0.000) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0.000, 0.000) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.175 0.7) (pt 1.175 0.7) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.175 0.7) (pt 1.175 -0.7) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.175 -0.7) (pt -1.175 -0.7) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.175 -0.7) (pt -1.175 0.7) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.5 0.25) (pt 0.5 0.25) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.5 0.25) (pt 0.5 -0.25) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.5 -0.25) (pt -0.5 -0.25) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.5 -0.25) (pt -0.5 0.25) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 0.15) (pt 0 -0.15) (width 0.05))
		)
	)
	(symbolDef "BLM15PX600BH1D" (originalName "BLM15PX600BH1D")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 650 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "BLM15PX600BH1D" (originalName "BLM15PX600BH1D") (compHeader (numPins 2) (numParts 1) (refDesPrefix FB)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "BLM15PX600BH1D"))
		(attachedPattern (patternNum 1) (patternName "NFZ15SG152SN10B")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "81-BLM15PX600BH1D")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/BLM15PX600BH1D?qs=9vOqFld9vZVffjoX8DlOqw%3D%3D")
		(attr "Manufacturer_Name" "Murata Electronics")
		(attr "Manufacturer_Part_Number" "BLM15PX600BH1D")
		(attr "Description" "Ferrite Beads 0402 60ohm 25% 5A AEC-Q200")
		(attr "<Hyperlink>" "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/emc/emifil/c31e.ashx?la=en-gb")
		(attr "<Component Height>" "0.55")
		(attr "<STEP Filename>" "BLM15PX600BH1D.stp")
		(attr "<STEP Offsets>" "X=0.25;Y=0;Z=0.25")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=90")
	)

)
