const express = require('express');
const app = express();
var mysql = require('mysql');

app.use(express.json());

const con = mysql.createConnection({
	host: 'mysqldockerexample_mysql_1',
	port: 3306,
	user: 'exampleuser',
	password: 'password',
	database: "classicmodels"
});

con.connect((err) => {
	if(err){
		throw err;
	}
});

//creates router
var router = express.Router();

//middleware
router.use(function(req, res, next) {
	console.log("Something is happening");
	next();
});

//GET ROUTES
router.get('/', (req, res) => {
	res.send('HELLO WORLD!');
});

router.get('/products', (req, res) =>  {
	con.query("select * from products", function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

router.get('/product/:productCode', (req, res) => {
	var query = "select * from products where productCode=\""+req.params.productCode+"\"";
	con.query(query, function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

router.get('/payments', (req, res) => {
	con.query("select * from payments", function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

//POST ROUTES
router.post('/products', (req, res) => {
	var query = "insert into products (productCode, productName, productLine,"+
	"productScale, productVendor, productDescription, quantityInStock, buyPri"+
	"ce, MSRP) values (\""+req.query.productCode+"\", \""+req.query.productName+"\", \""+
	req.query.productLine+"\", \""+req.query.productScale+"\", \""+req.query.productVendor+
	"\", \""+req.query.productDescription+"\", \""+req.query.quantityInStock+"\", \""+
	req.query.buyPrice+"\", \""+req.query.MSRP+"\");";

	con.query(query, function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

router.post('/payments', (req, res) => {
	var query = "insert into payments (customerNumber, checkNumber, paymentDate,"+
	"amount) values (\""+req.query.customerNumber+"\", \""+req.query.checkNumber+"\", \""+
	req.query.paymentDate+"\", \""+req.query.amount+"\");";

	con.query(query, function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

//PUT ROUTES
router.put('/product/:productCode', (req, res) => {
	var query = "update products set quantityInStock="+req.query.quantityInStock+" "+
	"where productCode=\""+req.params.productCode+"\";";
	con.query(query, function(err, result, fields){
		res.end(JSON.stringify(result));
	})
});

//DELETE ROUTES
router.delete('/product/:productCode', (req, res) => {
	var query = "delete from products where productCode=\""+req.params.productCode+"\";";
	con.query(query, function(err, result, fields){
		console.log(err);
		res.end(JSON.stringify(result));
	})
});

//Register ROUTES
app.use('/api', router);

//PORT ENVIRONMENT VARIABLE
const port = process.env.PORT || 8080;
app.listen(port, () => console.log(`Listening on port ${port}..`));