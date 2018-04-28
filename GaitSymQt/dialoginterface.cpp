#include "dialoginterface.h"
#include "ui_dialoginterface.h"

#include <QColorDialog>

#include <typeinfo>
#include <iostream>

#include <ode/ode.h>

#include <Simulation.h>
#include <Environment.h>
#include <Body.h>
#include <Joint.h>
#include <Geom.h>
#include <Muscle.h>
#include <CylinderWrapStrap.h>
#include <TwoCylinderWrapStrap.h>
#include <Contact.h>
#include <Reporter.h>

// Simulation global
extern Simulation *gSimulation;


DialogInterface::DialogInterface(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogInterface)
{
    m_ui->setupUi(this);
}

DialogInterface::~DialogInterface()
{
    delete m_ui;
}

void DialogInterface::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogInterface::setColours()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    m_ui->pushButtonEnvironmentColour->setStyleSheet(COLOUR_STYLE.arg(m_EnvironmentColour.name()).arg(getIdealTextColour(m_EnvironmentColour).name()).arg(getAlphaColourHint(m_EnvironmentColour).name()));
    m_ui->pushButtonBodyColour->setStyleSheet(COLOUR_STYLE.arg(m_BodyColour.name()).arg(getIdealTextColour(m_BodyColour).name()).arg(getAlphaColourHint(m_BodyColour).name()));
    m_ui->pushButtonJointColour->setStyleSheet(COLOUR_STYLE.arg(m_JointColour.name()).arg(getIdealTextColour(m_JointColour).name()).arg(getAlphaColourHint(m_JointColour).name()));
    m_ui->pushButtonGeomColour->setStyleSheet(COLOUR_STYLE.arg(m_GeomColour.name()).arg(getIdealTextColour(m_GeomColour).name()).arg(getAlphaColourHint(m_GeomColour).name()));
    m_ui->pushButtonGeomForceColour->setStyleSheet(COLOUR_STYLE.arg(m_GeomForceColour.name()).arg(getIdealTextColour(m_GeomForceColour).name()).arg(getAlphaColourHint(m_GeomForceColour).name()));
    m_ui->pushButtonStrapColour->setStyleSheet(COLOUR_STYLE.arg(m_StrapColour.name()).arg(getIdealTextColour(m_StrapColour).name()).arg(getAlphaColourHint(m_StrapColour).name()));
    m_ui->pushButtonStrapForceColour->setStyleSheet(COLOUR_STYLE.arg(m_StrapForceColour.name()).arg(getIdealTextColour(m_StrapForceColour).name()).arg(getAlphaColourHint(m_StrapForceColour).name()));
    m_ui->pushButtonStrapCylinderColour->setStyleSheet(COLOUR_STYLE.arg(m_StrapCylinderColour.name()).arg(getIdealTextColour(m_StrapCylinderColour).name()).arg(getAlphaColourHint(m_StrapCylinderColour).name()));
    m_ui->pushButtonReporterColour->setStyleSheet(COLOUR_STYLE.arg(m_ReporterColour.name()).arg(getIdealTextColour(m_ReporterColour).name()).arg(getAlphaColourHint(m_ReporterColour).name()));

}

