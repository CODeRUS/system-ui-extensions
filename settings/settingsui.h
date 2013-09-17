#ifndef SETTINGSUI_H
#define SETTINGSUI_H

#include <QLocale>
#include <QTranslator>

#include <MApplicationWindow>
#include <MPannableViewport>
#include <MLinearLayoutPolicy>
#include <MApplicationPage>
#include <MLayout>
#include <MImageWidget>
#include <MButton>
#include <MDialog>

#include <stdio.h>
#include <QDebug>
#include <QTimer>

#include <DcpWidget>

class MLabel;

class StatusMenuExtensionsWidget : public DcpWidget
{
Q_OBJECT

public:
    StatusMenuExtensionsWidget(QGraphicsWidget *parent = 0);
    virtual ~StatusMenuExtensionsWidget();

    MLayout *m_layout;
    MLinearLayoutPolicy *m_policy;

protected:
    void initWidget();

protected slots:
    void loadingFinished();
};

#endif // SETTINGSUI_H
