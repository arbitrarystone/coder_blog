#ifndef __STONE_EMAIL_SMTP_H__
#define __STONE_EMAIL_SMTP_H__

#include "src/socket_stream.hpp"
#include "email.hpp"
#include <sstream>

namespace stone {

struct SmtpResult {
    typedef std::shared_ptr<SmtpResult> ptr;
    enum Result {
        OK = 0,
        IO_ERROR = -1
    };

    SmtpResult(int r, const std::string& m)
        :result(r)
        ,msg(m) {
    }

    int result;
    std::string msg;
};

class SmtpClient : public stone::SocketStream {
public:
    typedef std::shared_ptr<SmtpClient> ptr;
    static SmtpClient::ptr Create(const std::string& host, uint32_t port, bool ssl= false);
    SmtpResult::ptr send(EMail::ptr email, int64_t timeout_ms = 1000, bool debug = false);

    std::string getDebugInfo();
private:
    SmtpResult::ptr doCmd(const std::string& cmd, bool debug);
private:
    SmtpClient(Socket::ptr sock);
private:
    std::string m_host;
    std::stringstream m_ss;
    bool m_authed = false;
};

}

#endif

