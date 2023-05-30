import {
	Chart as ChartJS,
	BarElement,
	CategoryScale,
	LinearScale,
	Tooltip,
	Legend
} from 'chart.js';

import {Bar} from 'react-chartjs-2';

ChartJS.register(
	BarElement,
	CategoryScale,
	LinearScale,
	Tooltip,
	Legend
)

function BarGraph() {
	const data = {
		labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
		datasets: [ 
			{
				label: 'Voltage',
				data: [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
				backgroundColor: 'darkcyan',
				borderColor: 'black',
				borderWidth: 1
			},
			{
				label: 'Temperature',
				data: [2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
				backgroundColor: 'darkgreen',
				borderColor: 'black',
				borderWidth: 1
			},
			{
				label: 'IV',
				data: [3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2],
				backgroundColor: 'lightgreen',
				borderColor: 'black',
				borderWidth: 1
			}
			 
		]
	}
	
	const options = {
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
					text: 'Voltage (V)',
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
	}
	
	return (
		<div
			style = {
					{padding: '10px'}
				}
		>
			<Bar
				data = {data}
				options = {options}
			></Bar>
		</div>
	);
}

export default BarGraph;
