import './BarGraph.css';
import {Bar} from 'react-chartjs-2';
import {
	Chart as ChartJS,
	BarElement,
	CategoryScale,
	LinearScale,
	Tooltip,
	Legend
} from 'chart.js';

ChartJS.register(
	BarElement,
	CategoryScale,
	LinearScale,
	Tooltip,
	Legend
)

function BarGraph ({Refresh, changeState1, changeState2, 
	changeState3, barData, options})
{

	return (
        	<div className = "Graph">
        		&nbsp;
			<div className = "GraphTabs">
				&nbsp;
				&nbsp;
				<button className = "CV" onClick={changeState1}> Cell Voltage </button>
				&nbsp;
				<button className = "Temps" onClick={changeState2}> Temperatures </button>
				&nbsp;
				<button className = "IV" onClick={changeState3}> IV </button>
				&nbsp;
				&nbsp;
				&nbsp;
				<button className = "Refresh" onClick={Refresh}> Refresh </button>
			</div>
			&nbsp;
        			<Bar data={barData} options={options} />
        		&nbsp;
        		&nbsp;
        	</div>
	);
}


export default BarGraph;
