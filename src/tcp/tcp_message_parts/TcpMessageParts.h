//
// Created by Константин Беляков on 01.03.2025.
//

#ifndef BITOCEN_TCPMESSAGEPARTS_H
#define BITOCEN_TCPMESSAGEPARTS_H

#include "TcpMessageSPart.h"
#include "TcpMessageIPart.h"
#include "TcpMessageDPart.h"

namespace tcp {

    class TcpMessageParts;
    using TcpMessagePartsPtr = std::shared_ptr<TcpMessageParts>;

    class TcpMessageParts {
    public:
        TcpMessageParts() : s_part_(nullptr), i_part_(nullptr), d_part_(nullptr) {}

        TcpMessageParts(const TcpMessageSPartPtr& s_part, const TcpMessageIPartPtr& i_part, const TcpMessageDPartPtr& d_part) :
                    s_part_(s_part), i_part_(i_part), d_part_(d_part) {}

        void set_s_part(const TcpMessageSPartPtr& s_part) {
            s_part_ = s_part;
        }

        void set_i_part(const TcpMessageIPartPtr& i_part) {
            i_part_ = i_part;
        }

        void set_d_part(const TcpMessageDPartPtr& d_part) {
            d_part_ = d_part;
        }

        TcpMessageSPartPtr get_s_part() {
            return s_part_;
        }

        TcpMessageIPartPtr get_i_part() {
            return i_part_;
        }

        TcpMessageDPartPtr get_d_part() {
            return d_part_;
        }

    private:
        TcpMessageSPartPtr s_part_;
        TcpMessageIPartPtr i_part_;
        TcpMessageDPartPtr d_part_;
    };

}


#endif //BITOCEN_TCPMESSAGEPARTS_H
