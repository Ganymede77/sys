#ifndef LOFTABLE_H
#define LOFTABLE_H

#include <QStandardItemModel>
#include <QMainWindow>
#include "mhs/mhsets.h"
#include "mhs/problemsets.h"

class LOFTable : public QMainWindow
{
    Q_OBJECT
public:
    LOFTable(QMap<int, ProblemSets> probs, QMap<int, MhSets> mhs, QString saveLoc, QString version, QWidget *parent = nullptr);
    QMap<int, ProblemSets> probsList;
    QMap<int, MhSets> mhsList;
    std::vector<MhSets> selectedMhs;


    QStandardItemModel *model;
    explicit LOFTable(QWidget *parent = nullptr);
    void load(std::string fname);
public slots:
    void save(std::string fname);
private:
    QString saveLocation;
};

#endif // LOFTABLE_H
