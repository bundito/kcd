#include <QString>
#include <QDebug>

#include <KLocalizedString>
#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>

#include "kcdconfig.h"
#include "parsekdesrc.h"
#include "metadata.h"



kcdConfig::kcdConfig()
{

   ParseKdesrc pk;
   metadata md;

   KSharedConfigPtr m_config = KSharedConfig::openConfig(QStringLiteral("kcdrc"));
   generalGroup = KConfigGroup(m_config, QStringLiteral("General"));
   generalGroup.writeEntry(QStringLiteral("lastRefreshed"), QDateTime::currentDateTime());

   //updateCfg();
}
void kcdConfig::setup() {

    QString source = pk.getSourceDir();
    storeData(QStringLiteral("sourceDir"), source);

    QString install = pk.getInstallDir();
    storeData(QStringLiteral("installDir"), install);

    QString xmlFile = md.getMetaData(source);
    storeData(QStringLiteral("xmlFile"), xmlFile);

}

void kcdConfig::storeData(QString key, QVariant value) {

    generalGroup.writeEntry(key, value);
    generalGroup.sync();
}

void kcdConfig::updateCfg() {

    qDebug() << i18n("getting metadata");
    getSourceDir();
    getMetaData();

    //KConfig config(QStringLiteral("kcdrc"));


    generalGroup.writeEntry("SourceDir", pk.getSourceDir());
    generalGroup.writeEntry("rcFile", pk.findRcFile());;
    generalGroup.writeEntry("xmlFile", md.getMetaData(pk.getSourceDir()));
    generalGroup.writeEntry("installDir", pk.getInstallDir());
    generalGroup.sync();
}


void kcdConfig::storeXMLFile(QString file) {
    generalGroup.writeEntry("xmlfile", file);
    generalGroup.sync();
}

QString kcdConfig::getRcFile() {
    m_rcFile = pk.findRcFile();
    return m_rcFile;
}

QString kcdConfig::getSourceDir() {

    return generalGroup.readEntry("SourceDir");
}

QString kcdConfig::getMetaData() {
    m_metaDir = md.getMetaData(m_sourceDir);
    return m_metaDir;
}
