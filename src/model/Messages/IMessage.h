//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_IMESSAGE_H
#define BITOCEN_IMESSAGE_H

#include <memory>


namespace model {

    class IMessage;
    using IMessagePtr = std::shared_ptr<IMessage>;

    IMessagePtr make_message(const std::string& con_id, const std::string& data);

    class IMessage {

    };
}

#endif //BITOCEN_IMESSAGE_H
