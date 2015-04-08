// Analyze Image test


var assert = require("assert");
var cloudcv = require("../../cloudcv.js");
var fs     = require('fs');



cloudcv.analyzeImage("num.png", function(error, result) 
{           
	console.log(result.dominantColors.length);    
 
});