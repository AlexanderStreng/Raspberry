#pragma once

#include <mongoose.h>

#define SCADA_DEFAULT_DOCUMENT_ROOT "./www/"


class Server {
public:
	Server(int port = 1337);
	virtual ~Server();

private:
	int mongooseBeginRequestCallback(mg_connection* connection);
	//void mongooseProcessEquipletInfo(mg_connection* conn, mg_request_info* request_info);

	mg_context* mongooseContext;
};
