#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>

class TreeNode;

class JsonSerializer
{
public:
    static bool saveToFile(TreeNode *root, const QString &filePath);
    static TreeNode *loadFromFile(const QString &filePath);

    static QJsonObject serialize(TreeNode *node);
    static TreeNode *deserialize(const QJsonObject &obj);
};

#endif // JSONSERIALIZER_H
