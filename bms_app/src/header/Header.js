import './Header.css'

function AppHeader()
{
	return (
		<header className = "App-Header">
			<div className = "Logo">
      				<text className = "Title-Logo"> Logo </text>
      			</div>
      			<div className = "Settings">
      				<text className = "Settings-Logo"> Settings </text>
      				<div className = "Tabs">
      					{/*
      						possibly integrate links for each text
      					*/}
      					
      					<text className = "Display"> Display </text>
      					<text className = "Signals"> Signals </text>
      					<text className = "Switch"> Switch </text>
      					<text className = "CellManagement"> Cell Management </text>
      					<text className = "General"> General </text>
      				</div>
      			</div>
      		</ header>
	);
}

export default AppHeader;
