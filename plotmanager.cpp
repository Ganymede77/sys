#include <iostream>
#include <limits>
#include <QSortFilterProxyModel>
#include <sstream>
#include "loftable.h"
#include "plotmanager.h"

PlotManager::PlotManager(QMap<int, ProblemSets> probsL, QMap<int, MhSets> mhsL, QString saveLoc, QString versionFather, QMap<QString, QVariant> lofMhSettingsFather, QWidget *parent) : QMainWindow(parent)
{
    move(parent->geometry().topLeft());
    saveLocation = saveLoc;
    chart = new QCustomPlot(this);
    chartBoxPlot = new QCPStatisticalBox(chart->xAxis, chart->yAxis);
    QBrush boxBrush(QColor(60, 60, 255, 100));
    boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
    chartBoxPlot->setBrush(boxBrush);

    table = new QTableViewClipboard(this);
    lofMhSettings = lofMhSettingsFather;
    setWindowTitle("LOF System Results Explorer - "+versionFather);

    probsList = probsL;
    mhsList = mhsL;
    version = versionFather;

    //====================================
    // MENU
    //====================================
    actJpeg = new QAction("..as JPEG");
    connect(actJpeg, SIGNAL(triggered()), this, SLOT(SaveAsJpeg()));
    actBmp = new QAction("..as BMP");
    connect(actBmp, SIGNAL(triggered()), this, SLOT(SaveAsBmp()));
    actPng = new QAction("..as PNG");
    connect(actPng, SIGNAL(triggered()), this, SLOT(SaveAsPng()));
    actExplorer = new QAction("...in File Manager");
    connect(actExplorer, SIGNAL(triggered()), this, SLOT(OpenExplorer()));
    actDat = new QAction("...as DAT");
    connect(actDat, SIGNAL(triggered()), this, SLOT(SaveAsDat()));
    menuBar = new QMenuBar();
    QMenu *mn_export = new QMenu("Export");
    QMenu *openDir = new QMenu("Open Results Directory");
    menuBar->addMenu(mn_export);
    mn_export->addAction(actJpeg);
    mn_export->addAction(actBmp);
    mn_export->addAction(actPng);
    mn_export->addAction(actDat);
    menuBar->addMenu(openDir);
    openDir->addAction(actExplorer);
    setMenuBar(menuBar);

    //====================================
    // PROBLEMS LIST
    //====================================
    probList = new QTreeWidget();
    probList->setHeaderHidden(true);
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
                if(probsList[i].GetMultiObjProblemSet()[j].GetMultiObjProblem() == -2 || probsList[i].GetMultiObjProblemSet()[j].GetMultiObjProblem() <= -4)
                    itemMJ->setBackgroundColor(0, QColor(204, 229, 255));
                else if(probsList[i].GetMultiObjProblemSet()[j].GetMultiObjProblem() == -3)
                    itemMJ->setBackgroundColor(0, QColor(255, 255, 204));
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
    mhList = new QTreeWidget();
    mhList->setHeaderHidden(true);
    for(int i = 0; i < mhsList.size(); ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, mhsList.value(i).GetMhSelected() + " - " + QString::number(i));
        mhList->addTopLevelItem(item);
    }
    mhList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mhList->setSelectionMode(QAbstractItemView::MultiSelection);

    QGroupBox *probMh_box = new QGroupBox("Problem-Metaheuristic Selection");
    QGridLayout *probMh_layout = new QGridLayout();
    probMh_layout->addWidget(probList, 0, 0);
    probMh_layout->addWidget(mhList, 0, 1);
    probMh_box->setLayout(probMh_layout);
    probMh_box->setMaximumWidth(430);
    probMh_box->setMinimumWidth(430);

    //====================================
    // VIEW SELECTION GROUP
    //====================================
    convergenceType = new QComboBox();
    convergenceType->setMinimumWidth(200);
    convergenceType->setMaximumWidth(200);
    convergenceType->addItem("Other Statistical Views");
    convergenceType->addItem("Convergence View");
    convergenceType->addItem("Results Variables View");

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
    QGridLayout *data_layout = new QGridLayout();
    data_layout->addWidget(maximumData, 0, 0);
    data_layout->addWidget(minimumData, 1, 0);
    data_layout->addWidget(minimumByRunData, 2, 0);
    data_layout->addWidget(minimumByRunOrderedData, 3, 0);
    data_layout->addWidget(meanData, 4, 0);
    data_layout->addWidget(medianData, 5, 0);
    data_layout->addWidget(varianceData, 6, 0);
    data_layout->addWidget(standardDeviationData, 7, 0);
    data_box->setLayout(data_layout);

    //====================================
    // 2 - CONVERGENCE VIEW
    //====================================
    QGroupBox *convergence_box = new QGroupBox("Data Selection");
    QGridLayout *convergence_layout = new QGridLayout();
    convergence_layout->addWidget(minimumConvergenceData, 0, 0, Qt::AlignTop);
    convergence_layout->addWidget(maximumConvergenceData, 1, 0, Qt::AlignTop);
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
    //xNormalize = new QCheckBox("Normalize x-Axis variables");
    //yNormalize = new QCheckBox("Normalize y-Axis variables");

    //std::string mhline;
    //namespace fs = ghc::filesystem;
    //fs::ifstream in(saveLocation.toStdString()+"/results_variables.dat");
    //getline(in, mhline);
    //in.close();
    //std::istringstream iss(mhline);
    //std::vector<std::string> mhheader((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
    //for(unsigned long ii=0; ii<mhheader.size(); ii++) {
    //    xAxisData->addItem(QString::fromStdString(mhheader[ii]));
    //    yAxisData->addItem(QString::fromStdString(mhheader[ii]));
    //}

    xAxisData->setMaximumWidth(175);
    xAxisData->setMinimumWidth(175);
    yAxisData->setMaximumWidth(175);
    yAxisData->setMinimumWidth(175);
    multiobjectiveDataTable = new QPushButton("Data Table");
    metaheuristic_layout->addWidget(lxAxisData, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    metaheuristic_layout->addWidget(xAxisData, 1, 0, Qt::AlignRight | Qt::AlignTop);
    //metaheuristic_layout->addWidget(xNormalize, 2, 0, Qt::AlignRight | Qt::AlignTop);
    metaheuristic_layout->addWidget(new QLabel(""), 3, 0, Qt::AlignHCenter | Qt::AlignBottom);
    metaheuristic_layout->addWidget(lyAxisData, 4, 0, Qt::AlignLeft | Qt::AlignTop);
    metaheuristic_layout->addWidget(yAxisData, 5, 0, Qt::AlignRight | Qt::AlignTop);
    //metaheuristic_layout->addWidget(yNormalize, 6, 0, Qt::AlignRight | Qt::AlignTop);
    metaheuristic_layout->addWidget(new QLabel(""), 7, 0, Qt::AlignHCenter | Qt::AlignBottom);
    //metaheuristic_layout->addWidget(multiobjectiveDataTable, 8, 0, Qt::AlignBottom);
    metaheuristic_box->setLayout(metaheuristic_layout);
    //connect(multiobjectiveDataTable, SIGNAL(clicked(bool)), this, SLOT(LoadDataTable()));

    convergenceStack = new QStackedWidget();
    convergenceStack->addWidget(data_box);
    convergenceStack->addWidget(convergence_box);
    convergenceStack->addWidget(metaheuristic_box);
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), convergenceStack, SLOT(setCurrentIndex(int)));
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeProbMhSelection(int)));
    connect(convergenceType, SIGNAL(currentIndexChanged(int)), this, SLOT(SuggestChartType()));
    convergenceType->setCurrentText("Other Statistical Views");
    convergenceType->setMaximumWidth(180);
    convergenceType->setMinimumWidth(180);

    QGroupBox *dataType_box = new QGroupBox("View Selection");
    QGridLayout *dataType_lay = new QGridLayout();
    dataType_lay->addWidget(convergenceType,0,0,Qt::AlignLeft | Qt::AlignTop);
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
    capData = new QCheckBox("Cap X axis data to the lesser\nsample");

    QGroupBox *chartSpecs_box = new QGroupBox("Chart Settings");
    QGridLayout *chartSpecs_lay = new QGridLayout();
    QLabel *lbl_xchart = new QLabel("X Axis Scale");
    QLabel *lbl_ychart = new QLabel("Y Axis Scale");
    QLabel *lbl_chartType = new QLabel("Chart Type");
    chartSpecs_lay->addWidget(lbl_chartType, 0, 0, Qt::AlignVCenter);
    chartSpecs_lay->addWidget(chartType, 0, 1);
    chartSpecs_lay->addWidget(lbl_xchart, 1, 0, Qt::AlignVCenter);
    chartSpecs_lay->addWidget(xAxisScale, 1, 1);
    chartSpecs_lay->addWidget(lbl_ychart, 2, 0, Qt::AlignVCenter);
    chartSpecs_lay->addWidget(yAxisScale, 2, 1);
    chartSpecs_lay->addWidget(capData, 3, 0, 1, 2, Qt::AlignTop);
    chartSpecs_box->setLayout(chartSpecs_lay);

    //====================================
    // CREATE CHART BUTTON
    //====================================
    QPushButton *btn_plot = new QPushButton("Create Chart");
    connect(btn_plot, SIGNAL(clicked()), this, SLOT(PreparePlot()));

    QGridLayout *selection_layout = new QGridLayout();
    selection_layout->addWidget(probMh_box, 0, 0);

    QGridLayout *viewdata_layout = new QGridLayout();
    viewdata_layout->addWidget(dataType_box, 0, 0, Qt::AlignTop);
    viewdata_layout->addWidget(convergenceStack,0,1);
    viewdata_layout->addWidget(chartSpecs_box, 0, 0, Qt::AlignBottom);
    viewdata_layout->addWidget(btn_plot, 2, 0, 1, 2);
    graphExplorer_box = new QGroupBox("Graph Explorer Settings");
    graphExplorer_box->setLayout(viewdata_layout);

    fileList = new QTreeWidget(this);
    fileList->setHeaderHidden(true);
    datatableExplorer_box = new QGroupBox("DataTable Explorer Settings");
    QGridLayout *fileList_layout = new QGridLayout();
    fileList_layout->addWidget(fileList, 0, 0);
    datatableExplorer_box->setVisible(false);
    datatableExplorer_box->setLayout(fileList_layout);

    selection_layout->addWidget(graphExplorer_box,1,0, Qt::AlignTop);
    selection_layout->addWidget(datatableExplorer_box,1,0, Qt::AlignTop);

    //====================================
    // GRAPH AND DATATABLES
    //====================================
    tabBarGrapherData = new QTabWidget(this);
    tabBarGrapherData->addTab(chart, "Graph Explorer");
    tabBarGrapherData->addTab(table, "DataTable Explorer");
    connect(tabBarGrapherData,SIGNAL(currentChanged(int)),this,SLOT(GrapherDataTabChange(int)));
    connect(probList,SIGNAL(itemSelectionChanged()),this,SLOT(ProblemMHListChange()));
    connect(mhList,SIGNAL(itemSelectionChanged()),this,SLOT(ProblemMHListChange()));
    connect(fileList, SIGNAL(itemSelectionChanged()), this, SLOT(FileListChange()));

    QGridLayout *main_layout = new QGridLayout();
    main_layout->addLayout(selection_layout, 0, 0);
    main_layout->addWidget(tabBarGrapherData, 0, 1);
    main_layout->setColumnStretch(1, 10);
    QWidget *dummy_central_widget = new QWidget();
    dummy_central_widget->setMinimumWidth(1200);
    dummy_central_widget->setLayout(main_layout);
    setCentralWidget(dummy_central_widget);
    PlotInitialConfiguration();
}

