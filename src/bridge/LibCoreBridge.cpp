#include "bridge/LibCoreBridge.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <nlohmann/json.hpp>

#include "api/book.hpp"
#include "api/common.hpp"
#include "api/logs.hpp"
#include "api/stats.hpp"

#include <optional>

using json = nlohmann::json;
using namespace libcore;

namespace {

QVariant jsonToVariantImpl(const json& j) {
    if (j.is_null())          return QVariant();
    if (j.is_boolean())       return QVariant(j.get<bool>());
    if (j.is_number_integer())return QVariant(static_cast<qlonglong>(j.get<long long>()));
    if (j.is_number_float())  return QVariant(j.get<double>());
    if (j.is_string())        return QVariant(QString::fromStdString(j.get<std::string>()));
    if (j.is_array()) {
        QVariantList arr;
        for (const auto& item : j) arr.append(jsonToVariantImpl(item));
        return arr;
    }
    if (j.is_object()) {
        QVariantMap map;
        for (auto it = j.begin(); it != j.end(); ++it) {
            map[QString::fromStdString(it.key())] = jsonToVariantImpl(it.value());
        }
        return map;
    }
    return QVariant();
}

} // namespace

QVariant LibCoreBridge::jsonToVariant(const QJsonValue&) {
    return QVariant();
}

LibCoreBridge::LibCoreBridge(QObject* parent) : QObject(parent) {}

void LibCoreBridge::setLibrary(const QString& library) {
    library_ = library;
}

void LibCoreBridge::setToken(const QString& token) {
    token_ = token;
}

QVariantList LibCoreBridge::bookList(bool available_only) {
    QVariantList out;
    if (library_.isEmpty()) return out;

    try {
        auto resp = api::book_list(library_.toStdString(), token_.toStdString(), available_only);
        if (!resp.value("ok", false)) return out;

        for (const auto& b : resp["data"]["books"]) {
            out.append(jsonToVariantImpl(b));
        }
    } catch (...) {}
    return out;
}

QVariantMap LibCoreBridge::bookInfo(qint64 id) {
    QVariantMap out;
    if (library_.isEmpty()) return out;

    try {
        auto resp = api::book_info_by_id(library_.toStdString(), id);
        if (!resp.value("ok", false)) return out;
        return jsonToVariantImpl(resp["data"]).toMap();
    } catch (...) {}
    return out;
}

QVariantMap LibCoreBridge::stats(const QString& user) {
    QVariantMap out;
    if (library_.isEmpty()) return out;

    try {
        std::optional<std::string> u;
        if (!user.isEmpty()) u = user.toStdString();
        auto resp = api::stats(library_.toStdString(), token_.toStdString(), u);
        if (!resp.value("ok", false)) return out;
        return jsonToVariantImpl(resp["data"]).toMap();
    } catch (...) {}
    return out;
}

QVariantList LibCoreBridge::logs(int tail) {
    QVariantList out;
    if (library_.isEmpty()) return out;

    try {
        auto resp = api::logs(library_.toStdString(), token_.toStdString(),
                              std::nullopt, std::nullopt, std::nullopt, tail);
        if (!resp.value("ok", false)) return out;

        for (const auto& l : resp["data"]["logs"]) {
            out.append(jsonToVariantImpl(l));
        }
    } catch (...) {}
    return out;
}
