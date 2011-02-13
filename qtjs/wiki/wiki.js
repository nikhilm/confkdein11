require("underscore.js");

if(load("qt.core") != undefined)
    throw new Error("Could not load qt.core");

var baseUrl = 'http://localhost:5000';

var render = function(fn, data) {
    print("HERE");
    var f = new QFile(fn);
    print("HERE");
    if(!f.open(QIODevice.ReadOnly))
        throw new Error("Error loading template " + fn);
    print("HERE");

    print("HERE");
    var ts = new QTextStream(f);
    print("HERE");
    return _.template(ts.readAll(), data);
}

var editTpl = render("edit.html");
var viewTpl = render("view.html");

var conn = new DB('database.db');

var editPage = function(req, res, page) {
    if( req.method == 'POST' && req.headers['content-type'] == 'application/x-www-form-urlencoded' ) {
        var newContent = "";
        req.data.connect(function(data) {
            var s = new QTextStream(QByteArray.fromPercentEncoding(data.replace(new QByteArray('+'), new QByteArray(' '))));
            newContent += s.readAll();
        });
        req.end.connect(function() {
            // crudely strip out 'content='
            newContent = newContent.slice(8);

            var exists = conn.getWhere('wiki', {'title': page});
            if( exists.next )
                conn.update('wiki', {'content': newContent}, {'title': page});
            else
                conn.insert('wiki', {'title': page, 'content': newContent});
            res.writeHead(301, {'Location': baseUrl + '/' + page});
            res.end();
        });
    }
    else {
        // TODO fetch earlier content if exists
        var exists = conn.getWhere('wiki', {'title': page});
        var content = '';
        if( exists.next )
            content = exists['content'];
        var data = editTpl({'title': page, 'content': content});
        res.writeHead(200, {'Content-Length': data.length});
        res.end(data);
    }
}

var viewPage = function(req, res, page) {
    var exists = conn.getWhere('wiki', {'title': page});
    var content = '';
    if( exists.next ) {
        content = exists['content'];
        var data = viewTpl({'title': page, 'content': content, 'editLink': baseUrl + '/edit/' + page});
        res.writeHead(200, {'Content-Length': data.length});
        res.end(data);
    }
    else {
        res.writeHead(301, {'Location': baseUrl + '/edit/' + page});
        res.end();
    }
}

var server = createServer(function(req, res) {
    var editRegex = /^\/edit\/(\w+)/;
    var viewRegex = /^\/([^\\]*)$/;


    print("PATH " + req.path);

    var page, match;
    if( !req.path || req.path == '/' ) {
        res.writeHead(301, {'Location': baseUrl + '/Home'});
        return res.end();
    }
    else if(match = req.path.match(editRegex)) {
        print("Edit");
        page = match[1];
        return editPage(req, res, page);
    }
    else if(match = req.path.match(viewRegex)) {
        print("View");
        page = match[1];
        return viewPage(req, res, page);
    }
    else {
        res.writeHead(404);
        res.end();
    }
});

server.listen(5000);
