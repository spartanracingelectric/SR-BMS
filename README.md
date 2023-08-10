# Senior_project_GUI
React GUI code base

Note:

1. after cloning repository open bms_app 
	- install the react scripts using the following command
	 ## 'npm install react-scripts'
	 otherwise you cannot run app on local host
2. to use the backend you must run both the backend and frontend parts simultaneously
	- frontend: open terminal in bms_app folder use: 
		## 'npm start'
	- backend: open terminal in serialcomm folder 
		## 'npm run dev' 
	- backend deals w/ serial communication

Todo List

1. serial port communication
	- initial testing is trying to send a HIGH signal to board
	- second wave of testing is board sending values back
	- third wave is trying to change array values in DataAnalysis.js
	- fourth wave is trying to change graph values in BarGraph.js\ 
		(values might be moved to DataAnalysis.js)
2. change graph info dynamically
	-if it takes long default to just show graph info using list
3. UML diagrams
