//
// Created by erico on 10/18/22.
//

#include "Ethernet.h"
/*#pragma push_macro("LOG")
#undef LOG*/

Ethernet::Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst):
        wiz(mosi, miso, sclk, cs, rst)  {}

void Ethernet::network_init() {
#ifdef LOG
    LOG("%ld: Started networking\n", uptime_sec);
#endif
    wiz.init(mac_addr);
    if(wiz.connect(NET_TIMEOUT_MS) != 0){
#ifdef LOG
        LOG("%ld: DHCP Failed!!\n", uptime_sec);
#endif
        is_net_connected = false;
        uptime_sec++;
        return;
    }
    is_net_connected  = true;
#ifdef LOG
    LOG("IP: %s\n" ,wiz.getIPAddress());
#endif
    uptime_sec++;
}

void Ethernet::socket_connect(const char* host, int port) {
#ifdef LOG
    LOG("%ld: Establishing TCP connection\n", uptime_sec);
#endif
    if(socket.connect(host, port, NET_TIMEOUT_MS) != 0){
#ifdef LOG
        LOG("%ld: Failed to establish TCP connection!!\n", uptime_sec);
#endif
        is_sock_connected = false;
        uptime_sec++;
        return;
    }
    is_sock_connected = true;
    socket.set_blocking(false);
#ifdef LOG
    LOG("%ld: Socked connected\n", uptime_sec);
#endif
    uptime_sec++;
}

void Ethernet::disconnect() {
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    wiz.disconnect();
#ifdef LOG
    LOG("%ld: Disconnected\n", uptime_sec);
#endif
    uptime_sec++;
}

void Ethernet::send_status() {
    uint32_t message_len_index = write_buffer.get_size();
    write_buffer.push(0); //placeholder for message length

    auto serialization_status = status.serialize(write_buffer);
    if(::EmbeddedProto::Error::NO_ERRORS == serialization_status)
    {
        write_buffer.get_data()[message_len_index] = write_buffer.get_size()-1;
        result = socket.send(reinterpret_cast<char *>(write_buffer.get_data()), (int) write_buffer.get_size());
        if (result < 0) {
#ifdef LOG
            LOG("Error! socket.send() returned: %d\n", result);
#endif
            disconnect();
        }
        else{
#ifdef LOG
            LOG("Status sent\n");
#endif
        }
    }
    write_buffer.clear();
}

void Ethernet::maintain_connection(const char* host, int port) {
    is_net_connected = (wiz.getIPAddress() != nullptr);
    is_sock_connected = socket.is_connected();
    if(!is_net_connected){
        network_init();
    }
    if(!is_sock_connected){
        socket_connect(host, port);
    }
}

void Ethernet::read_status() {
    // read from socket
    int bytes_read = socket.receive_all(reinterpret_cast<char *>(read_buffer.get_data()), BUFFER_SIZE);
    if(bytes_read == -1){
#ifdef LOG
        LOG("Failed to read from socket!!\n");
#endif
        return;
    }
#ifdef LOG
    LOG("Read from socket\n");
#endif
    read_buffer.set_bytes_written(bytes_read);
    auto deserialize_result = status.deserialize(read_buffer);
    if(deserialize_result != EmbeddedProto::Error::NO_ERRORS){
#ifdef LOG
        LOG("Failed to deserialize data!!\n");
#endif
        return;
    }
#ifdef LOG
    LOG("Deserialized received data\n");
#endif
    read_buffer.clear();
}

/*#pragma pop_macro("LOG")*/
