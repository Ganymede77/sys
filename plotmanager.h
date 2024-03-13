#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QMainWindow>
#include <QListView>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QMenuBar>

#include <QAction>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QFile>
#include <QDir>
#include <QMap>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QFileDialog>
#include <ghc/filesystem.hpp>

#include "qcustomplot.h"
#include "mhs/mhsets.h"
#include "mhs/problemsets.h"
#include "lofauxiliar.h"

namespace fs = ghc::filesystem;

class PlotManager : public QMainWindow
{
    Q_OBJECT
public:
    PlotManager(QMap<int, ProblemSets> probs, QMap<int, MhSets> mhs, QString saveLoc, QString version, QMap<QString, QVariant> lofMhSettingsFather, QWidget *parent = nullptr);
    QMap<int, ProblemSets> probsList;
    QMap<int, MhSets> mhsList;
    std::vector<MhSets> selectedMhs;
    QMap<QString, QVariant> lofMhSettings;
    void LoadDataVariables(QString filename, QStringList &header, QVector<QStringList> &vqsl, QMap<int, std::string> &vars, QVector<QString> &mhData, std::vector<ProblemSets> &selectedProbs, std::vector<int> &probPositions, std::vector<QString> &selMhs, std::vector<int> &mhPositions);

private slots:
    void PreparePlot();
    void SaveAsJpeg();
    void SaveAsPng();
    void SaveAsBmp();
    void SaveAsDat();
    void OpenExplorer();
    void TitleDoubleClick(QMouseEvent* event);
    void AxisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void LegendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void SelectionChanged();
    void MousePress(QMouseEvent* event);
    void MouseMove(QMouseEvent *event);
    void MouseRelease(QMouseEvent *event);
    void LoadDataTable(QString filename);
    void LoadDataVariablesSelectedInGUI(QString filename, QStringList &header, QVector<QStringList> &vqsl, QMap<int, std::string> &vars, QVector<QString> &mhData);
    void BeforeReplot();
    void ChangeProbMhSelection(int sel);
    void ChangeButtonColor(QColor c);
    void SuggestChartType();
    void GrapherDataTabChange(int);
    void ProblemMHListChange();
    void FileListChange();

private:
    void AddGraph(QMap<QString, QVariant> opts, QVector<double> x, QVector<double> y, QPen pen, QString curveName);
    void DiscoverVariablesColumnsInDAT(fs::ifstream &fi, std::vector<int> &columns, QMap<int, std::string> vars);
    qreal FindMedian(QVector<double> vals);
    void ProblemMHList(std::vector<ProblemSets> &selectedProbs, std::vector<int> &probPositions, std::vector<QString> &selMhs, std::vector<int> &mhPositions);
    void PlotInitialConfiguration();
    void PlotOtherStats(QMap<QString, QVariant> opts);
    void PlotConvergence(QMap<QString, QVariant> opts);
    void PlotMultiobjective(QMap<QString, QVariant> opts);

    // Legend
    bool draggingLegend;
    QPointF dragLegendOrigin;

    void AxisConfiguration(std::string xGraphType, std::string xLabel, std::string yGraphType, std::string yLabel);
    QSharedPointer<QCPAxisTickerText> *textTicker;

private:
    QString saveLocation;
    QString version;

    QCPTextElement *title;
    QComboBox *chartType;
    QComboBox *xAxisScale;
    QComboBox *yAxisScale;
    QTreeWidget *probList;
    QTreeWidget *mhList;

    QMenuBar *menuBar;
    QAction *actJpeg;
    QAction *actBmp;
    QAction *actPng;
    QAction *actDat;
    QAction *actExplorer;

    QTabWidget *tabBarGrapherData;
    QCustomPlot *chart;               // Line Chart e Scatter Chart
    QCPStatisticalBox *chartBoxPlot;  // Box Plot
    QGroupBox *graphExplorer_box;
    QTableViewClipboard *table;
    QGroupBox *datatableExplorer_box;
    QTreeWidget *fileList;

    //color selection of graph
    QPushButton *btn_color;

    //convergence
    QStackedWidget *convergenceStack;
    QComboBox *convergenceType;
    QRadioButton *minimumConvergenceData;
    QRadioButton *maximumConvergenceData;

    //others
    QRadioButton *maximumData;
    QRadioButton *minimumData;
    QRadioButton *minimumByRunData;
    QRadioButton *minimumByRunOrderedData;
    QRadioButton *medianData;
    QRadioButton *meanData;
    QRadioButton *varianceData;
    QRadioButton *standardDeviationData;
    QCheckBox *capData;

    //multiobjective
    QComboBox *xAxisData;
    QComboBox *yAxisData;
    QPushButton *multiobjectiveDataTable;
    QCheckBox *xNormalize;
    QCheckBox *yNormalize;
};

#endif // PLOTMANAGER_H
