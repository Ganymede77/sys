#include <fstream>
#include <QFile>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include "loftable.h"

LOFTable::LOFTable(QMap<int, ProblemSets> probs, QMap<int, MhSets> mhs, QString saveLoc, QString version, QWidget *parent) : QMainWindow(parent)
{
    move(parent->geometry().topLeft());
    saveLocation = saveLoc;
    //chart = new QCustomPlot();
    setWindowTitle("LOF System Plot Manager - "+version);

    probsList = probs;
    mhsList = mhs;
#if 0
    //====================================
    // MENU
    //====================================
    //QAction *actJpeg = new QAction("..as JPEG");
    //connect(actJpeg, SIGNAL(triggered()), this, SLOT(SaveAsJpeg()));
    QMenuBar *menuBar = new QMenuBar();
    QMenu *mn_export = new QMenu("Export");
    menuBar->addMenu(mn_export);
    mn_export->addAction(actJpeg);
    mn_export->addAction(actBmp);
    mn_export->addAction(actPng);
    setMenuBar(menuBar);

    //====================================
    // PROBLEMS LIST
    //====================================
    probList = new QTreeWidget();
    probList->setHeaderHidden(true);
    probList->setMinimumWidth(200);
    probList->setMaximumWidth(200);
    for(auto i=0; i<probsList.size(); ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, QString::fromStdString(probsList.value(i).GetFunctionSelected()) + " - " + QString::number(i));
        item->setData(0, Qt::UserRole, i);
        item->setData(1, Qt::UserRole, -1);
        if(probsL[i].GetMultiObjProblem()) {
            for(int j=0; j<probsList[i].GetMultiObjProblemSet().size(); ++j) {
                QTreeWidgetItem *itemMJ = new QTreeWidgetItem();
                itemMJ->setText(0, QString::fromStdString(probsL[i].GetMultiObjProblemSet()[j].GetMultiObjName()));
                itemMJ->setData(0, Qt::UserRole, i);
                itemMJ->setData(1, Qt::UserRole, j);
                item->addChild(itemMJ);
            }
        }
        probList->addTopLevelItem(item);
    }
    probList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    probList->setSelectionMode(QAbstractItemView::MultiSelection);

    //====================================
    // METAHEURISTICS LIST
    //====================================
    mhList = new QListView();
    mhList->setMinimumWidth(200);
    mhList->setMaximumWidth(200);
    QStandardItemModel *mhList_model = new QStandardItemModel();
    for(int i = 0; i < mhsList.size(); ++i) {
        QStandardItem *item = new QStandardItem(mhsList.value(i).GetMhSelected() + " - " + QString::number(i));
        mhList_model->appendRow(item);
    }
    mhList->setModel(mhList_model);
    mhList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mhList->setSelectionMode(QAbstractItemView::MultiSelection);

    QGroupBox *probMh_box = new QGroupBox("Problem-Metaheuristic Selection");
    QGridLayout *probMh_layout = new QGridLayout();
    probMh_layout->addWidget(probList, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    probMh_layout->addWidget(mhList, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    probMh_box->setLayout(probMh_layout);

    //====================================
    // VIEW SELECTION GROUP
    //====================================
    convergenceType = new QComboBox();
    convergenceType->setMinimumWidth(200);
    convergenceType->setMaximumWidth(200);
    convergenceType->addItem("Other Statistical Views");
    convergenceType->addItem("Convergence View");
    convergenceType->addItem("Multiobjective Explorer");

    //====================================
    // 1 - STATISTICAL VIEW
    //====================================
    maximumData = new QRadioButton("Maximum");
    maximumData->setToolTip("Displays the maximum found value for each iteration");
    minimumData = new QRadioButton("Minimum");
    minimumData->setToolTip("Displays the minimum found value for each iteration");
    minimumData->setChecked(true);
    minimumByRunData = new QRadioButton("Minimum by run");
    minimumByRunData->setToolTip("Displays the minimum found value for each run");
    minimumByRunOrderedData = new QRadioButton("Minimum by run (ordered)");
    minimumByRunOrderedData->setToolTip("Displays the minimum found value for each run, ordered from lesser to greater value");
    minimumConvergenceData = new QRadioButton("Convergence for each test");
    minimumConvergenceData->setToolTip("Displays the minimum found value for each iteration of each test");
    minimumConvergenceData->setChecked(true);
    maximumConvergenceData = new QRadioButton("Maximum Convergence");
    maximumConvergenceData->setToolTip("Displays the maximum found value for each iteration of each test");
    maximumConvergenceData->setHidden(true);
    medianData = new QRadioButton("Median");
    medianData->setToolTip("Displays the median value for each iteration");
    meanData = new QRadioButton("Mean");
    meanData->setToolTip("Displays the mean value for each iteration");
    varianceData = new QRadioButton("Variance");
    varianceData->setToolTip("Displays the variance of found values for each iteration");
    standardDeviationData = new QRadioButton("Standard Deviation");
    standardDeviationData->setToolTip("Displays the standard deviation of the found values for each iteration");
    QGroupBox *data_box = new QGroupBox("Data Selection");
    data_box->setMinimumWidth(200);
    data_box->setMaximumWidth(200);
    QGridLayout *data_layout = new QGridLayout();
    data_layout->addWidget(maximumData, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(minimumData, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(minimumByRunData, 2, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(minimumByRunOrderedData, 3, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(meanData, 4, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(medianData, 5, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(varianceData, 6, 0, Qt::AlignLeft | Qt::AlignTop);
    data_layout->addWidget(standardDeviationData, 7, 0, Qt::AlignLeft | Qt::AlignTop);
    data_box->setLayout(data_layout);

    //====================================
    // 2 - CONVERGENCE VIEW
    //====================================
    QGroupBox *convergence_box = new QGroupBox("Data Selection");
    QGridLayout *convergence_layout = new QGridLayout();
    convergence_layout->addWidget(minimumConvergenceData, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    convergence_layout->addWidget(maximumConvergenceData, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    convergence_box->setLayout(convergence_layout);

    //====================================
    // 3 - MULTIOBJECTIVE VIEW
    //====================================
    QGroupBox *metaheuristic_box = new QGroupBox("Axis Data Selection");
    QGridLayout *metaheuristic_layout = new QGridLayout();
    QLabel *lxAxisData = new QLabel;
    lxAxisData->setText("x-Axis Selection");
    QLabel *lyAxisData = new QLabel;
    lyAxisData->setText("y-Axis Selection");
    xAxisData = new QComboBox;
    yAxisData = new QComboBox;

    if(1) {
        std::string mhline;
        namespace fs = ghc::filesystem;
        fs::ifstream in(saveLocation.toStdString()+"/multiobjective.dat");
        getline(in, mhline);
        in.close();
        std::istringstream iss(mhline);
        std::vector<std::string> mhheader((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        for(unsigned long ii=0; ii<mhheader.size(); ii++) {
            xAxisData->addItem(QString::fromStdString(mhheader[ii]));
            yAxisData->addItem(QString::fromStdString(mhheader[ii]));
        }
    }

    xAxisData->setMaximumWidth(175);
    xAxisData->setMinimumWidth(175);
    yAxisData->setMaximumWidth(175);
    yAxisData->setMinimumWidth(175);
    multiobjectiveDataTable = new QPushButton("Data Table");
    multiobjectiveDataTable->setMaximumWidth(175);
    multiobjectiveDataTable->setMinimumWidth(175);
    metaheuristic_layout->addWidget(lxAxisData, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    metaheuristic_layout->addWidget(xAxisData, 1, 0, Qt::AlignHCenter | Qt::AlignTop);
    metaheuristic_layout->addWidget(lyAxisData, 2, 0, Qt::AlignLeft | Qt::AlignTop);
    metaheuristic_layout->addWidget(yAxisData, 3, 0, Qt::AlignHCenter | Qt::AlignTop);
    QSpacerItem *spmet = new QSpacerItem(0, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    metaheuristic_layout->addItem(spmet, 4, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    metaheuristic_layout->addWidget(new QLabel(""), 5, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_layout->addWidget(new QLabel(""), 6, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_layout->addWidget(new QLabel(""), 7, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_layout->addWidget(new QLabel(""), 8, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_layout->addWidget(multiobjectiveDataTable, 9, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_box->setLayout(metaheuristic_layout);
    connect(multiobjectiveDataTable, SIGNAL(clicked(bool)), this, SLOT(MultiobjectiveDataTable()));

    convergenceStack = new QStackedWidget();
    convergenceStack->addWidget(data_box);
    convergenceStack->addWidget(convergence_box);
    convergenceStack->addWidget(metaheuristic_box);
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), convergenceStack, SLOT(setCurrentIndex(int)));
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeProbMhSelection(int)));
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), this, SLOT(SuggestChartType()));
    convergenceType->setCurrentText("Other Statistical Views");

    QGroupBox *dataType_box = new QGroupBox("View Selection");
    QGridLayout *dataType_lay = new QGridLayout();
    dataType_lay->addWidget(convergenceType,0,0,Qt::AlignLeft | Qt::AlignTop);
    dataType_lay->addWidget(convergenceStack,0,1,Qt::AlignRight | Qt::AlignTop);
    dataType_box->setLayout(dataType_lay);

    //====================================
    // CHART SETTINGS
    //====================================
    chartType = new QComboBox();
    chartType->addItem("Line Chart");
    chartType->addItem("Box Plot");
    chartType->addItem("Scatter Chart");
    xAxisScale = new QComboBox();
    xAxisScale->addItem("Linear");
    xAxisScale->addItem("Logarithmic");
    yAxisScale = new QComboBox();
    yAxisScale->addItem("Linear");
    yAxisScale->addItem("Logarithmic");
    yAxisScale->setCurrentIndex(1);
    capData = new QCheckBox("Cap X axis data to the lesser sample");

    QGroupBox *chartSpecs_box = new QGroupBox("Chart Settings");
    QGridLayout *chartSpecs_lay = new QGridLayout();
    QLabel *lbl_xchart = new QLabel("X Axis Scale");
    QLabel *lbl_ychart = new QLabel("Y Axis Scale");
    QLabel *lbl_chartType = new QLabel("Chart Type");
    chartSpecs_lay->addWidget(lbl_chartType, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(chartType, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(lbl_xchart, 1, 0, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(xAxisScale, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(lbl_ychart, 2, 0, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(yAxisScale, 2, 1, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_lay->addWidget(capData, 3, 0, 1, 2, Qt::AlignLeft | Qt::AlignTop);
    chartSpecs_box->setLayout(chartSpecs_lay);

    //====================================
    // CREATE CHART BUTTON
    //====================================
    QPushButton *btn_plot = new QPushButton("Create Charts");
    connect(btn_plot, SIGNAL(clicked()), this, SLOT(PreparePlot()));

    QGridLayout *selection_layout = new QGridLayout();
    selection_layout->addWidget(probMh_box, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    QGridLayout *viewdata_layout = new QGridLayout();
    viewdata_layout->addWidget(dataType_box, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    //viewdata_layout->addWidget(convergenceStack, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    selection_layout->addLayout(viewdata_layout,1,0);
    selection_layout->addWidget(chartSpecs_box, 2, 0, Qt::AlignLeft | Qt::AlignTop);
    selection_layout->addWidget(btn_plot, 3, 0);
    selection_layout->setRowStretch(5, 10);
    selection_layout->setRowStretch(4, 10);

    QGridLayout *main_layout = new QGridLayout();
    main_layout->addLayout(selection_layout, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    main_layout->addWidget(chart, 0, 1);
    main_layout->setColumnStretch(1, 10);
    QWidget *dummy_central_widget = new QWidget();
    dummy_central_widget->setMinimumWidth(1200);
    dummy_central_widget->setLayout(main_layout);
    setCentralWidget(dummy_central_widget);
#endif
}

LOFTable::LOFTable(QWidget *parent)
{
#if 0
    model = new QStandardItemModel();
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    setModel(proxyModel);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);
#endif
}

void LOFTable::load(std::string fname)
{
    QFile file(QString::fromStdString(fname));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "LOF System", "Error: could not open "+QString::fromStdString(fname));
        return;
    }
    std::vector<QStringList> vec;
    QTextStream in(&file);
    QString line;
    QStringList lstLine;
    while(true) {
        lstLine = in.readLine().split(QRegExp("(\t| )"));
        vec.push_back(lstLine);
        if(in.atEnd())
            break;
    }
    file.close();
    model->setRowCount(vec.size()-1);
    model->setColumnCount(vec[0].size());
    model->setHorizontalHeaderLabels(vec[0]);
    for (unsigned int i=1; i<vec.size(); ++i)
        for (unsigned int j=0; j<vec[0].size(); j++) {
            QModelIndex index = model->index(i-1,j,QModelIndex());
            model->setData(index,vec[i][j].toDouble());
        }
}

void LOFTable::save(std::string fname)
{
    QFile file(QString::fromStdString(fname));
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, "LOF System", "Error: could not open "+QString::fromStdString(fname));
        return;
    }
    QTextStream out(&file);

    out << model->headerData(0, Qt::Horizontal).toString();
    for (unsigned int j=1; j<model->columnCount(); j++)
        out << "\t" << model->headerData(j, Qt::Horizontal).toString();
    for (unsigned int i=0; i<model->rowCount(); ++i) {
        out << "\n" << model->index(i,0).data().toString();
        for (unsigned int j=1; j<model->columnCount(); j++)
            out << "\t" << model->index(i,j).data().toString();
    }
}