void DialogInterface::colourEnvironment()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_EnvironmentColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonEnvironmentColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_EnvironmentColour = colour;

        gSimulation->GetEnvironment()->SetColour(m_EnvironmentColour.redF(), m_EnvironmentColour.greenF(), m_EnvironmentColour.blueF(), m_EnvironmentColour.alphaF());
        gSimulation->GetInterface()->EnvironmentColour.SetColour(m_EnvironmentColour.redF(), m_EnvironmentColour.greenF(), m_EnvironmentColour.blueF(), m_EnvironmentColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourBody()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_BodyColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonBodyColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_BodyColour = colour;

        std::map<std::string, Body *> *bodyList = gSimulation->GetBodyList();
        std::map<std::string, Body *>::const_iterator bodyIter;
        for (bodyIter = bodyList->begin(); bodyIter != bodyList->end(); bodyIter++) bodyIter->second->SetColour(m_BodyColour.redF(), m_BodyColour.greenF(), m_BodyColour.blueF(), m_BodyColour.alphaF());
        gSimulation->GetInterface()->BodyColour.SetColour(m_BodyColour.redF(), m_BodyColour.greenF(), m_BodyColour.blueF(), m_BodyColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourJoint()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_JointColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonJointColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_JointColour = colour;

        std::map<std::string, Joint *> *jointList = gSimulation->GetJointList();
        std::map<std::string, Joint *>::const_iterator jointIter;
        for (jointIter = jointList->begin(); jointIter != jointList->end(); jointIter++) jointIter->second->SetColour(m_JointColour.redF(), m_JointColour.greenF(), m_JointColour.blueF(), m_JointColour.alphaF());
        gSimulation->GetInterface()->JointColour.SetColour(m_JointColour.redF(), m_JointColour.greenF(), m_JointColour.blueF(), m_JointColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourGeom()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_GeomColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonGeomColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_GeomColour = colour;

        std::map<std::string, Geom *> *geomList = gSimulation->GetGeomList();
        std::map<std::string, Geom *>::const_iterator geomIter;
        for (geomIter = geomList->begin(); geomIter != geomList->end(); geomIter++) geomIter->second->SetColour(m_GeomColour.redF(), m_GeomColour.greenF(), m_GeomColour.blueF(), m_GeomColour.alphaF());
        gSimulation->GetInterface()->GeomColour.SetColour(m_GeomColour.redF(), m_GeomColour.greenF(), m_GeomColour.blueF(), m_GeomColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourGeomForce()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_GeomForceColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonGeomForceColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_GeomForceColour = colour;

        std::vector<Contact *> *contactList = gSimulation->GetContactList();
        for (unsigned int c = 0; c < contactList->size(); c++) (*contactList)[c]->SetColour(m_GeomForceColour.redF(), m_GeomForceColour.greenF(), m_GeomForceColour.blueF(), m_GeomForceColour.alphaF());
        gSimulation->GetInterface()->GeomForceColour.SetColour(m_GeomColour.redF(), m_GeomColour.greenF(), m_GeomColour.blueF(), m_GeomColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourStrap()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_StrapColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonStrapColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_StrapColour = colour;

        std::map<std::string, Muscle *> *muscleList = gSimulation->GetMuscleList();
        std::map<std::string, Muscle *>::const_iterator muscleIter;
        for (muscleIter = muscleList->begin(); muscleIter != muscleList->end(); muscleIter++)
        {
            muscleIter->second->GetStrap()->SetColour(m_StrapColour.redF(), m_StrapColour.greenF(), m_StrapColour.blueF(), m_StrapColour.alphaF());
            muscleIter->second->GetStrap()->SetLastDrawTime(-1);
        }
        gSimulation->GetInterface()->StrapColour.SetColour(m_StrapColour.redF(), m_StrapColour.greenF(), m_StrapColour.blueF(), m_StrapColour.alphaF());
        parentWidget()->update();
    }
}


void DialogInterface::colourStrapForce()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_StrapForceColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonStrapForceColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_StrapForceColour = colour;

        gSimulation->GetInterface()->StrapForceColour.SetColour(m_StrapForceColour.redF(), m_StrapForceColour.greenF(), m_StrapForceColour.blueF(), m_StrapForceColour.alphaF());
        std::map<std::string, Muscle *> *muscleList = gSimulation->GetMuscleList();
        std::map<std::string, Muscle *>::const_iterator muscleIter;
        for (muscleIter = muscleList->begin(); muscleIter != muscleList->end(); muscleIter++)
        {
            muscleIter->second->GetStrap()->SetForceColour(gSimulation->GetInterface()->StrapForceColour);
            muscleIter->second->GetStrap()->SetLastDrawTime(-1);
        }
        parentWidget()->update();
    }
}


void DialogInterface::colourStrapCylinder()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_StrapCylinderColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonStrapCylinderColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_StrapCylinderColour = colour;

        gSimulation->GetInterface()->StrapCylinderColour.SetColour(m_StrapCylinderColour.redF(), m_StrapCylinderColour.greenF(), m_StrapCylinderColour.blueF(), m_StrapCylinderColour.alphaF());
        std::map<std::string, Muscle *> *muscleList = gSimulation->GetMuscleList();
        std::map<std::string, Muscle *>::const_iterator muscleIter;
        for (muscleIter = muscleList->begin(); muscleIter != muscleList->end(); muscleIter++)
        {
            CylinderWrapStrap *cylinderWrapStrap = dynamic_cast<CylinderWrapStrap *>(muscleIter->second->GetStrap());
            if (cylinderWrapStrap)
            {
                cylinderWrapStrap->SetCylinderColour(gSimulation->GetInterface()->StrapCylinderColour);
                cylinderWrapStrap->SetLastDrawTime(-1);
            }
            else
            {
                TwoCylinderWrapStrap *twoCylinderWrapStrap = dynamic_cast<TwoCylinderWrapStrap *>(muscleIter->second->GetStrap());
                if (twoCylinderWrapStrap)
                {
                    twoCylinderWrapStrap->SetCylinderColour(gSimulation->GetInterface()->StrapCylinderColour);
                    twoCylinderWrapStrap->SetLastDrawTime(-1);
                }
            }
        }
        parentWidget()->update();
    }
}

