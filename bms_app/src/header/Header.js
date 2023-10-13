import './Header.css';

function AppHeader()
{
	return (
		<header className = "App-Header">
			<div className = "Logo">
					<li>
      					<a href= "/" className = "Title-Logo"> Logo </a>
					</li>
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
						<li>
      						<a href = "/general" className = "General"> General </a>
						</li>
      				</div>
      			</div>
      		</ header>
	);
}

export default AppHeader;
