//
// Created by Константин Беляков on 01.03.2025.
//

#ifndef BITOCEN_TCPMESSAGEIPART_H
#define BITOCEN_TCPMESSAGEIPART_H

#include <memory>
#include <string>

namespace tcp {

    class TcpMessageIPart;
    using TcpMessageIPartPtr = std::shared_ptr<TcpMessageIPart>;

    class TcpMessageIPart {
    public:
        TcpMessageIPart(const std::string& data) : data_(data) {}

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

#endif //BITOCEN_TCPMESSAGEIPART_H
