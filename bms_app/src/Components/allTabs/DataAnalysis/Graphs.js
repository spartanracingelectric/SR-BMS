import './Graphs.css';
import BarGraph from './BarGraph.js';

/*
	box that displays the graphs panel
	GraphTabs displays different graphs to display
		-might change to tabs for consistency
	BarGraph is the current graph displayed
		-will change along with GraphTabs to include more graphs
		-serves as a template
		-alter to make more appealing
		-might change to line graph in future
*/

function Graphs() {
	return (
		<div className = "Graphs" >
			<BarGraph />
		</div> 
	);
}

export default Graphs;
