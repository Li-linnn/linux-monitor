#include <QColor>
#include <QFont>

#include "monitor_inter.h"

namespace monitor {

QVariant MonitorInterModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role == Qt::FontRole) {
    return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
  }

  if (role == Qt::BackgroundRole) {
    return QVariant::fromValue(QColor(Qt::lightGray));
  }

  return QAbstractTableModel::headerData(section, orientation, role);
}
// 子类重写时，子类​​未覆盖​​基类中已处理的特定样式角色（如FontRole, BackgroundRole等），此处的设置就依然生效

QVariant MonitorInterModel::data(const QModelIndex &index, int role) const {
  if (role == Qt::TextAlignmentRole) {
    return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
  }

  if (role == Qt::TextColorRole) {
    return QVariant::fromValue(QColor(Qt::black));
  }

  if (role == Qt::BackgroundRole) {
    return QVariant::fromValue(QColor(Qt::white));
  }

  return QVariant();

}  // namespace monitor
}
