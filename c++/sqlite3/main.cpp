#include <iostream>
#include <vector>

#include "sqlite3.h"



int main() {

	const char* dbName = "test_database.sqlite";
	// const char* dbName = ":memory:";
	// const char * dbName = "";

	sqlite3* handle = nullptr;
	if (sqlite3_open(dbName, &handle)) {
		std::cout << "sqlite3_open failed! " << sqlite3_errmsg(handle) << std::endl;
		return -1;
	}
	std::cout << "Successfully opened!" << std::endl;

	char * errMsg = nullptr;

	const std::string createQuery = "CREATE TABLE test_table(name, age, cource);";
#pragma region EX
	// const std::string createQuery = "CREATE TABLE IF NOT EXISTS test_table(name, age, cource);";
#pragma endregion
	if (sqlite3_exec(handle, createQuery.c_str(), /*callback*/nullptr, /*cb 1st argument*/nullptr, &errMsg)) {
		std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully created!" << std::endl;


	

	auto readCallback = [](void* context, int columns, char **data, char **names) -> int {
		if (!columns) {
			std::cout << "Empty result!" << std::endl;
			return 0;
		}

		if (!names) {
			std::cout << "No columns!" << std::endl;
			return 0;
		}

		std::cout << "Columns:" << std::endl;
		for (int i=0; i<columns; ++i) {
			if (i != 0)
				std::cout << '\t';
			std::cout << names[i];
		}
		std::cout << std::endl;

		if (!data) {
			std::cout << "No data!" << std::endl;
			return 0;
		}

		std::cout << "Data:" << std::endl;
		for (int i=0; i<columns; ++i) {
			if (i != 0)
				std::cout << '\t';
			std::cout << data[i];
		}
		std::cout << std::endl;

		return 0;
	};

	const std::string selectAllQuery = "SELECT * FROM test_table;";
	if (sqlite3_exec(handle, selectAllQuery.c_str(), /*callback*/readCallback, /*cb 1st argument*/nullptr, &errMsg)) {
		std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully selected!" << std::endl;





	const std::vector<const char *> insertQueries = {
		"INSERT INTO test_table VALUES('Ivan', 28, 1);",
		"INSERT INTO test_table VALUES('Andrew', 32, 2);",
		"INSERT INTO test_table VALUES('Alex', 48, 3);"
	};

	for (const auto& query : insertQueries)
		if (sqlite3_exec(handle, query, /*callback*/nullptr, /*cb 1st argument*/nullptr, &errMsg)) {
			std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
			sqlite3_free(errMsg);
			return -1;
		}		
	std::cout << "Successfully inserted!" << std::endl;

	


	if (sqlite3_exec(handle, selectAllQuery.c_str(), /*callback*/readCallback, /*cb 1st argument*/nullptr, &errMsg)) {
		std::cout << "sqlite3_exec with createQuery failed! " << errMsg << std::endl;
		sqlite3_free(errMsg);
		return -1;
	}
	std::cout << "Successfully selected!" << std::endl;


	return 0;
}