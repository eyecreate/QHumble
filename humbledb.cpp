#include "humbledb.h"
#include "db/file.h"
#include "db/download.h"
#include "db/product.h"
#include "db/purchase.h"

HumbleDB::HumbleDB() : Nut::Database(),
    m_purchases(new Nut::TableSet<Purchase>(this)),
    m_products(new Nut::TableSet<Product>(this)),
    m_downloads(new Nut::TableSet<Download>(this)),
    m_files(new Nut::TableSet<File>(this))
{
    qRegisterMetaType<Purchase*>();
    qRegisterMetaType<Product*>();
    qRegisterMetaType<Download*>();
    qRegisterMetaType<File*>();
    qRegisterMetaType<HumbleDB*>();
}
