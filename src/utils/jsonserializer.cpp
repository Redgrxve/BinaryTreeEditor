#include "jsonserializer.h"
#include "binarytree.h"

#include <QFile>

bool JsonSerializer::saveToFile(TreeNode* root, const QString& filePath)
{
    QJsonObject json = serialize(root);
    QJsonDocument doc(json);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Не удалось открыть файл для записи:" << file.errorString();
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

TreeNode *JsonSerializer::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Не удалось открыть файл для чтения:" << file.errorString();
        return nullptr;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Ошибка парсинга JSON:" << parseError.errorString();
        return nullptr;
    }

    return deserialize(doc.object());
}

QJsonObject JsonSerializer::serialize(TreeNode *node)
{
    if (!node)
        return QJsonObject();

    QJsonObject obj;
    obj["value"] = node->value;
    obj["left"] = serialize(node->left);
    obj["right"] = serialize(node->right);
    return obj;
}

TreeNode *JsonSerializer::deserialize(const QJsonObject &obj)
{
    if (obj.isEmpty())
        return nullptr;

    TreeNode* node = new TreeNode(obj["value"].toInt());
    node->left = deserialize(obj["left"].toObject());
    node->right = deserialize(obj["right"].toObject());
    return node;
}
