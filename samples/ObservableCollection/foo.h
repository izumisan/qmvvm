#ifndef FOO_H
#define FOO_H

#include <QString>

class Foo
{
public:
    Foo() = default;
    Foo( const QString& name, const int value )
        : m_name( name )
        , m_value( value )
    {
    }
    virtual ~Foo() = default;

public:
    QString name() const { return m_name; }
    void setName( const QString& name ) { m_name = name; }
    int value() const { return m_value; }
    void setValue( const int value ) { m_value = value; }

private:
    QString m_name = {};
    int m_value = 0;
};

#endif // FOO_H
