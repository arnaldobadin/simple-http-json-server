#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <atomic>
#include <memory>

#include "consumer.h"
#include "request.h"
#include "response.h"
#include "struct.hpp"

class Server {
	public:
		Server(std::uint16_t port);
		~Server();

		struct Route {
			std::string path;
			Struct::Methods method;
			std::function<void (Request*, Response*)> callback;

			bool isValid() {
				if (!path.length()) return false;
				if (method < Struct::Methods::FIRST || method > Struct::Methods::LAST) return false;
				if (callback == nullptr) return false;
				return true;
			}
		};

		bool setRoute(const std::string& path, Struct::Methods method, std::function<void(Request*, Response*)> callback);
		bool getRoute(const std::string& path, Struct::Methods method, Route& route);

		bool start();
		bool stop();

	private:
		std::uint16_t _port;

		std::atomic<bool> _status;

		std::vector<Route> _routes;
		std::unique_ptr<Consumer> _consumer;

		void _process(int socket_in);
};

#endif