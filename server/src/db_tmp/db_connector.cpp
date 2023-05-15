//
// Created by Алексей on 14.05.2023.
//

#include "db_tmp/db_connector.h"


QSqlQuery DbConnectorTmp::MakeQuery(QString query_string) {
    Connect();

    QSqlQuery query(connection_);

    if (!query.exec(query_string)) {
        throw ConditionError(query.lastError().text().toStdString());
    }

    if (!query.isActive()) {
        throw ConditionError("Cant make request");
    }

    std::cout << "Query executed successfully" << std::endl;
    std::cout << "Amount of rows read: " << query.size() << std::endl;

    return query;
}

void DbConnectorTmp::Connect() {
    if (connection_.isOpen()) {
        return;
    }

    connection_ = QSqlDatabase::addDatabase("QPSQL");
    connection_.setDatabaseName(db_name_);
    connection_.setHostName("localhost");
    connection_.setUserName("aleksej");
    connection_.setPassword("postgres");

    bool is_open = connection_.open();

    if (!is_open) {
        throw DbConnectError("Cant connect to db");
    }
}


DbConnectorTmp::~DbConnectorTmp() {
    Disconnect();
}

void DbConnectorTmp::Disconnect() {
    if (connection_.isOpen()) {
        connection_.close();
    }
}
