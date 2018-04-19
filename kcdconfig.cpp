#include <QString>
#include <QDebug>

#include <KLocalizedString>
#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>

#include "kcdconfig.h"
#include "parsekdesrc.h"

kcdConfig::kcdConfig()
{
   KConfig config(QStringLiteral("kcdrc"));
   KSharedConfigPtr cfgPtr = KSharedConfig::openConfig(QStringLiteral("kcdrc"));
   KConfigGroup generalGroup( &config, QStringLiteral("General") );

   updateCfg();
}

void kcdConfig::updateCfg() {
    ParseKdesrc pk;
    metadata md;
    qDebug() << i18n("getting metadata");
    getSourceDir();
    getMetaData();

    //KConfig config(QStringLiteral("kcdrc"));
    KConfigGroup generalGroup( cfgPtr, QStringLiteral("General") );

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
    KConfigGroup generalGroup( cfgPtr, QStringLiteral("General") );
    return generalGroup.readEntry("SourceDir");
}

QString kcdConfig::getMetaData() {
    m_metaDir = md.getMetaData(m_sourceDir);
    return m_metaDir;
}
