const express = require('express'); //REST API for communication between frontend and backend
const cors = require('cors'); //ensures we are sending right headers

const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

const app = express();
const port = 8000;
app.use(cors());
app.use(express.json());

//Initialize serial port used
const myPort = new SerialPort({
	path: "COM5", 
	baudRate: 9600
});
const parser = myPort.pipe(new ReadlineParser({ delimiter: '\r\n' }));

//object that stores the data sent from board
var data = {
	volt: [Math.floor(Math.random() * 5), 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
	temp: [Math.floor(Math.random() * 5), 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
	curr: [Math.floor(Math.random() * 5), 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2],
	static: [(3.00).toFixed(2), (0.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2),
		(2.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (1.00).toFixed(2), (3.00).toFixed(2),
		(0.00).toFixed(2), (1.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (3.00).toFixed(2)]
};

//Send signal (h) to board to begin sending data
function getData() {
	myPort.write("h");

	return data;	
}

//frontend requests data to /graphdata to which backend responds and sends data object
app.get('/graphdata', (req, res) => {
    res.json(getData());
});

//backend goes to listening mode and "listens" for data sent from board
app.listen(port, () => {
  console.log(`Server is running on port ${port}.`);
});

myPort.on('open', onOpen);
parser.on('data', onData);

function onOpen() {
	console.log("Open Connection");
}

//sent data is dealt with this function
function onData(data) {
	console.log("Got: " + data);
}
