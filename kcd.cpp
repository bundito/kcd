#include <KAboutData>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include <KConfig>
#include <KSharedConfig>
#include <KConfigGroup>

#include <KLocalizedString>

#include "parsekdesrc.h"
#include "metadata.h"
#include "kcdxml.h"
#include "kcdconfig.h"


// custom output stream!
QTextStream& qStdOut() {
    static QTextStream ts(stdout);
    return ts;
}

// *** main app begins
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    kcdXML xml;

    QString pkgWanted;

    kcdConfig cfg;
    cfg.updateCfg();
   // QString rcFile = cfg.getRcFile();
   // qDebug() << rcFile;
   // qDebug() << cfg.getSourceDir();


   // KConfig config(QStringLiteral("kcdrc"));
   // KConfigGroup generalGroup( &config, "General" );
   // generalGroup.writeEntry(QStringLiteral("secondrun"), true);
   // config.sync();



   // KConfig config = KConfig::openConfig
   // KSharedConfigPtr cfgPtr = KSharedConfig::openConfig(QStringLiteral("kcdrc"));
    //KConfigGroup generalGroup (&config, QStringLiteral("General"));

    
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
        {{QStringLiteral("i"), QStringLiteral("set-install-dir")}, i18n("Set install destination directory")}
    });



    parser.process(app);
    aboutData.processCommandLine(&parser);

    if (parser.isSet(QStringLiteral("refresh"))) {

        ParseKdesrc pk;
        QString dir = pk.getFileLoc();

        metadata md;
        QString results = md.getMetaData(pk.getSourceDir());
        qDebug() << results;
        qStdOut() << i18n("Package listing refreshed.\n");
        exit(0);
    }

    const QStringList args = parser.positionalArguments();

    qDebug() << args;


    if (!args.isEmpty()) {
        pkgWanted = args[0];
    } else {
        parser.showHelp();
        exit(0);
    }


    if (pkgWanted != QStringLiteral("")) {
        qDebug() << pkgWanted;
        QString xmlFile = xml.getXMLfile();
        qDebug() << xmlFile;

        QString result = xml.doSearch(pkgWanted);
        qDebug() << "result" << result;



    }

    return 0;
}
