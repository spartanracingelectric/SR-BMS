import React from "react";
import './DataAnalysis.css';
import Graphs from './Graphs.js';
import BMSdata from './bmsData.js';

const DataAnalysis = () => {
	return (
		<div className = "BDA">
			&nbsp;
			<div className = "Info">
				&nbsp;
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
				&nbsp;
				<BMSdata />
			</div>
			&nbsp;
			&nbsp;
			&nbsp;
			<Graphs />
		</div>
	);
};

export default DataAnalysis;
