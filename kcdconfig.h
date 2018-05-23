#ifndef KCDCONFIG_H
#define KCDCONFIG_H

#include <QString>

#include "kcdparse.h"
#include "kcdmetadata.h"

#include <KConfig>
#include <KConfigGroup>
#include <KSharedConfig>


class kcdConfig
{
public:

    // default constructor
    kcdConfig();

    Kcdparse pk;
    Kcdmetadata md;

    KConfig cfg;
    KConfigGroup generalGroup;

    KSharedConfigPtr m_config;

    void updateCfg();

    void setup();

    void storeXMLFile(QString file);

    void openCfg();

    // TODO: find redundant/duplicate calls and eliminate
    void storeParameter(QString key, QVariant value);
    void storeData(QString key, QVariant value);



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

    QString getParameter(QString key);

};

#endif // KCDCONFIG_H
