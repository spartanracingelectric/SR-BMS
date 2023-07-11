import React,{Component} from 'react';
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

class BarGraph extends Component
{

constructor() {
    	super();
    	this.state = {
    		barData: {
    			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
			datasets: [ 
				{
					label: 'Voltage',
					data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
					backgroundColor: 'white'
				}
			 
			]
    		
    		},
    		options: {
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
		}
 	}
 	
 	this.changeState1 = this.changeState1.bind(this);
 	this.changeState2 = this.changeState2.bind(this);
 	this.changeState3 = this.changeState3.bind(this);
}

changeState1() {
	this.setState({
		barData: {
    			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
			datasets: [ 
				{
					label: 'Voltage',
					data: [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
					backgroundColor: 'white'
				}
			 
			]
    		
    		},
    		options: {
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
	})
}

changeState2() {
	this.setState({
		barData: {
    			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],
			datasets: [ 
				{
					label: 'Temperature',
					data: [2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
					backgroundColor: 'darkgreen'
				}
			 
			]
    		
    		},
    		options: {
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
						text: 'Temperature',
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
	})
}

changeState3() {
	this.setState({
		barData: {
    			labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
			datasets: [ 
				{
					label: 'IV',
					data: [3, 1, 2, -3, 1, -2, 3, 1, 2, -3],
					backgroundColor: 'lightgreen',
					borderColor: 'black',
					borderWidth: 1
				}
			 
			]
    		
    		},
    		options: {
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
						text: 'Current (i)',
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
						text: 'Voltage (V)',
						color: 'black'
					}
				}
			}
		}
	})
}


render() {
	return (
        	<div>
        		&nbsp;
			<div className = "GraphTabs">
				&nbsp;
				&nbsp;
				<button className = "CV" onClick={this.changeState1}> Cell Voltage </button>
				&nbsp;
				<button className = "Temps" onClick={this.changeState2}> Temperatures </button>
				&nbsp;
				<button className = "IV" onClick={this.changeState3}> IV </button>
			</div>
			&nbsp;
        			<Bar data={this.state.barData} options={this.state.options} />
        	</div>
	)
}
}

export default (BarGraph);