void PlotManager::PreparePlot()
{
    QStringList paths;
    std::vector<QString> selMhs;
    std::vector<int> probPositions, mhPositions;
    std::vector<int> alreadyInserted;
    std::vector<ProblemSets> selectedProbs;
    for(int i = 0; i < probList->selectionModel()->selectedRows().size(); ++i)
    {
        int probIndex = probList->selectedItems().at(i)->data(0,Qt::UserRole).toInt();
        int mobjIndex = probList->selectedItems().at(i)->data(1,Qt::UserRole).toInt();
        if(!probsList[probIndex].GetMultiObjProblem()) {
            selectedProbs.push_back(probsList[probIndex]);
            probPositions.push_back(probIndex);
        } else if(mobjIndex == -1) {
            alreadyInserted.push_back(probIndex);
            for(int j=0;j<probsList[probIndex].GetMultiObjProblemSet().size();j++) {
                selectedProbs.push_back(probsList[probIndex].GetMultiObjProblemSet()[j]);
                probPositions.push_back(probIndex);
            }
        } else if(std::find(alreadyInserted.begin(), alreadyInserted.end(), probIndex) == alreadyInserted.end()) {
            selectedProbs.push_back(probsList[probIndex].GetMultiObjProblemSet()[mobjIndex]);
            probPositions.push_back(probIndex);
        }
    }
    for(int i = 0; i < mhList->selectionModel()->selectedRows().size(); ++i) {
        int p = mhList->selectionModel()->selectedRows().at(i).row();
        selMhs.push_back(mhList->selectionModel()->selectedRows().at(i).data().toString());
        mhPositions.push_back(p);
    }
    if(selectedProbs.size() <= 0) {
        QMessageBox::information(this, "LOF System Plot Manager", "Please select at least one Problem to plot.");
        return;
    }
    if(selMhs.size() <= 0) {
        QMessageBox::information(this, "LOF System Plot Manager", "Please select at least one Metaheuristic to plot.");
        return;
    }
    QMap<QString, QVariant> options;
    QString projectName = lofMhSettings.value("projectName").toString();
    options.insert("projPath", projectName);

    QString index = "";
    for(unsigned int i = 0; i < selectedProbs.size(); ++i) {
        QString Prob = QString::fromStdString(probsList[probPositions[i]].GetFunctionSelected());
        for(unsigned int j = 0; j < selMhs.size(); ++j) {
            QString Mh = mhsList[mhPositions[j]].GetMhSelected();
            options.insertMulti("mhName", Mh);
            if(!selectedProbs[i].GetMultiObjProblem())
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            else
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + QString::fromStdString(selectedProbs[i].GetMultiObjName()) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            paths.append(index);
            index = "";
        }
    }

    options.insert("maximum", false);
    options.insert("minimum", false);
    options.insert("minimumRun", false);
    options.insert("minimumRunOrdered", false);
    options.insert("median", false);
    options.insert("mean", false);
    options.insert("variance", false);
    options.insert("standardDeviation", false);
    options.insert("minimumConvergence", false);
    options.insert("maximumConvergence", false);

    if(maximumData->isChecked())
        options.insert("maximum", true);
    if(minimumData->isChecked())
        options.insert("minimum", true);
    if(minimumByRunData->isChecked())
        options.insert("minimumRun", true);
    if(minimumByRunOrderedData->isChecked())
        options.insert("minimumRunOrdered", true);
    if(minimumConvergenceData->isChecked() && convergenceType->currentText() == "Convergence View")
        options.insert("minimumConvergence", true);
    if(maximumConvergenceData->isChecked())
        options.insert("maximumConvergence", true);
    if(medianData->isChecked())
        options.insert("median", true);
    if(meanData->isChecked())
        options.insert("mean", true);
    if(varianceData->isChecked())
        options.insert("variance", true);
    if(standardDeviationData->isChecked())
        options.insert("standardDeviation", true);

    if(chartType->currentText() == "Line Chart")
        options.insert("graphType", "Line Chart");
    else if(chartType->currentText() == "Box Plot")
        options.insert("graphType", "Box Plot");
    else if(chartType->currentText() == "Scatter Chart")
        options.insert("graphType", "Scatter Chart");

    if(xAxisScale->currentText() == "Linear")
        options.insert("xAxisScale", "Linear");
    else
        options.insert("xAxisScale", "Logarithmic");
    if(yAxisScale->currentText() == "Linear")
        options.insert("yAxisScale", "Linear");
    else
        options.insert("yAxisScale", "Logarithmic");
    if(capData->isChecked())
        options.insert("capData", true);
    else
        options.insert("capData", false);
    for(int i = 0; i < paths.size(); ++i)
        options.insertMulti("dataPath", paths.at(i));

    //plotting
    if(convergenceType->currentText() == "Other Statistical Views")
        PlotOtherStats(options);
    else if(convergenceType->currentText() == "Convergence View")
        PlotConvergence(options);
    else if(convergenceType->currentText() == "Results Variables View")
        PlotMultiobjective(options);
}

