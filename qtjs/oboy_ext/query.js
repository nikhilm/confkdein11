if(load("qt.sql") != undefined)
    throw Error("No qt.sql module available");

var conn = QSqlDatabase.addDatabase("QSQLITE", "default");
conn.setDatabaseName("mock.db");
if(!conn.open())
    throw Error("Error opening mock.db");

var server = createServer(function(req, res) {
    print("Connection!");

    res.writeHead(200, {
        'Content-Type': 'text/html',
    });

    res.write("<html><head><title>Freshest Meat</title></head><body><h1>The Freshesh Meat is at conf.kde.in!</h1><ul>");
    
    var q = new QSqlQuery(conn);
    q.exec("select title, link from up;");
    while(q.next()) {
        res.write('<li><a href="'+q.value(1) + '">' + q.value(0) + '</a></li>\n');
    }

    res.end("</ul></body></html>");
});

server.listen(5000);
