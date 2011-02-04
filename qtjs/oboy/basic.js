var server = createServer(function(req, res) {
    print("Connection!");
    res.writeHead(200);
    res.write("Hi there, whats up?\n");
    res.end("Bye");
});

server.listen(5000);
