var assert = require("assert");
var fs = require('fs');
var inspect = require('util').inpsect;

var cloudcv = require("../cloudcv.js");

describe('cv', function() {
  
  describe('detectNumbers', function()
  {

      it('process (File)', function(done)
      {
        cloudcv.detectNumbers("num.png", function(error, result)
        {
        assert.notStrictEqual(result, undefined);
        assert.equal(49, result.x);   
        done();     

        });

      });


      it('process (Buffer)', function(done)
      {
        var imageData = fs.readFileSync("num.png");
        cloudcv.detectNumbers(imageData, function(error, result)
        {
        assert.notStrictEqual(result, undefined);
        assert.equal(49, result.x);   
        done();     

        });

      });

  });

});

