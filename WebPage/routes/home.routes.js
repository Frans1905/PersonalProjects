
var express = require('express');
var router = express.Router();
var data = require('../data/mydata');
var path = require('path');
const session = require('express-session');

router.use(express.static(path.join(__dirname, 'public')));

let kategorije = [];
let produkti = [];
let kategorija = "";


router.get('/', function(req, res) {
    res.redirect('/home/getCategories/');
});


router.get('/home', function(req, res) {

    if (kategorija === "") {
        kategorija = "Dobrodošli";
    }

    if (!req.session.cart) {
        req.session.cart = [];
    }

    return res.render('home', {
        categories: kategorije,
        category: kategorija,
        products: produkti,
        cart: req.session.cart,
        session: req.session
    });
});

router.get('/home/getCategories/', function(req, res) {

    session: req.session;

    kategorije = [];

    for (var cat of data['categories']) {
        kategorije.push(cat);
    } 
    res.redirect('/home/');
});

router.get("/home/getProducts/:id", function(req, res) {

    session: req.session;


    let id = req.params.id;


    kategorija = id;

    if (id === undefined) {
        id = "Gitare";
    }

    produkti = [];
    for (var cat of data['categories']) {
        if (cat['name'] === id) {
            for (var product of cat['products']) {
                produkti.push(product);
            }
        }
    }

    res.redirect('/home/'); 
});

router.post('/add/:id', function(req, res) {

    let name = req.params.id.toString();
    let product = {name:name,quantity:1};

    if (req.session.cart) {
        if (!containsProduct(req.session.cart, name)) {
            req.session.cart.push(product);
        }
        else {
            for (var prod of req.session.cart) {
                if (prod.name === name) {
                    prod.quantity = prod.quantity + 1;
                }
            }
        }
    } 
    else { 
        req.session.cart = [];
        req.session.cart.push(product);
    }

    res.redirect('/home/');
});

function containsProduct(cart, name) {
    for (let product of cart) {
        if (product.name === name) {
            return true;
        }
    }
    return false;
}

module.exports = router;