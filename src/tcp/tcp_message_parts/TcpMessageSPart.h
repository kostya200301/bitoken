//
// Created by Константин Беляков on 01.03.2025.
//

#ifndef BITOCEN_TCPMESSAGESPART_H
#define BITOCEN_TCPMESSAGESPART_H

#include <cstddef>
#include <string>

namespace tcp {

    extern const size_t TCPMessageSPartSIZE;
    extern const std::string TCPMessageSPartBaseString;

    class TcpMessageSPart;
    using TcpMessageSPartPtr = std::shared_ptr<TcpMessageSPart>;

    class TcpMessageSPart {
    public:
        TcpMessageSPart(int info_part_size, int data_part_size) :
                                        info_part_size_(info_part_size),
                                        data_part_size_(data_part_size) {}

        int get_info_part_size() {return info_part_size_;};

        int get_data_part_size() {return data_part_size_;};

    private:
        int info_part_size_;
        int data_part_size_;
    };

}

#endif //BITOCEN_TCPMESSAGESPART_H
