#ifndef NONETWORK

#ifndef _NETWORK_H
#define _NETWORK_H

#include "timer.h"
#include "Module.h"

#include "net/PassiveSocket.h"
#include <thread>

class Sftpd;
class CommandQueue;
class Telnetd;

class Network : public Module
{
public:
    Network();
    virtual ~Network();

    void on_module_loaded();
    void on_idle(void* argument);
    void on_main_loop(void* argument);
    void on_get_public_data(void* argument);
    void dhcpc_configured(uint32_t ipaddr, uint32_t ipmask, uint32_t ipgw);
    void tapdev_send(void *pPacket, unsigned int size);

    // accessed from C
    Sftpd *sftpd;
    Telnetd *telnetd;
    struct {
        bool webserver_enabled:1;
        bool telnet_enabled:1;
        bool plan9_enabled:1;
        bool use_dhcp:1;
    };

    CPassiveSocket* socket;
    std::thread *network_thread;

private:
    void init();
    void setup_servers();
    uint32_t tick(uint32_t dummy);
    void handlePacket();
    void thread_main();

    CommandQueue *command_q;

    char *hostname;
    volatile uint32_t tickcnt;
    uint8_t mac_address[6];
    uint8_t ipaddr[4];
    uint8_t ipmask[4];
    uint8_t ipgw[4];
};

#endif

#endif