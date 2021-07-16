#include "demo_tool.hpp"

//#include "demo_data_source.hpp"




#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>


DemoTool::DemoTool(libm2k::context::Context *context, libm2k::analog::GenericAnalogIn*, ToolMenuItem *toolMenuItem)
	: m_identifier(0)
	, m_toolMenuItem(toolMenuItem)
{
//	ToolViewRecipe recipe;
//	recipe.helpBtnUrl = "https://google.com";
//	recipe.hasRunBtn = true;
//	recipe.hasSingleBtn = true;
//	recipe.hasPrintBtn = true;
//	m_toolView = ToolViewBuilder(recipe).build();

	toolMenuItem->getToolStopBtn()->setVisible(true);
//	connect(toolMenuItem->getToolStopBtn(), &QPushButton::toggled,
//		m_toolView->getRunBtn(), &QPushButton::setChecked);
//	connect(m_toolView->getRunBtn(), &QPushButton::toggled,
//		toolMenuItem->getToolStopBtn(), &QPushButton::setChecked);

//	connect(run_button, &QPushButton::clicked, [=](){
//		if (getDataSource()->acquireOwnership(DataSource::AcquirePolicy::TrySteal)) {
			// We own the hardware resource here
			// 1. do hardware settings
			// ...
			// 2. start the data source
//			getDataSource()->start();
//		} else {
//			m_statusLabel->setText("Failed to start!");
//		}
//	});

//	m_toolView->setStyleSheet("background-color: #e27d60");
}

int DemoTool::getIdentifier() const
{
	return m_toolMenuItem->position();
}

QWidget *DemoTool::getWidget()
{
//	return m_toolView;
	return nullptr;
}

std::vector<QWidget *> DemoTool::getPreferences()
{
	return {};
}

HardwareResource DemoTool::getHardwareResource() const
{
	// This tool has a data source, the data source in this
	// case is "talking" to the hardware so we return its
	// hardware resource
//	return getDataSource()->hardwareResource();
	return HardwareResource();
}
