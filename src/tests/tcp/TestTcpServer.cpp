#include <iostream>
#include "catch2/catch.hpp"
#include "tcp/TcpServer.h"
#include "crypto/CryptoHelper.h"


TEST_CASE("Test tcp", "[model][unit][coverage]") {
    CHECK(1 == 1);
    try {
        boost::asio::io_context io_context;

        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
        ssl_context.set_options(boost::asio::ssl::context::default_workarounds |
                                boost::asio::ssl::context::no_sslv2 |
                                boost::asio::ssl::context::single_dh_use);

        // Загрузка сертификата из строки
        ssl_context.use_certificate_chain(
                boost::asio::buffer(crypto::CryptoHelper::getCertCrt()));

        // Загрузка закрытого ключа из строки
        ssl_context.use_private_key(
                boost::asio::buffer(crypto::CryptoHelper::getCertKey()),
                boost::asio::ssl::context::pem);

        // Загрузка параметров DH из строки
        ssl_context.use_tmp_dh(
                boost::asio::buffer(crypto::CryptoHelper::getCertPem()));


        tcp::TcpServer server(io_context, ssl_context, 12345);

        server.start_accept();

        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}