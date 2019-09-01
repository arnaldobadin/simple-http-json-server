#ifndef REQUEST_H
#define REQUEST_H

#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>

#include "htonsv/server/packet.hpp"

using json = nlohmann::json;

class Request {
	public:
		Request(int socket, unsigned int buffer_size = 1024);
		~Request();

		static const unsigned int BUFFER_SIZE_DEFAULT = 1024;

		bool isValid() const;

		std::string getPath() const {return _packet.path;}
		Protocol::Item getMethod() const {return _packet.method;}
		std::string getHeader(const std::string& header) {return _packet.headers[header];}
		json getBody() const {return _packet.body;}

		bool valid() const;
		bool load();

	private:
		int _socket;
		unsigned int _buffer_size;

		bool _status;
		
		std::string _data;
		Packet::Item _packet;

		bool _receive();
		bool _transform();
};

#endif