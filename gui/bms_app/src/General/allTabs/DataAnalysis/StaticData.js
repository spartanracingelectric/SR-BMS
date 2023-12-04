import './StaticData.css';

function DataTitles({BData}) {
	return(
		<div className = "StaticBlock">
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
	);
}

export default DataTitles;
