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



    QString m_xmlFile;
    bool m_fileExists;
    QXmlStreamWriter m_stream;
    kcdConfig cfg;


    KSharedConfigPtr m_config();

    bool findXML (QString file);
    void addEntry (QString element);
    void openXML();
    void closeXML();
    void saveXMLFile();
    QString getXMLfile();
    QString doSearch(QString query);


};

#endif // KCPXML_H
