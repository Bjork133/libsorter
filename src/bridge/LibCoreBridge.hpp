#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

class LibCoreBridge : public QObject {
    Q_OBJECT

public:
    explicit LibCoreBridge(QObject* parent = nullptr);

    // Установить активную библиотеку (имя).
    Q_INVOKABLE void setLibrary(const QString& library);

    // Установить токен (из профиля).
    Q_INVOKABLE void setToken(const QString& token);

    // book.list → QVariantList (список книг).
    Q_INVOKABLE QVariantList bookList(bool available_only = false);

    // book.info(id) → QVariantMap.
    Q_INVOKABLE QVariantMap bookInfo(qint64 id);

    // stats(user?) → QVariantMap.
    Q_INVOKABLE QVariantMap stats(const QString& user = "");

    // logs(tail) → QVariantList.
    Q_INVOKABLE QVariantList logs(int tail = 50);

private:
    QString library_;
    QString token_;

    // Преобразование JSON → QVariant.
    static QVariant jsonToVariant(const QJsonValue& v);
};
