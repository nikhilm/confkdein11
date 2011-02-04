var server = createServer(function(req, res) {
    print("Connection!");
    res.writeHead(200);

    req.data.connect(res.write);
    req.end.connect(res.end);
});

server.listen(5000);
