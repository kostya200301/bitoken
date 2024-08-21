//
// Created by Константин Беляков on 20.08.2024.
//

#ifndef BITOCEN_JSONHELPER_H
#define BITOCEN_JSONHELPER_H

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <simdjson.h>
#include <memory>


namespace json {

    class JSONObjectBuilder;
    using JSONObjectBuilderPtr = std::shared_ptr<JSONObjectBuilder>;

    class JSONObjectBuilder {
    private:
        rapidjson::Document document;
        rapidjson::Document::AllocatorType& allocator;

    public:
        JSONObjectBuilder() : document(), allocator(document.GetAllocator()) {
            document.SetObject();
        }

        const rapidjson::Document& getDocument() const{
            return document;
        }

        std::string dump() const;

        void addMember(const std::string& key, const std::string& value);
        void addMember(const std::string& key, int value);
        void addMember(const std::string& key, const JSONObjectBuilderPtr& value);
        void addMember(const std::string& key, const std::vector<JSONObjectBuilderPtr>& values);
        void addMember(const std::string& key, const std::vector<std::string>& values);

    };

    class JSONObjectParser;
    using JSONObjectParserPtr = std::shared_ptr<JSONObjectParser>;

    class JSONObjectParser {
    private:
        simdjson::dom::parser parser;
        simdjson::dom::element document;
    public:
        simdjson::dom::element parseJSON(const std::string& str);
    };

    JSONObjectBuilderPtr getEmptyJSON();

}


#endif //BITOCEN_JSONHELPER_H
