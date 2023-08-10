const express = require('express');
const cors = require('cors');

const app = express();
const port = 8000;
var data = {
	volt: [Math.floor(Math.random() * 5), 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],
	temp: [Math.floor(Math.random() * 5), 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1],
	curr: [Math.floor(Math.random() * 5), 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2]
};

app.use(cors());
app.use(express.json());

app.get('/graphdata', (req, res) => {
    res.json({data});
});

app.listen(port, () => {
  console.log(`Server is running on port ${port}.`);
});
