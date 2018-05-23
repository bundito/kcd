#ifndef METADATA_H
#define METADATA_H

#include "kcdparse.h"

#include <QString>
#include <QFile>
#include <QRegularExpression>


class Kcdmetadata
{
public:

    QString findMetaDir(QString sourceDir);
    QString findMetaFile(QString metaDir);

     // basic constructor
     Kcdmetadata();

    // member variables
    QString m_metafile;

    // get metadata file
    QString getMetaData(QString sourceDir);

    // scan metadatafile
    QString scanMetaFile();

    // parse the metadata.yaml file
    void parseYAML(QString yamlFile);

    // further filter YAML to get rid of bogus stuff
    bool databasePrep(QString desc, QString path, QString name);

};

#endif // METADATA_H
