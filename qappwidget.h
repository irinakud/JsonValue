#ifndef QAPPWIDGET_H
#define QAPPWIDGET_H

#include <QWidget>

class QLineEdit;
class QPlainTextEdit;

/*!
   \brief QAppWidget class is a QWidget which allows to enter input QJsonDocument, path and shows the value from the path as a QJsonDocument.
 */
class QAppWidget : public QWidget
{
    Q_OBJECT
public:
    QAppWidget(QWidget* parent = nullptr);
    ~QAppWidget();

private Q_SLOTS:
    /*!
       \brief Validates the input document, calls getJsonValue function and updates output widget.
     */
    void getJsonValueSlot();

private:
    /*!
       \brief Shows the retrieved value in the output widget.
     */
    void updateJsonValueOutput(const QVariant& value);

    QPlainTextEdit* m_jsonDocumentInput;
    QLineEdit* m_jsonPathInput;
    QPlainTextEdit* m_jsonValueOutput;
};

#endif // QAPPWIDGET_H
