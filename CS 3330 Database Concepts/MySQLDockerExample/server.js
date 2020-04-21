const express = require('express');
const app = express();
app.use(express.json());

var mysql = require('mysql');
const connection= mysql.createConnection({
  host: 'mysql',
  user: 'exampleuser',
  password: 'password' 
});

app.get('/', (req, res) => {
res.send('HELLO WORLD!');
});

//PORT ENVIRONMENT VARIABLE
const port = process.env.PORT || 8080;
app.listen(port, () => console.log(`Listening on port ${port}..`));