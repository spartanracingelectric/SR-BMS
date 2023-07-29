import React, {useState} from "react";
import './DataAnalysis.css';
import BarGraph from './BarGraph.js';
import DataTitles from './StaticData.js';

let initialData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

function DataAnalysis() {
	/*
		Vdata, Idata, IVdata hold the graph data for the BMS
		Refresh() updates these states
		Note: not sure if we need IVdata if we have Voltage and Current data
	*/
	const [Vdata, setVdata] = useState (initialData);
	const [Idata, setIdata] = useState (initialData);
	const [IVdata, setIVdata] = useState (initialData);
	
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

	const changeState1 = () => {
		setBarData(barData => {
			return{
				labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
				datasets: [{
					label: 'Voltage',
					data: Vdata,
					backgroundColor: 'white'
				}]
			}
		});
		setOptions(options => {
			return{ 
				...options,
				scales: {
					...options.scales,
						y: {
							...options.scales.y,
								title: {
									...options.scales.y.title,
										text: 'Voltage (V)'
								}
						}
				}
			}
		});
	}

	const changeState2 = () => {
		setBarData(barData => {
			return{
				labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
				datasets: [{
					label: 'Temperature',
					data: Idata,
					backgroundColor: 'darkgreen'
				}]
			}
		});
		setOptions(options => {
			return{ 
				...options,
				scales: {
					...options.scales,
						y: {
							...options.scales.y,
								title: {
									...options.scales.y.title,
										text: 'Temperature'
								}
						}
				}
			}
		});
	}

	const changeState3 = () => {
		setBarData(barData => {
			return{
				labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
				datasets: [{
					label: 'IV',
					data: IVdata,
					backgroundColor: 'lightgreen'
				}]
			}
		});
		setOptions(options => {
			return{ 
				...options,
				scales: {
					...options.scales,
						y: {
							...options.scales.y,
								title: {
									...options.scales.y.title,
										text: 'Current (i)'
								}
						},
						x: {
							...options.scales.x,
							title: {
								...options.scales.x.title,
								text: 'Voltage (V)'
							}
						}
				}
			}
		});	
	}
	
	
	function UpdateVoltage() {
		const n1Data = [Math.floor(Math.random() * 5), 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3];
		setVdata(n1Data);
	}
	
	function UpdateCurrent() {
		const n2Data = [Math.floor(Math.random() * 5), 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1];
		setIdata(n2Data);
	}
	
	function UpdateIV() {
		const n3Data = [Math.floor(Math.random() * 5), 1, 2, -3, 1, -2, 3, 1, 2, -3];
		setIVdata(n3Data);
	}

	function Refresh() {
		UpdateVoltage();
		UpdateCurrent();
		UpdateIV();
		
		UpdateData();
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
			<BarGraph Refresh = {Refresh} changeState1 = {changeState1} changeState2 = {changeState2} 
				changeState3 = {changeState3} barData = {barData} options = {options}/>
		</div>
	);
}

export default DataAnalysis;
