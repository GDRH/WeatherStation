var http = require('http');
//Create server
http.createServer(function(req,res){
	res.writeHead(200,{'Content-Type': 'text/html'});
	//Get the added-on text after the base url
	//http(s)://domain.port/something
	//We are getting that something after the domain and port
	var url = req.url;
	//Create a variable to store our split JSON string
	//The un-split string would look like: %7B"time":"2:23","data":21%7D
	// %22 is the character "
	//Also create 2 variables to store our time and temperature
	var splitString = url.split("%22");
	var time;
	var temp;
	//Set the time
	time = splitString[3];
	if(splitString[6]){ //For some reason the first time this script is executed it works great 
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
	//Write the Time and Temperature
	res.write("Time:"+time +"Temperature:"+temp);
	//End server
	res.end();
}).listen(3000); // What port to liste on