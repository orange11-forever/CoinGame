#ifndef DATACONFIG_H
#define DATACONFIG_H
#include <QObject>
#include<QMap>
#include<QVector>
class DataConfig : public QObject
{
    Q_OBJECT
public:
    explicit DataConfig(QObject *parent = nullptr);
    QMap<int,QVector<QVector<int>>>m_Data;//关卡数据容器
signals:
};

#endif // DATACONFIG_H
