import './Header.css';
import logo from './SR_logo_original.png';

function AppHeader()
{
	return (
		<header className = "App-Header">
			<div className = "Logo">
					<li>
      					<a href= "/">
						  <img  src = {logo} alt = "SAELogo" className = "Title-Logo" /> 
						</a>
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
