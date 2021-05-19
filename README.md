# JsonValue

The project demonstrates the function `QVariant getJsonValue(QJsonValue root, const QString &path)`. 

The function reads a json value from a `root` with a `path` string which uses dot `.` as keys separator and square brackets `[array index number]`.

Here is a json document sample:
```
{
    "id": "file",
    "value": "This is the first value",
    "value2": "This is another value",
    “number”: 180,
    "popup": {
        "menu_items": [
            {"value": "New1", "onclick": "CreateNewDoc1()"},
            {"value": "Open1", "onclick": "OpenDoc1()"},
            {"value": "Close1", "onclick": "CloseDoc1()"}
        ]
    }
}
```

