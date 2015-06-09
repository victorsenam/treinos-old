var serveStatic = require('serve-static');
var finalhandler = require('finalhandler');
var http = require('http');

// setup servestatic
var serve = serveStatic('./', {index: 'cover.html'});

// setup server
var server = http.createServer(function (req, res) {
    var done = finalhandler(req, res);
    serve(req, res, done);
});

server.listen(3000);
