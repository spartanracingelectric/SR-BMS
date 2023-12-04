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

function BarGraph ({barData, options})
{

	return (
        	<div>
        		<Bar data={barData} options={options} width = "500" height = "300" />
        	</div>
	);
}


export default BarGraph;
