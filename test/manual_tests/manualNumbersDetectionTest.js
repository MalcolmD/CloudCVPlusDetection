// numbers-detection test


var assert = require("assert");
var cloudcv = require("../../cloudcv.js");
var fs     = require('fs');



cloudcv.detectNumbers("../num.png", function(error, result) 
{           
	console.log("Done");    
 
});