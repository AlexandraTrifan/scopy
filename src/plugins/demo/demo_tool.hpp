#ifndef DEMO_TOOL_HPP
#define DEMO_TOOL_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>

#include "toolmenuitem.h"
#include "core/tool_interface.hpp"
//#include <scopy/gui/tool_view_builder.hpp>
#include <libm2k/context.hpp>
#include <libm2k/analog/genericanalogin.hpp>

using namespace scopy::core;
using namespace adiscope;

class DemoTool : public QObject, public ToolInterface
{
	Q_OBJECT
public:
	DemoTool(libm2k::context::Context* context, libm2k::analog::GenericAnalogIn*,
		 ToolMenuItem *toolMenuItem);

	// ToolInterface interface
	int getIdentifier() const;
public:
	QWidget *getWidget() override;
	std::vector<QWidget *> getPreferences() override;
	HardwareResource getHardwareResource() const override;

private:
	int m_identifier;
//	ToolView *m_toolView{nullptr};
	QLabel *m_statusLabel{nullptr};
	ToolMenuItem* m_toolMenuItem;
};

#endif // DEMO_TOOL_HPP
