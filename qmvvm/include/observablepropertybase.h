#ifndef IZM_QMVVM_OBSERVABLEPROPERTYBASE_H
#define IZM_QMVVM_OBSERVABLEPROPERTYBASE_H

#include <QObject>
#include <QVariant>

namespace izm
{
namespace qmvvm
{

class ObservablePropertyBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QVariant value READ valueProperty WRITE setValueProperty NOTIFY valuePropertyChanged )
Q_SIGNALS:
    void valuePropertyChanged() const;

public:
    explicit ObservablePropertyBase( QObject* parent = nullptr );
    virtual ~ObservablePropertyBase() = default;

public:
    virtual QVariant valueProperty() const = 0;
    virtual void setValueProperty( const QVariant& value ) = 0;

public:
    virtual void raiseValuePropertyChanged() const;
};

} // namespace qmvvm
} // namespace izm

#endif // IZM_QMVVM_OBSERVABLEPROPERTYBASE_H
