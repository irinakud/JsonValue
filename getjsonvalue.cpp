#include "getjsonvalue.h"
#include "qgetjsonvalueexception.h"

#include <QJsonArray>
#include <QJsonObject>

/*!
  \brief Checks if the input path is valid using QRegularExpression.
   "key1[1].key2.key3[4][5].4.key5" is a valid path, the function returns true.
 */
bool isValidJsonPath(const QString& path)
{
    QRegularExpression validPathRx(QRegularExpression::anchoredPattern("(\\w+(\\[\\d+\\]){0,}\\.){0,}(\\w+(\\[\\d+\\]){0,}){1,1}$")); // anchoredPattern from Qt 5.12
    return validPathRx.match(path).hasMatch();
}

/*!
 * \brief Checks if the input is a key, i.e. a word without brackets or dots.
 */
bool isKey(const QString& str)
{
    QRegularExpression isKeyRx("^\\w+$");
    return isKeyRx.match(str).hasMatch();
}

/*!
 * \brief Returns the key value from the input before reaching brackets, i.e. returns "myKey" from input "myKey[0][9]".
 */
QString getKey(const QString& str)
{
    QRegularExpression keyRx = QRegularExpression("^\\w+");
    QRegularExpressionMatch match = keyRx.match(str);

    if (match.hasMatch())
        return match.captured(0);

    return QString();
}

/*!
 * \brief Parces the input and returns a list of indices.
 */
QStringList getIndices(const QString& str)
{
    return str.split(QRegularExpression("\\[|\\]"), Qt::SkipEmptyParts);;
}

QVariant getJsonValue(QJsonValue root, const QString& path)
{
    // Boundary conditions checks:

    if (root.isUndefined())
        throw QGetJsonValueException("input QJsonValue root is undefined");

    if (path.isEmpty())
        return root.toVariant();

    if (!isValidJsonPath(path))
        throw QGetJsonValueException("path is invalid");

    if (!root.isArray() && !root.isObject() && !path.isEmpty())
        return QVariant();

    // Going through each part of the path, separated by ".":

    QStringList keysAndIndicesList = path.split(".");

    foreach (QString part, keysAndIndicesList)
    {
        if (!root.isObject())
            return QVariant();

        // Checking if the part is just a key, i.e. it does not have brackets [], or a key followed by indices in square brackets
        if (isKey(part)) // the part is a key
        {
            root = root[part];
        }
        else // the part is a key with brackets []
        {
            // Retrieving the key before the brackets []
            QString key = getKey(part);

            if (key.isEmpty())
                return QVariant();

            root = root[key];
            part.remove(key);

            // Retreiving all the indices from the part
            QStringList indexList = getIndices(part);
            if (indexList.count() == 0 || !root.isArray())
                return QVariant();

            // Going through all the retreived indices:
            foreach (QString indexStr, indexList)
            {
                QJsonArray jsonArray = root.toArray();
                int index = indexStr.toInt();
                if (index < jsonArray.count())
                    root = jsonArray[index];
                else
                    return QVariant();
            }
        }
    }

    QVariant result = root.toVariant();
    return result;
}
