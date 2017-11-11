#include <SFML/Network/Http.hpp>
#include <stdio.h>

FILE * fd;
char dataBuffer[128];

int main(){

	fd = fopen("/dev/ttyACM0", "r");// Open TTY port for input

	//--------------------------------------------------------
    sf::Http http;// Create a new HTTP client
    http.setHost("http://192.168.0.110");// Here is the ip the HTTP client connects to
    sf::Http::Request request("Temperature-Reading");// Prepare a request
    request.setMethod(sf::Http::Request::Post);// Set request method to POST
    //--------------------------------------------------------

	while(true){

		//--------------------------------------------------------
		// Read data from the arduino & format the packages
		fscanf(fd,"%c",&dataBuffer); // <--- read N bytes by some protocol ( @matei ) to the dataBuffer
		putchar(*dataBuffer); // display the databuffer to the screen ( in this case it's only 1 byte each time )
		// the screen output is just for debugging purposes and will be removed in the final product.
		//--------------------------------------------------------



		//--------------------------------------------------------
		// Here we send the package to the server
		request.setBody(dataBuffer); // <--- this should be formated as a JSON string ( @radu )
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
