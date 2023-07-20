import React, {useState} from "react";
import './DataAnalysis.css';
import BarGraph from './BarGraph.js';
import DataTitles from './StaticData.js';

let initialData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

function DataAnalysis() {
	
	/*
		Data array = [Vpack, Cpack, Ppack, CVhigh,
			CVavg, CVlow, Cmismatch, TBhigh, TBavg,
			TBlow, Vload, Pload, Vcharger, Pcharger]
			
		Note: try changing array values using serial communication first 
			before trying to change graph values
	*/
	
	const [BData, SetData] = useState(initialData);

	function UpdateData() {
		 const newData = [(3.00).toFixed(2), (0.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2),
		(2.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (1.00).toFixed(2), (3.00).toFixed(2),
		(0.00).toFixed(2), (1.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (3.00).toFixed(2)]
		
		SetData(newData);
	}

	return (
		<div className = "BDA">
			&nbsp;
			<div className = "Info">
				&nbsp;
				<DataTitles />
				&nbsp;
				<div className = "Data">
				{/*
					display bms data here
					maybe load data from a json file?
				*/}
					&nbsp;
					<text>{BData[0]} V</text>
					<text>{BData[1]} A</text>
					<text>{BData[2]} W</text>
					<text>{BData[3]} V</text>
					<text>{BData[4]} V</text>
					<text>{BData[5]} V</text>
					<text>{BData[6]} V</text>
					&nbsp;
					&nbsp;
					<text>{BData[7]} C</text>
					<text>{BData[8]} C</text>
					<text>{BData[9]} C</text>
					&nbsp;
					&nbsp;
					<text>{BData[10]} V</text>
					<text>{BData[11]} W</text>
					<text>{BData[12]} V</text>
					<text>{BData[13]} W</text>
				</div>
			</div>
			&nbsp;
			&nbsp;
			&nbsp;
			<BarGraph UpdateData = {UpdateData}/>
		</div>
	);
}

export default DataAnalysis;
