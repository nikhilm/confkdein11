var server = createServer(function(req, res) {
    print("Connection! " + req.remoteAddress + ":" + req.remotePort);
    print("User agent " + req.headers['user-agent']);
    print(req.method, req.httpVersion, req.url, req.path);

    var data = "Must it be assumed that because we are engineers, beauty is not our concern? -- Gustave Eiffel";
    res.writeHead(200, {
        'Content-Type': 'text/html',
        'Content-Length' : data.length
    });
    res.write(data);
});

server.listen(5000);
