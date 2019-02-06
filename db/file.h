#ifndef FILE_H
#define FILE_H

#include <QString>

class File
{
public:
    explicit File();
    int getId();
    QString getName();
    int getFileSize();
    QString getMD5();
    QString getWebURL();
    QString getBitTorrentURL();
    int getDownloadId();
    void setId(int id);
    void setName(QString name);
    void setFileSize(int filesize);
    void setMD5(QString md5);
    void setWebURL(QString webUrl);
    void setBitTorrentURL(QString bitTorrentUrl);
    void setDownloadId(int id);

private:
    int id;
    QString name;
    int filesize;
    QString md5;
    QString webUrl;
    QString bitTorrentUrl;
    int downloadId;
};

#endif // FILE_H
