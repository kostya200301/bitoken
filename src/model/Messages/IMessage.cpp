#include "IMessage.h"
#include "json/JSONHelper.h"
#include <spdlog/spdlog.h>

#include "TestMessage.h"

namespace model {

    IMessagePtr make_message(const std::string& con_id, const std::string& data) {
        json::JSONObjectParserPtr parser = std::make_shared<json::JSONObjectParser>();
        auto doc = parser->parseJSON(data);
        if (parser->get_error() != simdjson::error_code::SUCCESS) {
            std::cerr << "JSON parsing error: " << simdjson::error_message(parser->get_error());
            return nullptr;
        }
        auto type = doc["type"].get_string();
        if (type.value().compare("TestMessage") == 0) {
            return std::make_shared<TestMessage>(con_id, parser);
        }
        return nullptr;

    }

    IMessagePtr make_message(const std::string& con_id, const tcp::TcpMessagePartsPtr& tcp_parts) {
        json::JSONObjectParserPtr parser_info = std::make_shared<json::JSONObjectParser>();
        auto doc_info = parser_info->parseJSON(tcp_parts->get_i_part()->get_clear_data());
        if (parser_info->get_error() != simdjson::error_code::SUCCESS) {
            std::cerr << "JSON parsing error: " << simdjson::error_message(parser_info->get_error());
            return nullptr;
        }

        json::JSONObjectParserPtr parser_data = std::make_shared<json::JSONObjectParser>();
        auto doc_data = parser_data->parseJSON(tcp_parts->get_d_part()->get_clear_data());
        if (parser_data->get_error() != simdjson::error_code::SUCCESS) {
            std::cerr << "JSON parsing error: " << simdjson::error_message(parser_data->get_error());
            return nullptr;
        }

        auto type = doc_info["type"].get_string();
        if (type.value().compare("TestMessage") == 0) {
            return std::make_shared<TestMessage>(con_id, parser_data);
        }
        return nullptr;

    }

}
