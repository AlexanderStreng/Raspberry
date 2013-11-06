#include <server.h>
#include <algorithm>
#include <string>
#include <mongoose.h>

#ifdef __CDT_PARSER__
namespace std {
	std::string to_string(...);
}
#endif


static const char *ajax_reply_start_success = "HTTP/1.1 200 OK\r\n"
		"Cache: no-cache\r\n"
		"Content-Type: application/x-javascript\r\n"
		"\r\n";

static const char *ajax_reply_start_failed =
		"HTTP/1.1 500 Internal Server Error\r\n"
				"Cache: no-cache\r\n"
				"Content-Type: application/x-javascript\r\n"
				"\r\n";


server::server(int port) {
	const char *mongooseOptions[] = {
			"listening_ports", std::to_string(port).c_str(),
			"document_root", SCADA_DEFAULT_DOCUMENT_ROOT,
			NULL
	};

	mg_callbacks mongooseCallbacks;
	memset(&mongooseCallbacks, 0, sizeof(mongooseCallbacks));
	mongooseCallbacks.begin_request = &mongooseBeginRequestCallback;

	mongooseContext = mg_start(&mongooseCallbacks, this, mongooseOptions);
}

server::~EquipletScada() {
	mg_stop (mongooseContext);
}

int server::mongooseBeginRequestCallback(mg_connection* connection) {
	mg_request_info *request_info = mg_get_request_info(connection);

	int processed = 1;
	if (strcmp(request_info->uri, "/remote/procedurecall") == 0) {
		//mongooseProcessEquipletInfo(connection, request_info);
		std::cout << "remote/prodcedurecall" << std::endl;
	} else {
		processed = 0;
	}

	return processed;
}

/*
void EquipletScada::mongooseProcessEquipletInfo(mg_connection* conn, mg_request_info* request_info) {
	const char* state = rexos_statemachine::state_txt[equiplet->getCurrentState()];
	const char* mode = rexos_statemachine::mode_txt[equiplet->getCurrentMode()];
	JSONNode jsonObject;
	jsonObject.push_back(JSONNode("name", equiplet->getName()));
	jsonObject.push_back(JSONNode("state", state));
	jsonObject.push_back(JSONNode("mode", mode));

	mg_printf(conn, "%s", ajax_reply_start_success);

	mg_printf(conn, "%s", jsonObject.write_formatted().c_str());
}
*/
