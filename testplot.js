var plotly = require('plotly')("ishaan2307", "ewm3TW6C5lW4vWSj1aAG")
var data = [{x:[0,1,2], y:[3,2,1], type: 'bar'}];
var layout = {fileopt : "overwrite", filename : "simple-nodeexample"};
plotly.plot(data, layout, function (err, msg) {
 if (err) return console.log(err);
 console.log(msg);
});