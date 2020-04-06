#ifndef FM_GESTAOCOLABORADORES_H
#define FM_GESTAOCOLABORADORES_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_gestaoColaboradores;
}

class fm_gestaoColaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoColaboradores(QWidget *parent = nullptr);
    ~fm_gestaoColaboradores();
    Conexao con;

private slots:
    void on_btn_novo_novocolab_clicked();

    void on_btn_gravar_novocolab_clicked();

    void on_btn_cancelar_novocolab_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_listacolab_itemSelectionChanged();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::fm_gestaoColaboradores *ui;
};

#endif // FM_GESTAOCOLABORADORES_H
