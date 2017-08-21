#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wcast-align"
#endif

#include "CommandQueue.h"

#include "Kernel.h"
#include "Config.h"
#include "SlowTicker.h"

#include "Network.h"
#include "PublicDataRequest.h"
#include "clock-arch.h"
#include "NetworkPublicAccess.h"
#include "checksumm.h"
#include "ConfigValue.h"

#include "StreamOutputPool.h"

#include "telnetd.h"
#include "shell.h"

#define network_enable_checksum CHECKSUM("enable")
#define network_webserver_checksum CHECKSUM("webserver")
#define network_telnet_checksum CHECKSUM("telnet")
#define network_plan9_checksum CHECKSUM("plan9")
#define network_mac_override_checksum CHECKSUM("mac_override")
#define network_ip_address_checksum CHECKSUM("ip_address")
#define network_hostname_checksum CHECKSUM("hostname")
#define network_ip_gateway_checksum CHECKSUM("ip_gateway")
#define network_ip_mask_checksum CHECKSUM("ip_mask")

static Network* theNetwork;

Network::Network()
{
    theNetwork= this;
    tickcnt= 0;
    sftpd= NULL;
    hostname = NULL;
    command_q= CommandQueue::getInstance();
}

Network::~Network()
{
    if (hostname != NULL) {
        delete hostname;
    }
    theNetwork= nullptr;
}

static bool parse_ip_str(const string &s, uint8_t *a, int len, int base=10, char sep = '.')
{
    int p = 0;
    const char *n;
    for (int i = 0; i < len; i++) {
        if (i < len - 1) {
            size_t o = s.find(sep, p);
            if (o == string::npos) return false;
            n = s.substr(p, o - p).c_str();
            p = o + 1;
        } else {
            n = s.substr(p).c_str();
        }
        a[i] = (int)strtol(n, NULL, base);
    }
    return true;
}

static bool parse_hostname(const string &s)
{
    const std::string::size_type str_len = s.size();
    if(str_len > 63){
        return false;
    }
    for (unsigned int i = 0; i < str_len; i++) {
        const char c = s.at(i);
        if(!(c >= 'a' && c <= 'z')
                && !(c >= 'A' && c <= 'Z')
                && !(i != 0 && c >= '0' && c <= '9')
                && !(i != 0 && i != str_len - 1 && c == '-')){
            return false;
        }
    }
    return true;
}

void Network::on_module_loaded()
{
    if ( !THEKERNEL->config->value( network_checksum, network_enable_checksum )->by_default(false)->as_bool() ) {
        // as not needed free up resource
        delete this;
        return;
    }

    telnet_enabled = THEKERNEL->config->value(network_checksum, network_telnet_checksum, network_enable_checksum)->by_default(false)->as_bool();

    THEKERNEL->slow_ticker->attach( 100, this, &Network::tick );

    // Register for events
    this->register_for_event(ON_IDLE);
    this->register_for_event(ON_MAIN_LOOP);
    this->register_for_event(ON_GET_PUBLIC_DATA);

    this->init();
}

void Network::init(void)
{
#if defined(_WIN32)
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed to initialize WinSocks. Error Code : %d", WSAGetLastError());
        return;
    }
#endif

    network_thread = new std::thread(&Network::thread_main, this);
}

void Network::thread_main(void)
{
    socket = new CPassiveSocket();
    socket->Initialize();
    socket->Listen("127.0.0.1", 23);

    while (socket && socket->IsSocketValid())
    {
        CActiveSocket *client = socket->Accept();
        if (client == nullptr)
            continue;

        THEKERNEL->streams->printf("New client connected: %s\n", client->GetClientAddr());

        telnetd = new Telnetd();
        telnetd->socket = client;
        telnetd->shell->start();

        constexpr int BUF_SIZE = 512;
        uint8 recv[BUF_SIZE];

        std::vector<uint8_t> data;
        data.reserve(BUF_SIZE);

        while (true) {
            int bytes = client->Receive(BUF_SIZE, recv);
            data.insert(data.end(), &recv[0], &recv[bytes]);

            if (bytes == 0)
                break;

            bool newLine = false;
            for (auto i = 0; i < bytes; i++)
                newLine |= data[data.size() - i - 1] == '\n';

            if (newLine)
            {
                data.push_back('\0');

                std::string cmd((char*)data.data());
                cmd.erase(std::remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
                cmd.erase(std::remove(cmd.begin(), cmd.end(), '\n'), cmd.end());

                telnetd->shell->input((char*) cmd.c_str());
                data.clear();
            }
        }

        telnetd->close();
        delete telnetd;
    }
}

uint32_t Network::tick(uint32_t dummy)
{
    tickcnt++;
    return 0;
}

void Network::on_idle(void *argument)
{

}

void Network::setup_servers()
{
    if (telnet_enabled)
        telnetd = new Telnetd();
}

void Network::on_main_loop(void *argument)
{
    // issue commands here if any available
    while(command_q->pop()) {
        // keep feeding them until empty
    }
}

void Network::handlePacket(void)
{
}

void Network::on_get_public_data(void* argument) {
    PublicDataRequest* pdr = static_cast<PublicDataRequest*>(argument);

    if (!pdr->starts_with(network_checksum)) return;

    if (pdr->second_element_is(get_ip_checksum)) {
        pdr->set_data_ptr(this->ipaddr);
        pdr->set_taken();

    }
    else if (pdr->second_element_is(get_ipconfig_checksum)) {
        // NOTE caller must free the returned string when done
        char buf[200];
        int n1 = snprintf(buf, sizeof(buf), "IP Addr: %d.%d.%d.%d\n", ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);
        int n2 = snprintf(&buf[n1], sizeof(buf) - n1, "IP GW: %d.%d.%d.%d\n", ipgw[0], ipgw[1], ipgw[2], ipgw[3]);
        int n3 = snprintf(&buf[n1 + n2], sizeof(buf) - n1 - n2, "IP mask: %d.%d.%d.%d\n", ipmask[0], ipmask[1], ipmask[2], ipmask[3]);
        int n4 = snprintf(&buf[n1 + n2 + n3], sizeof(buf) - n1 - n2 - n3, "MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
            mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
        char *str = (char *)malloc(n1 + n2 + n3 + n4 + 1);
        memcpy(str, buf, n1 + n2 + n3 + n4);
        str[n1 + n2 + n3 + n4] = '\0';
        pdr->set_data_ptr(str);
        pdr->set_taken();
    }
}