void PlotManager::PlotConvergence(QMap<QString, QVariant> opts)
{
    chart->clearPlottables();

    namespace fs = ghc::filesystem;

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    int pathCount = opts.values("dataPath").size();
    QString statPath = "";
    QString dataType = "";
    int idxGraph=-1;
    for(int i = 0; i < pathCount; ++i) {
        QString generalPath = saveLocation + "/" + opts.values("dataPath").at(i).toString();
        QString probMhPath = opts.values("dataPath").at(i).toString();
        QString mhName = opts.values("mhName").at(i).toString();
        statPath = "";
        dataType = "";

        bool testsCounted = false;
        int dirCount = 0;
        while(!testsCounted)
            if( fs::exists(QString(generalPath + "/result/teste_" + QString::number(dirCount)).toStdString()) )
                dirCount++;
            else
                testsCounted = true;
        for(int t=0; t<dirCount; ++t) {
            statPath = generalPath + "/result/teste_" + QString::number(t) + "/out/" + mhName.toUpper() + "_Evolution_0.txt";
            QFile f(statPath);
            f.open(QIODevice::ReadOnly);
            if(!f.isOpen()) {
                QMessageBox::critical(this, "LOF System Plot Manager", "The Evolution file could not be open!");
                return;
            }
            QTextStream txt(&f);

            //reading values from the file
            QStringList vals;
            while(true) {
                QString line = txt.readLine();
                if(line == Q_NULLPTR)
                    break;
                //removes the first line if it is not a number
                else if(!line.at(0).isNumber())
                    continue;
                else {
                    QStringList items = line.split("\t");
                    items.removeLast();
                    items.removeLast();
                    vals.append(items);
                }
            }
            f.close();

            //separating the values from the iterations of the stats file
            double vtmp;
            QVector<double> iterations;
            QVector<double> values;
            for(int e = 0; e < vals.size(); e+=2) {
                vtmp = vals.at(e).toDouble();
                if(vtmp < 1e-100)
                    vtmp = 0.0;
                iterations.append(vtmp);
            }

            for(int o = 1; o < vals.size(); o+=2) {
                vtmp = vals.at(o).toDouble();
                if(vtmp < 1e-100)
                    vtmp = 0.0;
                values.append(vtmp);
            }

            dataType = "Convergence for each test";

            QString legendName = probMhPath;
            legendName = legendName + " - Test " + QString::number(t);

            int r = QRandomGenerator::global()->bounded(0, 255);
            int g = QRandomGenerator::global()->bounded(0, 255);
            int b = QRandomGenerator::global()->bounded(0, 255);

            QPen pen;
            pen.setWidth(1);
            pen.setColor(QColor(r, g, b));

            if(opts.value("graphType").toString() == "Line Chart" || opts.value("graphType").toString() == "Scatter Chart") {
                AddGraph(opts, iterations, values, pen, legendName);

                AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), "Iteration", opts.value("yAxisScale").toString().toStdString(), "Value");
            } else if(opts.value("graphType").toString() == "Box Plot") {
                QVector<double> vvaluesSort = values;
                QVector<double> vvaluesLower, vvaluesUpper;
                std::sort(vvaluesSort.begin(), vvaluesSort.end());
                for(int lq = 0; lq < vvaluesSort.size()/2; ++lq)
                    vvaluesLower.append(vvaluesSort.at(lq));
                for(int uq = values.size()/2; uq < vvaluesSort.size(); ++uq)
                    vvaluesUpper.append(vvaluesSort.at(uq));

                double lower = vvaluesSort.first();
                double upper = vvaluesSort.last();
                double median = FindMedian(vvaluesSort);
                double lowQuart = FindMedian(vvaluesLower);
                double upQuart = FindMedian(vvaluesUpper);

                QCPStatisticalBox *box = new QCPStatisticalBox(chart->xAxis, chart->yAxis);
                idxGraph++;
                box->addData(idxGraph, lower, lowQuart, median, upQuart, upper);

                box->setBrush(QBrush(QColor(r, g, b), Qt::SolidPattern));
                if(r <= 70 && g <= 70 && b <=70)
                    box->setMedianPen(QPen(QColor(255, 255, 255), 3));

                AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), "", opts.value("yAxisScale").toString().toStdString(), "Values");

                // prepare manual x axis labels:
                chart->xAxis->setSubTicks(false);
                chart->xAxis->setTickLength(0, pathCount-1);
                chart->xAxis->setTicker(textTicker);
                chart->xAxis->setTickLabelRotation(20);
                textTicker->addTick(idxGraph, legendName);
                chart->legend->setVisible(false);
                chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
            }
        }
    }

    title->setText(dataType);

    //rescaling the axis
    chart->rescaleAxes();
    chart->xAxis->scaleRange(1.2);
    chart->yAxis->scaleRange(1.2);
    chart->replot();
}

void PlotManager::PlotMultiobjective(QMap<QString, QVariant> opts)
{
    QStringList header;
    QVector<QString> mh;
    QVector<QStringList> vqsl;
    QMap<int, std::string> vars;
    int qtdMetaheuristicSelected = mhList->selectionModel()->selectedRows().size();

    chart->clearPlottables();

    title->setText("Result Variables View: "+yAxisData->currentText()+" vs "+xAxisData->currentText());

    LoadDataVariablesSelectedInGUI("Result Variables", header, vqsl, vars, mh);

    int xAxis = xAxisData->currentIndex();
    int yAxis = yAxisData->currentIndex();
    double tx,ty;

    //qDebug("");
    //qDebug("MH SIZE: %d", mh.size());
    QVector<long> mhIndex;
    QString mhTemp="";
    for(long imh=0; imh<mh.size();imh++)
        if(mh[imh] != mhTemp) {
            //qDebug("imh: %d - mh[imh]: %s - mhTemp: %s", imh, mh[imh].toStdString().c_str(), mhTemp.toStdString().c_str());
            mhIndex.push_back(imh);
            mhTemp = mh[imh];
        }
    mhIndex.push_back(mh.size());
    mhIndex.push_back(mh.size());

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

    for(long imh=0; imh<qtdMetaheuristicSelected;imh++) {
        //qDebug("MH: %s", mh[mhIndex[imh]].toStdString().c_str());
        //qDebug("INIT: %d - END: %d", mhIndex[imh], mhIndex[imh+1]);
        QVector<double> x;
        QVector<double> y;
        for(long i=mhIndex[imh]; i<mhIndex[imh+1];i++) {
            tx = vqsl[i].at(xAxis).toDouble();
            ty = vqsl[i].at(yAxis).toDouble();
            x.append(tx);
            y.append(ty);
        }

        int r = QRandomGenerator::global()->bounded(0, 255);
        int g = QRandomGenerator::global()->bounded(0, 255);
        int b = QRandomGenerator::global()->bounded(0, 255);
        QPen pen;
        pen.setWidth(1);
        pen.setColor(QColor(r, g, b));

        if(opts.value("graphType").toString() == "Line Chart" || opts.value("graphType").toString() == "Scatter Chart") {
            AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), xAxisData->currentText().toStdString(), opts.value("yAxisScale").toString().toStdString(), yAxisData->currentText().toStdString());

            AddGraph(opts, x, y, pen, mh[mhIndex[imh]]);
        } else if(opts.value("graphType").toString() == "Box Plot") {
            QVector<double> vvaluesSort, vvaluesLower, vvaluesUpper;
            vvaluesSort=y;

            std::sort(vvaluesSort.begin(), vvaluesSort.end());

            for(int lq = 0; lq < vvaluesSort.size()/2; ++lq)
                vvaluesLower.append(vvaluesSort.at(lq));

            for(int uq = y.size()/2; uq < vvaluesSort.size(); ++uq)
                vvaluesUpper.append(vvaluesSort.at(uq));

            double lower = vvaluesSort.first();
            double upper = vvaluesSort.last();
            double median = FindMedian(vvaluesSort);
            double lowQuart = FindMedian(vvaluesLower);
            double upQuart = FindMedian(vvaluesUpper);

            QVector<double> outliers;
            double iqr = upQuart - lowQuart;
            double outThresh = iqr*1.5;
            double upThresh = upQuart+outThresh;
            double lowThresh = lowQuart-outThresh;
            for(int out = 0; out < vvaluesLower.size(); ++out)
                if(vvaluesLower.at(out) < lowThresh)
                    outliers.insert(outliers.size(), vvaluesLower.at(out));

            for(int out = 0; out < vvaluesUpper.size(); ++out)
                if(vvaluesUpper.at(out) > upThresh)
                    outliers.insert(outliers.size(), vvaluesUpper.at(out));

            QCPStatisticalBox *box = new QCPStatisticalBox(chart->xAxis, chart->yAxis);
            box->addData(imh+1, lower, lowQuart, median, upQuart, upper, outliers);

            box->setBrush(QBrush(QColor(r, g, b), Qt::SolidPattern));
            if(r <= 70 && g <= 70 && b <=70)
                box->setMedianPen(QPen(QColor(255, 255, 255)));

            QCPScatterStyle sty(QCPScatterStyle::ssCircle, QColor(r,g,b), 6);
            box->setOutlierStyle(sty);

            AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), "", opts.value("yAxisScale").toString().toStdString(), "Values");

            // prepare manual x axis labels:
            chart->xAxis->setSubTicks(false);
            chart->xAxis->setTickLength(0, qtdMetaheuristicSelected);
            chart->xAxis->setTicker(textTicker);
            chart->xAxis->setTickLabelRotation(20);
            QString boxName = mh[mhIndex[imh]];
            textTicker->addTick(imh+1, boxName);
            chart->legend->setVisible(false);
        }
    }
    //rescaling the axis
    chart->rescaleAxes();
    chart->xAxis->scaleRange(1.2);
    chart->yAxis->scaleRange(1.2);
    chart->replot();
}

