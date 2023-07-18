import './BarGraph.css';
import {useState} from 'react';
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

function BarGraph ()
{

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
				text: 'N/A',
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
});

const changeState1 = () => {
	setBarData(barData => {
		return{
			...barData,
			datasets: [{
				label: 'Voltage',
				data: [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
				backgroundColor: 'white'
			}]
		}
	});
	setOptions(options => {
		return{ 
			...options,
			scales: {
				...options.scales,
					y: {
						...options.scales.y,
							title: {
								...options.scales.y.title,
									text: 'Voltage (V)'
							}
					}
			}
		}
	});
}

const changeState2 = () => {
	setBarData(barData => {
		return{
			...barData,
			datasets: [{
				label: 'Temperature',
				data: [2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
				backgroundColor: 'darkgreen'
			}]
		}
	});
	setOptions(options => {
		return{ 
			...options,
			scales: {
				...options.scales,
					y: {
						...options.scales.y,
							title: {
								...options.scales.y.title,
									text: 'Temperature'
							}
					}
			}
		}
	});
}

const changeState3 = () => {
	setBarData(barData => {
		return{
			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
			datasets: [{
				label: 'IV',
				data: [3, 1, 2, -3, 1, -2, 3, 1, 2, -3],
				backgroundColor: 'lightgreen'
			}]
		}
	});
	setOptions(options => {
		return{ 
			...options,
			scales: {
				...options.scales,
					y: {
						...options.scales.y,
							title: {
								...options.scales.y.title,
									text: 'Current (i)'
							}
					},
					x: {
						...options.scales.x,
						title: {
							...options.scales.x.title,
							text: 'Voltage (V)'
						}
					}
			}
		}
	});	
}

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
				<button className = "Refresh" > Refresh </button>
			</div>
			&nbsp;
        			<Bar data={barData} options={options} />
        		&nbsp;
        	</div>
	);
}


export default (BarGraph);
