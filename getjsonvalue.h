#ifndef GETJSONVALUE_H
#define GETJSONVALUE_H

#include <QJsonValue>

/*!
 * \brief Reads a value from the root with a path. Throws exception if root or path are invalid.
 */
QVariant getJsonValue(QJsonValue root, const QString& path);

#endif // GETJSONVALUE_H
