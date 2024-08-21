#include <miniupnpc/miniupnpc.h>
#include <miniupnpc/upnpcommands.h>
#include <miniupnpc/upnperrors.h>
#include <cstddef>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void setupPortForwarding(int port) {
    struct UPNPDev *devlist;
    struct UPNPUrls urls;
    struct IGDdatas data;
    char lanaddr[64];

    // Получение списка устройств UPnP в сети
    devlist = upnpDiscover(5000, NULL, NULL, 0, 0, 2, NULL);
    if (devlist) {
        int status = UPNP_GetValidIGD(devlist, &urls, &data, lanaddr, sizeof(lanaddr));
        if (status >= 1) {
            if (status == 2) {
                std::cerr << "Found multiple IGDs, using the first one: " << urls.controlURL << std::endl;
            }
            // Проброс порта
            char port_str[6];
            sprintf(port_str, "%d", port);
            int result = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
                                             port_str, port_str, lanaddr, "My P2P Node",
                                             "TCP", NULL, NULL);
            if (result == UPNPCOMMAND_SUCCESS) {
                std::cout << "Port forwarding setup successful!" << std::endl;
            } else {
                std::cerr << "Port forwarding failed: " << strupnperror(result) << std::endl;
            }
        } else {
            std::cerr << "No valid IGD found." << std::endl;
        }
        freeUPNPDevlist(devlist);
    } else {
        std::cerr << "No UPnP devices found." << std::endl;
    }
}

void startListening(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "Hello from the server!\n";

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Привязка сокета к порту (только SO_REUSEADDR)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Начало прослушивания порта
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening on port " << port << "..." << std::endl;

    // Ожидание и обработка входящих соединений
    while (true) {
        std::cout << "Waiting for connections..." << std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Чтение данных от клиента
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0) {
            std::cout << "Received: " << buffer << std::endl;
        } else {
            std::cerr << "Error reading from socket." << std::endl;
        }

        // Ответ клиенту
        if (send(new_socket, response, strlen(response), 0) < 0) {
            std::cerr << "Error sending response." << std::endl;
        } else {
            std::cout << "Response sent to client." << std::endl;
        }

        // Закрытие соединения с клиентом
        close(new_socket);
    }
}

int main() {
    const int PORT = 33433;

    // Настройка проброса порта
    setupPortForwarding(PORT);

    // Начало прослушивания на порту
    startListening(PORT);

    return 0;
}
