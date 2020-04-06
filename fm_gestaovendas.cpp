#include "fm_gestaovendas.h"
#include "ui_fm_gestaovendas.h"
#include <QtSql>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QDesktopServices>

fm_gestaoVendas::fm_gestaoVendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoVendas)
{
    ui->setupUi(this);

    ui->tw_listaProdutosVendas->horizontalHeader()->setVisible(true);
    ui->tw_listaProdutosVendas->setColumnCount(5);
    QStringList cabe1={"Mov.","Produto","Qtde","Valor U.","Valor T."};
    ui->tw_listaProdutosVendas->setHorizontalHeaderLabels(cabe1);
    ui->tw_listaProdutosVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listaProdutosVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_listaProdutosVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaProdutosVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tw_listaVendas->horizontalHeader()->setVisible(true);
    ui->tw_listaVendas->setColumnCount(6);
    QStringList cabe2={"ID","Data","Hora","Colab.","V.Total","T.Pgto"};
    ui->tw_listaVendas->setHorizontalHeaderLabels(cabe2);
    ui->tw_listaVendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tw_listaVendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_listaVendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaVendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

    con.abrir();
    int contlinhas=0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas");
    query.exec();
    query.first();
    do{
        ui->tw_listaVendas->insertRow(contlinhas);
        ui->tw_listaVendas->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_listaVendas->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_listaVendas->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_listaVendas->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_listaVendas->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_listaVendas->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
        contlinhas++;
    }while (query.next());
    con.fechar();
}

fm_gestaoVendas::~fm_gestaoVendas()
{
    delete ui;
}

void fm_gestaoVendas::on_tw_listaVendas_itemSelectionChanged()
{
    //ui->tw_listaVendas->clear();
    ui->tw_listaProdutosVendas->setRowCount(0);
    con.abrir();
    int contlinhas=0;
    QSqlQuery query;
    query.prepare("select id_movimentacao,produto,qtde,valor_un,valor_total from tb_produtosVendas where id_venda="+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text());
    if(!query.exec()){
        qDebug() << "ERRO" << query.lastError().text();
    }
    query.first();
    do{
        ui->tw_listaProdutosVendas->insertRow(contlinhas);
        ui->tw_listaProdutosVendas->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_listaProdutosVendas->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_listaProdutosVendas->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_listaProdutosVendas->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_listaProdutosVendas->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
        contlinhas++;
    }while (query.next());
    con.fechar();

}

void fm_gestaoVendas::on_btn_filtrar_clicked()
{
    ui->tw_listaVendas->setRowCount(0);
    con.abrir();
    int contlinhas=0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas where data_venda between '"+ui->de_dataini->text()+"' and '"+ui->de_datafim->text()+"'");
    query.exec();
    query.first();
    do{
        ui->tw_listaVendas->insertRow(contlinhas);
        ui->tw_listaVendas->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_listaVendas->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_listaVendas->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_listaVendas->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_listaVendas->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
        ui->tw_listaVendas->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));
        contlinhas++;
    }while (query.next());
    con.fechar();
}

void fm_gestaoVendas::on_btn_relatorioPDF_clicked()
{
    QString nome=QDir::currentPath()+"/"+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text()+"_vendas.pdf";

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome);

    QPainter painter;
    if(!painter.begin(&printer)){
        qDebug()<<"ERRO ao abrir PDF";
        return;
    }

    int linha=350;
    int salto=20;

    painter.drawPixmap(25,25,QPixmap(":/imagens/cadeado/lojaItalo.png"));

    painter.drawText(25,300,"ID:"+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),0)->text());
    painter.drawText(150,300,"Data:"+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),1)->text());
    painter.drawText(400,300,"Colab.:"+ui->tw_listaVendas->item(ui->tw_listaVendas->currentRow(),3)->text());

    for(int i=0;i<ui->tw_listaProdutosVendas->rowCount();i++){
        painter.drawText(25,linha,ui->tw_listaProdutosVendas->item(i,0)->text());
        painter.drawText(50,linha,ui->tw_listaProdutosVendas->item(i,1)->text());
        painter.drawText(300,linha,"Qtde. "+ui->tw_listaProdutosVendas->item(i,2)->text());
        linha+=salto;
    }

    printer.newPage();

    painter.drawText(25,25,"Loja Teste");

    painter.end();

    QDesktopServices::openUrl(QUrl("file:///"+nome));
}
