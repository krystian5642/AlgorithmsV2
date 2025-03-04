#ifndef PROPERTYLAYOUTFACTORY_H
#define PROPERTYLAYOUTFACTORY_H

#include <QHash>
#include <QObject>

class QBoxLayout;

namespace PropertyLayoutFactoryUtils
{
    QString convertCamelCaseToSpaces(const QString& input);
}

class PropertyLayoutFactory
{
    using CreateLayoutFunction = std::function<QBoxLayout*(const QMetaProperty&, QObject*, QWidget*)>;

public:
    static PropertyLayoutFactory& get();

    void registerCreateLayoutForType(int type, CreateLayoutFunction func);
    QBoxLayout* createLayoutForProperty(const QMetaProperty& property, QObject* propertyObject, QWidget* parent);

private:
    PropertyLayoutFactory();

    QHash<int, CreateLayoutFunction> registeredLayoutCreators;
};

#endif // PROPERTYLAYOUTFACTORY_H
