const express = require('express');
const cors = require('cors');

const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

const EventEmitter = require('events');

const insert = new EventEmitter();

const app = express();
const port = 8000;
app.use(cors());
app.use(express.json());

const myPort = new SerialPort({path: "COM4", 
	baudRate: 9600
});
const parser = myPort.pipe(new ReadlineParser({ delimiter: '\r\n' }));

var data = {
	volt: [Math.floor(Math.random() * 5), 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
	temp: [Math.floor(Math.random() * 5), 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
	curr: [Math.floor(Math.random() * 5), 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2],
	static: [(3.00).toFixed(2), (0.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2),
		(2.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (1.00).toFixed(2), (3.00).toFixed(2),
		(0.00).toFixed(2), (1.00).toFixed(2), (1.00).toFixed(2), (2.00).toFixed(2), (3.00).toFixed(2)]
};

var strindex = 0;
var valdex = 0;
var text = "";

insert.on('start', () => {
	var x = parseInt(text, 2);
	console.log(x);
	//console.log(valdex);
	strindex = 0;
	data.static[valdex] = x.toFixed(2);
	valdex++;
	text = "";
	if(valdex == 14)
		valdex = 0;
});

function getData() {
	myPort.write("h");

	return data;	
}

app.get('/graphdata', (req, res) => {
    res.json(getData());
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}.`);
});

myPort.on('open', onOpen);
parser.on('data', onData);

function onOpen() {
	console.log("Open Connection");
}

function onData(data) {
	console.log("Got: " + data);
	text = text + data;
	strindex++;
	if(strindex == 8) {
		insert.emit('start');
	}
}
