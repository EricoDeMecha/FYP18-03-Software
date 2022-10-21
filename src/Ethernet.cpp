//
// Created by erico on 10/18/22.
//

#include "Ethernet.h"

Ethernet::Ethernet(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName rst):
        wiz(mosi, miso, sclk, cs, rst)  {}

void Ethernet::network_init() {
    log("%ld: Started networking\n", uptime_sec);
    wiz.init(mac_addr);
    if(wiz.connect(NET_TIMEOUT_MS) != 0){
        log("%ld: DHCP Failed!!\n", uptime_sec);
        is_net_connected = false;
        uptime_sec++;
        return;
    }
    is_net_connected  = true;
    log("IP: %s\n" ,wiz.getIPAddress());
    uptime_sec++;
}

void Ethernet::socket_connect() {
    log("%ld: Establishing TCP connection\n", uptime_sec);
    if(socket.connect(HOST, PORT, NET_TIMEOUT_MS) != 0){
        log("%ld: Failed to establish TCP connection!!\n", uptime_sec);
        is_sock_connected = false;
        uptime_sec++;
        return;
    }
    is_sock_connected = true;
    socket.set_blocking(false);
    log("%ld: Socked connected\n", uptime_sec);
    uptime_sec++;
}

void Ethernet::disconnect() {
    // Close the socket to return its memory and bring down the network interface
    socket.close();
    // Bring down the ethernet interface
    wiz.disconnect();
    log("%ld: Disconnected\n", uptime_sec);
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
            log("Error! socket.send() returned: %d\n", result);
            disconnect();
        }
        else{
            log("Status sent\n");
        }
    }
    write_buffer.clear();
}

void Ethernet::maintain_connection() {
    is_net_connected = (wiz.getIPAddress() != nullptr);
    is_sock_connected = socket.is_connected();
    if(!is_net_connected){
        network_init();
    }
    if(!is_sock_connected){
        socket_connect();
    }
}

void Ethernet::read_status() {
    // read from socket
    int bytes_read = socket.receive_all(reinterpret_cast<char *>(read_buffer.get_data()), BUFFER_SIZE);
    if(bytes_read == -1){
        log("Failed to read from socket!!\n");
        return;
    }
    log("Read from socket\n");
    read_buffer.set_bytes_written(bytes_read);
    auto deserialize_result = status.deserialize(read_buffer);
    if(deserialize_result != EmbeddedProto::Error::NO_ERRORS){
        log("Failed to deserialize data!!\n");
        return;
    }
    log("Deserialized received data\n");
    read_buffer.clear();
}


