//
// Created by Алексей on 01.05.2023.
//

#pragma once

#include "request_handling/i_route.h"


class UserRoute : public IRoute {
private:
    int user_id_;
    std::unique_ptr<IDbModel> model_;
    std::unique_ptr<IDbConnectorTmp> db_connector_;

public:
    UserRoute() = default;

    explicit UserRoute(int user_id, std::unique_ptr<IDbModel> model = nullptr) :
            user_id_(user_id),
            model_(model.release()),
            db_connector_(std::make_unique<DbConnectorTmp>()) {}

    MessageInfo Get(int id) override;

    MessageInfo Post(json::value body) override;

    MessageInfo Delete(int id) override;
};
