#include "kcdoutput.h"

#include <QVariant>
#include <QString>
#include <QTextStream>>

KcdOutput::KcdOutput()
{

}

QVariant KcdOutput::out(QVariant output) {
    // custom output stream!
        static QTextStream output(stdout);
        return output;

}
