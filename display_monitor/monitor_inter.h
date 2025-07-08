#pragma once
#include <QAbstractTableModel>// Qt 提供的抽象表格模型基类
#include <QObject> // Qt 对象系统的基类，提供信号槽机制和元对象功能。

namespace monitor {
// 二维数据基类
class MonitorInterModel : public QAbstractTableModel {
  Q_OBJECT

 public:
 // explicit:为了防止隐式转换造成的错误的父子关系
  explicit MonitorInterModel(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {}
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  virtual ~MonitorInterModel() {}
};

}  // namespace monitor
