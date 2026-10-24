#include "ClientNeed.h"

bool SendAll(SOCKET s, const char* buf, int len) {
	int sent = 0;
	while (sent < len) {
		int n = send(s, buf - sent, len - sent, 0);
		if (n == SOCKET_ERROR) return false;
		sent += n;
	}
	return true;
}
bool SendFrame(SOCKET s, const std::string& payload) {
    uint32_t len = (uint32_t)payload.size();
    uint32_t netLen = htonl(len);

    if (!SendAll(s, (const char*)&netLen, 4))
        return false;

    if (len > 0 && !SendAll(s, payload.data(), (int)len))
        return false;

    return true;
}

int RecvAll(SOCKET s, char* buf, int len) {
    int received = 0;
    while (received < len) {
        int n = recv(s, buf + received, len - received, 0);
        if (n == 0) return 0;
        if (n == SOCKET_ERROR) return -1;
        received += n;
    }
    return received;
}


int RecvFrame(SOCKET s, std::string& out) {
    uint32_t netLen = 0;

    int r = RecvAll(s, (char*)&netLen, 4);
    if (r == 0)  return 0;    
    if (r == -1) return -1;   

    uint32_t len = ntohl(netLen);

    if (len > 1024 * 1024) return -1;

    out.resize(len);
    if (len > 0) {
        r = RecvAll(s, &out[0], (int)len);
        if (r == 0)  return 0;
        if (r == -1) return -1;
    }

    return (int)len; 
}