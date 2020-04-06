#ifndef FM_GESTAOVENDAS_H
#define FM_GESTAOVENDAS_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_gestaoVendas;
}

class fm_gestaoVendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoVendas(QWidget *parent = nullptr);
    ~fm_gestaoVendas();
    Conexao con;

private slots:
    void on_tw_listaVendas_itemSelectionChanged();

    void on_btn_filtrar_clicked();

    void on_btn_relatorioPDF_clicked();

private:
    Ui::fm_gestaoVendas *ui;
};

#endif // FM_GESTAOVENDAS_H
