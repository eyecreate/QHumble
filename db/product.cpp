#include "product.h"
#include "download.h"

Product::Product(QObject *parent) : Nut::Table(parent),
    m_id(0), m_intname(""), m_humanname(""), m_iconurl(""), m_downloads(new Nut::TableSet<Download>(this))
{
}

NUT_IMPLEMENT_CHILD_TABLE(Product, Download, downloads)
