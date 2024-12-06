#include "cpp-httplib/httplib.h"
#include <sqlite3.h>
#include <sstream>

void generateReport(std::ostringstream& response) {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int exit = sqlite3_open("chip_design.db", &db);
    if (exit) {
        response << "{\"error\": \"Cannot open database\"}";
        return;
    }

    const char* query = "SELECT Type, Name FROM Components;";
    sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);

    response << "[";
    bool first = true;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        if (!first) response << ",";
        response << "{"
                 << "\"Type\":\"" << sqlite3_column_text(stmt, 0) << "\","
                 << "\"Name\":\"" << sqlite3_column_text(stmt, 1) << "\""
                 << "}";
        first = false;
    }

    response << "]";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    httplib::Server svr;

    svr.Get("/report", [](const httplib::Request&, httplib::Response& res) {
        std::ostringstream response;
        generateReport(response);
        res.set_content(response.str(), "application/json");
    });

    std::cout << "Server started at http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}
