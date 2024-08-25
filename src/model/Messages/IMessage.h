//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_IMESSAGE_H
#define BITOCEN_IMESSAGE_H

#include <memory>
#include "json/JSONHelper.h"


namespace model {

    class IMessage;
    using IMessagePtr = std::shared_ptr<IMessage>;

    IMessagePtr make_message(const std::string& con_id, const std::string& data);

    class IMessage {
    public:
        virtual json::JSONObjectParserPtr get_json_parser() const = 0;
    };
}

#endif //BITOCEN_IMESSAGE_H
