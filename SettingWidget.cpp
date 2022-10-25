#include "SettingWidget.h"
#include "ui_SettingWidget.h"
#include <QPainter>
#include <QDebug>

SettingWidget::SettingWidget(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::SettingWidget),
    followWidget(NULL),
    curLabel(NULL)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowModal);
    setTitleH(ui->setting->height());
    resize(580,420);

    exit = new Button(this);
    exit->init(EXIT_BUTTON);
    exit->resize(45,40);
    exit->move(width()-exit->width()-12, 12);
    connect(exit,&Button::clicked,this,&SettingWidget::hide);

    //----------------------------选项---------------------------------

    connect(ui->system,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->decode,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->dxvahdFilter,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->d3d11vaFilter,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->about,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->coder,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);
    connect(ui->addition,&SettingLabel::triggerCheckedSignal,this,&SettingWidget::triggerChecked);

    connect(ui->system,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->decode,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->dxvahdFilter,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->d3d11vaFilter,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->about,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->coder,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);
    connect(ui->addition,&SettingLabel::cancelCheckedSignal,this,&SettingWidget::cancelChecked);

    //----------------------------选项widget-------------------------------

    systemWidget = new SystemWidget(this);
    systemWidget->hide();

    decodeWidget = new DecodeWidget(this);
    decodeWidget->hide();

    dxvahdFilterWidget = new DXVAHDFilterWidget(this);
    dxvahdFilterWidget->hide();

    d3d11vaFilterWidget = new D3D11VAFilterWidget(this);
    d3d11vaFilterWidget->hide();

    additionWidget = new AdditionWidget(this);
    additionWidget->hide();

    aboutWidget = new AboutWidget(this);
    aboutWidget->hide();

    coderWidget = new CoderWidget(this);
    coderWidget->hide();

    //-----------------------------映射----------------------------------

    to[ui->system] = systemWidget;
    to[ui->decode] = decodeWidget;
    to[ui->dxvahdFilter] = dxvahdFilterWidget;
    to[ui->d3d11vaFilter] = d3d11vaFilterWidget;
    to[ui->addition] = additionWidget;
    to[ui->about] = aboutWidget;
    to[ui->coder] = coderWidget;

    //--------------------------------------------------------------------

    ui->decode->triggerChecked();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::follow(QWidget* w)
{
    followWidget=w;
}

D3D11VAFilterWidget* SettingWidget::getD3D11VAFilterWidget()
{
    return d3d11vaFilterWidget;
}

DXVAHDFilterWidget* SettingWidget::getDXVAHDFilterWidget()
{
    return dxvahdFilterWidget;
}

void SettingWidget::triggerChecked(SettingLabel* is)
{
    if(is == curLabel) return;

    if(curLabel)
        curLabel->cancelChecked();

    if(to[is])
    {
        ui->centerLayout->addWidget(to[is]);
        to[is]->show();
    }

    curLabel = is;
}

void SettingWidget::cancelChecked(SettingLabel* is)
{
    if(to[is])
    {
        ui->centerLayout->removeWidget(to[is]);
        to[is]->hide();
    }
}

void SettingWidget::paintEvent(QPaintEvent*)
{
    QImage title(":/settingTitle.jpg");
    int titleH = ui->setting->height();

    QPainter painter(this);

    QRect rect(0,0,width(),titleH);
    painter.drawImage(rect, title.scaled(QSize(width(),titleH),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    painter.setBrush(QColor(235,235,235));
    painter.setPen(Qt::transparent);

    int leftW = ui->decode->x() + ui->decode->width();
    painter.drawRect(0,titleH,leftW,height());
}

void SettingWidget::showFollow()
{
    if(followWidget)
    {
        int x = (followWidget->width() - width())/2 + followWidget->x();
        int y = (followWidget->height() - height())/2 + followWidget->y();
        move(x,y);
    }

    show();
}
