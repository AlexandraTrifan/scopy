/*
 * Copyright (c) 2019 Analog Devices Inc.
 *
 * This file is part of Scopy
 * (see http://www.github.com/analogdevicesinc/scopy).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEVICE_WIDGET_HPP
#define DEVICE_WIDGET_HPP

#include <QWidget>
#include <QPushButton>

#include "iio.h"
#include "core/plugin_interface.hpp"

namespace Ui {
class Device;
}

namespace adiscope {
class InfoPage;
class ToolLauncher;

class DeviceWidget : public QWidget
{
	Q_OBJECT
public:
	explicit DeviceWidget(std::string uri, scopy::core::PluginInterface *plugin,
			      QWidget *parent = nullptr);
	virtual ~DeviceWidget();

	QPushButton* deviceButton() const;
	QPushButton* connectButton() const;
	QPushButton* calibrateButton() const;

	void setChecked(bool);
	bool isChecked();

	std::string uri() const;
	void setUri(const std::string &uri);

	void highlightDevice();
	void click();

	InfoPage *infoPage() const;
	void setInfoPage(InfoPage *infoPage);

	bool connected() const;
	void setConnected(bool, bool, struct iio_context* ctx = nullptr);

	void setName(std::string name);
	void setIcon(QIcon icon);

	scopy::core::PluginInterface *plugin() const;
Q_SIGNALS:
	void selected(bool);
	void connected(bool);

	void nameChanged();
	void iconChanged();
	void forgetDevice(std::string);

public Q_SLOTS:
	void on_btn_toggled(bool);
	void forgetDevice_clicked(bool);
//	void identifyDevice_clicked(bool);

private Q_SLOTS:
//	void on_connectBtn_clicked(bool);
	void refreshName();
	void refreshIcon();

protected:
	Ui::Device *m_ui;
	std::string m_uri;
	std::string m_name;
	InfoPage *m_infoPage;
	bool m_connected;
	bool m_selected;
	QIcon m_icon;
	scopy::core::PluginInterface *m_plugin;
};

//class M2kDeviceWidget : public DeviceWidget
//{
//	Q_OBJECT
//public:
//	explicit M2kDeviceWidget(QString uri, QString name,
//				 ToolLauncher *parent = nullptr);
//	~M2kDeviceWidget();
//};

//class DeviceBuilder
//{
//public:
//	enum DeviceType {
//		GENERIC = 0,
//		M2K = 1,
//	};

//	static DeviceWidget* newDevice(DeviceType dev_type,
//				       QString uri, QString name,
//				       ToolLauncher *parent = nullptr)
//	{
//		switch (dev_type) {
//		case GENERIC: return new DeviceWidget(uri, name, parent);
//		case M2K: return new M2kDeviceWidget(uri, name, parent);
//		}
//		return nullptr;
//	}
//};

} /* namespace adiscope */

#endif // DEVICE_WIDGET_HPP
