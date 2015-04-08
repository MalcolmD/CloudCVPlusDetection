// numbers-detection test

var cloudcv = require("../../cloudcv.js");
var fs     = require('fs');



cloudcv.detectNumbers("GroupPic.jpg", function(error, result) 
{           
	console.log("Done");    
	console.log(result);
 
});
