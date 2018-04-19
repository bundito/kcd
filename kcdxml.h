#ifndef KCPXML_H
#define KCPXML_H

#include <QString>
#include <QXmlStreamWriter>
#include <KSharedConfig>

#include "kcdconfig.h"

class kcdXML
{
public:
    // generic constructor
    kcdXML();

    qint8 m_total;
    qint8 m_installed;
    QXmlStreamWriter m_stream;

    QString m_xmlFile;
    bool m_fileExists;

    kcdConfig cfg;


    KSharedConfigPtr m_config();

    bool findXML(QString file);
    void addEntry (QString element);
    void openXML();
    void closeXML();
    void saveXMLFile();
    QString getXMLfile();
    QString doSearch(QString query);


};

#endif // KCPXML_H
