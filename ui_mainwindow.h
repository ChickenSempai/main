/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_3;
    QLabel *label_7;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *Brightness;
    QSlider *slider_b;
    QLabel *percent_b;
    QGroupBox *Color;
    QSlider *slider_c;
    QLabel *percent_c;
    QGroupBox *Saturation;
    QSlider *slider_s;
    QLabel *percent_s;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(420, 472);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(191, 185, 206, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(223, 220, 230, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(95, 92, 103, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(127, 123, 137, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        MainWindow->setPalette(palette);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 390, 91, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 10, 291, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(20);
        label_2->setFont(font);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 80, 401, 71));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(90, 30, 54, 21));
        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(140, 30, 121, 22));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush8(QColor(0, 170, 127, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush8);
        QBrush brush9(QColor(0, 255, 191, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush9);
        QBrush brush10(QColor(0, 212, 159, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(0, 85, 63, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(0, 113, 84, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush13(QColor(127, 212, 191, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        comboBox->setPalette(palette1);
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 30, 51, 20));
        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 30, 51, 20));
        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(330, 30, 61, 20));
        Brightness = new QGroupBox(centralWidget);
        Brightness->setObjectName(QString::fromUtf8("Brightness"));
        Brightness->setGeometry(QRect(10, 160, 402, 61));
        slider_b = new QSlider(Brightness);
        slider_b->setObjectName(QString::fromUtf8("slider_b"));
        slider_b->setGeometry(QRect(16, 30, 351, 20));
        slider_b->setCursor(QCursor(Qt::ClosedHandCursor));
        slider_b->setMinimum(1);
        slider_b->setMaximum(100);
        slider_b->setTracking(false);
        slider_b->setOrientation(Qt::Horizontal);
        percent_b = new QLabel(Brightness);
        percent_b->setObjectName(QString::fromUtf8("percent_b"));
        percent_b->setGeometry(QRect(370, 30, 31, 20));
        Color = new QGroupBox(centralWidget);
        Color->setObjectName(QString::fromUtf8("Color"));
        Color->setGeometry(QRect(10, 230, 402, 61));
        slider_c = new QSlider(Color);
        slider_c->setObjectName(QString::fromUtf8("slider_c"));
        slider_c->setGeometry(QRect(16, 30, 351, 20));
        slider_c->setCursor(QCursor(Qt::ClosedHandCursor));
        slider_c->setMinimum(1);
        slider_c->setMaximum(359);
        slider_c->setTracking(false);
        slider_c->setOrientation(Qt::Horizontal);
        percent_c = new QLabel(Color);
        percent_c->setObjectName(QString::fromUtf8("percent_c"));
        percent_c->setGeometry(QRect(370, 30, 31, 20));
        Saturation = new QGroupBox(centralWidget);
        Saturation->setObjectName(QString::fromUtf8("Saturation"));
        Saturation->setGeometry(QRect(10, 300, 402, 61));
        slider_s = new QSlider(Saturation);
        slider_s->setObjectName(QString::fromUtf8("slider_s"));
        slider_s->setGeometry(QRect(16, 30, 351, 20));
        slider_s->setCursor(QCursor(Qt::ClosedHandCursor));
        slider_s->setMinimum(1);
        slider_s->setMaximum(100);
        slider_s->setTracking(false);
        slider_s->setOrientation(Qt::Horizontal);
        percent_s = new QLabel(Saturation);
        percent_s->setObjectName(QString::fromUtf8("percent_s"));
        percent_s->setGeometry(QRect(370, 30, 31, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 420, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Yeelight Bulb Toggle", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272", nullptr));
        comboBox->setCurrentText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\265\320\272\321\202", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\320\262\321\213\320\272\320\273", nullptr));
        Brightness->setTitle(QCoreApplication::translate("MainWindow", "\320\257\321\200\320\272\320\276\321\201\321\202\321\214", nullptr));
        percent_b->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        Color->setTitle(QCoreApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", nullptr));
        percent_c->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        Saturation->setTitle(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\213\321\211\320\265\320\275\320\275\320\276\321\201\321\202\321\214", nullptr));
        percent_s->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
