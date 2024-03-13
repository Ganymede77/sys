/********************************************************************************
** Form generated from reading UI file 'lofmhsettings.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOFMHSETTINGS_H
#define UI_LOFMHSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LofMhSettings
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *grpBx_trace_files;
    QCheckBox *chkBx_trace_func_entry;
    QCheckBox *chkBx_trace_warning;
    QCheckBox *chkBx_trace_functional;
    QCheckBox *chkBx_trace_func_leave;
    QCheckBox *chkBx_trace_error;
    QCheckBox *chkBx_trace_debug;
    QGroupBox *grpBx_seed_config;
    QLabel *lbl_seed_initial;
    QComboBox *cmbBx_seed_initial;
    QLabel *lbl_seed_input;
    QLineEdit *lnEdt_seed;
    QGroupBox *grpBx_parallel_config;
    QComboBox *cmbBx_parallel_cmp;
    QLabel *lbl_nbr_nodes;
    QSpinBox *spnBx_nmb_nodes;
    QRadioButton *rdBtn_parallel_pop;
    QRadioButton *rdBtn_parallel_search;
    QCheckBox *chkBx_parallel_activated;
    QRadioButton *rdBtn_parallel_run;
    QGroupBox *grpBx_other_settings;
    QCheckBox *chkBx_auto_gen_stats;
    QCheckBox *chkBx_auto_gen_dir;
    QComboBox *cmbBx_opt_type_problem;
    QLabel *lbl_opt_type_problem;
    QSpinBox *spnBx_nmb_repet;
    QLabel *lbl_nmb_repet;
    QLabel *lbl_project_name;
    QLineEdit *lnEdt_project_name;

    void setupUi(QDialog *LofMhSettings)
    {
        if (LofMhSettings->objectName().isEmpty())
            LofMhSettings->setObjectName("LofMhSettings");
        LofMhSettings->setWindowModality(Qt::ApplicationModal);
        LofMhSettings->resize(505, 471);
        LofMhSettings->setFocusPolicy(Qt::ClickFocus);
        LofMhSettings->setAutoFillBackground(true);
        buttonBox = new QDialogButtonBox(LofMhSettings);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(89, 420, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        grpBx_trace_files = new QGroupBox(LofMhSettings);
        grpBx_trace_files->setObjectName("grpBx_trace_files");
        grpBx_trace_files->setGeometry(QRect(310, 251, 179, 161));
        chkBx_trace_func_entry = new QCheckBox(grpBx_trace_files);
        chkBx_trace_func_entry->setObjectName("chkBx_trace_func_entry");
        chkBx_trace_func_entry->setGeometry(QRect(11, 21, 149, 18));
        chkBx_trace_warning = new QCheckBox(grpBx_trace_files);
        chkBx_trace_warning->setObjectName("chkBx_trace_warning");
        chkBx_trace_warning->setGeometry(QRect(11, 94, 149, 18));
        chkBx_trace_functional = new QCheckBox(grpBx_trace_files);
        chkBx_trace_functional->setObjectName("chkBx_trace_functional");
        chkBx_trace_functional->setGeometry(QRect(11, 70, 149, 17));
        chkBx_trace_func_leave = new QCheckBox(grpBx_trace_files);
        chkBx_trace_func_leave->setObjectName("chkBx_trace_func_leave");
        chkBx_trace_func_leave->setGeometry(QRect(11, 46, 149, 17));
        chkBx_trace_error = new QCheckBox(grpBx_trace_files);
        chkBx_trace_error->setObjectName("chkBx_trace_error");
        chkBx_trace_error->setGeometry(QRect(11, 143, 149, 17));
        chkBx_trace_debug = new QCheckBox(grpBx_trace_files);
        chkBx_trace_debug->setObjectName("chkBx_trace_debug");
        chkBx_trace_debug->setGeometry(QRect(11, 119, 149, 17));
        grpBx_seed_config = new QGroupBox(LofMhSettings);
        grpBx_seed_config->setObjectName("grpBx_seed_config");
        grpBx_seed_config->setGeometry(QRect(9, 130, 269, 96));
        lbl_seed_initial = new QLabel(grpBx_seed_config);
        lbl_seed_initial->setObjectName("lbl_seed_initial");
        lbl_seed_initial->setGeometry(QRect(11, 31, 100, 16));
        cmbBx_seed_initial = new QComboBox(grpBx_seed_config);
        cmbBx_seed_initial->addItem(QString());
        cmbBx_seed_initial->addItem(QString());
        cmbBx_seed_initial->setObjectName("cmbBx_seed_initial");
        cmbBx_seed_initial->setGeometry(QRect(125, 31, 86, 22));
        lbl_seed_input = new QLabel(grpBx_seed_config);
        lbl_seed_input->setObjectName("lbl_seed_input");
        lbl_seed_input->setGeometry(QRect(11, 61, 34, 16));
        lnEdt_seed = new QLineEdit(grpBx_seed_config);
        lnEdt_seed->setObjectName("lnEdt_seed");
        lnEdt_seed->setEnabled(false);
        lnEdt_seed->setGeometry(QRect(52, 61, 126, 22));
        lnEdt_seed->setAutoFillBackground(false);
        lnEdt_seed->setReadOnly(false);
        grpBx_parallel_config = new QGroupBox(LofMhSettings);
        grpBx_parallel_config->setObjectName("grpBx_parallel_config");
        grpBx_parallel_config->setEnabled(true);
        grpBx_parallel_config->setGeometry(QRect(310, 90, 179, 161));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grpBx_parallel_config->sizePolicy().hasHeightForWidth());
        grpBx_parallel_config->setSizePolicy(sizePolicy);
        grpBx_parallel_config->setMinimumSize(QSize(0, 0));
        cmbBx_parallel_cmp = new QComboBox(grpBx_parallel_config);
        cmbBx_parallel_cmp->addItem(QString());
        cmbBx_parallel_cmp->addItem(QString());
        cmbBx_parallel_cmp->addItem(QString());
        cmbBx_parallel_cmp->addItem(QString());
        cmbBx_parallel_cmp->addItem(QString());
        cmbBx_parallel_cmp->setObjectName("cmbBx_parallel_cmp");
        cmbBx_parallel_cmp->setEnabled(false);
        cmbBx_parallel_cmp->setGeometry(QRect(11, 101, 119, 22));
        lbl_nbr_nodes = new QLabel(grpBx_parallel_config);
        lbl_nbr_nodes->setObjectName("lbl_nbr_nodes");
        lbl_nbr_nodes->setEnabled(true);
        lbl_nbr_nodes->setGeometry(QRect(11, 130, 104, 16));
        spnBx_nmb_nodes = new QSpinBox(grpBx_parallel_config);
        spnBx_nmb_nodes->setObjectName("spnBx_nmb_nodes");
        spnBx_nmb_nodes->setEnabled(true);
        spnBx_nmb_nodes->setGeometry(QRect(129, 130, 41, 22));
        spnBx_nmb_nodes->setMinimumSize(QSize(10, 0));
        spnBx_nmb_nodes->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spnBx_nmb_nodes->setMinimum(1);
        spnBx_nmb_nodes->setMaximum(999999);
        rdBtn_parallel_pop = new QRadioButton(grpBx_parallel_config);
        rdBtn_parallel_pop->setObjectName("rdBtn_parallel_pop");
        rdBtn_parallel_pop->setEnabled(true);
        rdBtn_parallel_pop->setGeometry(QRect(10, 60, 132, 20));
        rdBtn_parallel_pop->setChecked(true);
        rdBtn_parallel_search = new QRadioButton(grpBx_parallel_config);
        rdBtn_parallel_search->setObjectName("rdBtn_parallel_search");
        rdBtn_parallel_search->setEnabled(true);
        rdBtn_parallel_search->setGeometry(QRect(10, 40, 113, 20));
        rdBtn_parallel_search->setChecked(false);
        chkBx_parallel_activated = new QCheckBox(grpBx_parallel_config);
        chkBx_parallel_activated->setObjectName("chkBx_parallel_activated");
        chkBx_parallel_activated->setEnabled(true);
        chkBx_parallel_activated->setGeometry(QRect(10, 20, 81, 20));
        chkBx_parallel_activated->setChecked(false);
        chkBx_parallel_activated->setTristate(false);
        rdBtn_parallel_run = new QRadioButton(grpBx_parallel_config);
        rdBtn_parallel_run->setObjectName("rdBtn_parallel_run");
        rdBtn_parallel_run->setEnabled(true);
        rdBtn_parallel_run->setGeometry(QRect(10, 80, 132, 20));
        rdBtn_parallel_run->setChecked(false);
        grpBx_other_settings = new QGroupBox(LofMhSettings);
        grpBx_other_settings->setObjectName("grpBx_other_settings");
        grpBx_other_settings->setGeometry(QRect(18, 239, 261, 191));
        chkBx_auto_gen_stats = new QCheckBox(grpBx_other_settings);
        chkBx_auto_gen_stats->setObjectName("chkBx_auto_gen_stats");
        chkBx_auto_gen_stats->setGeometry(QRect(10, 60, 198, 20));
        chkBx_auto_gen_dir = new QCheckBox(grpBx_other_settings);
        chkBx_auto_gen_dir->setObjectName("chkBx_auto_gen_dir");
        chkBx_auto_gen_dir->setEnabled(false);
        chkBx_auto_gen_dir->setGeometry(QRect(10, 80, 226, 20));
        chkBx_auto_gen_dir->setChecked(true);
        cmbBx_opt_type_problem = new QComboBox(grpBx_other_settings);
        cmbBx_opt_type_problem->addItem(QString());
        cmbBx_opt_type_problem->addItem(QString());
        cmbBx_opt_type_problem->setObjectName("cmbBx_opt_type_problem");
        cmbBx_opt_type_problem->setGeometry(QRect(160, 30, 104, 22));
        lbl_opt_type_problem = new QLabel(grpBx_other_settings);
        lbl_opt_type_problem->setObjectName("lbl_opt_type_problem");
        lbl_opt_type_problem->setGeometry(QRect(-6, 30, 159, 16));
        spnBx_nmb_repet = new QSpinBox(grpBx_other_settings);
        spnBx_nmb_repet->setObjectName("spnBx_nmb_repet");
        spnBx_nmb_repet->setGeometry(QRect(140, 100, 40, 22));
        spnBx_nmb_repet->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spnBx_nmb_repet->setMaximum(99999999);
        lbl_nmb_repet = new QLabel(grpBx_other_settings);
        lbl_nmb_repet->setObjectName("lbl_nmb_repet");
        lbl_nmb_repet->setGeometry(QRect(31, 100, 97, 16));
        lbl_nmb_repet->setAutoFillBackground(true);
        lbl_nmb_repet->setFrameShape(QFrame::NoFrame);
        lbl_nmb_repet->setAlignment(Qt::AlignCenter);
        lbl_project_name = new QLabel(LofMhSettings);
        lbl_project_name->setObjectName("lbl_project_name");
        lbl_project_name->setGeometry(QRect(20, 70, 77, 16));
        lnEdt_project_name = new QLineEdit(LofMhSettings);
        lnEdt_project_name->setObjectName("lnEdt_project_name");
        lnEdt_project_name->setEnabled(true);
        lnEdt_project_name->setGeometry(QRect(110, 70, 113, 22));
        lnEdt_project_name->setMaxLength(80);

        retranslateUi(LofMhSettings);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, LofMhSettings, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, LofMhSettings, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(LofMhSettings);
    } // setupUi

    void retranslateUi(QDialog *LofMhSettings)
    {
        LofMhSettings->setWindowTitle(QCoreApplication::translate("LofMhSettings", "LOF-MH Settings", nullptr));
        grpBx_trace_files->setTitle(QCoreApplication::translate("LofMhSettings", "Trace Files", nullptr));
        chkBx_trace_func_entry->setText(QCoreApplication::translate("LofMhSettings", "Trace Function Entry", nullptr));
        chkBx_trace_warning->setText(QCoreApplication::translate("LofMhSettings", "Trace Warning", nullptr));
        chkBx_trace_functional->setText(QCoreApplication::translate("LofMhSettings", "Trace Functional", nullptr));
        chkBx_trace_func_leave->setText(QCoreApplication::translate("LofMhSettings", "Trace Function Leave", nullptr));
        chkBx_trace_error->setText(QCoreApplication::translate("LofMhSettings", "Trace Error", nullptr));
        chkBx_trace_debug->setText(QCoreApplication::translate("LofMhSettings", "Trace Debug", nullptr));
        grpBx_seed_config->setTitle(QCoreApplication::translate("LofMhSettings", "Seed Configuration", nullptr));
        lbl_seed_initial->setText(QCoreApplication::translate("LofMhSettings", "Seed Initial Value", nullptr));
        cmbBx_seed_initial->setItemText(0, QCoreApplication::translate("LofMhSettings", "Randomly", nullptr));
        cmbBx_seed_initial->setItemText(1, QCoreApplication::translate("LofMhSettings", "Constant", nullptr));

        lbl_seed_input->setText(QCoreApplication::translate("LofMhSettings", "Seed:", nullptr));
        lnEdt_seed->setPlaceholderText(QCoreApplication::translate("LofMhSettings", "User's Seed", nullptr));
        grpBx_parallel_config->setTitle(QCoreApplication::translate("LofMhSettings", "Parallel Configuration", nullptr));
        cmbBx_parallel_cmp->setItemText(0, QCoreApplication::translate("LofMhSettings", "THREAD_MODE", nullptr));
        cmbBx_parallel_cmp->setItemText(1, QCoreApplication::translate("LofMhSettings", "OPENMP_MODE", nullptr));
        cmbBx_parallel_cmp->setItemText(2, QCoreApplication::translate("LofMhSettings", "MPI_MODE", nullptr));
        cmbBx_parallel_cmp->setItemText(3, QCoreApplication::translate("LofMhSettings", "ROME_MODE", nullptr));
        cmbBx_parallel_cmp->setItemText(4, QCoreApplication::translate("LofMhSettings", "QPROCESS_MODE", nullptr));

        cmbBx_parallel_cmp->setCurrentText(QCoreApplication::translate("LofMhSettings", "THREAD_MODE", nullptr));
#if QT_CONFIG(tooltip)
        lbl_nbr_nodes->setToolTip(QCoreApplication::translate("LofMhSettings", "This is the detected ideal number of threads in the processor", nullptr));
#endif // QT_CONFIG(tooltip)
        lbl_nbr_nodes->setText(QCoreApplication::translate("LofMhSettings", "Number of Threads", nullptr));
#if QT_CONFIG(tooltip)
        spnBx_nmb_nodes->setToolTip(QCoreApplication::translate("LofMhSettings", "This is the detected ideal number of threads in the processor", nullptr));
#endif // QT_CONFIG(tooltip)
        rdBtn_parallel_pop->setText(QCoreApplication::translate("LofMhSettings", "Parallel Population", nullptr));
        rdBtn_parallel_search->setText(QCoreApplication::translate("LofMhSettings", "Parallel Tests", nullptr));
        chkBx_parallel_activated->setText(QCoreApplication::translate("LofMhSettings", "Activated", nullptr));
        rdBtn_parallel_run->setText(QCoreApplication::translate("LofMhSettings", "Parallel by Demand", nullptr));
        grpBx_other_settings->setTitle(QCoreApplication::translate("LofMhSettings", "Other Settings", nullptr));
        chkBx_auto_gen_stats->setText(QCoreApplication::translate("LofMhSettings", "Auto Generate Statistical Files", nullptr));
        chkBx_auto_gen_dir->setText(QCoreApplication::translate("LofMhSettings", "Create a Directory for Each Project", nullptr));
        cmbBx_opt_type_problem->setItemText(0, QCoreApplication::translate("LofMhSettings", "Minimization", nullptr));
        cmbBx_opt_type_problem->setItemText(1, QCoreApplication::translate("LofMhSettings", "Maximization", nullptr));

        lbl_opt_type_problem->setText(QCoreApplication::translate("LofMhSettings", "Optimization Type Problem:", nullptr));
        lbl_nmb_repet->setText(QCoreApplication::translate("LofMhSettings", "Number of Runs:", nullptr));
#if QT_CONFIG(tooltip)
        lbl_project_name->setToolTip(QCoreApplication::translate("LofMhSettings", "Project name", nullptr));
#endif // QT_CONFIG(tooltip)
        lbl_project_name->setText(QCoreApplication::translate("LofMhSettings", "Project Name", nullptr));
#if QT_CONFIG(tooltip)
        lnEdt_project_name->setToolTip(QCoreApplication::translate("LofMhSettings", "Project name", nullptr));
#endif // QT_CONFIG(tooltip)
        lnEdt_project_name->setPlaceholderText(QCoreApplication::translate("LofMhSettings", "Project Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LofMhSettings: public Ui_LofMhSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOFMHSETTINGS_H
