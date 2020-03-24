/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind_Replace;
    QAction *actionBuild;
    QAction *actionRun;
    QAction *actionCode_Analysis;
    QAction *actionError_Message;
    QAction *actionWarning_Messages;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *upperLayout;
    QTreeWidget *treeWidget;
    QTextEdit *textEdit;
    QHBoxLayout *bottomLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuBuild;
    QMenu *menuTools;
    QMenu *menuWindow;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(984, 740);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/snowflake.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionFind_Replace = new QAction(MainWindow);
        actionFind_Replace->setObjectName(QStringLiteral("actionFind_Replace"));
        actionBuild = new QAction(MainWindow);
        actionBuild->setObjectName(QStringLiteral("actionBuild"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionCode_Analysis = new QAction(MainWindow);
        actionCode_Analysis->setObjectName(QStringLiteral("actionCode_Analysis"));
        actionError_Message = new QAction(MainWindow);
        actionError_Message->setObjectName(QStringLiteral("actionError_Message"));
        actionWarning_Messages = new QAction(MainWindow);
        actionWarning_Messages->setObjectName(QStringLiteral("actionWarning_Messages"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        upperLayout = new QHBoxLayout();
        upperLayout->setObjectName(QStringLiteral("upperLayout"));
        treeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMinimumSize(QSize(230, 557));
        treeWidget->setBaseSize(QSize(0, 0));
        treeWidget->setRootIsDecorated(false);
        treeWidget->setHeaderHidden(true);

        upperLayout->addWidget(treeWidget);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        upperLayout->addWidget(textEdit);


        verticalLayout->addLayout(upperLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName(QStringLiteral("bottomLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/play.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(42, 42));
        pushButton->setFlat(true);

        verticalLayout_2->addWidget(pushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        bottomLayout->addLayout(verticalLayout_2);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        bottomLayout->addWidget(tabWidget);


        verticalLayout->addLayout(bottomLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 984, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuBuild = new QMenu(menubar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuWindow = new QMenu(menubar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuBuild->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuWindow->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionFind_Replace);
        menuBuild->addAction(actionBuild);
        menuBuild->addAction(actionRun);
        menuTools->addAction(actionCode_Analysis);
        menuWindow->addAction(actionError_Message);
        menuWindow->addAction(actionWarning_Messages);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "[WIDE] Winter IDE", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "New", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", nullptr));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", nullptr));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", nullptr));
        actionFind_Replace->setText(QApplication::translate("MainWindow", "Find/Replace", nullptr));
        actionBuild->setText(QApplication::translate("MainWindow", "Build", nullptr));
        actionRun->setText(QApplication::translate("MainWindow", "Run", nullptr));
        actionCode_Analysis->setText(QApplication::translate("MainWindow", "Code Analysis", nullptr));
        actionError_Message->setText(QApplication::translate("MainWindow", "Error Messages", nullptr));
        actionWarning_Messages->setText(QApplication::translate("MainWindow", "Warning Messages", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Name", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Root", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "custom.wpl", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "main.wpl", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">/-</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">-</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">@</span><span style=\" font-family:'Consolas'; fo"
                        "nt-size:8pt; color:#24292e;\">authors</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">-</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> Israel Efraim de Oliveira</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">-</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> Jos\303\251 Carlos Zancanaro</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span sty"
                        "le=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">-/</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">\302\240</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">def</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#6f42c1;\">main</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">() -&gt; Integer {</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; m"
                        "argin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 Float magro = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">18.5</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">, normal = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">25.0</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">, gordinho = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">30.0</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">; </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 Float altura = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">1.75</span><span style=\" font-family:'Co"
                        "nsolas'; font-size:8pt; color:#24292e;\">, peso = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">72.1</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 Float imc = peso </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">/</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> altura </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">**</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">2</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-"
                        "family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 String mensagem;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 choose </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">from</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> {</sp"
                        "an><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">\302\240 \302\240\302\240|&gt;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> imc </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">&lt;=</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> magro -&gt; mensagem = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;Abaixo do peso.&quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:"
                        "#d73a49;\">\302\240 \302\240\302\240|&gt;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> imc </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">&lt;=</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> normal -&gt; mensagem = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;Est\303\241 normal.&quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">\302\240 \302\240\302\240|&gt;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> imc </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">&lt;=</span><span style=\" font-family:'Consolas'; font-s"
                        "ize:8pt; color:#24292e;\"> gordinho -&gt; mensagem = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;Acima do peso.&quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#d73a49;\">\302\240 \302\240\302\240|&gt;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> otherwise -&gt; mensagem = </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;Alien!&quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-inden"
                        "t:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240 }</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">\302\240 print</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">(</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;IMC: &quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">, imc);</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\""
                        " margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">\302\240 print</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">(</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#032f62;\">&quot;Classifica\303\247\303\243o: &quot;</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">, mensagem);</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">\302\240</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-si"
                        "ze:8pt; color:#d73a49;\">\302\240 return</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\"> </span><span style=\" font-family:'Consolas'; font-size:8pt; color:#005cc5;\">0</span><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">;</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Consolas'; font-size:8pt; color:#24292e;\">}</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> </span></p></body></html>", nullptr));
        pushButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Errors", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Warnings", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Build", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
