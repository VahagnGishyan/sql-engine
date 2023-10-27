#include <QtSql>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create an SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydb.db");

    if (!db.open()) {
        qDebug() << "Failed to open the database:" << db.lastError().text();
        return 1;
    }

    // Create a table
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, age INTEGER)")) {
        qDebug() << "Table creation failed:" << query.lastError().text();
        return 1;
    }

    // Insert data into the table
    query.prepare("INSERT INTO users (name, age) VALUES (?, ?)");
    query.addBindValue("John Doe");
    query.addBindValue(30);
    if (!query.exec()) {
        qDebug() << "Data insertion failed:" << query.lastError().text();
        return 1;
    }

    // Retrieve data from the table
    if (!query.exec("SELECT * FROM users")) {
        qDebug() << "Data retrieval failed:" << query.lastError().text();
        return 1;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int age = query.value(2).toInt();
        qDebug() << "ID:" << id << ", Name:" << name << ", Age:" << age;
    }

    // Close the database
    db.close();

    return 0;
}
