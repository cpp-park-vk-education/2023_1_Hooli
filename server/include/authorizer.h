//
// Created by Алексей on 01.05.2023.
//

#include <QCryptographicHash>

#pragma once

#include "i_authorizer.h"


class Authorizer : public IAuthorizer {
public:
    json::value Authorise() override;

    json::value Register() override;

    bool IsAuthorised() override;
};
