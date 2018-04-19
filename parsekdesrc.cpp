#include "parsekdesrc.h"

#include "kcdconfig.h"

#include <QFile>
#include <QString>
#include <QUrl>
#include <QProcessEnvironment>
#include <QRegularExpression>

#include <KLocalizedString>

#include <QDebug>

ParseKdesrc::ParseKdesrc() {
    m_rcLocation = findRcFile();
}


void ParseKdesrc::setFileLoc(QString file) {
    m_rcLocation = file;
}

QString ParseKdesrc::getFileLoc() {
    return m_rcLocation;
}

QString ParseKdesrc::findRcFile()
{
    QString rcFile = QStringLiteral(".kdesrc-buildrc");
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString homeDir = env.value(QStringLiteral("HOME"));
    m_homedir = homeDir;
    homeDir.append(QStringLiteral("/"));

    QString testLoc = homeDir.append(rcFile);
    QFile kdFile(testLoc);
    if (!kdFile.exists()) {
        return i18n("Not found at expected location. Set manually.");
    }
    m_rcLocation = testLoc;
    QString doIt = parseFile();
    return testLoc;

}

QString ParseKdesrc::parseFile() {

    QFile rcFile(m_rcLocation);

    if (!rcFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return i18n("Unable to read file.");

    QRegularExpression sourceDir(QStringLiteral("^ *source-dir (.*)"));
    QRegularExpression installDir(QStringLiteral("kdedir (.*)"));

    QTextStream in(&rcFile);
    while (!in.atEnd()) {
        QString line = in.readLine();

        QRegularExpressionMatch sourceMatch = sourceDir.match(line);
        if (sourceMatch.hasMatch()) {
            // qDebug() << "source: " << sourceMatch.captured(1);
            m_sourceDir = sourceMatch.captured(1);
        }
        QRegularExpressionMatch installMatch = installDir.match(line);
        if (installMatch.hasMatch()) {
            // qDebug() << "install: " << installMatch.captured(1);
            m_installDir = installMatch.captured(1);
        }
    }

    // apparently, Qt does not expand ~ into your real home directory
    QRegularExpression tilde(QStringLiteral("~"));
    m_sourceDir.replace(tilde, m_homedir);
    m_installDir.replace(tilde, m_homedir);



    return i18n("Parsing successful.");
}

QString ParseKdesrc::getInstallDir() { return m_installDir; }
QString ParseKdesrc::getSourceDir() { return m_sourceDir; }