void PlotManager::PlotOtherStats(QMap<QString, QVariant> opts)
{
    chart->clearPlottables();

    int pathCount = opts.values("dataPath").size();
    QString statPath = "";
    QString dataType = "";
    double maximumXValue = INT_MAX;

    //getting the X cap value
    if(capData->isChecked()) {
        QList<double> seriesBiggestXValue;
        for(int i = 0; i < pathCount; ++i) {
            QString generalPath = saveLocation + "/" + opts.values("dataPath").at(i).toString();
            QString probMhPath = opts.values("dataPath").at(i).toString();
            QString prefix = "statistic";
            statPath = "";
            dataType = "";

            if(opts.value("maximum").toBool()) {
                statPath = generalPath + "/" + prefix + "_Maximos.dat";
                dataType = "Maximum values";
            } else if(opts.value("minimum").toBool()) {
                statPath = generalPath + "/" + prefix + "_Minimos.dat";
                dataType = "Minimum values";
            } else if(opts.value("minimumRun").toBool() || opts.value("minimumRunOrdered").toBool()) {
                statPath = generalPath + "/" + prefix + "_Minimos_por_Run.dat";
                dataType = "Minimum values by run";
            } else if(opts.value("median").toBool()) {
                statPath = generalPath + "/" + prefix + "_Medianas.dat";
                dataType = "Median values";
            } else if(opts.value("mean").toBool()) {
                statPath = generalPath + "/" + prefix + "_Medias.dat";
                dataType = "Mean values";
            } else if(opts.value("variance").toBool()) {
                statPath = generalPath + "/" + prefix + "_Variancias.dat";
                dataType = "Variance";
            } else if(opts.value("standardDeviation").toBool()) {
                statPath = generalPath + "/" + prefix + "_DesPadrao.dat";
                dataType = "Standard Deviation";
            }

            QStringList tempVals;
            //number of itens per row
            int numbOfVariations = 0;
            //reading values from the file
            QFile f(statPath);
            f.open(QIODevice::ReadOnly);
            QTextStream txt(&f);
            while(true) {
                QString line = txt.readLine();
                QStringList items;
                if(line == Q_NULLPTR)
                    break;
                //ignores the first line if it is not a number
                else if(!line.at(0).isNumber())
                    continue;
                else {
                    items = line.split("\t");
                    items.removeLast();
                    numbOfVariations = items.size();
                    tempVals.append(items);
                }
            }
            f.close();

            double dtmp;
            QList<double> currentSerieXValue;
            for(int v = 0; v < numbOfVariations/2; ++v) {
                currentSerieXValue.clear();
                //since each stat file is different, it must be interpreted separately
                if(opts.value("standardDeviation").toBool() || opts.value("maximum").toBool() ||
                        opts.value("mean").toBool() || opts.value("median").toBool() ||
                        opts.value("minimum").toBool() || opts.value("variance").toBool()) {
                    for(int e = v*2; e < tempVals.size(); e+= numbOfVariations) {
                        dtmp = tempVals.at(e).toDouble();
                        if(dtmp < 1e-100)
                            dtmp = 0.0;
                        currentSerieXValue.append(dtmp);
                    }
                } else if(opts.value("minimumRun").toBool()) {
                    //this stat is run based, not iteration based
                    if(numbOfVariations <=2)
                        for(int e = 0; e < tempVals.size()/2; e++)
                            currentSerieXValue.append(e+1);
                    else
                        for(int e = 0; e < tempVals.size()/(numbOfVariations/2); e++)
                            currentSerieXValue.append(e+1);
                } else if(opts.value("minimumRunOrdered").toBool()) {
                    //this stat is run based, not iteration based
                    if(numbOfVariations <=2)
                        for(int e = 0; e < tempVals.size()/2; e++)
                            currentSerieXValue.append(e+1);
                    else
                        for(int e = 0; e < tempVals.size()/(numbOfVariations/2); e++)
                            currentSerieXValue.append(e+1);
                }
            }

            double biggest = 0;
            for(int c = 0; c < currentSerieXValue.size(); c++)
                if(currentSerieXValue.at(c) > biggest)
                    biggest = currentSerieXValue.at(c);

            seriesBiggestXValue.append(biggest);
        }
        for(int c = 0; c < seriesBiggestXValue.size(); c++)
            if(seriesBiggestXValue.at(c) < maximumXValue)
                maximumXValue = seriesBiggestXValue.at(c);
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    for(int i = 0; i < pathCount; ++i) {
        QString generalPath = saveLocation + "/" + opts.values("dataPath").at(i).toString();
        QString probMhPath = opts.values("dataPath").at(i).toString();
        QString prefix = "statistic";
        statPath = "";
        dataType = "";

        if(opts.value("maximum").toBool()) {
            statPath = generalPath + "/" + prefix + "_Maximos.dat";
            dataType = "Maximum values";
        } else if(opts.value("minimum").toBool()) {
            statPath = generalPath + "/" + prefix + "_Minimos.dat";
            dataType = "Minimum values";
        } else if(opts.value("minimumRun").toBool() || opts.value("minimumRunOrdered").toBool()) {
            statPath = generalPath + "/" + prefix + "_Minimos_por_Run.dat";
            dataType = "Minimum values by run";
        } else if(opts.value("median").toBool()) {
            statPath = generalPath + "/" + prefix + "_Medianas.dat";
            dataType = "Median values";
        } else if(opts.value("mean").toBool()) {
            statPath = generalPath + "/" + prefix + "_Medias.dat";
            dataType = "Mean values";
        } else if(opts.value("variance").toBool()) {
            statPath = generalPath + "/" + prefix + "_Variancias.dat";
            dataType = "Variance";
        } else if(opts.value("standardDeviation").toBool()) {
            statPath = generalPath + "/" + prefix + "_DesPadrao.dat";
            dataType = "Standard Deviation";
        }

        title->setText(dataType);

        QFile f(statPath);
        f.open(QIODevice::ReadOnly);
        if(!f.isOpen()) {
            QMessageBox::critical(this, "LOF System Plot Manager", "The statistical file " + statPath + " could not be open!");
            return;
        }
        QTextStream txt(&f);

        QStringList vals;
        //number of itens per row
        int numbOfVariations = 0;
        //reading values from the file
        while(true) {
            QString line = txt.readLine();
            QStringList items;
            if(line == Q_NULLPTR)
                break;
            //ignores the first line if it is not a number
            else if(!line.at(0).isNumber())
                continue;
            else {
                items = line.split("\t");
                items.removeLast();
                numbOfVariations = items.size();
                vals.append(items);
            }
        }
        f.close();

        int thresh = 1;
        for(int v = 0; v < numbOfVariations/2; ++v) {
            //separating the values from the iterations of the stats file
            QVector<double> iterations;
            QVector<double> values;
            //since each stat file is different, it must be interpreted separately
            if(opts.value("standardDeviation").toBool() || opts.value("maximum").toBool() ||
                    opts.value("mean").toBool() || opts.value("median").toBool() ||
                    opts.value("minimum").toBool() || opts.value("variance").toBool())
            {
                for(int e = v*2; e < vals.size(); e+= numbOfVariations)
                    if(vals.at(e).toDouble() <= maximumXValue)
                        iterations.append(vals.at(e).toDouble());

                double v20220328;
                for(int o = v+thresh; o < vals.size(); o+= numbOfVariations) {
                    /* AP & RYT 2022-03-28 */
                    /* VER AQUI SOBRE VALORES NEGATIVOS EM GRAFICO LOGARITMO */
                    v20220328 = vals.at(o).toDouble();
                    if(v20220328 < 0 && yAxisScale->currentText() == "Logarithmic") {
                        QMessageBox msgBox;
                        msgBox.setText("WARNING");
                        msgBox.setInformativeText("Logarithm scale does not support negative values!!! Changing scale to Linear");
                        msgBox.setStandardButtons(QMessageBox::Ok);
                        msgBox.setDefaultButton(QMessageBox::Ok);
                        int ret = msgBox.exec();
                        if(ret == QMessageBox::Ok) {
                            yAxisScale->setCurrentText("Linear");
                            PreparePlot();
                        }
                    }
                    values.append(v20220328);
                }
            }
            else if(opts.value("minimumRun").toBool()) {
                //this stat is run based, not iteration based
                if(numbOfVariations <=2)
                    for(int e = 0; e < vals.size()/2; e++)
                        iterations.append(e+1);
                else
                    for(int e = 0; e < vals.size()/(numbOfVariations/2); e++)
                        iterations.append(e+1);
                for(int o = v+thresh; o < vals.size(); o+= numbOfVariations)
                    values.append(vals.at(o).toDouble());
            } else if(opts.value("minimumRunOrdered").toBool()) {
                //this stat is run based, not iteration based
                if(numbOfVariations <=2)
                    for(int e = 0; e < vals.size()/2; e++)
                        iterations.append(e+1);
                else
                    for(int e = 0; e < vals.size()/(numbOfVariations/2); e++)
                        iterations.append(e+1);
                for(int o = v+thresh; o < vals.size(); o+= numbOfVariations)
                    values.append(vals.at(o).toDouble());
                std::sort(values.begin(), values.end());
            }
            thresh++;

            int r = QRandomGenerator::global()->bounded(0, 255);
            int g = QRandomGenerator::global()->bounded(0, 255);
            int b = QRandomGenerator::global()->bounded(0, 255);
            QPen pen;
            pen.setWidth(1);
            pen.setColor(QColor(r, g, b));
            std::string xLabel;
            if(opts.value("standardDeviation").toBool() || opts.value("maximum").toBool() || opts.value("mean").toBool() || opts.value("median").toBool() || opts.value("minimum").toBool() || opts.value("variance").toBool())
                xLabel = "Objective Function Calls";
            else if(opts.value("minimumRun").toBool() || opts.value("minimumRunOrdered").toBool())
                xLabel = "Run";
            QString curveName = probMhPath;
            if(numbOfVariations > 2)
                curveName = curveName + " variation " + QString::number(v+1);

            if(opts.value("graphType").toString() == "Line Chart" || opts.value("graphType").toString() == "Scatter Chart") {
                AddGraph(opts, iterations, values, pen, curveName);
                AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), xLabel, opts.value("yAxisScale").toString().toStdString(), "Value");
            } else if(opts.value("graphType").toString() == "Box Plot") {
                QVector<double> vvaluesSort, vvaluesLower, vvaluesUpper;
                vvaluesSort=values;

                std::sort(vvaluesSort.begin(), vvaluesSort.end());

                for(int lq = 0; lq < vvaluesSort.size()/2; ++lq)
                    vvaluesLower.append(vvaluesSort.at(lq));

                for(int uq = values.size()/2; uq < vvaluesSort.size(); ++uq)
                    vvaluesUpper.append(vvaluesSort.at(uq));

                double lower = vvaluesSort.first();
                double upper = vvaluesSort.last();
                double median = FindMedian(vvaluesSort);
                double lowQuart = FindMedian(vvaluesLower);
                double upQuart = FindMedian(vvaluesUpper);

                QVector<double> outliers;
                double iqr = upQuart - lowQuart;
                double outThresh = iqr*1.5;
                double upThresh = upQuart+outThresh;
                double lowThresh = lowQuart-outThresh;
                for(int out = 0; out < vvaluesLower.size(); ++out)
                    if(vvaluesLower.at(out) < lowThresh)
                        outliers.insert(outliers.size(), vvaluesLower.at(out));

                for(int out = 0; out < vvaluesUpper.size(); ++out)
                    if(vvaluesUpper.at(out) > upThresh)
                        outliers.insert(outliers.size(), vvaluesUpper.at(out));

                QCPStatisticalBox *box = new QCPStatisticalBox(chart->xAxis, chart->yAxis);
                box->addData(i, lower, lowQuart, median, upQuart, upper, outliers);

                box->setBrush(QBrush(QColor(r, g, b), Qt::SolidPattern));
                if(r <= 70 && g <= 70 && b <=70)
                    box->setMedianPen(QPen(QColor(255, 255, 255)));

                QCPScatterStyle sty(QCPScatterStyle::ssCircle, QColor(r,g,b), 6);
                box->setOutlierStyle(sty);

                AxisConfiguration(opts.value("xAxisScale").toString().toStdString(), "", opts.value("yAxisScale").toString().toStdString(), "Values");

                // prepare manual x axis labels:
                chart->xAxis->setSubTicks(false);
                chart->xAxis->setTickLength(0, pathCount-1);
                chart->xAxis->setTicker(textTicker);
                chart->xAxis->setTickLabelRotation(20);
                QString boxName = probMhPath;
                if(numbOfVariations > 2)
                    textTicker->addTick(i, boxName.remove(0, opts.value("projPath").toString().size()) + " variation " + QString::number(v+1));
                else
                    textTicker->addTick(i, boxName.remove(0, opts.value("projPath").toString().size()));
                chart->legend->setVisible(false);
            }
        }
    }

    //rescaling the axis
    chart->rescaleAxes();
    chart->xAxis->scaleRange(1.2);
    chart->yAxis->scaleRange(1.2);
    chart->replot();
}

