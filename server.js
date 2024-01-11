var app = require('express')();
app.use(require('express').static(__dirname + '/src'));

app.listen(3005, function () {
  console.log('Example app listening on port 3005!');
});