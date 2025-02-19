QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/AppControl.cpp \
    Model/IO/FileHandler.cpp \
    Model/Parser/Analysers/Constants.cpp \
    Model/Parser/Analysers/Lexical.cpp \
    Model/Parser/Analysers/OperatorDefinitions.cpp \
    Model/Parser/Analysers/Semantic.cpp \
    Model/Parser/Analysers/Syntactic.cpp \
    Model/Parser/Analysers/TypeDefinitions.cpp \
    Model/Parser/Parser.cpp \
    View/AssemblerWindow.cpp \
    View/CodeEditor/BIP_ASM_SyntaxHighlighter.cpp \
    View/CodeEditor/CodeEditor.cpp \
    View/AnalysisWindow.cpp \
    View/CodeEditor/Line_Number_Area.cpp \
    View/CodeEditor/WPLSyntaxHighlighter.cpp \
    View/MainWindow.cpp \
    View/NameTableWindow.cpp \
    main.cpp

HEADERS += \
    Control/AppControl.hpp \
    Model/Composite.hpp \
    Model/IO/FileHandler.hpp \
    Model/Parser/Analysers/ActionDefinitions.hpp \
    Model/Parser/Analysers/AnalysisError.hpp \
    Model/Parser/Analysers/Constants.hpp \
    Model/Parser/Analysers/Lexical.hpp \
    Model/Parser/Analysers/LexicalError.hpp \
    Model/Parser/Analysers/LoggerBase.hpp \
    Model/Parser/Analysers/OperatorDefinitions.hpp \
    Model/Parser/Analysers/SemanticTable.hpp \
    Model/Parser/Analysers/Semantic.hpp \
    Model/Parser/Analysers/SemanticError.hpp \
    Model/Parser/Analysers/SemanticTable_impl.hpp \
    Model/Parser/Analysers/Symbols.hpp \
    Model/Parser/Analysers/Syntactic.hpp \
    Model/Parser/Analysers/SyntaticError.hpp \
    Model/Parser/Analysers/Token.hpp \
    Model/Parser/Analysers/TypeDefinitions.hpp \
    Model/Parser/Asm/BipDefinitions.hpp \
    Model/Parser/Parser.hpp \
    View/AssemblerWindow.hpp \
    View/CodeEditor/BIP_ASM_SyntaxHighlighter.hpp \
    View/CodeEditor/CodeEditor.hpp \
    View/AnalysisWindow.hpp \
    View/CodeEditor/Line_Number_Area.hpp \
    View/CodeEditor/WPLSyntaxHighlighter.hpp \
    View/MainWindow.hpp \
    View/NameTableWindow.hpp

FORMS += \
    View/AnalysisWindow.ui \
    View/AssemblerWindow.ui \
    View/MainWindow.ui \
    View/NameTableWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    View/resources/main.qrc