void PlotManager::TitleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
    {
        // Set the plot title by double clicking on it
        bool ok;
        QString newTitle = QInputDialog::getText(this, "LOF System Plot Manager", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if(ok)
            title->setText(newTitle);
        chart->replot();
    }
}

void PlotManager::AxisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if(part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "LOF System Plot Manager", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if(ok)
            axis->setLabel(newLabel);

        chart->replot();
    }
}

void PlotManager::LegendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if(item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);

        QHBoxLayout *legend_lay = new QHBoxLayout();
        QLabel *lbl_legend = new QLabel("Legend");
        QLineEdit *lnEdt_txt = new QLineEdit(plItem->plottable()->name());
        lnEdt_txt->setPlaceholderText("Legend Text");
        legend_lay->addWidget(lbl_legend, Qt::AlignLeft);
        legend_lay->addWidget(lnEdt_txt, Qt::AlignLeft);

        QHBoxLayout *color_lay = new QHBoxLayout();
        QLabel *lbl_color = new QLabel("Graphic Color");
        btn_color = new QPushButton();
        QColor col = plItem->plottable()->pen().color();
        this->ChangeButtonColor(col);
        QColorDialog *colorDialog = new QColorDialog(col, this);
        connect(btn_color, SIGNAL(clicked(bool)), colorDialog, SLOT(exec()));
        connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(ChangeButtonColor(QColor)));
        color_lay->addWidget(lbl_color, Qt::AlignLeft);
        color_lay->addWidget(btn_color, Qt::AlignLeft);

        QDialog *dialog = new QDialog(this);
        QGridLayout *lay = new QGridLayout();
        dialog->setLayout(lay);
        dialog->setWindowTitle("Lof System's Plot Manager");
        dialog->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

        QHBoxLayout *btn_lay = new QHBoxLayout();
        QPushButton *btn_ok = new QPushButton("Ok");
        QPushButton *btn_cancel = new QPushButton("Cancel");
        connect(btn_ok, SIGNAL(pressed()), dialog, SLOT(accept()));
        connect(btn_cancel, SIGNAL(pressed()), dialog, SLOT(reject()));
        btn_lay->addWidget(btn_ok, Qt::AlignLeft);
        btn_lay->addWidget(btn_cancel, Qt::AlignLeft);

        lay->addLayout(legend_lay, 0, 0, Qt::AlignLeft);
        lay->addLayout(color_lay, 1, 0, Qt::AlignLeft);
        lay->addLayout(btn_lay, 2, 0, Qt::AlignRight);

        int ret = dialog->exec();
        if(ret == QDialog::Accepted)
        {
            QPen p = plItem->plottable()->pen();
            p.setColor(colorDialog->selectedColor());
            plItem->plottable()->setPen(p);
            plItem->plottable()->setName(lnEdt_txt->text());
        }

        chart->replot();
    }
}

void PlotManager::ChangeButtonColor(QColor col)
{
    btn_color->setStyleSheet("background-color: rgb(" + QString::number(col.red()) + ","
                             + QString::number(col.green()) + "," + QString::number(col.blue()) + ")");
}

void PlotManager::SelectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (chart->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || chart->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            chart->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || chart->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        chart->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        chart->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (chart->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || chart->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            chart->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || chart->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        chart->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        chart->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<chart->graphCount(); ++i)
    {
        QCPGraph *graph = chart->graph(i);
        QCPPlottableLegendItem *item = chart->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }

    chart->replot();
}

void PlotManager::MousePress(QMouseEvent* event)
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged
//    if(event->button() != Qt::RightButton) {
//        if (chart->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
//            chart->axisRect()->setRangeDrag(chart->xAxis->orientation());
//        else if (chart->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
//            chart->axisRect()->setRangeDrag(chart->yAxis->orientation());
//        else
//            chart->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
//    }
//    else if(event->button() == Qt::RightButton)

    if (chart->legend->selectTest(event->pos(), false) > 0) {
        draggingLegend = true;
        // since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
        QPointF mousePoint((event->pos().x()-chart->axisRect()->left())/double(chart->axisRect()->width()),
                           (event->pos().y()-chart->axisRect()->top())/double(chart->axisRect()->height()));
        dragLegendOrigin = mousePoint-chart->axisRect()->insetLayout()->insetRect(0).topLeft();
    } else if(event->button() == Qt::RightButton) {
        chart->rescaleAxes();
        chart->xAxis->scaleRange(1.2);
        chart->yAxis->scaleRange(1.2);
    }

    chart->replot();
}

void PlotManager::MouseMove(QMouseEvent *event)
{
    if(draggingLegend)
    {
        QRectF rect = chart->axisRect()->insetLayout()->insetRect(0);
        // since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
        QPointF mousePoint((event->pos().x()-chart->axisRect()->left())/double(chart->axisRect()->width()),
                           (event->pos().y()-chart->axisRect()->top())/double(chart->axisRect()->height()));
        rect.moveTopLeft(mousePoint-dragLegendOrigin);
        chart->axisRect()->insetLayout()->setInsetRect(0, rect);
        chart->replot();
    }
    else
    {
        int x = qRound(chart->xAxis->pixelToCoord(event->pos().x()));
        double y = chart->yAxis->pixelToCoord(event->pos().y());

        chart->setToolTip(QString("%1 , %2").arg(x).arg(y));
    }
}

void PlotManager::MouseRelease(QMouseEvent *event)
{
    Q_UNUSED(event)
    draggingLegend = false;
}

