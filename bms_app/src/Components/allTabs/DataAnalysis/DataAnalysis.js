import React, {useState} from "react";
import './DataAnalysis.css';
import BarGraph from './BarGraph.js';
import DataTitles from './StaticData.js';
import StateButton from './StateButtons.js';

let initialData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
let cellGroups = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12];

function DataAnalysis() {
	/*
		Vdata, Idata, IVdata hold the graph data for the BMS
		Refresh() updates these states
		Note: not sure if we need IVdata if we have Voltage and Current data
	*/
	const [Vdata, setVdata] = useState (initialData);
	const [Tdata, setTdata] = useState (initialData);
	const [Idata, setIdata] = useState (initialData);
	
	// barData and options hold the displayed graph data
	const [barData, setBarData] = useState ({
		labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
		datasets: [ 
			{
				label: 'Voltage',
				data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
				backgroundColor: 'white'
			}
			 
		]
	});
	
	const [options, setOptions] = useState ({
		scales: {
			y: {
				ticks: {
					color: 'black'
				},
				grid: {
					color: 'grey'
				},
				title: {
					display: true,
					text: 'N/A',
					color: 'black'
				}
			},
			x: {
				ticks: {
					color: 'black'
				},
				grid: {
					color: 'grey'
				},
				title: {
					display: true,
					text: 'Cell Size',
					color: 'black'
				}
			}
		}
	});
	
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
	
	
	function UpdateVoltage() {
		const n1Data = [Math.floor(Math.random() * 5), 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3];
		setVdata(n1Data);
	}
	
	function UpdateTemperature() {
		const n2Data = [Math.floor(Math.random() * 5), 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1];
		setTdata(n2Data);
	}
	
	function UpdateCurrent() {
		const n3Data = [Math.floor(Math.random() * 5), 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2];
		setIdata(n3Data);
	}

	function Refresh() {
		UpdateVoltage();
		UpdateCurrent();
		UpdateTemperature();
		
		UpdateData();
	}

	return (
		<div className = "BDA">
			&nbsp;
			<div className = "Info">
				&nbsp;
				<DataTitles BData = {BData}/>
			</div>
			&nbsp;
			&nbsp;
			&nbsp;
			<div className = "Graph">
				&nbsp;
				&nbsp;
				<div className = "GraphTabs">
					<StateButton bName = {'Cell Voltage'} barData = {barData} setBarData = {setBarData} 
						options = {options} setOptions = {setOptions} cellGroups = {cellGroups} gData = {Vdata} 	
						dTitle = {'Voltage'} bgColor = {'white'} yTitle = {'Voltage (V)'} xTitle = {'Cell Size'}/>
					<StateButton bName = {'Temperature'} barData = {barData} setBarData = {setBarData} 
						options = {options} setOptions = {setOptions} cellGroups = {cellGroups} gData = {Tdata} 
						dTitle = {'Temperature'} bgColor = {'darkgreen'} yTitle = {'Temperature (C)'} 
						xTitle = {'Cell Size'}/>
					<StateButton bName = {'IV'} barData = {barData} setBarData = {setBarData} options = {options} 
						setOptions = {setOptions} cellGroups = {Vdata} gData = {Idata} dTitle = {'IV'} 
						bgColor = {'lightgreen'} yTitle = {'Current (I)'} xTitle = {'Voltage'}/>
					&nbsp;
        				&nbsp;
        				<button className = "Refresh" onClick={Refresh}> Refresh </button>
				</div>
				&nbsp;
					<BarGraph barData = {barData} options = {options}/>
			</div>
		</div>
	);
}

export default DataAnalysis;
