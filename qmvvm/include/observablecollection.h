#ifndef IZM_QMVVM_OBSERVABLECOLLECTION_H
#define IZM_QMVVM_OBSERVABLECOLLECTION_H

#include "qmvvm_global.h"
#include "observablecollectionbase.h"
#include "collectionrole.h"
#include "observablehelper.h"

namespace izm
{
namespace qmvvm
{

template<class T>
class ObservableCollection : public ObservableCollectionBase
{
public:
    ObservableCollection( QObject* parent = nullptr )
        : ObservableCollectionBase( parent )
    {
    }
    ObservableCollection( const QList<CollectionRole<T>>& roles,
                          QObject* parent = nullptr )
        : ObservableCollection( {}, roles, parent )
    {
    }
    ObservableCollection( const QList<T>& values,
                          const QList<CollectionRole<T>>& roles,
                          QObject* parent = nullptr )
        : ObservableCollectionBase( parent )
        , m_roles( roles )
    {
        for ( auto&& x: values )
        {
            add( x );
        }
    }

    virtual ~ObservableCollection() = default;

public:
    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const override
    {
        Q_UNUSED( parent );
        return m_values.size();
    }

    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override
    {
        auto&& ret = QVariant();
        if ( index.isValid() )
        {
            auto&& roleIndex = role - roleOffset();
            if ( ( 0 <= roleIndex ) && ( roleIndex < m_roles.size() ) )
            {
                auto&& getter = m_roles.at( roleIndex ).getter();
                if ( getter )
                {
                    ret = getter( m_values.at( index.row() ) );
                }
            }
        }
        return ret;
    }

    virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override
    {
        bool ret = false;
        if ( index.isValid() && ( data( index, role ) != value ) )
        {
            auto&& roleIndex = role - roleOffset();
            if ( ( 0 <= roleIndex ) && ( roleIndex < m_roles.size() ) )
            {
                auto&& setter = m_roles.at( roleIndex ).setter();
                if ( setter )
                {
                    setter( m_values[ index.row() ], value );
                    ret = true;

                    raiseDataChanged( index, index, { role } );
                    raiseCollectionChanged( CollectionChangeAction::ItemChange, index.row() );
                }
            }
        }
        return ret;
    }

protected:
    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> ret {};
        for ( int i = 0; i < m_roles.size(); ++i )
        {
            auto&& role = roleOffset() + i;
            ret.insert( role, m_roles.at( i ).roleName().toStdString().c_str() );
        }
        return ret;
    }

public:
    void add( const T& value )
    {
        beginInsertRows( QModelIndex(), rowCount(), rowCount() );
        m_values.append( value );
        endInsertRows();

        raiseCollectionChanged( CollectionChangeAction::Add, m_values.size() - 1 );
    }

    void insert( const int pos, const T& value )
    {
        beginInsertRows( QModelIndex(), pos, pos );
        m_values.append( value );
        endInsertRows();

        raiseCollectionChanged( CollectionChangeAction::Add, pos );
    }

    void remove( const T& value )
    {
        auto&& it = std::find( m_values.cbegin(), m_values.cend(), value );
        if ( it != m_values.cend() )
        {
            auto&& removeIndex = it - m_values.cbegin();
            removeAt( removeIndex );
        }
    }

    void removeAt( const int pos )
    {
        beginRemoveRows( QModelIndex(), pos, pos );
        m_values.removeAt( pos );
        endRemoveRows();

        raiseCollectionChanged( CollectionChangeAction::Remove, pos );
    }

    void removeAll()
    {
        beginResetModel();
        m_values.clear();
        endResetModel();

        raiseCollectionChanged( CollectionChangeAction::Reset );
    }

    T value( const int& index ) const { return m_values.at( index ); }

    QList<T> values() const { return m_values; }

    bool setValue( const int pos, const T& value, bool doesRaiseDataChanged = true )
    {
        bool ret = false;
        if ( ( 0 <= pos ) && ( pos < m_values.size() ) )
        {
            if ( m_values.at( pos ) != value )
            {
                m_values[ pos ] = value;
                ret = true;

                if ( doesRaiseDataChanged )
                {
                    raiseDataChanged( index( pos ), index( pos ), roleNames().keys().toVector() );
                    raiseCollectionChanged( CollectionChangeAction::ItemChange, pos );
                }
            }
        }
        return ret;
    }

    int count() const { return m_values.count(); }

private:
    constexpr int roleOffset() const { return Qt::UserRole + 1; }

private:
    QList<T> m_values = {};
    QList<CollectionRole<T>> m_roles = {};
};

#if !defined(IZM_QMVVM_BUILT_IN)
template class IZMQMVVMSHARED_EXPORT ObservableCollection<bool>;
template class IZMQMVVMSHARED_EXPORT ObservableCollection<unsigned int>;
template class IZMQMVVMSHARED_EXPORT ObservableCollection<int>;
template class IZMQMVVMSHARED_EXPORT ObservableCollection<float>;
template class IZMQMVVMSHARED_EXPORT ObservableCollection<double>;
template class IZMQMVVMSHARED_EXPORT ObservableCollection<QString>;
#else
extern template class ObservableCollection<bool>;
extern template class ObservableCollection<unsigned int>;
extern template class ObservableCollection<int>;
extern template class ObservableCollection<float>;
extern template class ObservableCollection<double>;
extern template class ObservableCollection<QString>;
#endif

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLECOLLECTION_H