void DialogInterface::colourReporter()
{
    const QString COLOUR_STYLE("QPushButton { background-color : %1; color : %2; border: 4px solid %3; }");

    QColor colour;
    colour = QColorDialog::getColor(m_ReporterColour, this, "Select Color", QColorDialog::ShowAlphaChannel);
    if (colour.isValid())
    {
        m_ui->pushButtonReporterColour->setStyleSheet(COLOUR_STYLE.arg(colour.name()).arg(getIdealTextColour(colour).name()).arg(getAlphaColourHint(colour).name()));
        m_ReporterColour = colour;

        std::map<std::string, Reporter *> *reporterList = gSimulation->GetReporterList();
        std::map<std::string, Reporter *>::const_iterator reporterIter;
        for (reporterIter = reporterList->begin(); reporterIter != reporterList->end(); reporterIter++) reporterIter->second->SetColour(m_ReporterColour.redF(), m_ReporterColour.greenF(), m_ReporterColour.blueF(), m_ReporterColour.alphaF());
        gSimulation->GetInterface()->ReporterColour.SetColour(m_ReporterColour.redF(), m_ReporterColour.greenF(), m_ReporterColour.blueF(), m_ReporterColour.alphaF());
        parentWidget()->update();
    }
}

// return an ideal label colour, based on the given background colour.
// Based on http://www.codeproject.com/cs/media/IdealTextColor.asp
QColor DialogInterface::getIdealTextColour(const QColor& rBackgroundColour)
{
    const int THRESHOLD = 105;
    int BackgroundDelta = (rBackgroundColour.red() * 0.299) + (rBackgroundColour.green() * 0.587) + (rBackgroundColour.blue() * 0.114);
    return QColor((255- BackgroundDelta < THRESHOLD) ? Qt::black : Qt::white);
}

QColor DialogInterface::getAlphaColourHint(const QColor& colour)
{
    // (source × Blend.SourceAlpha) + (background × Blend.InvSourceAlpha)
    QColor background;
    background.setRgbF(1.0, 1.0, 1.0);
    QColor hint;
    hint.setRedF((colour.redF() * colour.alphaF()) + (background.redF() * (1 - colour.alphaF())));
    hint.setGreenF((colour.greenF() * colour.alphaF()) + (background.greenF() * (1 - colour.alphaF())));
    hint.setBlueF((colour.blueF() * colour.alphaF()) + (background.blueF() * (1 - colour.alphaF())));
    return hint;
}

