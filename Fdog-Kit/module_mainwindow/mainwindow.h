﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "module_zookeeper/zookeepermanagewidget.h"
#include "module_zookeeper/zookeeperwidget.h"
#include "module_connect/createconnect.h"
#include "module_historyconnect/historyconnectwidget.h"
#include "module_ssh/sshwidget.h"
#include "module_tool/toolswidget.h"
#include <QGraphicsDropShadowEffect>
#include <QVector>
#include <QRect>
#include "module_setting/settingwidget.h"
#include <QSystemTrayIcon>
#include "module_config/config.h"
#include "module_thrift/thriftwidget.h"
#include "module_flowlayout/flowlayout.h"
#include "module_sql/sqlhandle.h"
#include "module_ssh/downloadwidget.h"
#include "module_qss/qss.h"
#define STRETCH_RECT_HEIGHT 10       // 拉伸小矩形的高度;
#define STRETCH_RECT_WIDTH 10        // 拉伸小矩形的宽度;

#define DARK_THEME 1   //暗黑主题
#define LIGHT_THEME 2  //浅色主题
#define BLUE_THEME 3   //蓝色主题


enum WindowStretchRectState
{
    NO_SELECT = 0,              // 鼠标未进入下方矩形区域;
    LEFT_TOP_RECT,              // 鼠标在左上角区域;
    TOP_BORDER,                 // 鼠标在上边框区域;
    RIGHT_TOP_RECT,             // 鼠标在右上角区域;
    RIGHT_BORDER,               // 鼠标在右边框区域;
    RIGHT_BOTTOM_RECT,          // 鼠标在右下角区域;
    BOTTOM_BORDER,              // 鼠标在下边框区域;
    LEFT_BOTTOM_RECT,           // 鼠标在左下角区域;
    LEFT_BORDER                 // 鼠标在左边框区域;
};



namespace Ui {
class MainWindow;
}


