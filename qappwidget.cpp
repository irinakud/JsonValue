#include "qappwidget.h"
#include "getjsonvalue.h"
#include "qgetjsonvalueexception.h"

#include <QPlainTextEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

QAppWidget::QAppWidget(QWidget* parent) : QWidget(parent)
{
    QGridLayout* test2Layout = new QGridLayout;

    // Initializing input widget for JSON Document:

    test2Layout->addWidget(new QLabel(tr("JSON Document: ")), 0, 0);
    m_jsonDocumentInput = new QPlainTextEdit;
    test2Layout->addWidget(m_jsonDocumentInput, 1, 0, 1, 3);

    QString defaultText = "{\n    \"id\": \"file\",\n    \"value\": \"This is the first value\",\n    \"value2\": \"This is another value\",\n  "
"  \"number\": 180,\n    \"popup\": {\n        \"menu_items\": [\n            {\"value\": \"New1\", \"onclick\": \"CreateNewDoc1()\"},\n           "
" {\"value\": \"Open1\", \"onclick\": \"OpenDoc1()\"},\n            {\"value\": \"Close1\", \"onclick\": \"CloseDoc1()\"}\n        ]\n    }\n}";

    m_jsonDocumentInput->setPlainText(defaultText);

    // Initializing input widget for the path and connecting returnPressed to the getJsonValueSlot slot:

    QLabel* jsonPathLabel = new QLabel(tr("Enter JSON Path: "));
    test2Layout->addWidget(jsonPathLabel, 2, 0);
    m_jsonPathInput = new QLineEdit;
    m_jsonPathInput->setText("popup.menu_items[1].value");
    test2Layout->addWidget(m_jsonPathInput, 2, 1);

    connect(m_jsonPathInput, &QLineEdit::returnPressed, this, &QAppWidget::getJsonValueSlot);

    // Creating the button "Get Value" and connecting it to the getJsonValueSlot slot:

    QPushButton* getValueButton = new QPushButton(tr("Get Value"));
    test2Layout->addWidget(getValueButton, 2, 2, Qt::AlignHCenter);

    connect(getValueButton, &QPushButton::clicked, this, &QAppWidget::getJsonValueSlot);

    // Initializing the output widget for the retrieved value:

    QLabel* jsonValueLabel = new QLabel(tr("JSON Value: "));
    test2Layout->addWidget(jsonValueLabel, 3, 0);
    m_jsonValueOutput = new QPlainTextEdit;
    m_jsonValueOutput->setReadOnly(true);
    test2Layout->addWidget(m_jsonValueOutput, 4, 0, 1, 3);

    setLayout(test2Layout);
}
QAppWidget::~QAppWidget()
{

}
void QAppWidget::getJsonValueSlot()
{
    QTextDocument* doc = m_jsonDocumentInput->document();
    QString text = doc->toPlainText();
    QByteArray raw = text.toUtf8();

    // Checking if the input is a valid JSON document:
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(raw, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        QMessageBox errorMessage;
        errorMessage.setText("QJsonParseError: " + jsonError.errorString());
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.exec();
        return;
    }

    QVariant variant = jsonDocument.toVariant();
    QJsonValue rootJsonValue = QJsonValue::fromVariant(variant);

    QString path = m_jsonPathInput->text();

    // Calling the getJsonValue function:
    try
    {
        QVariant jsonValue = getJsonValue(rootJsonValue, path);
        updateJsonValueOutput(jsonValue);
    }
    catch (QGetJsonValueException& ex)
    {
        QMessageBox errorMessage;
        errorMessage.setText("QGetJsonValueException: " + ex.getMessage());
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.exec();
    }
}
void QAppWidget::updateJsonValueOutput(const QVariant& value)
{
    QJsonValue jsonValue = QJsonValue::fromVariant(value);
    QString text;
    if (jsonValue.isObject() || jsonValue.isArray())
    {
        QJsonDocument doc = QJsonDocument::fromVariant(value);
        text = doc.toJson();
    }
    else if (jsonValue.isUndefined())
    {
        text = "<Undefined>";
    }
    else if (jsonValue.isNull())
    {
        text = "<Null>";
    }
    else
    {
        text = value.toString();
    }
    m_jsonValueOutput->setPlainText(text);
}
