#include "TrackerControlWidget.h"
#include <wombat/basetypes.h>
#include <wombatui_qt/helpers/QWombatProject.h>
#include <wombatui_qt/helpers/QGlobalState.h>

#include <QtGui>

namespace wombat
{

    TrackerControlWidget::TrackerControlWidget(QWidget *parent) :
        QWidget(parent)
    {
        setupUi(this);
        initUi();
        readProjectData();
    }

    TrackerControlWidget::~TrackerControlWidget()
    {

    }

	void TrackerControlWidget::readProjectData()
	{
		QWombatProject *project = QGlobalState::instance()->currentProject;
		if(project == 0) return;

		QVariant primitiveType 	= project->valueMap.value("tracker/primitive_type", wombat::CylinderPrimitve);
		QVariant labelType 		= project->valueMap.value("tracker/label_type", wombat::UniformLabeling);
		QVariant avgLength 		= project->valueMap.value("tracker/avg_length", 20);
		QVariant weightType 	= project->valueMap.value("tracker/weight_type", wombat::WeightingSimple);
		QVariant compareType	= project->valueMap.value("tracker/compare_type", wombat::CompareOverlappingWithMasking);
		QVariant numParticles 	= project->valueMap.value("tracker/num_particles", 100);
		QVariant numLayers 		= project->valueMap.value("tracker/num_layers", 20);
		QVariant annealingRate 	= project->valueMap.value("tracker/annealing_rate", 0.25);
		QVariant minAnnealingRate= project->valueMap.value("tracker/min_annealing_rate", 0.1);
		QVariant intitialBeta 	= project->valueMap.value("tracker/initial_beta", 0.1);
		QVariant stopOnOptimum 	= project->valueMap.value("tracker/stop_on_optimum", false);
		QVariant generateMFiles = project->valueMap.value("tracker/generate_m_files", false);
		QVariant diffusion 		= project->valueMap.value("tracker/diffusion_strategy", CovarianceDiffusion);
		QVariant generator 		= project->valueMap.value("tracker/generator_strategy", GaussianDiffusion);
		QVariant mode 			= project->valueMap.value("tracker/optimum_strategy", PeakMode);

		diffusionStrategyComboBox->setCurrentIndex(diffusionStrategyComboBox->findData(diffusion, Qt::UserRole));
		particleGeneratorComboBox->setCurrentIndex(particleGeneratorComboBox->findData(generator, Qt::UserRole));
		modeSelectorComboBox->setCurrentIndex(modeSelectorComboBox->findData(mode, Qt::UserRole));

		primitiveBox->setCurrentIndex(primitiveBox->findData(primitiveType, Qt::UserRole));
		labelBox->setCurrentIndex(labelBox->findData(labelType, Qt::UserRole));
		numVoxelsSlider->setValue(avgLength.toInt());

		weightBox->setCurrentIndex(weightBox->findData(weightType, Qt::UserRole));
		comparisonBox->setCurrentIndex(comparisonBox->findData(compareType, Qt::UserRole));

		numberParticlesSpinBox->setValue(numParticles.toInt());
		numberLayersSpinBox->setValue(numLayers.toInt());
		annealingRateSpinBox->setValue(annealingRate.toDouble());
		minAnnealingRateSpinBox->setValue(minAnnealingRate.toDouble());
		initialBetaSpinBox->setValue(intitialBeta.toDouble());

		optimumCheckBox->setChecked(stopOnOptimum.toBool());
		generateMFilesCheckBox->setChecked(generateMFiles.toBool());
	}


	void TrackerControlWidget::writeProjectData()
	{
		QWombatProject *project = QGlobalState::instance()->currentProject;
		if(project == 0) return;

		// RASTERIZATION
		QVariant primitiveType 	= primitiveBox->itemData(primitiveBox->currentIndex(), Qt::UserRole);
		QVariant labelType 		= labelBox->itemData(labelBox->currentIndex(), Qt::UserRole);
		QVariant avgLength 		= numVoxelsSlider->value();

		// WEIGHTING
		QVariant weightType 	= weightBox->itemData(weightBox->currentIndex(), Qt::UserRole);
		QVariant compareType	= comparisonBox->itemData(comparisonBox->currentIndex(), Qt::UserRole);

		// PARTITIONING
		// TODO: partitioning data

		// FILTER
		QVariant numParticles 	= numberParticlesSpinBox->value();
		QVariant numLayers 		= numberLayersSpinBox->value();
		QVariant annealingRate 	= annealingRateSpinBox->value();
		QVariant minAnnealingRate	= minAnnealingRateSpinBox->value();
		QVariant intitialBeta 	= initialBetaSpinBox->value();
		QVariant stopOnOptimum 	= optimumCheckBox->isChecked();

		QVariant diffusion = diffusionStrategyComboBox->itemData(diffusionStrategyComboBox->currentIndex(), Qt::UserRole);
		QVariant generator = particleGeneratorComboBox->itemData(particleGeneratorComboBox->currentIndex(), Qt::UserRole);
		QVariant mode = modeSelectorComboBox->itemData(modeSelectorComboBox->currentIndex(), Qt::UserRole);

		// MISC
		QVariant generateMFiles = generateMFilesCheckBox->isChecked();


		project->valueMap.replace("tracker/primitive_type"	, primitiveType);
		project->valueMap.replace("tracker/label_type"		, labelType);
		project->valueMap.replace("tracker/avg_length"		, avgLength);

		project->valueMap.replace("tracker/weight_type", weightType);
		project->valueMap.replace("tracker/compare_type", compareType);

		project->valueMap.replace("tracker/num_particles", numParticles);
		project->valueMap.replace("tracker/num_layers", numLayers);
		project->valueMap.replace("tracker/annealing_rate", annealingRate);
		project->valueMap.replace("tracker/min_annealing_rate", minAnnealingRate);
		project->valueMap.replace("tracker/initial_beta", intitialBeta);
		project->valueMap.replace("tracker/stop_on_optimum", stopOnOptimum);
		project->valueMap.replace("tracker/diffusion_strategy", diffusion);
		project->valueMap.replace("tracker/generator_strategy", generator);
		project->valueMap.replace("tracker/optimum_strategy", mode);

		project->valueMap.replace("tracker/generate_m_files", generateMFiles);
	}

