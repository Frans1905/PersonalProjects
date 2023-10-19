var express = require('express')
var ejs = require('ejs') 
var path = require('path');
var bodyParser = require('body-parser');
var session = require('express-session');


var app = express();

app.use(bodyParser.urlencoded({extended: true}));

app.use(
    session({
        secret: "anything",
        resave: false,
        saveUninitialized: true
    })
);

const homeRouter = require('./routes/home.routes');
const cartRouter = require('./routes/cart.routes');

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(express.static('public'));

app.use('/', homeRouter);
app.use('/cart', cartRouter);

app.listen(8000);


