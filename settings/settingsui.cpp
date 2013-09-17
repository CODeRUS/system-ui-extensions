#include "settingsui.h"

#include "brightnesswidget.h"
#include "toolswidget.h"

#include <MLabel>

StatusMenuExtensionsWidget::StatusMenuExtensionsWidget(QGraphicsWidget *parent):
    DcpWidget(parent)
{
    setReferer(-1);
    initWidget();

    // this demonstrates the usage of the progress indicator:
    //setProgressIndicatorVisible (true);
    //QTimer::singleShot ( 8000, this, SLOT(loadingFinished()) );
}

void StatusMenuExtensionsWidget::initWidget()
{
//    m_layout = new MLayout(this);
//    m_policy = new MLinearLayoutPolicy(m_layout, Qt::Vertical);
//    m_policy->setSpacing(0);
//    m_layout->setPolicy(m_policy);

    MLabel *title = new MLabel("Status Menu Extensions", this);
    QFont font = title->font();
    font.setPixelSize(35);
//    font.setBold(true);
    font.setUnderline(true);
    title->setFont(font);
    title->setColor(QColor(255,255,255));
    title->setPos(10,0);
//    m_policy->addItem(title);

    MBrightnessWidgetSettings *brightness = new MBrightnessWidgetSettings(this);
    brightness->setPos(10,80);

    MToolsWidgetSettings *tools = new MToolsWidgetSettings(this);
    tools->setMaximumWidth(480);
    tools->setMinimumWidth(480);
    tools->setPos(10, 160);
//    m_policy->addItem(tools);
}

void StatusMenuExtensionsWidget::loadingFinished()
{
    //setProgressIndicatorVisible (false);
}

StatusMenuExtensionsWidget::~StatusMenuExtensionsWidget()
{

}

