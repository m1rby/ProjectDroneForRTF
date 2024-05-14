#ifndef DB_H
#define DB_H
using namespace std ;

void sqlread(sqlite3* db, const char* sql) {
    char* errmsg;
    int OpenDB = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
}


void initializeDroneDatabase() {
    sqlite3* droneDB;
    int OpenDB = sqlite3_open("DroneDatabase.db", &droneDB);
    const char* sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Drones ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Model TEXT NOT NULL, "
        "Weight INT NOT NULL, "
        "Max_Speed INT NOT NULL, "
        "Battery_Life INT NOT NULL, "
        "Current_Battery INT NOT NULL);";
    sqlread(droneDB, sqlCreateTable);

    // Заполнение таблицы случайными данными
    const char* models[] = { "Drone1", "Drone2", "Drone3", "Drone4" }; //Случайные модели возможные
    srand(time(NULL));
    int n = rand() % 11 + 10;

    for (int i = 0; i < n; i++) {
        char sqlInsert[512];
snprintf(sqlInsert, sizeof(sqlInsert),
    "INSERT INTO Drones (Model, Weight, Max_Speed, Battery_Life, Current_Battery) VALUES ('%s', %d, %d, %d, %d)",
    models[rand() % 4], rand() % 1000 + 500, rand() % 50 + 10, 100, rand() % 100 + 1); //Задаем случайные значения
        sqlread(droneDB, sqlInsert);
    }

    sqlite3_close(droneDB); //закрываем связь с бд
}

// Функция для вывода данных из базы данных дронов
void printDroneDatabaseContents() {
    sqlite3* droneDB;
    sqlite3_stmt* statement;  // Указатель
    int OpenDB = sqlite3_open("DroneDatabase.db", &droneDB);

    const char* sqlSelect = "SELECT ID, Model, Weight, Max_Speed, Battery_Life, Current_Battery FROM Drones;"; //Запрос sql
    OpenDB = sqlite3_prepare_v2(droneDB, sqlSelect, -1, &statement, NULL);
    //Читаем по строчкам
    while ((OpenDB = sqlite3_step(statement)) == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        const unsigned char* model = sqlite3_column_text(statement, 1);
        int weight = sqlite3_column_int(statement, 2);
        int maxSpeed = sqlite3_column_int(statement, 3);
        int batteryLife = sqlite3_column_int(statement, 4);
        int currentBattery = sqlite3_column_int(statement, 5);

        cout << "ID: " << id
            << ", Model: " << (model ? reinterpret_cast<const char*>(model) : "NULL") //случайный выбор модели
            << ", Weight: " << weight
            << ", Max_Speed: " << maxSpeed
            << ", Battery_Life: " << batteryLife
            << ", Current_Battery: " << currentBattery << endl;
    }

    sqlite3_close(droneDB);       // Закрываем соединение с базой данных
}

#endif // DB.H
