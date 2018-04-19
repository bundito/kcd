#include "kcdxml.h"
#include "parsekdesrc.h"
#include "kcdconfig.h"

#include <QString>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>
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

bool kcdXML::findXML(QString fname) {
    QString baseName = QStringLiteral("/kcd.xml");
    fname.append(baseName);

    m_xmlFile = fname;

    qDebug() << "XML File: " << m_xmlFile;

    QFile xmlFile(fname);

    if (!xmlFile.exists()) {
        // qDebug() << i18n("No XML File");
        QFile file(m_xmlFile);
        file.open(QIODevice::WriteOnly);
        QXmlStreamWriter stream(&file);
        stream.writeStartDocument();
        stream.setAutoFormatting(true);
        bool ok = stream.hasError();
        if (!ok) {
            // qDebug() << i18n("Streamwriter has error");
            return false;
        } else {
            // qDebug() << i18n("XML File created");
            m_fileExists = true;
            return true;
        }
    } else {
        // qDebug() << i18n("File exists");
        m_fileExists = true;
        return true;
    }
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
    qDebug() << mfLoc;
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
}

void kcdXML::closeXML() {
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

    QString xq = QStringLiteral(" \
        <result> \
        {doc(\"XMLFILE\")/module[name=\"QUERY\"<path>{path}</path>} \
        </result>");

   QRegularExpression xmlFile(QStringLiteral("XMLFILE"));
   QRegularExpression searchString(QStringLiteral("QUERY"));
    xq.replace(xmlFile, m_xmlFile);
    xq.replace(searchString, query);

    qDebug() << getXMLfile();

   return xq;

}
