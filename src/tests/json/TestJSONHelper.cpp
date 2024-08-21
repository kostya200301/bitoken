#include <iostream>
#include <catch2/catch.hpp>
#include "json/JSONHelper.h"
#include <vector>
#include <chrono>

TEST_CASE("Test json methods", "[model][unit][coverage]") {

    auto jsonObj =  json::getEmptyJSON();
    jsonObj->addMember("asd", "asd");
    jsonObj->addMember("asd2", 123);
    jsonObj->addMember("asd22", 123);
    jsonObj->addMember("asd23", {"asdasd", "qdwdqwd", "qdwdqw", "dqdq"});
    auto jsonObj2 =  json::getEmptyJSON();
    jsonObj2->addMember("asdas1", 1231);
    jsonObj2->addMember("asdas2", {"dqwdwqdqw", "dqdqwd", "dqwdqwd"});
    jsonObj2->addMember("asdas22", {"dqwdwqdqw", "dqdqwd", "dqwdqwd"});
    jsonObj2->addMember("asdas23", {"dqwdwqdqw", "dqdqwd", "dqwdqwd"});
    jsonObj->addMember("asd245", jsonObj2);

    std::string dump = jsonObj->dump();
    CHECK(dump == "{\"asd\":\"asd\",\"asd2\":123,\"asd22\":123,\"asd23\":[\"asdasd\",\"qdwdqwd\",\"qdwdqw\",\"dqdq\"],\"asd245\":{\"asdas1\":1231,\"asdas2\":[\"dqwdwqdqw\",\"dqdqwd\",\"dqwdqwd\"],\"asdas22\":[\"dqwdwqdqw\",\"dqdqwd\",\"dqwdqwd\"],\"asdas23\":[\"dqwdwqdqw\",\"dqdqwd\",\"dqwdqwd\"]}}");
    json::JSONObjectParser parser;
    auto parseRes = parser.parseJSON(dump);
    auto name = parseRes["asd"].get_string();
    CHECK(std::string(name.value()) == "asd");
    CHECK(name.value().compare("asd") == 0);

    std::string strWithError = "{\"ff\":123}";
    auto parseRes_ = parser.parseJSON(strWithError);
    auto name_ = parseRes_["ff"].get_int64();
    CHECK(name_.value() == 123);


}
