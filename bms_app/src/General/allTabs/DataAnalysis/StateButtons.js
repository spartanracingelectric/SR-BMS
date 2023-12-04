import './StateButtons.css';

/*
	bName		-button text
	barData		-graph data object for display
	setBarData	-function to update barData
	options		-graph options object for display
	setOptions	-function to update options
	cellGroups	-array holding labels for x-axis bars
	gData		-array holding either Voltage/Temp/IV data
	dTitle		-name indicating which data is being displayed
	bgColor		-color for the bars
	yTitle		-label of the y-axis
	xTitle		-label of thex-axis
	gMode		-currently displayed graph data
	setGmode	-function to update mode
*/

function StateButton({bName, barData, setBarData, options, setOptions, 
	cellGroups, gData, dTitle, bgColor, yTitle, xTitle, setGmode}) {

	function changeState() {
		setBarData(barData => {
			return{
				labels: cellGroups,
				datasets: [{
					label: dTitle,
					data: gData,
					backgroundColor: bgColor
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
										text: yTitle
								}
						},
						x: {
							...options.scales.x,
							title: {
								...options.scales.x.title,
								text: xTitle
							}
						}
				}
			}
		});
		setGmode(dTitle);
	}
	
	return(
		<div className = "Button">
			<button className = "Size" onClick={changeState}> {bName} </button>
			&nbsp;
		</div>
	);
}

export default StateButton;
