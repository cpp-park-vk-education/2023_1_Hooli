//
// Created by Алексей on 09.05.2023.
//

#pragma once

#include <boost/asio/strand.hpp>
#include <chrono>
#include <functional>
#include <memory>

#include "i_client.h"
#include "message_info.h"
#include "response_handler.h"


class ClientHttp : public IClient {
public:
<<<<<<< HEAD
    ClientHttp(http::request<http::string_body> request) :
=======
    explicit ClientHttp(http::request<http::string_body> request) :
>>>>>>> c98f5213f2e8d43f918ec8782d2e47008bf30fc4
            resolver_(net::make_strand(ioc_)),
            stream_(net::make_strand(ioc_)),
            response_handler_(std::make_unique<ResponseHandler>()),
            request_(std::move(request)) {}

    void Run(
            const std::string &host,
            const std::string &port,
            const std::string &target
    ) override;

    MessageInfo GetResponse() override;

private:
    net::io_context ioc_;
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    http::request<http::string_body> request_;
    http::response<http::string_body> response_;
    beast::flat_buffer buffer_;
    std::unique_ptr<IResponseHandler> response_handler_;

private:
    void Write();

};

