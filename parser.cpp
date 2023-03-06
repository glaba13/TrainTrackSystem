#include "parser.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QDebug>


//EXAMPLE

/*
  <segment id="1">
    <link ref="2"/>
  </segment>
  <segment id="2">
    <link ref="3"/>
  </segment>
  <segment id="3">
    <link ref="1"/>
  </segment>


*/

/*
 * Parses xml config file and if succesful serilized inside the trackGraph and draws on display
 */

void ParseConfig(QString filename,  TrackGUI &gui, TrackGraph &tg, vector<Train> &trains)
{
    QFile *xmlFile = new QFile(filename);
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No such file";
        return;
    }
    QXmlStreamReader *xmlReader = new QXmlStreamReader(xmlFile);

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element

        QXmlStreamReader::TokenType token = xmlReader->readNext();
        qDebug() << "Token " << token << xmlReader->name();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {

            if(xmlReader->name() == "segment") {
                int newSegment = xmlReader->attributes().value("id").toString().toInt();
                qDebug() << "newSegment: " << newSegment;

                gui.AddNode(newSegment);
                tg.addSegment(newSegment);
                if(xmlReader->attributes().hasAttribute("x") && xmlReader->attributes().hasAttribute("y")){
                    int x = xmlReader->attributes().value("x").toString().toInt();
                    int y = xmlReader->attributes().value("y").toString().toInt();
                    gui.SetNodeXY(newSegment, x, y);

                }
                while(xmlReader->readNextStartElement()){
                    if(xmlReader->name() == "link"){
                        int to = xmlReader->attributes().value("id").toString().toInt();
                        //TODO
                        qDebug() << "TO: " << to;
                        tg.addEdge(newSegment, to);
                        gui.AddConnection(newSegment, to);
                    }
                    xmlReader->readNextStartElement();
                }

                continue;
            }

            if(xmlReader->name() == "train") {
                int from = xmlReader->attributes().value("from").toString().toInt();
                int to = xmlReader->attributes().value("to").toString().toInt();
                qDebug() << "Adding train" << from << to;
                bool dir = true;
                if(xmlReader->attributes().hasAttribute("dir")) {
                    dir = xmlReader->attributes().value("dir").toString().toInt();
                }
                trains.push_back(Train(from, to, dir));
            }
        }
    }


    //close reader and flush file
    xmlReader->clear();
    xmlFile->close();

}