void PlotManager::LoadDataTable(QString filename)
{
    QStringList tokens, header;
    QVector<QString> mh;
    QVector<QStringList> vqsl;
    QMap<int, std::string> vars;

    if(filename.contains("Result Variables") || filename.contains("Project Variables") || filename.contains("Project & Result Variables")) {
        LoadDataVariablesSelectedInGUI(filename, header, vqsl, vars, mh);
    } else {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::information(this, "LOF System", "Error: could not open "+filename);
            return;
        }
        QTextStream in(&file);
        QStringList lstLine;
        header = in.readLine().split(QRegExp("(\t| )"));
        header.pop_back();
        while(true) {
            lstLine = in.readLine().split(QRegExp("(\t| )"));
            lstLine.pop_back();
            vqsl.push_back(lstLine);
            if(in.atEnd())
                break;
        }
        file.close();
    }
    QStandardItemModel *model = new QStandardItemModel(vqsl.size(),vqsl[0].size(),this);
    model->setHorizontalHeaderLabels(header);
    for (long i=0; i<vqsl.size(); ++i)
        for (long j=0; j<vqsl[i].size(); j++) {
            QModelIndex index = model->index(i,j,QModelIndex());
            model->setData(index,vqsl[i][j].toDouble());
        }
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSortingEnabled(true);
}

void PlotManager::LoadDataVariables(QString filename, QStringList &header, QVector<QStringList> &vqsl, QMap<int, std::string> &vars, QVector<QString> &mhData, std::vector<ProblemSets> &selectedProbs, std::vector<int> &probPositions, std::vector<QString> &selMhs, std::vector<int> &mhPositions)
{
    QStringList tokens;
    QStringList paths;
    QString index = saveLocation+"/";

    if(filename.contains("Project & Result Variables"))
    {
        vars = probsList[probPositions[0]].GetProbVars_name();
        QMap<int, std::string> tmpvar = probsList[probPositions[0]].GetProbResultsNames();
        for (auto i = tmpvar.constBegin(); i != tmpvar.constEnd(); ++i)
            vars.insert(i.key(), i.value());
    }
    else if(filename.contains("Project Variables"))
        vars = probsList[probPositions[0]].GetProbVars_name();
    else if(filename.contains("Result Variables"))
        vars = probsList[probPositions[0]].GetProbResultsNames();

    vars.insert(vars.size(),"ObjectiveFunction");

    for(int h=0; h<vars.size(); h++)
        header.append(QString::fromStdString(vars[h]));

    for(unsigned int j = 0; j < selMhs.size(); ++j) {
        std::vector<int> varsColumns;
        mhsList[mhPositions[j]].CalculateParameterCount();
        int repetitions = mhsList[mhPositions[j]].GetParameterCount() * lofMhSettings.value("numberOfRepetitions").toInt();
        QString Mh = mhsList[mhPositions[j]].GetMhSelected();
        for(unsigned int i = 0; i < selectedProbs.size(); ++i)
        {
            QString Prob = QString::fromStdString(probsList[probPositions[i]].GetFunctionSelected());
            bool getHeader = true;
            if(!selectedProbs[i].GetMultiObjProblem())
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            else
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + QString::fromStdString(selectedProbs[i].GetMultiObjName()) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            for(int l = 0; l < repetitions; ++l)
            {
                QString file = index + "/result/teste_" + QString::number(l) + "/out/" + mhsList[mhPositions[j]].GetMhSelected() + "_0.dat";
                std::string line;
                if(fs::exists(file.toStdString().c_str()))
                {
                    fs::ifstream fi(file.toStdString().c_str());
                    if(getHeader)
                    {
                        varsColumns.clear();
                        getHeader = false;
                        DiscoverVariablesColumnsInDAT(fi, varsColumns, vars);
                        if(varsColumns.size() != vars.size())
                        {
                            QString msg = "Error: Please, select problems with the same variables to show. Missing variables in " + index;
                            msg += "\nVariables:";
                            for(auto xxx : vars.keys())
                                msg += "\n" + QString::fromStdString(vars[xxx]);
                            msg += "\nvarsColumns.size(): " + QString::number(varsColumns.size());
                            msg += "\nvars.size(): " + QString::number(vars.size());
                            QMessageBox::information(this, "LOF-MH", msg);
                            fi.close();
                            return;
                        }
                    } else
                        getline(fi,line); // Extract Header
                    getline(fi,line);
                    while(!fi.eof())
                    {
                        tokens = QString::fromStdString(line).split(QRegExp("( |\t)"));
                        QStringList qsl;
                        if(varsColumns.size() && tokens.size() > (varsColumns[varsColumns.size()-1]+varsColumns.size()-1))
                        {
                            //std::cout << "\nvarsColumns.size(): " << varsColumns.size() << "\n"; std::cout.flush();
                            //std::cout << "\ntokens.size(): " << tokens.size() << "\n"; std::cout.flush();
                            //std::cout << "\nvarsColumns[varsColumns.size(): " << varsColumns[varsColumns.size()-1] << "\n"; std::cout.flush();
                            for(unsigned long jj=0;jj<varsColumns.size();jj++)
                            {
                                qsl.append(tokens[varsColumns[jj]]);
                            }
                            if(qsl[0].size()) {
                                mhData.append(Mh);
                                vqsl.push_back(qsl);
                            }
                        }
                        getline(fi,line);
                    }
                    fi.close();
                }
                else
                {
                    std::cout << "\nFile not found: " << file.toStdString() << "\n";
                }

            }
            index = saveLocation+"/";
        }
    }
}

void PlotManager::LoadDataVariablesSelectedInGUI(QString filename, QStringList &header, QVector<QStringList> &vqsl, QMap<int, std::string> &vars, QVector<QString> &mhData)
{
    QStringList tokens;
    QStringList paths;
    QString projectName = saveLocation+"/"+lofMhSettings.value("projectName").toString();
    QString index = projectName + "_";
    std::vector<ProblemSets> selectedProbs;
    std::vector<QString> selMhs;
    std::vector<int> probPositions, mhPositions;

    ProblemMHList(selectedProbs, probPositions, selMhs, mhPositions);

    LoadDataVariables(filename, header, vqsl, vars, mhData, selectedProbs, probPositions, selMhs, mhPositions);
}

void PlotManager::BeforeReplot()
{
    // this is to prevent the legend from stretching if the plot is stretched.
    // Since we've set the inset placement to be ipFree, the width/height of the legend
    // is also defined in axisRect coordinates (0..1) and thus would stretch.
    // This is due to change in a future release (probably QCP 2.0) since it's basically a design mistake.
    chart->legend->setMaximumSize(chart->legend->minimumOuterSizeHint());
}

void PlotManager::ChangeProbMhSelection(int sel)
{
//    if(sel == 0) {
//        probList->setSelectionMode(QAbstractItemView::SingleSelection);
//        probList->clearSelection();
//        mhList->setSelectionMode(QAbstractItemView::SingleSelection);
//        mhList->clearSelection();
//    } else if(sel == 1) {
        probList->setSelectionMode(QAbstractItemView::MultiSelection);
        probList->clearSelection();
        mhList->setSelectionMode(QAbstractItemView::MultiSelection);
        mhList->clearSelection();
//    }
}

qreal PlotManager::FindMedian(QVector<double> vals)
{
    if (vals.size() <= 0)
        return 0;
    else
    {
        std::sort(vals.begin(), vals.end());
        if (vals.size() % 2 == 0)
            return (vals.at(vals.size()/2.0 - 1.0) + vals.at(vals.size()/2.0))/2.0;
        else
            return vals.at(vals.size()/2.0);
    }
}

void PlotManager::AxisConfiguration(std::string xGraphType, std::string xLabel, std::string yGraphType, std::string yLabel)
{
    chart->xAxis->setLabel(QString::fromStdString(xLabel));
    chart->xAxis->setTickLabelRotation(0);
    chart->yAxis->setLabel(QString::fromStdString(yLabel));

    if(xGraphType == "Linear") {
        chart->xAxis->setScaleType(QCPAxis::stLinear);
        chart->xAxis->grid()->setSubGridVisible(false);
        chart->xAxis->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
        chart->xAxis->setNumberFormat("gb");
        chart->xAxis->setNumberPrecision(6);
        chart->xAxis2->setScaleType(QCPAxis::stLinear);
        chart->xAxis2->grid()->setSubGridVisible(false);
        chart->xAxis2->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
    } else if(xGraphType == "Logarithmic") {
        chart->xAxis->setScaleType(QCPAxis::stLogarithmic);
        chart->xAxis->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
        chart->xAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        chart->xAxis->setNumberPrecision(1); // makes sure "1*10^4" is displayed only as "10^4"
        chart->xAxis2->setScaleType(QCPAxis::stLogarithmic);
        chart->xAxis2->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
    }
    if(yGraphType == "Linear") {
        chart->yAxis->setScaleType(QCPAxis::stLinear);
        chart->yAxis->grid()->setSubGridVisible(false);
        chart->yAxis->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
        chart->yAxis->setNumberFormat("gb");
        chart->yAxis->setNumberPrecision(6);
        chart->yAxis2->setScaleType(QCPAxis::stLinear);
        chart->yAxis2->grid()->setSubGridVisible(false);
        chart->yAxis2->setTicker(QSharedPointer<QCPAxisTicker>(new QCPAxisTicker));
    } else if(yGraphType == "Logarithmic") {
        chart->yAxis->setScaleType(QCPAxis::stLogarithmic);
        chart->yAxis->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
        chart->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
        chart->yAxis->setNumberPrecision(1); // makes sure "1*10^4" is displayed only as "10^4"
        chart->yAxis2->setScaleType(QCPAxis::stLogarithmic);
        chart->yAxis2->setTicker(QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog));
    }
    chart->rescaleAxes();
    chart->xAxis->scaleRange(1.2);
    chart->yAxis->scaleRange(1.2);
    chart->replot();
}

