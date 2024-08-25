//
// Created by Константин Беляков on 24.08.2024.
//

#ifndef BITOCEN_TESTMESSAGE_H
#define BITOCEN_TESTMESSAGE_H

#include "json/JSONHelper.h"
#include "model/Messages/IMessage.h"

namespace model {

    class TestMessage : public IMessage {
    public:
        TestMessage(const std::string& con_id, json::JSONObjectParserPtr json_builder);
    private:
        json::JSONObjectParserPtr json_builder_;

        std::string con_id_;
    };

}


#endif //BITOCEN_TESTMESSAGE_H
