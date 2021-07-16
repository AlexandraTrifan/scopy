#include "m2k_tool_pack.hpp"

#include "src/logicanalyzer/logic_analyzer.h"

#include <scopy/core/tool_interface.hpp>
#include <scopy/core/hardware_resource.hpp>

#include "src/oscilloscope.hpp"
#include "src/signal_generator.hpp"

#include "src/tool.hpp"

#include "libm2k/m2k.hpp"

#include "toolmenu.h"
#include "filter.hpp"
#include "toolmenuitem.h"

using namespace scopy::core;

// Adapt to ToolInterface in order to use the plugin system
class ToolToToolInterfaceAdapter : public ToolInterface {

public:
	ToolToToolInterfaceAdapter(adiscope::Tool *tl, int identifier)
		: m_tl(tl)
		, m_identifier(identifier) {}

	// ToolInterface interface
public:
	QWidget *getWidget() override {
		return m_tl;
	}

	int getIdentifier() const override {
		return m_identifier;
	}

	std::vector<QWidget *> getPreferences() override {
		return {/*m_tl->preferences*/};
	}

	HardwareResource getHardwareResource() const override {
		return {{""}, "", HardwareResource::ConnectionType::USB};
	}

private:
	adiscope::Tool *m_tl;
	int m_identifier;
};

// Plugin implementation

M2kToolPack::M2kToolPack() : QObject()
{

}

std::vector<ToolInterface *> M2kToolPack::getTools(iio_context *ctx, void *toolMenu)
{

	// !!!!!!!!!!!!!!!!!
	// In order for this reinterpret_cast to work w/o causing undefined behaviour
	// ToolMenu, BaseMenu, ToolMenuItem, and all the classes that are being used
	// in the source code of this plugin need to be identical to the ones used
	// in scopy::gui
	// If undefined behaviour is observed, the reinterpret_cast can be replaced with
	// the following lines:
	// auto fltr = new Filter(ctx);
	// adiscope::ToolMenu *tm = new adiscope::ToolMenu(nullptr, nullptr);
	// tm->loadToolsFromFilter(fltr);
	// The result should be a separate tool menu for the instantiated tools below
	// w/o the one that is provided by the ToolLauncher through the void * ptr. With
	// this test we can identify if the undefined behaviour is coming from the
	// reinterpret_cast or not

	// !!!!!!!!!!!!!!!!!
	// if tools need buttons from the menu
	// where casts are involved for example in the oscilloscope
	// auto btn = dynamic_cast<CustomPushButton *>(run_button);
	// reinterpret_cast is needed for this work:
	// auto btn = reinterpret_cast<CustomPushButton *>(run_button);

	adiscope::ToolMenu *tm = reinterpret_cast<adiscope::ToolMenu *>(toolMenu);

	adiscope::Tool *osc = new adiscope::Oscilloscope(ctx,
							nullptr,
							tm->getToolMenuItemFor(adiscope::TOOL_OSCILLOSCOPE),
							nullptr,
							nullptr);

	adiscope::Tool *siggen = new adiscope::SignalGenerator(ctx,
							nullptr,
							tm->getToolMenuItemFor(adiscope::TOOL_SIGNAL_GENERATOR),
							nullptr,
							nullptr);

	adiscope::Tool *la = new adiscope::logic::LogicAnalyzer(ctx,
								nullptr,
								tm->getToolMenuItemFor(adiscope::TOOL_LOGIC_ANALYZER),
								nullptr,
								nullptr);


	// {adiscope::logic::LogicAnalyzer::getDetails()}

	return {new ToolToToolInterfaceAdapter(osc, adiscope::TOOL_OSCILLOSCOPE),
		new ToolToToolInterfaceAdapter(siggen, adiscope::TOOL_SIGNAL_GENERATOR),
		new ToolToToolInterfaceAdapter(la, adiscope::TOOL_LOGIC_ANALYZER)};
}

std::vector<QWidget *> M2kToolPack::getControls()
{
	return {};
}
