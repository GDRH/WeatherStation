#include <SFML/Network/Http.hpp>
#include <stdio.h>
#include <time.h>
#include <string.h>

char LinkBuffer[256];
char value[256];

void generateURI( const char * value ){
	// "/WeatherStation/save?time=2017-11-12+10:25:23&value=25"
	memset(LinkBuffer,0,256);
	strcat(LinkBuffer,"/WeatherStation/save?time=");
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	char dateBuffer[100];
	strftime (dateBuffer,80,"%F+%T",timeinfo);
	strcat(LinkBuffer, dateBuffer);
	strcat(LinkBuffer, "&value=");
	strcat(LinkBuffer,value);
}

FILE * fd;
char dataBuffer[128];

int main(){

	fd = fopen("/dev/ttyACM0", "r");// Open TTY port for input

	//--------------------------------------------------------
    sf::Http http;// Create a new HTTP client
    http.setHost("www.gdrh.ro",4474);// Here is the ip the HTTP client connects to
    sf::Http::Request request("");// Prepare a request
    request.setMethod(sf::Http::Request::Get);// Set request method to POST
    //--------------------------------------------------------

	while(true){

		//--------------------------------------------------------
		// Read data from the arduino & format the packages
		fscanf(fd,"%s",&value); // <--- read N bytes by some protocol ( @matei ) to the dataBuffer
		printf("Value : %s",value); // display the databuffer to the screen ( in this case it's only 1 byte each time )
		// the screen output is just for debugging purposes and will be removed in the final product.
		//-------------------------------------------------------

		generateURI(value);
		printf(" %s\n\n",LinkBuffer);

		//--------------------------------------------------------
		// Here we send the package to the server
		request.setUri(LinkBuffer); // <--- this should be formated as a JSON string ( @radu )
		//--------------------------------------------------------



		sf::Http::Response response = http.sendRequest(request);// Send the request
		sf::Http::Response::Status status = response.getStatus();// Check the status code and display the result
		if ( status == sf::Http::Response::ConnectionFailed ){
			// ... handle readings in case the connection fails ( @antonio )
		}

		/* // This is used in case you're expecting a message back ( GET requests )
		if (status == sf::Http::Response::Ok){
			std::cout << response.getBody() << std::endl;
		}
		else{
			std::cout << "Error " << status << std::endl;
		}*/
	}
}
