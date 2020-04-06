#include "fm_log.h"
#include "ui_fm_log.h"
#include <QMessageBox>
#include "fm_principal.h"
#include "variaveis_globais.h"

fm_log::fm_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_log)
{
    ui->setupUi(this);
    logado=false;
}

fm_log::~fm_log()
{
    delete ui;
}

void fm_log::on_btn_logar_clicked()
{
    if(!con.abrir()){
        QMessageBox::warning(this,"ERRO","Erro ao abrir o banco de dados");
    }else{
        QString username, senha;
        username=ui->txt_username->text();
        senha=ui->txt_senha->text();
        QSqlQuery query;
        query.prepare("select * from tb_colaboradores where username_colab='"+username+"' and senha_colab='"+senha+"'");
        if(query.exec()){
            query.first();
            if(query.value(1).toString()!=""){
                variaveis_globais::logado=true;
                variaveis_globais::nome_colab=query.value(1).toString();
                variaveis_globais::id_colab=query.value(0).toInt();
                variaveis_globais::acesso_colab=query.value(5).toString();
                con.fechar();
                close();
            }else{
                QMessageBox::warning(this,"ERRO","Colaborador não encontrado");
            }
        }else{
            QMessageBox::warning(this,"ERRO","Falha no login");
        }
    }
    //Login
    con.fechar();
}

void fm_log::on_btn_cancelar_clicked()
{
    logado=false;
    close();
}
