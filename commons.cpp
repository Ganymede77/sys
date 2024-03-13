#include <cmath>
#include <iostream>
#include <QFileInfo>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QXmlStreamReader>
#include "commons.h"

QVariantList GetMultipleAttFromMap(QMap <QString, QVariant> map, QString tag){
    QVariantList data;
    for(int i = 0; i < map.size(); ++i)
    {
        if(map.value(tag + QString::number(i)).isValid())
            data.append(map.value(tag + QString::number(i)));
        else
            break;
    }
    return data;
}

QString GenerateWidgetListInputInfo(WidgetListInput &widget)
{
    QString info = "\n";
    int valuesQtd = widget.GetValues().size();
    for(int i = 0; i < valuesQtd; ++i)
        info += "      \u21B3Value" + QString::number(i) + ": " + widget.GetValues().at(i).toString() + "\n";

    return info;
}

QString GenerateStepInfo(QString start, QString stop, QString step)
{
    QString info = "\n";
    double startD = start.toDouble();
    double stopD = stop.toDouble();
    double stepD = step.toDouble();

    int valuesQtd = 0;
    if(valuesQtd > 0)
        valuesQtd = int((stopD - startD)/stepD);

    for(int i = 0; i <= valuesQtd; ++i)
    {
        info += "      \u21B3Value" + QString::number(i) + ": " + QString::number(startD) + "\n";
        startD += stepD;
    }

    return info;
}

QVariantList CalculateStepList(QString start, QString stop, QString step)
{
    double startD = start.toDouble();
    double stopD = stop.toDouble();
    double stepD = step.toDouble();

    QVariantList values;
    //values.append(startD);

    int nmbSteps = 0;
    if(stepD > 0)
        nmbSteps = int((stopD - startD)/stepD);

    for(int i = 0; i <= nmbSteps; ++i)
    {
        values.append(startD);
        startD += stepD;
    }

    if((startD + stepD) > stopD)
        values.append(stopD);

    /*while(startD < stopD)
    {
        if((startD + stepD) > stopD)
        {
            values.append(stopD);
            break;
        }
        else
        {
            startD += stepD;
            values.append(startD);
        }
    }*/

    return values;
}

QString GenerateRandomChar(int leng)
{
    QString c = "";
    QString alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "abcdefghijklmnopqrstuvwxyz";

    for(int i = 0; i < leng; ++i)
        //c += alphanum[unsigned(rand()) % (sizeof(alphanum) - 1)];
        c += alphanum[QRandomGenerator::global()->bounded(alphanum.size()-1)];

    return c;
}

QMap<int, QMap<QString, QVariant>> LoadMultipleMhAttFromFile(QFile *f, QString key, QString tag, QString att)
{
    //this is a convention function made to simplify the code on the load system
    //it gets a file, key, tag and att to read from a xml file and assign the multiple value inputs to a map
    //the map is returned and can be united with another one, like in the load system
    f->open(QFile::ReadOnly);

    QXmlStreamReader reader(f->readAll());
    QMap<int, QMap<QString, QVariant>> fullMap;

    f->close();
    int pos = 0;
    while(!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            if (reader.name() == tag)
            {
                bool tagEnded = false;
                bool found = false;
                int k = 0;
                QMap<QString, QVariant> map;
                QStringList readerStringAtts;
                QXmlStreamAttributes readerAtts = reader.attributes();

                for(int a = 0; a < readerAtts.size(); ++a)
                    readerStringAtts.append(readerAtts.at(a).name().toString());

                while(!tagEnded)
                {
                    QString expected = att + QString::number(k);
                    if(readerStringAtts.contains(expected))
                    {
                        for(int y = 0; y < readerStringAtts.size(); ++y)
                        {
                            if(readerStringAtts.at(y) == expected)
                            {
                                found = true;
                                map.insert(key + QString::number(k), readerAtts.at(y).value().toString());
                            }
                        }

                        k++;
                    }
                    else
                        tagEnded = true;
                }
                if(found)
                {
                    fullMap.insert(pos, map);
                    pos++;
                }
            }
        }
    }

    return fullMap;
}

