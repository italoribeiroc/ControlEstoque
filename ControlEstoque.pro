QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    fm_editarprodutovenda.cpp \
    fm_gestaocolaboradores.cpp \
    fm_gestaoestoque.cpp \
    fm_gestaovendas.cpp \
    fm_log.cpp \
    fm_novavenda.cpp \
    funcoes_globais.cpp \
    main.cpp \
    fm_principal.cpp

HEADERS += \
    Conexao.h \
    fm_editarprodutovenda.h \
    fm_gestaocolaboradores.h \
    fm_gestaoestoque.h \
    fm_gestaovendas.h \
    fm_log.h \
    fm_novavenda.h \
    fm_principal.h \
    funcoes_globais.h \
    variaveis_globais.h

FORMS += \
    fm_editarprodutovenda.ui \
    fm_gestaocolaboradores.ui \
    fm_gestaoestoque.ui \
    fm_gestaovendas.ui \
    fm_log.ui \
    fm_novavenda.ui \
    fm_principal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Arquivo_de_recursos.qrc
