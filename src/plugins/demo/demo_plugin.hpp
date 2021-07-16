#ifndef DEMOPLUGIN_HPP
#define DEMOPLUGIN_HPP

#include <QObject>
#include <QWidget>

#include "core/plugin_interface.hpp"
#include "toolmenuitem.h"

using namespace scopy::core;
using namespace adiscope;

class DemoPlugin : public QObject, public scopy::core::PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Scopy.Core.PluginInterface" FILE "demo_plugin.json")
	Q_INTERFACES(scopy::core::PluginInterface)
public:
	DemoPlugin();

	std::vector<ToolInterface*> getTools(struct iio_context *ctx, const char *uri, void *toolMenu) override;
	std::vector<void*> getToolsInfo(iio_context *ctx, void *toolMenu) override;
//	std::vector<ToolInterface*> getTools(struct iio_context *ctx, scopy::gui::ToolMenu *menu) override;
	bool compatible(const std::unordered_set<std::string> &iio_device_list/*iio_context*/) const override;
//	std::vector<QWidget*> getControls(/*iio_context*/) override;
	int priority() const override { return 0; }
	std::string getName() const override;;
	QIcon getIcon() const override;
//	scopy::gui::Filter* getFilter() override;
	QWidget* getInfoWidget() override;
	std::vector<QWidget*> getExtraControls(/*iio_context*/) override;


private:
	void scan(iio_context *ctx, const char *uri, void *toolMenu);
public Q_SLOTS:
	void calibrateClicked();

private:
	std::map<std::string, ToolMenuItem*> m_devs_and_menus;
	QWidget *m_info_widget;
	std::vector<QWidget*> m_extra_controls;
	std::vector<ToolInterface*> m_tools;
};

#endif // DEMOPLUGIN_HPP