QVariantList GetXmlAttribute(QFile *file, QString tag, QString att)
{
    //Get the value of an attribute on a tag, returning it as a list of found values
    if(!file->isOpen())
        file->open(QFile::ReadOnly);
    QFileInfo fileInfo(*file);
    if(!file->isOpen()) {
        //asserts the file was encountered
        if(file->fileName() == "./UI/GeneralConfigurationModel.xml") {
            QMessageBox msgBox(QMessageBox::Critical, "LOF-MH", "<i>/UI/GeneralConfigurationModel.xml</i> is missing or corrupted! LOF System cannot proceed.", QMessageBox::Close);
            msgBox.exec();
            exit(EXIT_FAILURE);
        } else if(file->fileName() != "") {
            QMessageBox msgBox(QMessageBox::Information, "LOF-MH", "<i>"+fileInfo.fileName()+"</i> could not be read! Please verify if the file has the correct extension.", QMessageBox::Ok);
            msgBox.exec();
        }
    }

    QXmlStreamReader reader(file->readAll());
    QVariantList fndAtt;
    file->close();

    while(!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == tag) {
                for(int i = 0; i < reader.attributes().size(); ++i) {
                    if(reader.attributes().at(i).name().toString() == att) {
                        fndAtt.append( reader.attributes().value(att).toString() );
                        break;
                    }
                }
            }
        }
    }
    return fndAtt;
}

double GetXmlDoubleAttributeAt(QFile *xmlFile, QString tag, QString att, int position)
{
    QVariantList qa = GetXmlAttribute(xmlFile, tag, att);
    if(qa.size()-1 >= position)
        return qa.at(position).toDouble();
    else
        return 0.0;
}

int GetXmlIntAttributeAt(QFile *xmlFile, QString tag, QString att, int position)
{
    QVariantList qa = GetXmlAttribute(xmlFile, tag, att);
    if(qa.size()-1 >= position)
        return qa.at(position).toInt();
    else
        return 0;
}

QString GetXmlStringAttributeAt(QFile *xmlFile, QString tag, QString att, int position)
{
    QVariantList qa = GetXmlAttribute(xmlFile, tag, att);
    if(qa.size()-1 >= position)
        return qa.at(position).toString();
    else
        return "";
}

QList<QMap<QString, QString>> GetXmlTag(QFile *file, QString tag)
{
    //Get the value of an attribute on a tag, returning it as a list of found values
    if(!file->isOpen())
        file->open(QFile::ReadOnly);
    QFileInfo fileInfo(*file);

    if(!file->isOpen())
    {
        //asserts the file was encountered
        if(file->fileName() == "./UI/GeneralConfigurationModel.xml")
        {
            QMessageBox msgBox(QMessageBox::Critical, "LOF-MH", "<i>/UI/GeneralConfigurationModel.xml</i> is missing or corrupted! LOF System cannot proceed.", QMessageBox::Close);
            msgBox.exec();
            exit(EXIT_FAILURE);
        }
        else if(file->fileName() != "")
        {
            QMessageBox msgBox(QMessageBox::Information, "LOF-MH", "<i>"+fileInfo.fileName()+"</i> could not be read! Please verify if the file has the correct extension.", QMessageBox::Ok);
            msgBox.exec();
        }
    }

    QXmlStreamReader reader(file->readAll());
    QList<QMap <QString, QString>> allTags;
    QMap <QString, QString> allAtts;

    file->close();
    while(!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            if (reader.name() == tag)
            {
                for(int i = 0; i < reader.attributes().size(); ++i)
                    allAtts.insert(reader.attributes().at(i).name().toString(), reader.attributes().at(i).value().toString());

                allTags.append(allAtts);
            }
        }
    }
    return allTags;
}

QString GetXmlTextValue(QFile *file, QString tag)
{
    //Get the value of an attribute on a tag, returning it as a list of found values
    if(!file->isOpen())
        file->open(QFile::ReadOnly);

    QXmlStreamReader reader(file->readAll());
    QString value;

    file->close();
    while(!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            if (reader.name() == tag)
            {
                value = reader.readElementText();
            }
        }
    }

    return value;
}


double RoundDecimals(double number)
{
    return static_cast<double>(floor(number * 1e3)) / 1e3;
}


std::vector<std::string> split(const std::string& s, char seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}
