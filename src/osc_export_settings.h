#ifndef OSC_EXPORT_SETTINGS_H
#define OSC_EXPORT_SETTINGS_H

/* Qt includes */
#include <QMap>
#include <QPushButton>
#include <QStandardItem>
#include <QString>
#include <QWidget>

/* Local includes */
#include "dropdown_switch_list.h"

namespace Ui {
class ExportSettings;
}

namespace adiscope {
class ExportSettings : public QWidget {
	Q_OBJECT

public:
	explicit ExportSettings(QWidget *parent = 0);
	~ExportSettings();

	void clear();

public Q_SLOTS:
	void addChannel(int id, QString name);
	void removeChannel(int id);
	void onExportChannelChanged(QStandardItem *);

	QPushButton *getExportButton();
	QPushButton *getExportAllButton();
	QMap<int, bool> getExportConfig();
	void setExportConfig(QMap<int, bool> config);
	void on_btnExportAll_clicked();
	void enableExportButton(bool on);
	void disableUIMargins();
	void setTitleLabelVisible(bool enabled);
	void setExportAllButtonLabel(const QString &text);

protected:
	Ui::ExportSettings *ui;
	DropdownSwitchList *exportChannels;
	void checkIfAllActivated();
	int nr_channels;
	QMap<int, bool> oldSettings;
};
} // namespace adiscope

#endif // OSC_EXPORT_SETTINGS_H
