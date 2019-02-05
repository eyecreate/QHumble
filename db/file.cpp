#include "file.h"

File::File(QObject *parent) : Nut::Table(parent),
    m_id(0), m_name(""), m_filesize(0), m_md5(""), m_weburl(""), m_bittorrenturl("")
{
}
