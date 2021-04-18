#include "bytes.h"

Bytes::Bytes()
{
    model = nullptr;

    if(readFile(&fileBytes)) {
        inHex = formatHex(fileBytes);
        inAscii = formatAscii(fileBytes);

        for (int i = 0; i < BYTESPERLINE; i++) {
            horizontalHeader.append(QString("%1").arg(i, 2, 16, QLatin1Char( '0' )));
        }

        for (int i = -1; i < BYTESPERLINE; i++) {
            horizontalHeader.append("");
        }

        model = new QStandardItemModel();

        model->setHorizontalHeaderLabels(horizontalHeader);
        model->setVerticalHeaderLabels(verticalHeader);

        // Here you can set your data in table view

        QList<QStandardItem*> columns;

        QStringList addresses;

        QString tmp = "";
        QString tmpAscii = "";

        addresses.append(QString("%1").arg(0, 10, 16, QChar('0')));

        int lineCount = 0;

        //qDebug("HexSize: %d  ASCIISize: %d", inHex.size(), inAscii.size());
        //qDebug("Hex: " + inHex.toLatin1() + "ASCI: " + inAscii.toLatin1());
        for(int i = 0, j = 0; i < inHex.size(); i++) { //For new columns
            if(inHex[i] == '\t') {
                QStandardItem* tmpItem = new QStandardItem(tmp);       //add hex
                tmpItem->setTextAlignment(Qt::AlignCenter);
                columns.append(tmpItem);
                tmp = "";
                tmpAscii += inAscii[j];
                j++;
            }
            else if(inHex[i] == '\n') {         //For new rows
                QStandardItem* tmpItem = new QStandardItem("\t");  //add ascii
                tmpItem->setTextAlignment(Qt::AlignCenter);
                columns.append(tmpItem);

                for(int k = 0; k < tmpAscii.size(); k++) {
                    QStandardItem* tmpItem = new QStandardItem(tmpAscii[k]);  //add ascii
                    tmpItem->setTextAlignment(Qt::AlignCenter);
                    columns.append(tmpItem);
                }

                tmpAscii = "";
                lineCount++;
                model->appendRow(columns);
                columns.clear();
                if(i != inHex.size() - 1)
                    addresses.append(QString("%1").arg(lineCount * 16, 10, 16, QChar('0')));    //add address
            }
            else {
                tmp += inHex[i];
            }
        }
        model->setVerticalHeaderLabels(addresses);
    }
}

bool Bytes::readFile(QByteArray* bytes) {
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::ExistingFile);       //Pick existing file
    fileDialog.setViewMode(QFileDialog::Detail);             //Show in detail
    if (!fileDialog.exec()) {                                //Attempt to launch file dialog
        return 0;                                         //Exit if open failed
    }

    QString filePath = (fileDialog.selectedFiles())[0];      //Get path

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {                   //Attempt to open file for reading
        return 0;
    }

    *bytes = file.readAll().toHex();                           //Read file bytes
    return 1;
}

QString Bytes::formatHex(QByteArray bytes) {
    QString bytesf;
    int count = 0;

    for (int i = 1; i < BYTECOUNT * 2; i+=2) {
        bytesf += QString(bytes[i-1]) + QString(bytes[i]) + '\t';
        count += 1;
        if (count % BYTESPERLINE == 0) {
            bytesf += '\n';
        }
    }
    return bytesf;
}

QString Bytes::formatAscii(QByteArray bytes) {
    QByteArray asciiBytes = QByteArray::fromHex(bytes);

    QString bytesf;
    int count = 0;

    for (int i = 0; i < BYTECOUNT; i++) {
        if((asciiBytes[i] < 0x20 || asciiBytes[i] > 0x7e)) {
            bytesf += '.';
        }
        else {
            bytesf += QString(asciiBytes[i]);
        }
        count += 1;
        /*
        if (count % BYTESPERLINE == 0) {
            bytesf += '\n';
        }
        */
    }
    return bytesf;
}
