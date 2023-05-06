//
// Created by Алексей on 01.05.2023.
//

#pragma once

#include "i_route.h"


class UserFriendRoute : public IRoute {
private:
    int user_id_;
    std::unique_ptr<IDbModel> model_;

public:
    UserFriendRoute() = default;

    explicit UserFriendRoute(int user_id, std::unique_ptr<IDbModel> model = nullptr) :
            user_id_(user_id),
            model_(model.release()) {}

    MessageInfo Get(int id) override;

    MessageInfo Post(json::value body) override;

    MessageInfo Delete(int id) override;
};