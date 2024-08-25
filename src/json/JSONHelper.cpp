//
// Created by Константин Беляков on 20.08.2024.
//

#include "JSONHelper.h"
#include <string>
#include <vector>

namespace json {

    void JSONObjectBuilder::addMember(const std::string& key, const std::string& value) {
        rapidjson::Value jsonKey(key.c_str(), key.size(), allocator);
        rapidjson::Value jsonValue(value.c_str(), value.size(), allocator);

        document.AddMember(jsonKey, jsonValue, allocator);
    }

    void JSONObjectBuilder::addMember(const std::string& key, int value) {
        rapidjson::Value jsonKey(key.c_str(), key.size(), allocator);
        rapidjson::Value jsonValue(value);

        document.AddMember(jsonKey, jsonValue, allocator);
    }

    void JSONObjectBuilder::addMember(const std::string& key, const JSONObjectBuilderPtr& value) {
        rapidjson::Value jsonKey(key.c_str(), key.size(), allocator);

        const rapidjson::Value& nestedDocument = value->getDocument();

        rapidjson::Value copyOfNestedDocument;
        copyOfNestedDocument.CopyFrom(nestedDocument, allocator);

        document.AddMember(jsonKey, copyOfNestedDocument, allocator);
    }

    void JSONObjectBuilder::addMember(const std::string& key, const std::vector<JSONObjectBuilderPtr>& values) {
        rapidjson::Value jsonKey(key.c_str(), key.size(), allocator);
        rapidjson::Value jsonArray(rapidjson::kArrayType);

        for (const auto& value : values) {
            const rapidjson::Value& nestedDocument = value->getDocument();
            rapidjson::Value copyOfNestedDocument;
            copyOfNestedDocument.CopyFrom(nestedDocument, allocator);
            jsonArray.PushBack(copyOfNestedDocument, allocator);
        }

        document.AddMember(jsonKey, jsonArray, allocator);
    }

    void JSONObjectBuilder::addMember(const std::string& key, const std::vector<std::string>& values) {
        rapidjson::Value jsonKey(key.c_str(), key.size(), allocator);
        rapidjson::Value jsonArray(rapidjson::kArrayType);

        for (const auto& value : values) {
            rapidjson::Value val(value.c_str(), value.size(), allocator);
            jsonArray.PushBack(val, allocator);
        }

        document.AddMember(jsonKey, jsonArray, allocator);
    }

    std::string JSONObjectBuilder::dump() const {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        return buffer.GetString();
    }

    JSONObjectBuilderPtr getEmptyJSON() {
        return std::make_shared<JSONObjectBuilder>();
    }

    simdjson::dom::element JSONObjectParser::parseJSON(const std::string& str) {
        error = parser.parse(str).get(document);
        return document;
    }

    simdjson::dom::element JSONObjectParser::get_json() const {
        return document;
    }
}
