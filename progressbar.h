#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QDialog>
#include <QFileDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QProgressBar>
#include <QPlainTextEdit>
#include <QDialogButtonBox>


//class ProgressBarDialog : public QMessageBox
class ProgressBarDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ProgressBarDialog(QString msg, QWidget *parent = nullptr);
    ~ProgressBarDialog();

    QPushButton *ok;
    QPushButton *abort;
    QPushButton *abortA;
    QPushButton *clicked;
    QMessageBox *calcMessage;

    QLabel *text;
    QLabel *projLabel;
    QLabel *repetitionLabel;
    QProgressBar *projBar;
    QProgressBar *repetitionBar;
    //QProgressBar *infBar;
    long projBarVal, projBarTotal;
    long repetitionBarVal, repetitionBarTotal;
    //long infBarVal, infBarTotal;

    QGroupBox *repetitionBox;
    QGroupBox *projBox;
    QGridLayout *boxGrid;

    QDialogButtonBox *buttonBox;

    void appendMessage(const QString& text);
    QPushButton* clickedButton();
    void closeBtn(void);
    //void infBarSetRange(long min, long max);
    void projBarSetRange(long min, long max);
    void projBarSetValue(long val);
    void projLabelSetText(QString val);
    void repetitionBarSetRange(long min, long max);
    void repetitionBarSetValue(long val);
    void repetitionLabelSetText(QString val);
    void setText(QString val);
    void testParalelismInterface(bool flag);

private:
    QFile m_logFile;

    QPlainTextEdit *messageArea;

private slots:
    void abortClicked(void) { clicked = abort; }
    void abortAClicked(void) { clicked = abortA; }
public slots:
    void update(int status);

};

#endif // PROGRESSBAR_H
