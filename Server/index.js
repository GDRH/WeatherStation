var http = require('http');
var mysql = require('mysql');
//Connect to databse
var con = mysql.createConnection({
  host: "127.0.0.1",
  user: "root",
  password: "",
  database: "gdrh_project"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
});
//Create server
http.createServer(function(req,res){
	res.writeHead(200,{'Content-Type': 'text/html'});
	//Get the added-on text after the base url
	//http://gdrh.ro:4474/senzor?date=2017-11-12 10:33&temperature=22.45
	//We are getting that something after the domain and port
	var url = req.url;
	//Create a variable to store our split JSON string
	//The un-split string would look like: %7B"time":"2:23","data":21%7D
	// %22 is the character "
	//Also create 2 variables to store our time and temperature
	var time;
	var temp;
	if(url != "/favicon.ico"){
	//Set the time
		/*time = splitString[3];
		if(splitString[6]) { //For some reason the first time this script is executed it works great 
							//but then the second time is executed (by executed i mean the program going throu it multiple times)
							//it , for some reason, makes the split string undefined
			//Set the temperature
			temp = splitString[6].split(":")[1].split("%7D")[0];
		}
		//If there is an error in formating:
		else
		{
			time = "Error";
			temp = "Error";
		}
		var sql = "INSERT INTO temp_logs (date, temperature) VALUES (time, temp)";
  		con.query(sql, function (err, result) {
   		if (err) throw err;
    	console.log("1 record inserted");
  		});*/
		//Write the Time and Temperature
		//res.write("Time:"+time +"Temperature:"+temp);
		//res.write(splitString.toString());
		console.log(req.url);
	}
	//End server
	res.end();
}).listen(4474); // What port to listen on
//