    void TrackerControlWidget::initUi()
    {
    	// ******************* rasterization tab *************************
    	primitiveBox->addItem("LinePrimitive" ,  wombat::LinePrimitive);
    	primitiveBox->addItem("CylinderPrimitve" ,  wombat::CylinderPrimitve);
    	primitiveBox->addItem("QuadricPrimitive" ,  wombat::QuadricPrimitive);
    	primitiveBox->setCurrentIndex(1);

    	labelBox->addItem("UniformLabeling", wombat::UniformLabeling);
    	labelBox->addItem("DistanceLabeling", wombat::DistanceLabeling);
    	labelBox->addItem("SquareDistanceLabeling", wombat::SquareDistanceLabeling);
    	labelBox->setCurrentIndex(0);

    	// ******************* weighting tab *************************
    	weightBox->addItem("default", WeightingSimple);

    	comparisonBox->addItem("overlapping", CompareOverlapping);
    	comparisonBox->addItem("overlapping with mask", CompareOverlappingWithMasking);
    	comparisonBox->addItem("symmetric overlapping", CompareOverlappingWithSymmetry);

    	// ******************* partitioning tab *************************

    	// ******************* filter tab *************************
    	diffusionStrategyComboBox->addItem("constant", ConstantDiffusion);
    	diffusionStrategyComboBox->addItem("alpha values", AlphaDiffusion);
    	diffusionStrategyComboBox->addItem("variance based", VarianceDiffusion);
    	diffusionStrategyComboBox->addItem("covariance based", CovarianceDiffusion);

    	particleGeneratorComboBox->addItem("gaussian w. ref. pose", GaussianDiffusion);
    	particleGeneratorComboBox->addItem("iterative (last particle set)", IterativeDiffusion);
    	particleGeneratorComboBox->addItem("random field", RandomFieldDiffusion);

    	modeSelectorComboBox->addItem("peak", PeakMode);
		modeSelectorComboBox->addItem("average", AverargeMode);
		modeSelectorComboBox->addItem("weighted average", WeightedAverageMode);
    	// ******************* misc tab *************************

    	connect(primitiveBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));
    	connect(labelBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));

    	connect(weightBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));
    	connect(comparisonBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));

    	connect(numVoxelsSlider, SIGNAL(valueChanged(int)), this, SLOT(updateProjectData()));
    	connect(weightBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));
    	connect(comparisonBox, SIGNAL(activated(int)), this, SLOT(updateProjectData()));

    	connect(numberParticlesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateProjectData()));
    	connect(numberLayersSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateProjectData()));
    	connect(annealingRateSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateProjectData()));
    	connect(minAnnealingRateSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateProjectData()));
    	connect(initialBetaSpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateProjectData()));
        connect(showResultsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateProjectData()));

        connect(rasterizeButton, SIGNAL(clicked()), this, SIGNAL(rasterizeRequested()));
        connect(weightButton, SIGNAL(clicked()), this, SIGNAL(weightingRequested()));
        connect(runButton, SIGNAL(clicked()), this, SIGNAL(runClicked()));
        connect(runStepButton, SIGNAL(clicked()), this, SIGNAL(oneStepClicked()));
        connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stopClicked()));

        connect(updateFilterButton, SIGNAL(clicked()), this, SIGNAL(updateParticleFilter()));
        connect(updateFilterButton, SIGNAL(clicked()), this, SLOT(printProjectMap()));
    }


    void TrackerControlWidget::updateProjectData()
    {
    	writeProjectData();
    	parameterChanged();

    }

    void TrackerControlWidget::printProjectMap()
    {
		QWombatProject *project = QGlobalState::instance()->currentProject;
		if(project == 0) return;

		QString message;
		for(QMultiMap<QString, QVariant>::iterator it = project->valueMap.begin();
				it != project->valueMap.end(); it++)
		{
			message.append(it.key());
			message.append(" : ");
			message.append(it.value().toString());
			message.append("\n");
		}

		QMessageBox::information(this, "values", message);
    }
}