class WidgetMouseFilter : public QObject
{
   Q_OBJECT
public:
   WidgetMouseFilter(QObject *parent = nullptr) : QObject(parent) {}

protected:
    bool eventFilter(QObject *object, QEvent *event) {
        if (object->isWidgetType()) {
            QWidget *widget = static_cast<QWidget*>(object);
            if (event->type() == QEvent::Enter) {
                // 当鼠标进入widget时增加宽度
                widget->resize(widget->width() + 10, widget->height());
                widget->resize(widget->width(), widget->height() + 10);
            } else if (event->type() == QEvent::Leave) {
                // 当鼠标离开widget时还原宽度
                widget->resize(widget->width() - 10, widget->height());
                widget->resize(widget->width(), widget->height() - 10);
            }
        }
        // 继续传递事件
        return false;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void calculateCurrentStrechRect();

    WindowStretchRectState getCurrentStretchState(QPoint cursorPos);
    void updateMouseStyle(WindowStretchRectState stretchState);
    void updateWindowSize();
    void setSupportStretch(bool isSupportStretch);

    void mousePressEvent(QMouseEvent *event);       //鼠标点击
    void mouseMoveEvent(QMouseEvent *event);        //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);     //鼠标释放
    void mouseDoubleClickEvent(QMouseEvent *event); //鼠标双击
    //void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

    void changeEvent(QEvent *event);

    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void newConnectZk(QString name, QString host, QString port);

    //创建托盘显示
    void createSystemTray();

    //根据设置窗口样式
    void setWindowsByConf();

    //检测新版本
    void checkNewVersion();

    //判断版本
    bool isVersionGreater(const QString &version1, const QString &version2);

    //切换主题
    void changeMainWindowTheme();


private slots:
    void on_toolButton_close_clicked();

    void on_toolButton_min_clicked();

    void on_toolButton_max_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_newCreate();

    void on_newTool();

    
    void on_newConnnect(connnectInfoStruct& cInfoStruct);

    void rece_fastConnection(connnectInfoStruct& cInfoStruct);

    void rece_findConnection(QString text, int type = 0);
    
    void rece_windowsSetting();

    void on_newClose();


    void on_widget_welcome_body_widget2_newCreate_newTerminal_clicked();

    void rece_widget_welcome_body_widget2_newCreate_newTool_clicked();

    void on_comboBox_tool_currentIndexChanged(int index);

    void on_lineEdit_hex_textChanged(const QString &arg1);

    void on_lineEdit_dec_textChanged(const QString &arg1);

    void on_lineEdit_oct_textChanged(const QString &arg1);

    void on_lineEdit_bin_textChanged(const QString &arg1);

    void on_toolButton_decode_clicked();

    void on_toolButton_encode_clicked();

    void rece_showtimestamp();
    void on_toolButton_time2date_clicked();

    void on_toolButton_date2time_clicked();

    void on_toolButton_timestamp_copy_clicked();

    void on_toolButton_closetool_clicked();

    void rece_toolButton_fullScreen_sign();

    void rece_connection_success(sshwidget * sw);

    void rece_connection_fail(sshwidget * sw);

    void closeWindow();

    void minWindow();

    void maxWindow();

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void restoreWindow();

    void on_tabWidget_customContextMenuRequested(const QPoint &pos);

    //托盘菜单
    void rece_systemTrayMenu();

    void on_toolButton_thrift_tool_clicked();

    void on_toolButton_zk_tool_clicked();

    void on_toolButton_side_theme_clicked();

    void on_toolButton_side_setting_clicked();

    void on_toolButton_side_thrift_clicked();

    void on_toolButton_side_zookeeper_clicked();

    void on_toolButton_side_github_clicked();

    void on_toolButton_side_about_clicked();

    void on_toolButton_side_home_clicked();

    void on_toolButton_side_shell_clicked();

    void on_toolButton_side_tool_clicked();

    void rece_reconnection_sgin();

    void rece_copyTag_sgin();

    void rece_close_sgin();

    void rece_closeOther_sgin();

    void rece_closeAll_sgin();

    void on_toolButton_side_qss_clicked();

    void on_toolButton_side_mysql_clicked();

    void on_toolButton_newVersion_clicked();

    void whenAnimationFinish();

    void on_toolButton_more_clicked();

private:
    Ui::MainWindow *ui;
    //FlowLayout * m_flowlayout;
    QRect m_leftTopRect;
    QRect m_leftBottomRect;
    QRect m_rightTopRect;
    QRect m_rightBottomRect;
    QRect m_topBorderRect;
    QRect m_rightBorderRect;
    QRect m_bottomBorderRect;
    QRect m_leftBorderRect;

    QRect mWindow;
    QSystemTrayIcon* trayIcon;

    QGraphicsDropShadowEffect * defaultShadow;
    QPoint last;            //窗口拖动用变量
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool showFlag = false;  //窗口显示标志位 默认false 正常显示
    bool isPressedWidget;

    QMenu * men;            //新建菜单栏
    QAction * ssh;          //ssh连接
    QAction * zk;           //zk连接
    QAction * kafka;        //kafka连接
    QAction * redis;        //redis连接
    QAction * db;           //database连接

    QMenu * men_tool;       //工具菜单栏

    QAction * jsonFormat;   //json格式化
    QAction * xmlFormat;    //xml格式化
    QAction * textDiff;     //url文本对比
    QAction * textTest;     //thrift接口测试
    QAction * zkVisual;     //zk可视化
    QAction * toolAssemble; //小工具集合


    WindowStretchRectState m_stretchRectState;
    bool m_isMousePressed;
    QRect m_windowRectBeforeStretch;
    bool m_isSupportStretch;
    createconnect *ccwidget =nullptr;           //创建连接窗口
    historyconnectwidget * hcwidget = nullptr;  //快速连接
    toolswidget * tswidget = nullptr;           //创建工具窗口
    qss * qsswidget = nullptr;                  //创建qss工具窗口
    settingwidget * stwidget = nullptr;         //创建设置窗口
    zookeepermanagewidget * zmanagewidget = nullptr; //zk窗口
    thriftwidget * twidget = nullptr;           //thrift测试工具窗口

    QVector<zookeeperwidget*> zkWidgetList;
    QVector<sshwidget*> sshWidgetList;

    bool isShowToolKit = false; //是否显示工具栏
    bool isFullScreen = false;  //是否全屏
    bool isMaxShow = false;     //是否最大化显示
    config * confInfo = nullptr; //配置信息
    int currentTheme = 0;        //当前主题
    bool isFirst = false;           //是否第一次点击终端

    //操作数据库
    sqlhandle * db_;

    QString newVersion;         //新版本
    QString NewVersionData;     //新版本更新内容
    QString NewVersiondownLoad;  //新版本下载地址

    int mode = 2; //默认暗黑模式
    
};

#endif // MAINWINDOW_H
