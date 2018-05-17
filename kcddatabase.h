#ifndef KCDDATABASE_H
#define KCDDATABASE_H
#include <QString>
#include <kcdconfig.h>
#include <QSqlDatabase>

class KcdDatabase
{
public:
    // constructor
    KcdDatabase();

    // public member vars
    QString m_dbFile;
    kcdConfig m_cfg;      // config file
    QSqlDatabase db;    // main database


    // methods
    bool connect();
    bool createTables();
    void addRow(QString val);
    QVariant getPath(QString pkg);

    void clearModuleTable();

};


#endif // KCDDATABASE_H
