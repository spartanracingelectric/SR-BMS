import './bmsData.css';

function BMSdata() {
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
	);
}

export default BMSdata;