void PlotManager::SuggestChartType()
{
    if(convergenceType->currentText() == "Convergence View") {
        chartType->setCurrentText("Line Chart");
        yAxisScale->setCurrentText("Logarithmic");
    } else if(convergenceType->currentText() == "Other Statistical View") {
        chartType->setCurrentText("Line Chart");
        yAxisScale->setCurrentText("Logarithmic");
    } else if(convergenceType->currentText() == "Results Variables View") {
        chartType->setCurrentText("Scatter Chart");
        xAxisScale->setCurrentText("Linear");
        yAxisScale->setCurrentText("Linear");
    }
}

void PlotManager::GrapherDataTabChange(int tabIndex)
{
    if(tabIndex == 0) {
         datatableExplorer_box->setVisible(false);
         graphExplorer_box->setVisible(true);
         actJpeg->setVisible(true);
         actBmp->setVisible(true);
         actPng->setVisible(true);
         actDat->setVisible(false);
    } else if(tabIndex == 1) {
        datatableExplorer_box->setVisible(true);
        graphExplorer_box->setVisible(false);
        actJpeg->setVisible(false);
        actBmp->setVisible(false);
        actPng->setVisible(false);
        actDat->setVisible(true);
    }
}

void PlotManager::ProblemMHList(std::vector<ProblemSets> &selectedProbs, std::vector<int> &probPositions, std::vector<QString> &selMhs, std::vector<int> &mhPositions)
{
    std::vector<QString> alreadyInserted;
    for(int i = 0; i < probList->selectionModel()->selectedRows().size(); ++i) {
        int probIndex = probList->selectedItems().at(i)->data(0,Qt::UserRole).toInt();
        int mobjIndex = probList->selectedItems().at(i)->data(1,Qt::UserRole).toInt();
        if(!probsList[probIndex].GetMultiObjProblem()) {
            selectedProbs.push_back(probsList[probIndex]);
            probPositions.push_back(probIndex);
            alreadyInserted.push_back(QString::number(probIndex));
        } else if(mobjIndex == -1) {
            for(unsigned long j=0;j<probsList[probIndex].GetMultiObjProblemSet().size();j++) {
                if(std::find(alreadyInserted.begin(), alreadyInserted.end(), QString::number(probIndex)+"-"+QString::number(j)) == alreadyInserted.end()) {
                    selectedProbs.push_back(probsList[probIndex].GetMultiObjProblemSet()[j]);
                    probPositions.push_back(probIndex);
                    alreadyInserted.push_back(QString::number(probIndex)+"-"+QString::number(j));
                }
            }
        } else if(std::find(alreadyInserted.begin(), alreadyInserted.end(), QString::number(probIndex)+"-"+QString::number(mobjIndex)) == alreadyInserted.end()) {
            selectedProbs.push_back(probsList[probIndex].GetMultiObjProblemSet()[mobjIndex]);
            probPositions.push_back(probIndex);
            alreadyInserted.push_back(QString::number(probIndex)+"-"+QString::number(mobjIndex));
        }
    }
    for(int i = 0; i < mhList->selectionModel()->selectedRows().size(); ++i) {
        int p = mhList->selectionModel()->selectedRows().at(i).row();
        selMhs.push_back(mhList->selectionModel()->selectedRows().at(i).data().toString());
        mhPositions.push_back(p);
    }
}

void PlotManager::ProblemMHListChange()
{
    table->setModel(new QStandardItemModel(0,0,this));
    fileList->clear();
    if(probList->selectedItems().size()==0 || mhList->selectedItems().size()==0) {
        //QDesktopServices::openUrl(QUrl::fromLocalFile(lastSavingLocation));
        return;
    }
    QStringList paths;
    //QString projectName = lofMhSettings.value("projectName").toString();
    QString index = "";
    std::vector<ProblemSets> selectedProbs;
    std::vector<QString> selMhs;
    std::vector<int> probPositions, mhPositions;

    ProblemMHList(selectedProbs, probPositions, selMhs, mhPositions);

    xAxisData->clear();
    yAxisData->clear();
    for(unsigned long ii=0; ii<selectedProbs[0].GetProbResultsNames().size(); ii++) {
        xAxisData->addItem(QString::fromStdString(selectedProbs[0].GetProbResultsNames()[ii]));
        yAxisData->addItem(QString::fromStdString(selectedProbs[0].GetProbResultsNames()[ii]));
    }
    xAxisData->addItem("ObjectiveFunction");
    yAxisData->addItem("ObjectiveFunction");

    for(unsigned int i = 0; i < selectedProbs.size(); ++i) {
        QString Prob = QString::fromStdString(probsList[probPositions[i]].GetFunctionSelected());
        for(unsigned int j = 0; j < selMhs.size(); ++j) {
            mhsList[mhPositions[j]].CalculateParameterCount();
            int repetitions = mhsList[mhPositions[j]].GetParameterCount() * lofMhSettings.value("numberOfRepetitions").toInt();
            QString Mh = mhsList[mhPositions[j]].GetMhSelected();
            if(!selectedProbs[i].GetMultiObjProblem())
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            else
                index += (Prob + "_" + QString::number(probPositions[i]) + "_" + QString::fromStdString(selectedProbs[i].GetMultiObjName()) + "_" + Mh + "_" + QString::number(mhPositions[j]));
            for(int l = 0; l < repetitions; ++l)
                paths.append(index + "/result/teste_" + QString::number(l) + "/out/" + mhsList[mhPositions[j]].GetMhSelected() + "_0.dat");
            index = "";
        }
    }
    QTreeWidgetItem *item1 = new QTreeWidgetItem();
    item1->setText(0, "Project Variables");
    fileList->addTopLevelItem(item1);
    QTreeWidgetItem *item2 = new QTreeWidgetItem();
    item2->setText(0, "Result Variables");
    fileList->addTopLevelItem(item2);
    QTreeWidgetItem *item3 = new QTreeWidgetItem();
    item3->setText(0, "Project & Result Variables");
    fileList->addTopLevelItem(item3);
    for(int i=0; i<paths.size(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, paths[i]);
        fileList->addTopLevelItem(item);
    }
    fileList->resizeColumnToContents(0);
}

void PlotManager::FileListChange()
{
    if(fileList->selectedItems().size() == 0)
        return;
    QString file = saveLocation + "/" + fileList->selectedItems().at(0)->text(0);
    LoadDataTable(file);
}

