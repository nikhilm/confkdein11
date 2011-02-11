var conn = new DB("database.db");
if(!conn)
    throw Error("Error connecting to database");

// INSERT
conn.insert('planet', {'name': 'Shantanu Tushar Jha', 'blog': 'http://shantanutushar.com'});

conn.insert('planet', {'blog': 'http://kodeclutz.blogspot.com', 'name': 'Nikhil Marathe'});
// SELECT
print("--- GET");
var result = conn.get('planet');
while(result.next) {
    print(result['name'] + " -> " + result['blog']);
}

// SELECT where
print("--- GET WHERE");
var result = conn.getWhere('planet', {'name': 'Nikhil Marathe'});
while(result.next) {
    print(result['name'] + " -> " + result['blog']);
}

// UPDATE
print('--- After UPDATE')
conn.update('planet', {'blog': 'http://nytimes.com'}, {'name': 'Nikhil Marathe'});

print("--- GET");
var result = conn.get('planet');
while(result.next) {
    print(result['name'] + " -> " + result['blog']);
}
