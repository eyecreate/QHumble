#include "purchase.h"
#include "db/product.h"

Purchase::Purchase(QObject *parent) : Nut::Table(parent),
    m_id(0), m_type(""), m_humanname(""), m_intname(""), m_humbleid(""), m_products(new Nut::TableSet<Product>(this))
{
}

NUT_IMPLEMENT_CHILD_TABLE(Purchase, Product, products)
