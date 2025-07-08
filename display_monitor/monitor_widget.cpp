#include "monitor_widget.h"

namespace monitor {

MonitorWidget::MonitorWidget(QWidget *parent) {}

// 主窗口
QWidget *MonitorWidget::ShowAllMonitorWidget(const std::string& name) {
  QWidget *widget = new QWidget();
  stack_menu_ = new QStackedLayout();
  // 堆叠四个子控件，通过索引动态分页显示
  stack_menu_->addWidget(InitCpuMonitorWidget());
  stack_menu_->addWidget(InitSoftIrqMonitorWidget());
  stack_menu_->addWidget(InitMemMonitorWidget());
  stack_menu_->addWidget(InitNetMonitorWidget());

  // 布局
  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(InitButtonMenu(name), 1, 0);
  layout->addLayout(stack_menu_, 2, 0);
  widget->setLayout(layout);
  return widget;
}

// 菜单栏按钮
QWidget *MonitorWidget::InitButtonMenu(const std::string& name) {
  // char *name = getenv("USER");
  QPushButton *cpu_button = new QPushButton(QString::fromStdString(name) + "_cpu", this);
  QPushButton *soft_irq_button = new QPushButton(QString::fromStdString(name) + "_soft_irq", this);
  QPushButton *mem_button = new QPushButton(QString::fromStdString(name) + "_mem", this);
  QPushButton *net_button = new QPushButton(QString::fromStdString(name) + "_net", this);
  // QFont *font = new QFont("Microsoft YaHei", 15, 40);
  QFont font = QFont("Microsoft YaHei", 15, 40);
  cpu_button->setFont(font);
  soft_irq_button->setFont(font);
  mem_button->setFont(font);
  net_button->setFont(font);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(cpu_button);
  layout->addWidget(soft_irq_button);
  layout->addWidget(mem_button);
  layout->addWidget(net_button);

  QWidget *widget = new QWidget();
  widget->setLayout(layout);

  // connect(发送者，信号，接受者，槽函数（处理函数）)
  connect(cpu_button, SIGNAL(clicked()), this, SLOT(ClickCpuButton()));
  connect(soft_irq_button, SIGNAL(clicked()), this, SLOT(ClickSoftIrqButton()));
  connect(mem_button, SIGNAL(clicked()), this, SLOT(ClickMemButton()));
  connect(net_button, SIGNAL(clicked()), this, SLOT(ClickNetButton()));
 
  return widget;
}

// 以下四个函数分别是四个监控窗口
QWidget *MonitorWidget::InitCpuMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *cpu_load_label = new QLabel(this);
  cpu_load_label->setText(tr("Monitor CpuLoad:"));
  cpu_load_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_load_monitor_view_ = new QTableView;
  cpu_load_model_ = new CpuLoadModel(this);
  cpu_load_monitor_view_->setModel(cpu_load_model_);
  cpu_load_monitor_view_->show();

  QLabel *cpu_stat_label = new QLabel(this);
  cpu_stat_label->setText(tr("Monitor CpuStat:"));
  cpu_stat_label->setFont(QFont("Microsoft YaHei", 10, 40));

  cpu_stat_monitor_view_ = new QTableView;
  cpu_stat_model_ = new CpuStatModel(this);
  cpu_stat_monitor_view_->setModel(cpu_stat_model_);
  cpu_stat_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(cpu_load_label, 3, 0);
  layout->addWidget(cpu_load_monitor_view_, 4, 0, 2, 2);

  layout->addWidget(cpu_stat_label, 1, 0, 1, 1);
  layout->addWidget(cpu_stat_monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitSoftIrqMonitorWidget() {
  QWidget *widget = new QWidget();
  QLabel *softirq_label = new QLabel(this);
  softirq_label->setText(tr("Monitor softirq:"));
  softirq_label->setFont(QFont("Microsoft YaHei", 10, 40));

  softirq_monitor_view_ = new QTableView;
  softirq_model_ = new SoftirqModel(this);
  softirq_monitor_view_->setModel(softirq_model_);
  softirq_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(softirq_label, 1, 0);
  layout->addWidget(softirq_monitor_view_, 2, 0, 1, 2);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitMemMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *mem_label = new QLabel(this);
  mem_label->setText(tr("Monitor mem:"));
  mem_label->setFont(QFont("Microsoft YaHei", 10, 40));

  mem_monitor_view_ = new QTableView;
  mem_model_ = new MemModel(this);
  mem_monitor_view_->setModel(mem_model_);
  mem_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(mem_label, 1, 0);
  layout->addWidget(mem_monitor_view_, 2, 0, 1, 1);

  widget->setLayout(layout);
  return widget;
}

QWidget *MonitorWidget::InitNetMonitorWidget() {
  QWidget *widget = new QWidget();

  QLabel *net_label = new QLabel(this);
  net_label->setText(tr("Monitor net:"));
  net_label->setFont(QFont("Microsoft YaHei", 10, 40));

  net_monitor_view_ = new QTableView;
  net_model_ = new NetModel(this);
  net_monitor_view_->setModel(net_model_);
  net_monitor_view_->show();

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(net_label, 1, 0);
  layout->addWidget(net_monitor_view_, 2, 0, 1, 1);

  widget->setLayout(layout);
  return widget;
}

// 更新数据
void MonitorWidget::UpdateData(
    const monitor::proto::MonitorInfo &monitor_info) {
  softirq_model_->UpdateMonitorInfo(monitor_info);
  cpu_load_model_->UpdateMonitorInfo(monitor_info);
  cpu_stat_model_->UpdateMonitorInfo(monitor_info);
  mem_model_->UpdateMonitorInfo(monitor_info);
  net_model_->UpdateMonitorInfo(monitor_info);
}

void MonitorWidget::ClickCpuButton() { stack_menu_->setCurrentIndex(0); }
void MonitorWidget::ClickSoftIrqButton() { stack_menu_->setCurrentIndex(1); }
void MonitorWidget::ClickMemButton() { stack_menu_->setCurrentIndex(2); }
void MonitorWidget::ClickNetButton() { stack_menu_->setCurrentIndex(3); }
}  // namespace monitor
