// Analyze Image test


var assert = require("assert");
var cloudcv = require("../../cloudcv.js");
var fs     = require('fs');



cloudcv.analyzeImage("../opencv-logo.jpg", function(error, result) 
{           
	console.log(result.dominantColors.length);    
 
});