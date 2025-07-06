#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QImage>
#include <QBuffer>
#include <QFile>
#include <QTextStream>

QByteArray imageToBase64(const QImage &image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return byteArray.toBase64();
}

QString htmlImgTagFromImage(const QImage &image)
{
    QByteArray base64 = imageToBase64(image);
    QString html = R"(<img src="data:image/png;base64,%1" alt="img.png">)";
    return html.arg(QString::fromLatin1(base64));
}

bool saveHtmlToFile(const QString &html, const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    out << html;
    return true;
}

#endif // UTILS_H
