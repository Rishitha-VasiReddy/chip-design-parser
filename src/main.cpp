#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sqlite3.h>
#include <thread>
#include <vector>

// Initialize the SQLite database
void initializeDatabase() {
    sqlite3* db;
    char* errorMessage;

    int exit = sqlite3_open("chip_design.db", &db);
    if (exit) {
        std::cerr << "Error: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Drop the table if it exists (optional, for debugging purposes)
    const char* dropTableQuery = "DROP TABLE IF EXISTS Components;";
    sqlite3_exec(db, dropTableQuery, nullptr, nullptr, &errorMessage);

    // Create the Components table
    const char* createTableQuery =
        "CREATE TABLE IF NOT EXISTS Components ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Type TEXT NOT NULL, "
        "Name TEXT NOT NULL, "
        "Details TEXT);"; // Ensure Details column is included

    exit = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error: SQL error in CREATE TABLE query: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Database initialized and table created successfully!" << std::endl;
    }

    sqlite3_close(db);
}



// Insert data into the database
void insertIntoDatabase(const std::string& type, const std::string& name, const std::string& details = "") {
    sqlite3* db;
    char* errorMessage;

    int exit = sqlite3_open("../chip_design.db", &db);
    if (exit) {
        std::cerr << "Error: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string insertQuery = "INSERT INTO Components (Type, Name, Details) VALUES ('" + type + "', '" + name + "', '" + details + "');";
    exit = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Error: SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Inserted into database: " << type << ", " << name << ", " << details << std::endl;
    }

    sqlite3_close(db);
}

// Parse Verilog file
void parseVerilogFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    std::regex moduleRegex(R"(module\s+(\w+)\s*;)");
    std::regex wireRegex(R"(wire\s+(\w+)\s*;)");
    std::regex inputRegex(R"(input\s+(\w+)\s*;)");
    std::regex outputRegex(R"(output\s+(\w+)\s*;)");
    std::regex assignRegex(R"(assign\s+(\w+)\s*=\s*(.+)\s*;)");
    std::regex endmoduleRegex(R"(endmodule)");

    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_match(line, match, moduleRegex)) {
            std::cout << "Module definition found: " << match[1] << std::endl;
            insertIntoDatabase("Module", match[1]);
        } else if (std::regex_match(line, match, wireRegex)) {
            std::cout << "Wire definition found: " << match[1] << std::endl;
            insertIntoDatabase("Wire", match[1]);
        } else if (std::regex_match(line, match, inputRegex)) {
            std::cout << "Input definition found: " << match[1] << std::endl;
            insertIntoDatabase("Input", match[1]);
        } else if (std::regex_match(line, match, outputRegex)) {
            std::cout << "Output definition found: " << match[1] << std::endl;
            insertIntoDatabase("Output", match[1]);
        } else if (std::regex_match(line, match, assignRegex)) {
            std::cout << "Assign statement found: " << match[1] << " = " << match[2] << std::endl;
            insertIntoDatabase("Assign", match[1], match[2]);
        } else if (std::regex_match(line, endmoduleRegex)) {
            std::cout << "End of module found." << std::endl;
        } else if (!line.empty()) {
            std::cerr << "Unrecognized line: " << line << std::endl;
        }
    }

    file.close();
}

// Generate a report of all parsed components
void generateReport() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int exit = sqlite3_open("chip_design.db", &db);
    if (exit) {
        std::cerr << "Error: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* query = "SELECT Type, Name, Details FROM Components;";
    exit = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Error: SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "\n--- Report: Parsed Components ---\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "Type: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0))
                  << ", Name: " << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))
                  << ", Details: " << (sqlite3_column_text(stmt, 2) ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)) : "N/A")
                  << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


// Optimize the parsed design
void optimizeDesign() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    int exit = sqlite3_open("chip_design.db", &db);
    if (exit) {
        std::cerr << "Error: Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char* query = "SELECT Name FROM Components WHERE Type = 'Wire';";
    exit = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Error: SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "\n--- Optimization Suggestions ---\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string wire = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::cout << "Optimize wire: " << wire << " (e.g., check for redundancy or improve timing)." << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Main function
int main(int argc, char* argv[]) {
    initializeDatabase();

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1.v> <file2.v> ..." << std::endl;
        return 1;
    }

    std::vector<std::thread> threads;
    for (int i = 1; i < argc; ++i) {
        threads.emplace_back(parseVerilogFile, argv[i]);
    }

    for (auto& t : threads) {
        t.join();
    }

    optimizeDesign();
    generateReport();

    return 0;
}
