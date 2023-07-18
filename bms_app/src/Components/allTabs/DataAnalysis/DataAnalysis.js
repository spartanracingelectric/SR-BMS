import React from "react";
import './DataAnalysis.css';
import Graphs from './Graphs.js';

function DataTitles() {
	return(
		<div className = "InfoComp">
			&nbsp;
			<text>Voltage Pack:</text>
			<text>Currents Pack:</text>
			<text>Power Pack:</text>
			<text>CV High:</text>
			<text>CV Average:</text>
			<text>CV Low:</text>
			<text>C Mismatch:</text>
			&nbsp;
			&nbsp;
			<text>Temp Battery High:</text>
			<text>Temp Battery Average:</text>
			<text>Temp Battery Low:</text>
			&nbsp;
			&nbsp;
			<text>Voltage Load:</text>
			<text>Power Load:</text>
			<text>Voltage Charger:</text>
			<text>Power Charger:</text>
			&nbsp;
		</div>
	);
}

function DataAnalysis() {

	var Vpack = (3.00).toFixed(2);
	var Cpack = (0.00).toFixed(2);
	var Ppack = (1.00).toFixed(2);
	var CVhigh = (2.00).toFixed(2);
	var CVavg = (2.00).toFixed(2);
	var CVlow = (1.00).toFixed(2);
	var Cmismatch = (2.00).toFixed(2);
	var TBhigh = (1.00).toFixed(2);
	var TBavg = (3.00).toFixed(2);
	var TBlow = (0.00).toFixed(2);
	var Vload = (1.00).toFixed(2);
	var Pload = (1.00).toFixed(2);
	var Vcharger = (2.00).toFixed(2);
	var Pcharger = (3.00).toFixed(2);


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
					<text>{Vpack} V</text>
					<text>{Cpack} A</text>
					<text>{Ppack} W</text>
					<text>{CVhigh} V</text>
					<text>{CVavg} V</text>
					<text>{CVlow} V</text>
					<text>{Cmismatch} V</text>
					&nbsp;
					&nbsp;
					<text>{TBhigh} C</text>
					<text>{TBavg} C</text>
					<text>{TBlow} C</text>
					&nbsp;
					&nbsp;
					<text>{Vload} V</text>
					<text>{Pload} W</text>
					<text>{Vcharger} V</text>
					<text>{Pcharger} W</text>
				</div>
			</div>
			&nbsp;
			&nbsp;
			&nbsp;
			<Graphs />
		</div>
	);
}

export default DataAnalysis;
