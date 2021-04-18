#ifndef BYTES_H
#define BYTES_H

#include <QByteArray>
#include <QString>
#include "QFileDialog"
#include <QStandardItemModel>

#define BYTESPERLINE 16
#define BYTESALIGNMENT 16
#define BYTELINES 100
#define BYTECOUNT BYTESALIGNMENT * BYTELINES

class Bytes
{
public:
    QString inHex;
    QString inAscii;
    QStandardItemModel *model;
    QStringList horizontalHeader;
    QStringList verticalHeader;
    QByteArray fileBytes;

    Bytes();
    bool readFile(QByteArray*);
    QString formatHex(QByteArray);
    QString formatAscii(QByteArray);
};

#endif // BYTES_H
