#ifndef METADATA_H
#define METADATA_H

#include "parsekdesrc.h"

#include <QString>
#include <QFile>
#include <QRegularExpression>


class metadata
{
public:

    QString findMetaDir(QString sourceDir);
    QString findMetaFile(QString metaDir);

     // basic constructor
     metadata();

    // member variables
    QString m_metafile;

    // get metadata file
    QString getMetaData(QString sourceDir);

    // scan metadatafile
    QString scanMetaFile();

};

#endif // METADATA_H
