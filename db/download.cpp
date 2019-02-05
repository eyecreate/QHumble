#include "download.h"
#include "file.h"

Download::Download(QObject *parent) : Nut::Table(parent),
    m_id(0), m_platform(""), m_files(new Nut::TableSet<File>(this)), m_intname("")
{
}

NUT_IMPLEMENT_CHILD_TABLE(Download, File, files)
