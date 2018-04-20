#include "kcdxml.h"
#include "parsekdesrc.h"
#include "kcdconfig.h"


#include <QString>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>

#include <QtXml/QDomDocument>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


#include "KLocalizedString"

kcdXML::kcdXML()
{
    KSharedConfigPtr m_config = KSharedConfig::openConfig(QStringLiteral("kcdrc"));
    kcdConfig cfg;

    m_total = 0;
    m_installed = 0;

}

void kcdXML::startXml(QString fname) {
    QString baseName = QStringLiteral("/kcd.xml");
    fname.append(baseName);

    m_xmlFile = fname;

    QFile file(m_xmlFile);
    file.open(QIODevice::WriteOnly);

    QTextStream in(&file);

    in << (QStringLiteral("<?xml version='1.0' encoding='UTF-8'?>")) << "\n";
    in << (QStringLiteral("<modlist>")) << "\n";


    //qDebug() << "XML File: " << m_xmlFile;


}

void kcdXML::addEntry(QString data) {

    m_total++;

    QUrl url = QUrl::fromLocalFile(data);
    QString dirName = url.fileName();

    QString mfLoc = cfg.getSourceDir();
    mfLoc.append(QStringLiteral("/"));
    mfLoc.append(data);
    QDir dir(mfLoc);
    bool exists = dir.exists();
    if (exists) {
        m_installed++;
    }
    //qDebug() << mfLoc;
    QString inst = QString::number(exists);



    QXmlStreamAttribute installed(QStringLiteral("installed"), QStringLiteral("true"));

    QFile file(m_xmlFile);
    file.open(QIODevice::Append);
    QXmlStreamWriter m_stream(&file);
    m_stream.setAutoFormatting(true);
    m_stream.writeStartElement(QStringLiteral("module"));
    m_stream.writeTextElement(QStringLiteral("path"), data);
    m_stream.writeTextElement(QStringLiteral("name"), dirName);
    m_stream.writeTextElement(QStringLiteral("installed"), inst);
    m_stream.writeEndElement();

    //saveXMLFile();

}

void kcdXML::openXML() {
    QFile file(m_xmlFile);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter m_stream(&file);
    m_stream.setAutoFormatting(true);
    m_stream.writeStartDocument();
    m_stream.writeStartElement(QStringLiteral("<modlist>"));
}

void kcdXML::closeXML() {
    m_stream.writeEndElement();
    m_stream.writeEndDocument();
    QFile file(m_xmlFile);
    file.close();
}

QString kcdXML::getXMLfile() {
    return m_xmlFile;
}

void kcdXML::saveXMLFile() {
    cfg.storeXMLFile(m_xmlFile);
}

QString kcdXML::doSearch(QString query) {

    m_xmlFile = cfg.getXmlFile();
/**
    QString xq = QStringLiteral(" \
        <result> \
        {doc(\"XMLFILE\")/module[name=\"QUERY\"<path>{path}</path>} \
        </result>");

   QRegularExpression xmlFile(QStringLiteral("XMLFILE"));"
   QRegularExpression searchString(QStringLiteral("QUERY"));
    xq.replace(xmlFile, m_xmlFile);
    xq.replace(searchString, query);

**/

    QFile xml(m_xmlFile);
    xml.open(QIODevice::ReadWrite);
    QXmlStreamReader stream(&xml);

    while (!stream.atEnd()) {
        stream.readNextStartElement();
        stream.tokenString();
        stream.readNext();
    }

    if (stream.hasError()) {
        qDebug() << stream.errorString();
    }


   // qDebug() << getXMLfile();

   return QStringLiteral("foo");

}
