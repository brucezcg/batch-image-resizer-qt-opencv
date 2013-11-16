#include "outputdirdialog.h"
#include "ui_outputdirdialog.h"
#include <QSettings>
#include <QDebug>
#include "mainwindow.h"
OutputDirDialog::OutputDirDialog(QWidget *parent) :
    QDialog(parent),
    model(new QFileSystemModel),
    ui(new Ui::OutputDirDialog)
{
    ui->setupUi(this);
    model->setRootPath("");
    model->setFilter(QDir::AllDirs);
    ui->dirSelector->setModel(model);
    qDebug()<<parent;
    connect(ui->dirSelector, SIGNAL(clicked( QModelIndex )), this, SLOT(didSelectFolder(QModelIndex)))
            ;
    connect(ui->buttonApply, SIGNAL(clicked()), this, SLOT(buttonApplyPressed()));
    this->updateUI();

}

OutputDirDialog::~OutputDirDialog()
{
    delete ui;
    delete model;
}

void OutputDirDialog::didSelectFolder(QModelIndex index){
    QFileSystemModel *fileModel = (QFileSystemModel*) ui->dirSelector->model();
    selectedPath = fileModel->filePath(index);
    updateUI();
}

void OutputDirDialog::buttonApplyPressed(){
    MainWindow* main = (MainWindow*)this->parentWidget();
    QSettings* settings = main->settings;
    settings->setValue("output_dir",selectedPath);
    main->updateUI();
    qDebug() << QString("output dir set to ")<<settings->value("output_dir").value<QString>();
}

void OutputDirDialog::updateUI(){
    if(QFileInfo(selectedPath).isDir()){
        ui->buttonApply->setEnabled(true);
    }

    else{
        ui->buttonApply->setEnabled(false);
    }
}
