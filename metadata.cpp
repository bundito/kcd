#include "metadata.h"
#include "parsekdesrc.h"

#include <QFile>
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

metadata::metadata()
{
    //m_metafile = getMetaData();
}

QString metadata::getMetaData(QString sourceDir) {

    // The metadata file should be in ..src/kde-build-metadata

    qDebug() << i18n("Hello from metadata");

    QString mfLoc = sourceDir;
    mfLoc.append(QStringLiteral("/kde-build-metadata/logical-module-structure"));

    QFile metaFile(mfLoc);

    qDebug() << mfLoc;

    if (!metaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << i18n("Metafile open failed.");
        return i18n("Unable to read file.");
    }

    QByteArray jsonData = metaFile.readAll();
    QJsonParseError *err = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

    if (err->error != 0) {
         qDebug() << err->errorString();
    }

    QString dataDir = mfLoc;
    mfLoc.append(QStringLiteral("/kde-build-metadata"));

    kcdXML xml;
    xml.findXML(sourceDir.append(QStringLiteral("/kde-build-metadata")));
    //qDebug() << i18n("XML Result") << open;

    QJsonObject obj = doc.object();
    QVariantMap qvm = obj.toVariantMap();
    QVariantMap groups = qvm[QStringLiteral("groups")].toMap();

    QList<QString> item1 = groups.keys();

    xml.openXML();
    qint16 count = 0;
    Q_FOREACH(QString val, item1) {
      //  qDebug() << val;
        xml.addEntry(val);
        count++;
    }

    xml.closeXML();

    kcdConfig cfg;
    cfg.storeData(QStringLiteral("total"), count);
    cfg.storeData(QStringLiteral("installed"), xml.m_total);

    return xml.m_xmlFile;
}
