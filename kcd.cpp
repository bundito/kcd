#include <KAboutData>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <KLocalizedString>

#include "parsekdesrc.h"
#include "metadata.h";


int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    
    KAboutData aboutData(QStringLiteral("kcd"),
    		i18n("kcd"),
    		QStringLiteral("0.1b") + QStringLiteral(" - ") + QStringLiteral("abide"),
    		i18n("Easily navigate KDE source directories"),
    		KAboutLicense::GPL_V2,
    		i18n("(c) 2018 Scott P. Harvey"));
    aboutData.addAuthor(QStringLiteral("Scott P. Harvey"), QString(), QStringLiteral("scott@spharvey.me"));
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    aboutData.setupCommandLine(&parser);

    parser.addPositionalArgument(QStringLiteral("package-name"), i18n("Package directory to change into"));
    parser.addOptions({
        {{QStringLiteral("r"), QStringLiteral("refresh")},  i18n("Refresh list of packages")},
        {{QStringLiteral("s"), QStringLiteral("set-source-dir")}, i18n("Set base source directory")},
        {{QStringLiteral("i"), QStringLiteral("set-install-dir")}, i18n("Set install destination directory")},
        {{QStringLiteral("k"), QStringLiteral("kdesrc")}, i18n("Attempt to parse 'kdesrc-buildrc' for directories")}
    });

    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(QStringLiteral("kdesrc"))) {

        ParseKdesrc pk;

        QString dir = pk.getFileLoc();
        qDebug() << dir;
        QString results = pk.parseFile();
        qDebug() << results;
    }

    if (parser.isSet(QStringLiteral("refresh"))) {

        ParseKdesrc pk;
        QString dir = pk.getFileLoc();

        metadata md;
        QString results = md.findMetaFile();
        qDebug() << results;
    }

    return 0;
}
