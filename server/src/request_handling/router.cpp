//
// Created by Алексей on 01.05.2023.
//

#include "request_handling/router.h"

ErrorCode Router::GetParam(const std::string &param, url::params_base::iterator &iter) {
    auto parameter = request_.parameters_.find(param);
    if (parameter == request_.parameters_.end()) {
        std::cerr << "Error: improper url parameters" << std::endl;
        return error;
    }

    iter = parameter;
    return success;
}

ErrorCode Router::ToIntWithCheck(const url::params_base::iterator &iter, int &param) {
    try {
        param = std::stoi((*iter).value);
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Error: invalid url parameters" << std::endl;
        return error;
    } catch (...) {
        std::cerr << "Unexpected error with parameters" << std::endl;
        return error;
    }

    return success;
}

MessageInfo Router::Route(const ParsedRequest &request) {
    request_ = request;

    if (request_.parameters_.find("user_id") == request_.parameters_.end() &&
        request_.path_.find("/user/auth") != std::string::npos) {
        if (request_.path_ == "/user/auth/check") {
            if (request_.method_ == http::verb::get) {
                url::params_base::iterator param;
                if (GetParam("login", param) == error) {
                    return {{}, http::status::bad_request};
                }
                std::string login = (*param).value;

                return std::make_unique<UserAuthCheckRoute>()->Get(login);
            }
        }
    }

    if (request_.path_ == "/user" && request_.method_ == http::verb::post) {
        return std::make_unique<UserRoute>()->Post(request_.body_);
    }

    if (request_.path_.empty()) {
        std::cerr << "Error: empty path" << std::endl;
        return {{}, http::status::bad_request};
    }
    if (request_.parameters_.empty()) {
        std::cerr << "Error: empty url parameters" << std::endl;
        return {{}, http::status::bad_request};
    }

    url::params_base::iterator param;
    if (GetParam("user_id", param) == error) { return {{}, http::status::bad_request}; }
    int user_id = 0;
    if (ToIntWithCheck(param, user_id) == error) { return {{}, http::status::bad_request}; }
    if (user_id <= 0) {
        std::cerr << "Error: Non-positive user id" << std::endl;
        return {{}, http::status::not_found};
    }

    GetParam("resource_id", param);
    int resource_id = 0;
    if (ToIntWithCheck(param, resource_id) == error) { resource_id = user_id; }
    if (resource_id <= 0) {
        std::cerr << "Error: Non-positive user id" << std::endl;
        return {{}, http::status::not_found};
    }

    std::unique_ptr<IRoute> route;
    if (request_.path_ == "/user") {
        route = std::make_unique<UserRoute>(user_id);
    }

    if (request_.path_ == "/video") {
        route = std::make_unique<VideoRoute>(user_id);
    }

    if (request_.path_ == "/video/all") {
        route = std::make_unique<VideoAllRoute>(user_id);
    }

    if (request_.path_ == "/video/list") {
        route = std::make_unique<VideoListRoute>(user_id);
    }

    if (request_.path_ == "/video/list/all") {
        route = std::make_unique<VideoListAllRoute>(user_id);
    }

    if (!route) {
        std::cerr << "Error: Improper path" << std::endl;
        return {{}, http::status::not_found};
    }

    switch (request_.method_) {
        case (http::verb::get): {
            return route->Get(resource_id);
        }
        case (http::verb::post): {
            return route->Post(request_.body_);
        }
        case (http::verb::delete_): {
            return route->Delete(resource_id);
        }
        default: {
            return {{}, http::status::method_not_allowed};
        }
    }
}
