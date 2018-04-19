#ifndef KCDCONFIG_H
#define KCDCONFIG_H

#include <QString>

#include "parsekdesrc.h"
#include "metadata.h"

#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>


class kcdConfig
{
public:

    // default constructor
    kcdConfig();

    ParseKdesrc pk;
    metadata md;
    KConfig cfg;
    KConfigGroup generalGroup;
    KSharedConfigPtr cfgPtr;

    void updateCfg();

    void storeXMLFile(QString file);

    QString getMetaData();
    void setConfigFile(QString file);
    QString getConfigFile();

    QString m_rcFile;
    void setRcFile(QString file);
    QString getRcFile();

    QString m_sourceDir;
    void setSourceDir(QString dir);
    QString getSourceDir();

    QString m_metaDir;
    void setMetaDir(QString dir);
    QString getMetaDir();

    QString m_XmlFile;
    void setXmlFile(QString file);
    QString getXmlFile();

};

#endif // KCDCONFIG_H
