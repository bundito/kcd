#include "metadata.h"
#include "parsekdesrc.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <QStringList>
#include <QJsonObject>
#include <iterator>

#include <QSize>

#include <QDebug>

#include <KLocalizedString>

#include "kcdxml.h"
#include "kcdconfig.h"
#include "kcddatabase.h"

metadata::metadata()
{
    //m_metafile = getMetaData();
}

QString metadata::findMetaDir(QString sourceDir) {
    // hook into config

    // the metadata file should be $SRC/kde-build-metadata/logical-module-structure
    QString metaDir = sourceDir.append(QStringLiteral("/kde-build-metadata"));
    QDir md(metaDir);
    if (!md.exists()) {
        qDebug() << QStringLiteral("Metadata dir does not exist") << metaDir;
    }
    return metaDir;
}

QString metadata::findMetaFile(QString metaDir) {
    QString metaFile = metaDir.append(QStringLiteral("/logical-module-structure"));
    QFile mf(metaFile);
    if (!mf.exists()) {
        qDebug() << QStringLiteral("Metafile not found") << metaFile;
    }
    return metaFile;
}

QString metadata::getMetaData(QString sourceDir) {

    // The metadata file should be in ..src/kde-build-metadata
    QString metaDir = sourceDir.append(QStringLiteral("/kde-build-metadata"));

    QString mfLoc = sourceDir;
    mfLoc.append(QStringLiteral("/logical-module-structure"));

    QFile metaFile(mfLoc);

    qDebug() << mfLoc;

    if (!metaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << i18n("Metafile open failed.");
        qDebug() << mfLoc;
        exit(1);
    }

    QByteArray jsonData = metaFile.readAll();
    QJsonParseError *err = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

    if (err->error != 0) {
         //qDebug() << err->errorString();
    }

    QString dataDir = mfLoc;
    mfLoc.append(QStringLiteral("/kde-build-metadata"));


    kcdXML xml;
    xml.startXml(sourceDir.append(QStringLiteral("/kde-build-metadata")));
    //qDebug() << i18n("XML Result") << open;

    QJsonObject obj = doc.object();
    QVariantMap qvm = obj.toVariantMap();
    QVariantMap groups = qvm[QStringLiteral("groups")].toMap();

    QList<QString> item1 = groups.keys();

    KcdDatabase db;
    db.clearModuleTable();

    // ** THIS IS WHERE THE MAGIC HAPPENS **
    Q_FOREACH(QString val, item1) {
      //  qDebug() << val;
        db.addRow(val);
    }

    kcdConfig cfg;

    return xml.m_xmlFile;
}
