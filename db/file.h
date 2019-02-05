#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <Table>

class Download;
class File : public Nut::Table
{
    Q_OBJECT

    NUT_PRIMARY_AUTO_INCREMENT(id)
    NUT_DECLARE_FIELD(int, id, id, setId)
    NUT_NOT_NULL(name)
    NUT_DECLARE_FIELD(QString, name, name, setName)
    NUT_DECLARE_FIELD(int, filesize, filesize, setFilesize)
    NUT_DECLARE_FIELD(QString, md5, MD5, setMD5)
    NUT_DECLARE_FIELD(QString, weburl, webURL, setWebURL)
    NUT_DECLARE_FIELD(QString, bittorrenturl, bitTorrentURL, setBitTorrentURL)
    NUT_FOREGION_KEY(Download, int, download, download, setDownload)
public:
    Q_INVOKABLE File(QObject *parent = nullptr);

signals:

public slots:
};

Q_DECLARE_METATYPE(File*)

#endif // FILE_H
