#ifndef QGETJSONVALUEEXCEPTION_H
#define QGETJSONVALUEEXCEPTION_H

#include <QException>

/*!
  \brief QGetJsonValueException class derived from QException, contains a message which can be accessed through the getMessage() method.
 */
class QGetJsonValueException : public QException
{
public:
    QGetJsonValueException(const QString& message = "") : m_message(message) {}

    void raise() const override { throw *this; }
    QGetJsonValueException *clone() const override { return new QGetJsonValueException(*this); }

    QString getMessage() const { return m_message; }

private:
    QString m_message;

};

#endif // QGETJSONVALUEEXCEPTION_H
