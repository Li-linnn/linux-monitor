#include "cpu_softirq_model.h"

namespace monitor {
SoftirqModel::SoftirqModel(QObject* parent)
    : MonitorInterModel(parent) {
  header_ << tr("cpu");
  header_ << tr("hi");
  header_ << tr("timer");
  header_ << tr("net_tx");
  header_ << tr("net_rx");
  header_ << tr("block");
  header_ << tr("irq_poll");
  header_ << tr("tasklet");
  header_ << tr("sched");
  header_ << tr("hrtimer");
  header_ << tr("rcu");
}

int SoftirqModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int SoftirqModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}

QVariant SoftirqModel::headerData(int section, Qt::Orientation orientation,
                                          int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}

QVariant SoftirqModel::data(const QModelIndex& index, int role) const {
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }

  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return QVariant();
}

void SoftirqModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monito_info) {
  beginResetModel();
  monitor_data_.clear();

  for (int i = 0; i < monito_info.soft_irq_size(); i++) {
    monitor_data_.push_back(insert_one_soft_irq(monito_info.soft_irq(i)));
  }

  endResetModel();

  return;
} 

std::vector<QVariant> SoftirqModel::insert_one_soft_irq(
    const monitor::proto::SoftIrq& soft_irq) {
  std::vector<QVariant> soft_irq_list;
  for (int i = SoftIrqInfo::CPU_NAME; i < COLUMN_MAX; i++) {
    switch (i) {
      case SoftIrqInfo::CPU_NAME:
      // soft_irq_list.push_back(QVariant((soft_irq.cpu()));
        soft_irq_list.emplace_back(QVariant(QString::fromStdString(soft_irq.cpu())));
        break;
      case SoftIrqInfo::HI:
        soft_irq_list.emplace_back(QVariant(soft_irq.hi()));
        break;
      case SoftIrqInfo::TIMER:
        soft_irq_list.emplace_back(QVariant(soft_irq.timer()));
        break;
      case SoftIrqInfo::NET_TX:
        soft_irq_list.emplace_back(QVariant(soft_irq.net_tx()));
        break;
      case SoftIrqInfo::NET_RX:
        soft_irq_list.emplace_back(QVariant(soft_irq.net_rx()));
        break;
      case SoftIrqInfo::BLOCK:
        soft_irq_list.emplace_back(QVariant(soft_irq.block()));
        break;
      case SoftIrqInfo::IRQ_POLL:
        soft_irq_list.emplace_back(QVariant(soft_irq.irq_poll()));
        break;
      case SoftIrqInfo::TASKLET:
        soft_irq_list.emplace_back(QVariant(soft_irq.tasklet()));
        break;
      case SoftIrqInfo::SCHED:
        soft_irq_list.emplace_back(QVariant(soft_irq.sched()));
        break;
      case SoftIrqInfo::HRTIMER:
        soft_irq_list.emplace_back(QVariant(soft_irq.hrtimer()));
        break;
      case SoftIrqInfo::RCU:
        soft_irq_list.emplace_back(QVariant(soft_irq.rcu()));
        break;
      default:
        break;
    }
  }
  return soft_irq_list;
}
}  // namespace monitor
