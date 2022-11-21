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
    LOG("%zu: Started networking\n", ++uptime_sec);
#endif
    wiz.init(mac_addr, IP, IP_MASK, IP_GATEWAY);
    if(wiz.connect() != 0){
#ifdef LOG
        LOG("%zu: DHCP Failed!!\n", ++uptime_sec);
#endif
        is_net_connected = false;
        return;
    }
    is_net_connected  = true;
#ifdef LOG
    LOG("IP: %s\n" ,wiz.getIPAddress());
#endif
}

void Ethernet::socket_connect(const char* host, int port) {
#ifdef LOG
    LOG("%zu: Establishing TCP connection\n", ++uptime_sec);
    LOG("%zu:%s->%s:%d\n", ++uptime_sec,wiz.getIPAddress(),host, port);
#endif
    if(socket.connect(host, port) != 0){
#ifdef LOG
        LOG("%zu: Failed to establish TCP connection!!\n", ++uptime_sec);
#endif
        is_sock_connected = false;
        return;
    }
    is_sock_connected = true;
    socket.set_blocking(false);
#ifdef LOG
    LOG("%zu: Socket connected\n", ++uptime_sec);
#endif
}

void Ethernet::disconnect() {
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    wiz.disconnect();
#ifdef LOG
    LOG("%zu: Disconnected\n", ++uptime_sec);
#endif
}

void Ethernet::maintain_connection(const char* host, int port) {
    // reset uptime
    if(uptime_sec > 99){ uptime_sec = 0; }
    is_net_connected = (strcmp(wiz.getIPAddress(),"0.0.0.0") != 0);
    is_sock_connected = socket.is_connected();
    if(!is_net_connected){
        network_init();
    }
    if(!is_sock_connected){
        socket_connect(host, port);
    }
}


void Ethernet::send_data() {
    uint32_t message_len_index = write_buffer.get_size();
    write_buffer.push(0); //placeholder for message length

    auto serialization_status = m_reply.serialize(write_buffer);
    if(::EmbeddedProto::Error::NO_ERRORS == serialization_status){
        write_buffer.get_data()[message_len_index] = write_buffer.get_size()-1;
        result = socket.send(reinterpret_cast<char *>(write_buffer.get_data()), (int) write_buffer.get_size());
        if (result < 0) {
#ifdef LOG
            LOG("%zu: Error! socket.send() returned: %d\n", ++uptime_sec, result);
#endif
//            disconnect();
            socket.close();
        }
        else{
#ifdef LOG
            LOG("%zu: Status sent\n", ++uptime_sec);
#endif
        }
    }
    write_buffer.clear();
}

void Ethernet::read_data() {
    // read from socket
    int bytes_read = socket.receive_all(reinterpret_cast<char *>(read_buffer.get_data()), BUFFER_SIZE);
    if(bytes_read == -1){
#ifdef LOG
        LOG("%zu: Failed to read from socket!!\n", ++uptime_sec);
#endif
        return;
    }
#ifdef LOG
    LOG("%zu: Read from socket\n", ++uptime_sec);
#endif
    read_buffer.set_bytes_written(bytes_read);
    auto deserialize_result = m_command.deserialize(read_buffer);
    if(deserialize_result != EmbeddedProto::Error::NO_ERRORS){
#ifdef LOG
        LOG("%zu: Failed to deserialize data!!\n", ++uptime_sec);
#endif
        return;
    }
#ifdef LOG
    LOG("%zu: Deserialized received data\n", ++uptime_sec);
#endif
    read_buffer.clear();
}

/*#pragma pop_macro("LOG")*/
