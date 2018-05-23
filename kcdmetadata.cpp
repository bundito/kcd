#include "kcdmetadata.h"
#include "kcdparse.h"

#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <QStringList>
#include <QJsonObject>
#include <iterator>

#include <QDirIterator>

#include <QSize>

#include <QDebug>

#include <KLocalizedString>

#include "kcdxml.h"
#include "kcdconfig.h"
#include "kcddatabase.h"

Kcdmetadata::Kcdmetadata()
{
    //m_metafile = getMetaData();
}

QString Kcdmetadata::findMetaDir(QString sourceDir) {
    // hook into config

    // the metadata file should be $SRC/kde-build-metadata/logical-module-structure
    QString metaDir = sourceDir.append(QStringLiteral("/kde-build-metadata"));
    QDir md(metaDir);
    if (!md.exists()) {
        qDebug() << QStringLiteral("Metadata dir does not exist") << metaDir;
    }
    return metaDir;
}

QString Kcdmetadata::findMetaFile(QString metaDir) {
    QString metaFile = metaDir.append(QStringLiteral("/logical-module-structure"));
    QFile mf(metaFile);
    if (!mf.exists()) {
        qDebug() << QStringLiteral("Metafile not found") << metaFile;
    }
    return metaFile;
}

QString Kcdmetadata::getMetaData(QString sourceDir) {

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

    QStringList skipDirs;
    skipDirs << QStringLiteral("books")
                             << QStringLiteral("historial")
                             << QStringLiteral("kde-build-metadata")
                             << QStringLiteral("repo-metadata")
                             << QStringLiteral("sysadmin")
                             << QStringLiteral("unmaintained")
                             << QStringLiteral("websites")
                             << QStringLiteral(".")
                             << QStringLiteral("..")
                                ;

    QRegularExpression skipList(QStringLiteral("books|historical|kde-build-metadata|unmaintained|websites"));

    QDirIterator dirList(QStringLiteral("/home/bundito/kde/src/sysadmin/repo-metadata/projects"),

                        //QDir::NoDotAndDotDot,
                        QDirIterator::Subdirectories);

    while (dirList.hasNext()) {
        QString dirName = dirList.next();
        QRegularExpressionMatch match = skipList.match(dirName);

        if (match.hasMatch()) {
           // qDebug() << "Matched?" << dirName;
            continue;
        }

        QRegularExpression yaml(QStringLiteral("metadata.yaml"));
        QRegularExpressionMatch yMatch = yaml.match(dirName);
        if (yMatch.hasMatch()) {

            //qDebug() << dirName;
            parseYAML(dirName);
        }
    }


   ;

    return QStringLiteral("ok");
}

void Kcdmetadata::parseYAML(QString yamlFile) {

    QFile metaFile(yamlFile);
    if (!metaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << QStringLiteral("Cannot open metadata file");
        exit(1);
    }

    QRegularExpression desc(QStringLiteral("description: (.*)"));
    QRegularExpression projPath(QStringLiteral("projectpath: (.*)"));
    QRegularExpression repoPath(QStringLiteral("repopath: (.*)"));

    QString modDesc;
    QString modPath;
    QString modRepo;

    QTextStream in(&metaFile);
        while (!in.atEnd()) {
            QString line = in.readLine();

            QRegularExpressionMatch descMatch = desc.match(line);
            if (descMatch.hasMatch()) {
                modDesc = descMatch.captured(1);
                continue;
            }

            QRegularExpressionMatch projMatch = projPath.match(line);
            if (projMatch.hasMatch()) {
                modPath = projMatch.captured(1);
                continue;
            }

            QRegularExpressionMatch repoMatch = repoPath.match(line);
            if (repoMatch.hasMatch()) {
                modRepo = repoMatch.captured(1);
                continue;
            }



                bool result = databasePrep(modDesc, modPath, modRepo);
                if (result) {
                    qDebug() << modRepo;
                }


        }

}

bool Kcdmetadata::databasePrep(QString desc, QString path, QString name) {

    if (name.isEmpty() || name == QStringLiteral("null") || name == QStringLiteral("''")) {
        //return QStringLiteral("void");
        return false;
    }

    QRegularExpression rejects(QStringLiteral("sysadmin|website"));
    QRegularExpressionMatch fail(rejects.match(path));
    if (fail.hasMatch()) {
        return false;
    }

    return true;

}
