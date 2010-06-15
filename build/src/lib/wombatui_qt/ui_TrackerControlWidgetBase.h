/********************************************************************************
** Form generated from reading UI file 'TrackerControlWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKERCONTROLWIDGETBASE_H
#define UI_TRACKERCONTROLWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <wombatui_qt/widgets/PartitionEditorWidget.h>

QT_BEGIN_NAMESPACE

class Ui_TrackerControlWidgetBase
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tabRaster;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QComboBox *primitiveBox;
    QLabel *label_2;
    QComboBox *labelBox;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSlider *numVoxelsSlider;
    QLCDNumber *numVoxelsLCD;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *rasterizeButton;
    QSpacerItem *horizontalSpacer;
    QWidget *tabWeight;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QComboBox *weightBox;
    QLabel *label_5;
    QComboBox *comparisonBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *weightButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_10;
    wombat::PartitionEditorWidget *partitionWidget;
    QWidget *tabFilter;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *numberParticlesSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *numberLayersSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_7;
    QDoubleSpinBox *annealingRateSpinBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QCheckBox *stopAnnealingcheckBox;
    QSpacerItem *horizontalSpacer_8;
    QDoubleSpinBox *minAnnealingRateSpinBox;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_9;
    QDoubleSpinBox *initialBetaSpinBox;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_11;
    QComboBox *diffusionStrategyComboBox;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_12;
    QComboBox *particleGeneratorComboBox;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_13;
    QComboBox *modeSelectorComboBox;
    QCheckBox *optimumCheckBox;
    QSpacerItem *verticalSpacer_3;
    QWidget *tabMisc;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *generateMFilesCheckBox;
    QSpacerItem *horizontalSpacer_10;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *runButton;
    QPushButton *runStepButton;
    QPushButton *stopButton;
    QSpacerItem *horizontalSpacer_14;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_16;
    QPushButton *updateFilterButton;
    QCheckBox *showResultsCheckBox;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *TrackerControlWidgetBase)
    {
        if (TrackerControlWidgetBase->objectName().isEmpty())
            TrackerControlWidgetBase->setObjectName(QString::fromUtf8("TrackerControlWidgetBase"));
        TrackerControlWidgetBase->resize(553, 527);
        verticalLayout_3 = new QVBoxLayout(TrackerControlWidgetBase);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setContentsMargins(3, 3, 3, 3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(TrackerControlWidgetBase);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tabRaster = new QWidget();
        tabRaster->setObjectName(QString::fromUtf8("tabRaster"));
        verticalLayout = new QVBoxLayout(tabRaster);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(tabRaster);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        primitiveBox = new QComboBox(tabRaster);
        primitiveBox->setObjectName(QString::fromUtf8("primitiveBox"));

        gridLayout_2->addWidget(primitiveBox, 0, 1, 1, 1);

        label_2 = new QLabel(tabRaster);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        labelBox = new QComboBox(tabRaster);
        labelBox->setObjectName(QString::fromUtf8("labelBox"));

        gridLayout_2->addWidget(labelBox, 1, 1, 1, 1);

        label_3 = new QLabel(tabRaster);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        numVoxelsSlider = new QSlider(tabRaster);
        numVoxelsSlider->setObjectName(QString::fromUtf8("numVoxelsSlider"));
        numVoxelsSlider->setOrientation(Qt::Horizontal);
        numVoxelsSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout->addWidget(numVoxelsSlider);

        numVoxelsLCD = new QLCDNumber(tabRaster);
        numVoxelsLCD->setObjectName(QString::fromUtf8("numVoxelsLCD"));

        horizontalLayout->addWidget(numVoxelsLCD);


        gridLayout_2->addLayout(horizontalLayout, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 91, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rasterizeButton = new QPushButton(tabRaster);
        rasterizeButton->setObjectName(QString::fromUtf8("rasterizeButton"));

        horizontalLayout_2->addWidget(rasterizeButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabRaster, QString());
        tabWeight = new QWidget();
        tabWeight->setObjectName(QString::fromUtf8("tabWeight"));
        verticalLayout_2 = new QVBoxLayout(tabWeight);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(tabWeight);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        weightBox = new QComboBox(tabWeight);
        weightBox->setObjectName(QString::fromUtf8("weightBox"));

        gridLayout_3->addWidget(weightBox, 0, 1, 1, 1);

        label_5 = new QLabel(tabWeight);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        comparisonBox = new QComboBox(tabWeight);
        comparisonBox->setObjectName(QString::fromUtf8("comparisonBox"));

        gridLayout_3->addWidget(comparisonBox, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 160, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        weightButton = new QPushButton(tabWeight);
        weightButton->setObjectName(QString::fromUtf8("weightButton"));

        horizontalLayout_3->addWidget(weightButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabWidget->addTab(tabWeight, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_10 = new QHBoxLayout(tab);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        partitionWidget = new wombat::PartitionEditorWidget(tab);
        partitionWidget->setObjectName(QString::fromUtf8("partitionWidget"));

        horizontalLayout_10->addWidget(partitionWidget);

        tabWidget->addTab(tab, QString());
        tabFilter = new QWidget();
        tabFilter->setObjectName(QString::fromUtf8("tabFilter"));
        verticalLayout_4 = new QVBoxLayout(tabFilter);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(tabFilter);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        numberParticlesSpinBox = new QSpinBox(tabFilter);
        numberParticlesSpinBox->setObjectName(QString::fromUtf8("numberParticlesSpinBox"));
        numberParticlesSpinBox->setMinimum(1);
        numberParticlesSpinBox->setMaximum(10000);

        horizontalLayout_5->addWidget(numberParticlesSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(tabFilter);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        numberLayersSpinBox = new QSpinBox(tabFilter);
        numberLayersSpinBox->setObjectName(QString::fromUtf8("numberLayersSpinBox"));
        numberLayersSpinBox->setMinimum(1);
        numberLayersSpinBox->setMaximum(100);

        horizontalLayout_6->addWidget(numberLayersSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_9 = new QLabel(tabFilter);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_8->addWidget(label_9);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        annealingRateSpinBox = new QDoubleSpinBox(tabFilter);
        annealingRateSpinBox->setObjectName(QString::fromUtf8("annealingRateSpinBox"));
        annealingRateSpinBox->setMaximum(1);
        annealingRateSpinBox->setSingleStep(0.02);

        horizontalLayout_8->addWidget(annealingRateSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_10 = new QLabel(tabFilter);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_9->addWidget(label_10);

        stopAnnealingcheckBox = new QCheckBox(tabFilter);
        stopAnnealingcheckBox->setObjectName(QString::fromUtf8("stopAnnealingcheckBox"));

        horizontalLayout_9->addWidget(stopAnnealingcheckBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        minAnnealingRateSpinBox = new QDoubleSpinBox(tabFilter);
        minAnnealingRateSpinBox->setObjectName(QString::fromUtf8("minAnnealingRateSpinBox"));
        minAnnealingRateSpinBox->setMinimum(0);
        minAnnealingRateSpinBox->setMaximum(1);
        minAnnealingRateSpinBox->setSingleStep(0.02);

        horizontalLayout_9->addWidget(minAnnealingRateSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_11 = new QLabel(tabFilter);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_11->addWidget(label_11);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        initialBetaSpinBox = new QDoubleSpinBox(tabFilter);
        initialBetaSpinBox->setObjectName(QString::fromUtf8("initialBetaSpinBox"));
        initialBetaSpinBox->setMaximum(1000);

        horizontalLayout_11->addWidget(initialBetaSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_8 = new QLabel(tabFilter);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_13->addWidget(label_8);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);

        diffusionStrategyComboBox = new QComboBox(tabFilter);
        diffusionStrategyComboBox->setObjectName(QString::fromUtf8("diffusionStrategyComboBox"));

        horizontalLayout_13->addWidget(diffusionStrategyComboBox);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(tabFilter);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_12);

        particleGeneratorComboBox = new QComboBox(tabFilter);
        particleGeneratorComboBox->setObjectName(QString::fromUtf8("particleGeneratorComboBox"));

        horizontalLayout_14->addWidget(particleGeneratorComboBox);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(tabFilter);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_13);

        modeSelectorComboBox = new QComboBox(tabFilter);
        modeSelectorComboBox->setObjectName(QString::fromUtf8("modeSelectorComboBox"));

        horizontalLayout_15->addWidget(modeSelectorComboBox);


        verticalLayout_4->addLayout(horizontalLayout_15);

        optimumCheckBox = new QCheckBox(tabFilter);
        optimumCheckBox->setObjectName(QString::fromUtf8("optimumCheckBox"));

        verticalLayout_4->addWidget(optimumCheckBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        tabWidget->addTab(tabFilter, QString());
        tabMisc = new QWidget();
        tabMisc->setObjectName(QString::fromUtf8("tabMisc"));
        layoutWidget = new QWidget(tabMisc);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 319, 24));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        generateMFilesCheckBox = new QCheckBox(layoutWidget);
        generateMFilesCheckBox->setObjectName(QString::fromUtf8("generateMFilesCheckBox"));

        horizontalLayout_12->addWidget(generateMFilesCheckBox);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_10);

        tabWidget->addTab(tabMisc, QString());

        verticalLayout_3->addWidget(tabWidget);

        frame = new QFrame(TrackerControlWidgetBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        runButton = new QPushButton(frame);
        runButton->setObjectName(QString::fromUtf8("runButton"));

        horizontalLayout_4->addWidget(runButton);

        runStepButton = new QPushButton(frame);
        runStepButton->setObjectName(QString::fromUtf8("runStepButton"));

        horizontalLayout_4->addWidget(runStepButton);

        stopButton = new QPushButton(frame);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout_4->addWidget(stopButton);

        horizontalSpacer_14 = new QSpacerItem(251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);


        verticalLayout_3->addWidget(frame);

        frame_2 = new QFrame(TrackerControlWidgetBase);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_16 = new QHBoxLayout(frame_2);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        updateFilterButton = new QPushButton(frame_2);
        updateFilterButton->setObjectName(QString::fromUtf8("updateFilterButton"));

        horizontalLayout_16->addWidget(updateFilterButton);

        showResultsCheckBox = new QCheckBox(frame_2);
        showResultsCheckBox->setObjectName(QString::fromUtf8("showResultsCheckBox"));

        horizontalLayout_16->addWidget(showResultsCheckBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_3);


        verticalLayout_3->addWidget(frame_2);


        retranslateUi(TrackerControlWidgetBase);
        QObject::connect(numVoxelsSlider, SIGNAL(sliderMoved(int)), numVoxelsLCD, SLOT(display(int)));

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(TrackerControlWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *TrackerControlWidgetBase)
    {
        TrackerControlWidgetBase->setWindowTitle(QApplication::translate("TrackerControlWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TrackerControlWidgetBase", "primitive type:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TrackerControlWidgetBase", "voxel labeling:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TrackerControlWidgetBase", "avg. length (voxel):", 0, QApplication::UnicodeUTF8));
        rasterizeButton->setText(QApplication::translate("TrackerControlWidgetBase", "rasterize!", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabRaster), QApplication::translate("TrackerControlWidgetBase", "rasterization", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TrackerControlWidgetBase", "voxel weight generator:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TrackerControlWidgetBase", "voxel comparison algorithm:", 0, QApplication::UnicodeUTF8));
        weightButton->setText(QApplication::translate("TrackerControlWidgetBase", "calculate current weights", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabWeight), QApplication::translate("TrackerControlWidgetBase", "weighting", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("TrackerControlWidgetBase", "partitioning", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("TrackerControlWidgetBase", "number of particles", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("TrackerControlWidgetBase", "number of layers", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("TrackerControlWidgetBase", "desired annealing rate", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("TrackerControlWidgetBase", "stop at minimum annealing rate", 0, QApplication::UnicodeUTF8));
        stopAnnealingcheckBox->setText(QString());
        label_11->setText(QApplication::translate("TrackerControlWidgetBase", "initial beta", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("TrackerControlWidgetBase", "diffusion strategy", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("TrackerControlWidgetBase", "initial particle generator", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("TrackerControlWidgetBase", "mode selector", 0, QApplication::UnicodeUTF8));
        optimumCheckBox->setText(QApplication::translate("TrackerControlWidgetBase", "stop if optimum found", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFilter), QApplication::translate("TrackerControlWidgetBase", "filter", 0, QApplication::UnicodeUTF8));
        generateMFilesCheckBox->setText(QApplication::translate("TrackerControlWidgetBase", "generate Matlab Files (save particle weights)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabMisc), QApplication::translate("TrackerControlWidgetBase", "misc", 0, QApplication::UnicodeUTF8));
        runButton->setText(QApplication::translate("TrackerControlWidgetBase", "run", 0, QApplication::UnicodeUTF8));
        runStepButton->setText(QApplication::translate("TrackerControlWidgetBase", "one step", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("TrackerControlWidgetBase", "stop", 0, QApplication::UnicodeUTF8));
        updateFilterButton->setText(QApplication::translate("TrackerControlWidgetBase", "update particle filter", 0, QApplication::UnicodeUTF8));
        showResultsCheckBox->setText(QApplication::translate("TrackerControlWidgetBase", "show results", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackerControlWidgetBase: public Ui_TrackerControlWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKERCONTROLWIDGETBASE_H
