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

metadata::metadata()
{
    m_metafile = findMetaFile();
}

QString metadata::findMetaFile() {

    // The metadata file should be in ..src/kde-build-metadata

    ParseKdesrc pk;
    QString pk1 = pk.findRcFile();
    QString pk2 = pk.parseFile();
    QString mfLoc = pk.getSourceDir();
    mfLoc.append(QStringLiteral("/kde-build-metadata/logical-module-structure"));

    QFile metaFile(mfLoc);

    qDebug() << mfLoc;

    if (!metaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return i18n("Unable to read file.");
    }

    QByteArray jsonData = metaFile.readAll();
    QJsonParseError *err = new QJsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, err);

    if (err->error != 0) {
         qDebug() << err->errorString();
    }


    QJsonObject obj = doc.object();
    QVariantMap qvm = obj.toVariantMap();
    QVariantMap groups = qvm[QStringLiteral("groups")].toMap();

    QList<QString> item1 = groups.keys();

    Q_FOREACH(QString val, item1) {
        qDebug() << val;
    }

    qDebug() << item1[12];

    //qDebug() << first;



        return i18n("Success");

}
