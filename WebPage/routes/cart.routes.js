var express = require('express');
var path = require('path');
var router = express.Router();

router.get('/', function(req, res) {
    res.redirect('/cart/getAll');
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

    res.redirect('/cart/getAll');
});

router.post('/remove/:id', function(req, res) {

    let name = req.params.id;

    for (let i = 0; i < req.session.cart.length; i++) {
        if (req.session.cart[i].name === name) {
            if (req.session.cart[i].quantity === 1) {
                req.session.cart.splice(i, 1);
                break;
            } 
            req.session.cart[i].quantity = req.session.cart[i].quantity - 1;
        }
    }
    res.redirect('/cart/getAll');

});


router.get('/getAll', function(req, res) {

    if (!req.session.cart) {
        req.session.cart = [];
    }

    res.render('cart', {
        cart: req.session.cart,
        session: req.session
    })
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
