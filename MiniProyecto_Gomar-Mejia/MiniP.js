'use strict'

const mongoose = require('mongoose')
const Schema = mongoose.Schema 

const ProductSchema = Schema({
    btn:String,
    pos:String
})

module.exports = mongoose.model('product', ProductSchema) 
