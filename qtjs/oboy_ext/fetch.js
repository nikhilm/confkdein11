if(load("qt.core") != undefined)
    throw Error("No qt.core module available");
if(load("qt.xml") != undefined)
    throw Error("No qt.xml module available");
if(load("qt.network") != undefined)
    throw Error("No qt.network module available");

var server = createServer(function(req, res) {
    print("Connection!");

    var nm = new QNetworkAccessManager();
    var client_req = new QNetworkRequest(new QUrl("http://planetkde.org/rss20.xml"));
    var client_reply = nm.get(client_req);
    client_reply.finished.connect(function() {
        print("FINISHED");
        var ts = new QTextStream(client_reply.readAll());
        var doc = new QDomDocument('hi');
        doc.setContent(ts.readAll());
        var chan = doc.documentElement().firstChildElement('channel');

        var items = chan.elementsByTagName('item');
        res.writeHead(200, {"Content-Type": "text/html"});

        res.write("<ul>\n");
        for(var i = 0; i < items.length(); i++) {
            var item = items.at(i);

            res.write('<li><a href="' + item.firstChildElement('link').text() + '">');
            res.write(item.firstChildElement('title').text());
            res.write('</a></li>\n');
        }
        res.end('</ul>\n');
    });
});

server.listen(5000);
