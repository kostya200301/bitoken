//
// Created by Константин Беляков on 01.03.2025.
//

#ifndef BITOCEN_TCPMESSAGEDPART_H
#define BITOCEN_TCPMESSAGEDPART_H

#include <memory>
#include <string>

namespace tcp {

    class TcpMessageDPart;
    using TcpMessageDPartPtr = std::shared_ptr<TcpMessageDPart>;

    class TcpMessageDPart {
    public:
        TcpMessageDPart(const std::string& data) : data_(data) {}

        std::string get_data() const {
            return data_;
        }

        std::string get_clear_data() const {
            return data_.substr(1, data_.size() - 2);
        }
    private:
        std::string data_;
    };

}

#endif //BITOCEN_TCPMESSAGEDPART_H
