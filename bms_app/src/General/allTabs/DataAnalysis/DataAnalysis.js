import React, {useState} from "react";
import './DataAnalysis.css';
import BarGraph from './BarGraph.js';
import DataTitles from './StaticData.js';
import StateButton from './StateButtons.js';

let initialData = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
let cellGroups = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12];
const url1 = "http://localhost:8000/graphdata";

function DataAnalysis() {
	
	//holds string value fetched from server 8000 from server.js in serial comm
	//message is for debugging
	//const [message, setMessage] = useState("");

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
					text: 'Voltage',
					color: 'black'
				},
				suggestedMax: 4.5
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
					text: 'Cell Number',
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
	
	const [BData, setData] = useState(initialData);

	const Refresh = async () => {
		/*UpdateVoltage();
		UpdateCurrent();
		UpdateTemperature();
		
		UpdateData();
		
		Backend();*/
		
		const response = await fetch(url1, {
        		method: 'GET',
        		headers: {},
		}).catch(error => console.error(error));
      		
      		const result = await response.json();
      		const obj = JSON.stringify(result, null, 4);
      		//setMessage(obj);
      		const arr = JSON.parse(obj);
      		
			setVdata(arr.volt);
      		setTdata(arr.temp);
      		setIdata(arr.curr);
      		setData(arr.static);
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
				{/*<text> {message} </text>*/}
				<div className = "GraphTabs">
					<StateButton bName = {'Cell Voltage'} barData = {barData} setBarData = {setBarData} 
						options = {options} setOptions = {setOptions} cellGroups = {cellGroups} gData = {Vdata} 	
						dTitle = {'Voltage'} bgColor = {'white'} yTitle = {'Voltage (V)'} xTitle = {'Cell Number'}/>
					<StateButton bName = {'Temperature'} barData = {barData} setBarData = {setBarData} 
						options = {options} setOptions = {setOptions} cellGroups = {cellGroups} gData = {Tdata} 
						dTitle = {'Temperature'} bgColor = {'white'} yTitle = {'Temperature (C)'} 
						xTitle = {'Cell Number'}/>
					<StateButton bName = {'IV'} barData = {barData} setBarData = {setBarData} options = {options} 
						setOptions = {setOptions} cellGroups = {Vdata} gData = {Idata} dTitle = {'IV'} 
						bgColor = {'white'} yTitle = {'Current (I)'} xTitle = {'Voltage'}/>
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
