#include "demo_plugin.hpp"
#include "demo_tool.hpp"

#include "toolmenu.h"
#include <libm2k/context.hpp>
#include <libm2k/generic.hpp>
#include <libm2k/contextbuilder.hpp>

#include <QDebug>
#include <map>

using namespace std;
using namespace scopy::core;
using namespace adiscope;
using namespace libm2k::context;

DemoPlugin::DemoPlugin()
	: QObject()
{}

// scanUri -> ctx, uri, plugin  -> create ctx, get name, get tool details, prepare tools
// this is at the first selection
// at connect, only create them


void DemoPlugin::scan(iio_context *ctx, const char* uri, void *toolMenu)
{
	ToolMenu *tm = reinterpret_cast<ToolMenu *>(toolMenu);
	Context* tmpCtx = contextOpen(ctx, uri);
	Generic* generic = tmpCtx->toGeneric();
//	m_devs_and_menus.insert(std::make_pair(analogin->getName(), toolMenuItem));

	if (generic) {
		for (auto i_ain = 0; i_ain < generic->getAnalogInCount(); i_ain++) {
			auto analogin = generic->getAnalogIn(i_ain);
			auto tool = new DemoTool(tmpCtx, analogin, tm->getToolMenuItemFor(TOOL_OSCILLOSCOPE));
			m_tools.push_back(tool);
		}
//		for (auto i_ain = 0; i_ain < generic->getAnalogOutCount(); i_ain++) {
//			auto analogin = generic->getAnalogOut(i_ain);
//			m_tools.push_back(new DemoTool(tmpCtx, analogin, tm->getToolMenuItemFor(TOOL_OSCILLOSCOPE)));
//		}

		//check analogins and load stuff
		//oscilloscope (tmpCtx, analogin, toolmenuitem(saved by iio_dev))

	}
}

// this is equivalent to CONNECT
std::vector<ToolInterface*> DemoPlugin::getTools(iio_context *ctx, const char* uri, void *toolMenu)
{
	scan(ctx, uri, toolMenu);
	return m_tools;
//	const char *uri = "";
//	ToolMenu *tm = reinterpret_cast<ToolMenu *>(toolMenu);
//	Context* context = contextOpen(ctx, uri);

//	DemoTool *osc_tool = new DemoTool(context, tm->getToolMenuItemFor(TOOL_OSCILLOSCOPE));
//	return {osc_tool};
}

std::vector<void*> DemoPlugin::getToolsInfo(iio_context *ctx, void *toolMenu)
{
	// ToolDetails -> {name, icon, } getToolDetails static

	std::vector<void*> ret = {};
	const char *uri = "";
	ToolMenu *tm = reinterpret_cast<ToolMenu *>(toolMenu);
	Context* tmpCtx = contextOpen(ctx, uri);
	Generic* generic = tmpCtx->toGeneric();
	if (generic) {
		for (auto i_ain = 0; i_ain < generic->getAnalogInCount(); i_ain++) {
			auto analogin = generic->getAnalogIn(i_ain);
			auto toolMenuItem = tm->getToolMenuItemFor(TOOL_OSCILLOSCOPE);
			m_devs_and_menus.insert(std::make_pair(analogin->getName(), toolMenuItem));
			tm->insertMenuItem(toolMenuItem, i_ain);
			toolMenuItem->setEnabled(true);
			ret.push_back(toolMenuItem);
		}

		//check analogins and load stuff
		//oscilloscope (tmpCtx, analogin, toolmenuitem(saved by iio_dev))

	}

	return ret;


//	contextClose(context);
}

bool DemoPlugin::compatible(const std::unordered_set<std::string> &iio_device_list/*iio_context*/) const
{
	//load the plugin/file.json and check the iio_device_list

	return true;
}

//std::vector<QWidget*> DemoPlugin::getControls(/*iio_context*/) { return {}; }

std::string DemoPlugin::getName() const
{
	return "DEMO-DEV";
}

QIcon DemoPlugin::getIcon() const
{
	return QIcon("/home/alexandra/git-repos/Pixelpulse2/icons/pp2.ico");
}

QWidget *DemoPlugin::getInfoWidget()
{
	m_info_widget = new QWidget();
	m_info_widget->setStyleSheet("background-color:red");
//	if (m_info_widget) {

//	}
//	return nullptr;
	return m_info_widget;
}

std::vector<QWidget *> DemoPlugin::getExtraControls()
{
	auto btn = new QPushButton("Calibrate it!");
	m_extra_controls.push_back(btn);
	connect(btn, &QPushButton::clicked, this,
		&DemoPlugin::calibrateClicked);
	return m_extra_controls;
}

void DemoPlugin::calibrateClicked()
{
	qDebug() << "CLICKED\n";
}

//Filter *DemoPlugin::getFilter()
//{
//	Filter* pluginFilter = new Filter();
//}
