//#include "network.h"
//
//void network::connectToServer()
//{
//	socket = new tcp::socket(io_context);
//	tcp::resolver resolver(io_context);
//	tcp::resolver::results_type endpoints =
//		resolver.resolve(tcp::v4(), host, port);
//	asio::connect(*socket, endpoints);
//}
//
//string network::readFromServer()
//{
//	string buf;
//	asio::error_code error;
//	size_t len = socket->read_some(asio::buffer(buf));
//	if (error == asio::error::eof)
//	{
//		log("Connection closed cleanly by peer.");
//		return "";
//	}
//	else if (error)
//		throw asio::system_error(error);
//	return buf;
//}
//
//void network::writeIntoServer(string& message)
//{
//	asio::error_code ignored_error;
//	asio::write(socket, asio::buffer(message), ignored_error);
//}
