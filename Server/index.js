var http = require('http');
//
const { Client } = require('pg')

//DATABASE
const client = new Client({
  user: 'postgres',
  host: 'localhost',
  database: 'local_WheaterStation',
  password: 'postgres',
  port: 5432,
})
//CONNECT TO DATABASE
client.connect()

/*
client.query('SELECT * FROM public.\"Default\"', (err, res) => {
  if (err) {
    console.log(err.stack)
  } else {
    console.log(res.rows[0])
  }
})
*/

//Create server
http.createServer(function(req,res){
	res.writeHead(200,{'Content-Type': 'text/html'});
	//Vars
	var url = req.url;
	var l_time;
	var l_temp;
	var vals;
	var nextid;
	//Check if url is  NOT Favicon.ico
	if(url != "/favicon.ico"){
		//Get the time and temp
		l_time = decodeURIComponent(req.url.split("/WeatherStation/save?")[1].split("&")[1].split("=")[1]);
		l_temp = decodeURIComponent(req.url.split("/WeatherStation/save?")[1].split("&")[0].split("=")[1]);
		//For debug
		console.log(l_time);
		console.log(l_temp);
		console.log("----");
		//Make an array of thos two values
		vals = [l_temp , l_time];
		//Inser the into the DB
		client.query('INSERT INTO public.\"Default\"(temp,time) VALUES($1 , $2) RETURNING *', vals ,(err, res) => {
  			if (err) {
  				//Damn! An ERROR!
   		 		console.log(err.stack)
  			} else {
  				//Print in console the result
   		 		console.log(res.rows[0])
  			}
		})
	}
	//End server
	res.end();
}).listen(4474); // What port to listen on