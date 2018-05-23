#ifndef KDESRCPARSE_H
#define KDESRCPARSE_H

#include <QObject>
#include <QFile>
#include <QUrl>
#include <QString>

class Kcdparse : public QString {

public:

    Kcdparse();

    QString m_rcLocation;
	QString m_kdesrc;
    QString m_installDir;
    QString m_sourceDir;
    QString m_homedir;

    QString findRcFile();
    void setFileLoc(QString file);


    QString getFileLoc();
    QString parseFile();
    QString getInstallDir();
    QString getSourceDir();

};
#endif // KDESRCPARSE_H
