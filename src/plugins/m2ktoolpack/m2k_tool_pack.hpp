#ifndef M2KTOOLPACK_HPP
#define M2KTOOLPACK_HPP

#include <QObject>
#include <QWidget>

#include <scopy/core/plugin_interface.hpp>

#include <iio.h>

using namespace scopy::core;

class M2kToolPack : public QObject, public scopy::core::PluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Scopy.Core.PluginInterface" FILE "m2k_tool_pack.json")
	Q_INTERFACES(scopy::core::PluginInterface)
public:
	M2kToolPack();


	// PluginInterface interface
public:
	std::vector<ToolInterface *> getTools(struct iio_context *ctx/*, scopy::gui::ToolMenu *menu*/, void *toolMenu) override;
	bool compatible(const std::unordered_set<std::string> &iio_device_list/*iio_context*/) const override {return false;};
	std::vector<QWidget *> getControls() override;
};

#endif // M2KTOOLPACK_HPP