void PlotManager::PlotInitialConfiguration()
{
    chart->xAxis2->setVisible(true);
    chart->xAxis2->setTickLabels(false);
    chart->yAxis2->setVisible(true);
    chart->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(chart->xAxis, SIGNAL(rangeChanged(QCPRange)), chart->xAxis2, SLOT(setRange(QCPRange)));
    connect(chart->yAxis, SIGNAL(rangeChanged(QCPRange)), chart->yAxis2, SLOT(setRange(QCPRange)));

    chart->xAxis->setLabelFont(QFont("sans", 14, QFont::Bold));
    chart->yAxis->setLabelFont(QFont("sans", 14, QFont::Bold));

    // Legend
    chart->legend->setFont(QFont("sans", 9, QFont::Normal));
    chart->legend->setBrush(QBrush(QColor(255,255,255,230)));
    chart->legend->setSelectableParts(QCPLegend::spItems);
    chart->legend->setVisible(true);
    // set the placement of the legend (index 0 in the axis rect's inset layout) to not be
    // border-aligned (default), but freely, so we can reposition it anywhere:
    chart->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    draggingLegend = false;

    // Insert Title
    if(!chart->plotLayout()->hasElement(1, 0))
        chart->plotLayout()->insertRow(0);
    title = new QCPTextElement(chart, "LOF-SYSTEM", QFont("sans", 17, QFont::Bold));
    chart->plotLayout()->addElement(0, 0, title);
    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(TitleDoubleClick(QMouseEvent*)));

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(chart, SIGNAL(selectionChangedByUser()), this, SLOT(SelectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(chart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePress(QMouseEvent*)));
    connect(chart, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(AxisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(chart, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(LegendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    connect(chart, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(MouseMove(QMouseEvent*)));
    connect(chart, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(MousePress(QMouseEvent*)));
    connect(chart, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(MouseRelease(QMouseEvent*)));
    connect(chart, SIGNAL(beforeReplot()), this, SLOT(BeforeReplot()));

    chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
}

void PlotManager::AddGraph(QMap<QString, QVariant> opts, QVector<double> x, QVector<double> y, QPen pen, QString curveName)
{
    long idxGraph = chart->graphCount();
    if(opts.value("graphType").toString() == "Line Chart") {
        chart->addGraph();
        chart->graph(idxGraph)->setData(x, y);
        chart->graph(idxGraph)->setName(curveName);
        chart->graph(idxGraph)->setPen(pen);
        chart->graph(idxGraph)->setScatterStyle(QCPScatterStyle::ssDisc);
    } else if(opts.value("graphType").toString() == "Scatter Chart") {
        chart->addGraph();
        chart->graph(idxGraph)->setData(x, y);
        chart->graph(idxGraph)->setName(curveName);
        chart->graph(idxGraph)->setPen(pen);
        chart->graph()->setLineStyle(QCPGraph::lsNone);

        QVector<QCPScatterStyle::ScatterShape> shapes;
        shapes.append(QCPScatterStyle::ssCross);
        shapes.append(QCPScatterStyle::ssPlus);
        shapes.append(QCPScatterStyle::ssCircle);
        shapes.append(QCPScatterStyle::ssDisc);
        shapes.append(QCPScatterStyle::ssSquare);
        shapes.append(QCPScatterStyle::ssDiamond);
        shapes.append(QCPScatterStyle::ssStar);
        shapes.append(QCPScatterStyle::ssTriangle);
        shapes.append(QCPScatterStyle::ssTriangleInverted);
        shapes.append(QCPScatterStyle::ssCrossSquare);
        shapes.append(QCPScatterStyle::ssPlusSquare);
        shapes.append(QCPScatterStyle::ssCrossCircle);
        shapes.append(QCPScatterStyle::ssPlusCircle);
        shapes.append(QCPScatterStyle::ssPeace);
        int selShape = QRandomGenerator::global()->bounded(0, shapes.size());

        QCPScatterStyle st = shapes.at(selShape);
        st.setSize(st.size()*2);
        chart->graph(idxGraph)->setScatterStyle(st);
    } else if(opts.value("graphType").toString() == "Box Plot") {
        QVector<double> outliers;
        for(int out = 0; out < opts.value("BoxPlotOutliersSize").toInt(); ++out)
            outliers.push_back(opts.value("BoxPlotOutliers"+QString::number(out)).toDouble());
        //chartBoxPlot->addData(opts.value("BoxPlotIndex").toInt(),
        //                      opts.value("BoxPlotLower").toDouble(),
        //                      opts.value("BoxPlotLowQuart").toDouble(),
        //                     opts.value("BoxPlotMedian").toDouble(),
        //                      opts.value("BoxPlotUpQuart").toDouble(),
        //                      opts.value("BoxPlotUpper").toDouble(),
        //                      outliers);
        chartBoxPlot->addData(1, 1.1, 1.9, 2.25, 2.7, 4.2);
        chartBoxPlot->addData(2, 0.8, 1.6, 2.2, 3.2, 4.9, QVector<double>() << 0.7 << 0.34 << 0.45 << 6.2 << 5.84); // provide some outliers as QVector
        chartBoxPlot->addData(3, 0.2, 0.7, 1.1, 1.6, 2.9);
        chart->xAxis->setSubTicks(false);
        chart->xAxis->setTickLength(0, 4);
        chart->xAxis->setTickLabelRotation(20);
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTick(1, "Sample 1");
        textTicker->addTick(2, "Sample 2");
        textTicker->addTick(3, "Control Group");
        chart->xAxis->setTicker(textTicker);

        qDebug("Index: %d", opts.value("BoxPlotIndex").toInt());
        qDebug("Lower: %lf", opts.value("BoxPlotLower").toDouble());
        qDebug("LowQuart: %lf", opts.value("BoxPlotLowQuart").toDouble());
        qDebug("Median: %lf", opts.value("BoxPlotMedian").toDouble());
        qDebug("UpQuart: %lf", opts.value("BoxPlotUpQuart").toDouble());
        qDebug("Upper: %lf", opts.value("BoxPlotUpper").toDouble());
        qDebug("OutliersSize: %d", opts.value("BoxPlotOutliersSize").toInt());

        //chartBoxPlot->setBrush(pen.brush());

        //if(pen.brush().color().red() <= 70 && pen.brush().color().green() <= 70 && pen.brush().color().blue() <= 70)
        //    chartBoxPlot->setMedianPen(QPen(QColor(255, 255, 255)));

        //QCPScatterStyle sty(QCPScatterStyle::ssCircle, pen.brush().color(), 6);
        //chartBoxPlot->setOutlierStyle(sty);

        // prepare manual x axis labels:
        //chart->xAxis->setSubTicks(false);
        //chart->xAxis->setTickLength(0, opts.value("xTicksCount").toInt());
        //chart->xAxis->setTickLabelRotation(20);
        //for(int i=0; i<opts.value("BoxPlotYAxisTicks").toInt(); i++)
        //    textTicker->addTick(opts.value("BoxPlotIndex").toInt(), opts.value("BoxPlotYAxisTicks").toString());
        //chart->xAxis->setTicker(textTicker);
        //chart->legend->setVisible(false);
        //chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    }

    //rescaling the axis
    //chart->rescaleAxes();
    //double limit = 0.02 * (opts.value("rangeMaxX").toDouble() - opts.value("rangeMinX").toDouble());
    //chart->xAxis->setRange(opts.value("rangeMinX").toDouble()-limit, opts.value("rangeMaxX").toDouble()+limit);
    //limit = 0.02 * (opts.value("rangeMaxY").toDouble() - opts.value("rangeMinY").toDouble());
    //chart->yAxis->setRange(opts.value("rangeMinY").toDouble()-limit, opts.value("rangeMaxY").toDouble()+limit);

    //chart->replot();
}

void PlotManager::DiscoverVariablesColumnsInDAT(fs::ifstream &fi, std::vector<int> &columns, QMap<int, std::string> vars)
{
    std::string line;
    getline(fi,line);
    std::vector<std::string> tokens = split(line,'\t');
    // Results Variables Columns
    for(auto xxx : vars.keys()) {
        //qDebug("resvars: %s", resvars[xxx].c_str());
        int countHeader = 0;
        for(int jj=0;jj<tokens.size();jj++)
            if(tokens[jj] == vars[xxx]) {
                countHeader++;
                if(countHeader == 2) {
                    columns.push_back(jj);
                    break;
                }
            } else if(vars[xxx] == "ObjectiveFunction") {
                if(tokens[jj].find(vars[xxx]) != std::string::npos) {
                    countHeader++;
                    if(countHeader == 2) {
                        columns.push_back(jj);
                        break;
                    }
                }
            }
    }
    /*
    vars.insert(vars.size(), "ObjectiveFunction");
    // Objective Function Column
    int countHeader = 0;
    for(int jj=0;jj<tokens.size();jj++) {
        if(tokens[jj].find("ObjectiveFunction") != std::string::npos) {
            countHeader++;
            if(countHeader == 2) {
                columns.push_back(jj);
                break;
            }
        }
    }
    */
}

void PlotManager::SaveAsPng()
{
    QString filename = QFileDialog::getSaveFileName(this, "", "", "*.PNG");

    QPixmap p = chart->grab();
    p.save(filename, "PNG", 100);
}

void PlotManager::SaveAsJpeg()
{
    QString filename = QFileDialog::getSaveFileName(this, "", "", "*.JPEG");

    QPixmap p = chart->grab();
    p.save(filename, "JPEG", 100);
}

void PlotManager::SaveAsBmp()
{
    QString filename = QFileDialog::getSaveFileName(this, "", "", "*.BMP");

    QPixmap p = chart->grab();
    p.save(filename, "BMP", 100);
}

void PlotManager::SaveAsDat()
{
    table->selectAll();
    QAbstractItemModel *abmodel = table->model();
    QItemSelectionModel *model = table->selectionModel();
    QModelIndexList list = model->selectedIndexes();
    qSort(list);
    if(list.size() < 1)
        return;
    QString copy_table;
    QModelIndex last = list.last();
    QModelIndex previous = list.first();
    list.removeFirst();
    copy_table.append(abmodel->headerData(0,Qt::Horizontal).toString());
    for(int i = 1; i < abmodel->columnCount(); i++)
    {
        copy_table.append('\t');
        copy_table.append(abmodel->headerData(i,Qt::Horizontal).toString());
    }
    copy_table.append('\n');
    for(int i = 0; i < list.size(); i++)
    {
        QVariant data = abmodel->data(previous);
        QString text = data.toString();
        QModelIndex index = list.at(i);
        copy_table.append(text);
        if(index.row() != previous.row())
        {
            copy_table.append('\n');
        }
        else
        {
            copy_table.append('\t');
        }
        previous = index;
    }
    copy_table.append(abmodel->data(list.last()).toString());
    copy_table.append('\n');
    //QClipboard *clipboard = QApplication::clipboard();
    //clipboard->setText(copy_table);
    QString filename = QFileDialog::getSaveFileName(this, "", "", "*.dat");
    QFile qFile(filename);
    if(qFile.open(QIODevice::WriteOnly))
    {
        qFile.write(copy_table.toUtf8());
        qFile.close();
    }
}

void PlotManager::OpenExplorer()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(saveLocation));
}
