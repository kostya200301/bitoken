//
// Created by Константин Беляков on 24.08.2024.
//

#include "TestMessage.h"

namespace model {

    TestMessage::TestMessage(const std::string& con_id, json::JSONObjectParserPtr json_builder)
                        : json_builder_(std::move(json_builder)),
                          con_id_(con_id) {}


    json::JSONObjectParserPtr TestMessage::get_json_parser() const {
        return json_builder_;
    }

}

