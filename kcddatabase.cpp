#include "kcddatabase.h"
#include "kcdconfig.h"

#include <QDir>
#include <QUrl>
#include <QString>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

#include <KLocalizedString>

// thanks to Andrius Štikonas for this little trick
#define QSL(x) (QStringLiteral(x))



KcdDatabase::KcdDatabase()
{
    m_dbFile = QStringLiteral("/kcd.db");
    kcdConfig m_cfg;
    QSqlQuery sql;
}

bool KcdDatabase::connect() {

   QString dbDir = m_cfg.getParameter(QStringLiteral("metaDir"));
   QString dbName = dbDir.append(QStringLiteral("/kcd.db"));

   qDebug() << dbName;

   db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
   db.setHostName(QStringLiteral("localhost"));
   db.setDatabaseName(dbName);
   db.setUserName(QStringLiteral("kde"));
   db.setPassword(QStringLiteral("kde"));
   bool ok = db.open();

   if (!ok) {
       return false;
   }

   qDebug() << i18n("DB exists; scope it out.");

    QSqlQuery sql(db);
    bool test = sql.exec(QStringLiteral("SELECT timestamp FROM meta"));

    if (test) {
        qDebug() << i18n("DB exists and is populated");

    } else {
        QSqlError err = sql.lastError();
        qDebug() << i18n("DB Error:") << err;
        qDebug() << i18n("DB exists, needs filling");
        bool createOk = createTables();
        qDebug() << QSL("Create:") << createOk;
        return createOk;
    }

   return true;
}

bool KcdDatabase::createTables() {

    QSqlQuery sql(db);
    bool meta = sql.exec(QSL("CREATE TABLE meta ( \
                timestamp text NOT NULL, \
                modulesTotal int NOT NULL, \
                modulesInstalled int NOT NULL \
                ) " \
                ));
    qDebug() << sql.lastError();

    bool mods = sql.exec(QSL("CREATE TABLE modules ( \
                name text NOT NULL, \
                path text NOT NULL, \
                installed int NOT NULL, \
                alias text NOT NULL \
                ) " \
                ));
    qDebug() << sql.lastError();
    return (meta || mods);
}

void KcdDatabase::addRow(QString val) {

    qDebug() << QSL("val:") << val;

    if (!db.isOpen()) {
        connect();
    }

    kcdConfig cfg;

    bool installed = 1;      // sqlite uses 1/0 instead of true/false
    QString dir = cfg.getParameter(QSL("sourceDir")).append(QSL("/"));
    dir.append(val);
    QDir modLoc(dir);
    if (!modLoc.exists()) {
        installed = 0;
    }

    // QUrl.fragment easily pulls off from the final slash
    QUrl url = QUrl::fromLocalFile(dir);
    qDebug() << "Url" << url;
    QString name = url.fileName();

    qDebug() << QSL("name:") << name;

    QSqlQuery sql(db);

    sql.prepare(QSL("INSERT INTO modules \
                   ( name, path, installed, alias ) \
                   VALUES (:name, :path, :installed, :alias) \
                   "));

    sql.bindValue(QSL(":name"), name);
    sql.bindValue(QSL(":path"), dir);
    sql.bindValue(QSL(":installed"), installed);
    sql.bindValue(QSL(":alias"), QSL(""));

    bool insert = sql.exec();
    if (!insert) {
        qDebug() << QSL("Insert failed:") << sql.lastError();
    }

    db.commit();

}

QVariant KcdDatabase::getPath(QString pkg) {

    if (!db.isOpen()) {
        connect();
    }

    QSqlQuery sql(db);

    qDebug() << QSL("pkg") << pkg;

    sql.prepare(QSL("SELECT path FROM modules WHERE name=:name;"));
    sql.bindValue(QSL(":name"), pkg);
    bool ok = sql.exec();
    qDebug() << QSL("select:") << ok;
    qDebug() << QSL("error:") << sql.lastError();
    sql.first();
    QVariant result = sql.value(0);
    qDebug() << result;
    //QString result = QSL("test");
    return result;

}

void KcdDatabase::clearModuleTable() {

    // should be faster to dump the table contents than try to update

    if (!db.isOpen()) {
        connect();
    }

    QSqlQuery sql(db);

    sql.prepare(QSL("DELETE from modules WHERE 1=1;"));
    sql.exec();
    return;


}
