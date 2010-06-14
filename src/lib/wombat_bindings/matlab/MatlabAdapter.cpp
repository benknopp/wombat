#include "MatlabAdapter.h"
#include <wombat/helpers.h>

#include <sstream>
#include <iostream>
#include <iomanip>

namespace wombat
{

    std::string toMatlabString(const BodyStateVector &_vector)
    {
        std::stringstream s;
        s << "[ ";
        for(unsigned i=0; i < _vector.size(); i++)
        {
            s << _vector[i] << " ; ";
        }

        s << " ]";

        return s.str();
    }


    MatlabAdapter::MatlabAdapter()
    {
        mBufferSize = 4096;
        mBuffer = (char*) malloc(mBufferSize+1);
        mBuffer[mBufferSize] = '\0';
    }

    void MatlabAdapter::init()
    {
        initModel();
        initSegments();
        initJoints();
        initGenCoords();
        //printMap();
    }

    bool MatlabAdapter::configure(const BodyStateVector &_state, BodyConfiguration &_configuration)
    {
        std::stringstream cmd;
        std::string modelName = getModelName(0);
        cmd << "q0=";
        cmd << toMatlabString(_state);
        cmd << ";";

        cmd << "Model.States.time = 1;";
        cmd << modelName;
        cmd << " = fkin(1, q0, zeros(length(q0),1), Model);";

        //TRACE("%s", cmd.str().c_str());

        int status =engEvalString(mEngine, cmd.str().c_str());
        if(status)
        {
            Logger::criticalErrorMessage("calculating forward kinematics failed");
            return false;
        }

        cmd.clear();
        cmd << "A = reshape([";
        cmd << modelName;
        cmd << ".Body.A], 9, ";
        cmd << tree.partNodes.size();
        cmd << ");";

        cmd << "R = [";
        cmd << modelName;
        cmd << ".Body.R];";

        cmd << "P = [A; R];";

        //TRACE("%s", cmd.str().c_str());
        status =engEvalString(mEngine, cmd.str().c_str());
        if(status)
        {
            Logger::criticalErrorMessage("collecting pose information failed");
            return false;
        }

        mxArray *mxPose = 0;
        if((mxPose =engGetVariable(mEngine, "P")) == 0)
        {
            Logger::criticalErrorMessage("cant evaluate pose. sorry.");
            return false;
        }

        double* pose = mxGetPr(mxPose);


        _configuration.rotations.resize(tree.partNodes.size());
        _configuration.translations.resize(tree.partNodes.size());
        // write pose for all ridgid body parts
        for(unsigned i=0; i < tree.partNodes.size(); i++)
        {
            _configuration.rotations.at(i).transpose() <<  pose[12*i+0], pose[12*i+1], pose[12*i+2],
                pose[12*i+3], pose[12*i+4], pose[12*i+5], pose[12*i+6], pose[12*i+7], pose[12*i+8];
            _configuration.translations.at(i) << pose[12*i+9], pose[12*i+10], pose[12*i+11];
        }

        return (status == 0);
    }


    //bool MatlabAdapter::configure(const std::vector<BodyState> &_state, std::vector<BodyConfiguration> &_configuration)
    bool MatlabAdapter::configure(const std::vector<BodyStateVector> &, std::vector<BodyConfiguration> &)
    {
        bool success = true;
        // TODO: implement

        return success;
    }



    void MatlabAdapter::initModel()
    {
        mEngine = engOpen(mEngineArgs.size() ?  mEngineArgs.toStdString().c_str(): "\0");
        engOutputBuffer(mEngine, mBuffer, mBufferSize);

        if(mEngine == 0)
        {
            TRACE("warning: connection failed!");
        }

        const QString modelDir = "cd '" +  mWorkingDir + "/Projects/MMM" + "'";
        TRACE("working dir is: %s", modelDir.toStdString().c_str());

        int retVal = 0;
        retVal += engEvalString(mEngine, modelDir.toStdString().c_str());
        retVal += engEvalString(mEngine, "initializeModelAdapter");

        // *************** read out dofs ****************************
        retVal += engEvalString(mEngine, "numDOFs = length(Model.q0);");
        mxArray* mxNumDOFs = 0;

        if((mxNumDOFs =engGetVariable(mEngine, "numDOFs")) == 0)
        {
            TRACE("WARNING: can't evaluate degrees of freedom");
            mxDestroyArray(mxNumDOFs);
            return;
        }

        tree.dofs.resize(static_cast<int>(mxGetPr(mxNumDOFs)[0]));
        TRACE("model has %lu degrees of freedom", tree.dofs.size());

        // ************** read out segment / joint information *************
        retVal += engEvalString(mEngine, "numSegs = size(Model.Body,2);");
        retVal += engEvalString(mEngine, "numJoints = size(Model.Joint,2);");
        mxArray *mxNumSegs = 0, *mxNumJoints = 0;

        if((mxNumSegs =engGetVariable(mEngine, "numSegs")) == 0) {
            TRACE("WARNING: can't evaluate number of segments");
            mxDestroyArray(mxNumSegs);
            return;
        }

        if((mxNumJoints =engGetVariable(mEngine, "numJoints")) == 0) {
            TRACE("WARNING: can't evaluate number of joints");
            mxDestroyArray(mxNumJoints);
            return;
        }
        tree.jointNodes.resize(static_cast<int>(mxGetPr(mxNumJoints)[0]));
        tree.partNodes.resize(static_cast<int>(mxGetPr(mxNumSegs)[0]));
        //model.numJoints = static_cast<int>(mxGetPr(mxNumJoints)[0]);
        //model.numSegments = static_cast<int>(mxGetPr(mxNumSegs)[0]);

        mxDestroyArray(mxNumDOFs);
        mxDestroyArray(mxNumJoints);
        mxDestroyArray(mxNumSegs);

    }

    void MatlabAdapter::initSegments()
    {
        engEvalString(mEngine, "names={Model.Body.Name}'");
        mxArray *mxNames = engGetVariable(mEngine, "names");
        mxArray *mxCell = 0;

        for(unsigned i=0; i < tree.partNodes.size(); i++)
        {
            mxCell = mxGetCell(mxNames, i);
            char* name = mxArrayToString(mxCell);
            tree.partNodes.at(i).name = name;
            tree.partNodes.at(i).parent = 0;
        }

        mxDestroyArray(mxNames);

    }

    void MatlabAdapter::initJoints()
    {
        engEvalString(mEngine, "joints = {Model.Joint.Name, Model.Joint.Bodies}");

        QString query = "jointParentIds = reshape([Model.Joint.BodiesNr],2," +
                QString::number(tree.jointNodes.size()) +  ")";
        engEvalString(mEngine, query.toStdString().c_str());

        engEvalString(mEngine, "jointDofs = [Model.Joint.nq]");
        engEvalString(mEngine, "cjoint = {Model.Joint.qNr}");
        // array of size 1 x dof, contains the degrees of freedom in correct order
        engEvalString(mEngine, "jointIds = cell2mat(cjoint(:))");

        mxArray *mxJoints = engGetVariable(mEngine, "joints");
        //mxArray *mxJointParentIds = engGetVariable(mEngine, "jointParentIds");
        mxArray *mxJointDofs = engGetVariable(mEngine, "jointDofs");
        mxArray *mxJointIds = engGetVariable(mEngine, "jointIds");
        mxArray *mxCell = 0;

        // double *jointParentIds = mxGetPr(mxJointParentIds);
        // TODO: use jointParentIds

        double *jointDofs = mxGetPr(mxJointDofs);
        double *jointIds = mxGetPr(mxJointIds);
        int count=0;

        for(unsigned i=0; i < tree.jointNodes.size(); i++)
        {
            tree.jointNodes.at(i).parent = 0;

            mxCell = mxGetCell(mxJoints,i);
            char* name = mxArrayToString(mxCell);
            tree.jointNodes.at(i).name = name;

            //  find parents
            mxCell = mxGetCell(mxJoints,i+tree.jointNodes.size());
            char* jointDeps = mxArrayToString(mxCell);
            std::string jd = jointDeps;
            std::vector<std::string> names =  splitString(jd, " ");

            BodyPartNode* pre = findBodyPart(tree.partNodes, names[0]);
            BodyPartNode* post = findBodyPart(tree.partNodes, names[1]);

            if(pre)
            {
                tree.jointNodes.at(i).parent = pre;
                pre->children.push_back(&(tree.jointNodes.at(i)));
            } else
            {
                std::cout << name << "has no parent";
            }

            if(post)
            {
                tree.jointNodes.at(i).children.push_back(post);
                post->parent = &(tree.jointNodes.at(i));
            } else
            {
                std::cout << name << "has no childs";
            }


            tree.jointNodes.at(i).indices.resize(jointDofs[i]);

            for(unsigned k=0; k < tree.jointNodes.at(i).indices.size(); k++)
            {
                unsigned dof = jointIds[count++];
                tree.jointNodes.at(i).indices.at(k) = dof-1; // Matlab indices start at 1 !!!
            }
        } // end for

        tree.findRoot();
        mxDestroyArray(mxJoints);
        //mxDestroyArray(mxJointParentIds);
        mxDestroyArray(mxJointDofs);
        mxDestroyArray(mxJointIds);
//        mxDestroyArray(mxCell);
    }


    void MatlabAdapter::initGenCoords()
    {
        engEvalString(mEngine, "coordNames = {Model.GenCoor.Name}");
        engEvalString(mEngine, "coordRanges = [ Model.lb; Model.ub]");

        mxArray *mxNames = engGetVariable(mEngine, "coordNames");
        mxArray *mxRanges = engGetVariable(mEngine, "coordRanges");

        double* values = mxGetPr(mxRanges);
        double min, max, stepSize;

        unsigned size = tree.dofs.size();
        for(unsigned i=0; i < size; i++)
        {
            mxArray *mxCell = mxGetCell(mxNames, i);
            char* name = mxArrayToString(mxCell);

            min = values[i];
            max = values[i+size];
            stepSize = (max-min) / 100.0;
            if(stepSize > 0.05) stepSize = 0.05;

            DegreeOfFreedom dof(min, max, 0, stepSize);
            dof.name = name;

            if(dof.name.size() > 6)
            {
            	if(dof.name.substr(0,6).compare("root_r") == 0)
            	{
            		TRACE("limited");
            		dof.rangeType = DegreeOfFreedom::limitedRange;
            		dof.min = -5;
            		dof.max = 5;
            	} else
            	{
            		TRACE("circular");
            		dof.rangeType = DegreeOfFreedom::circularRange;
            		dof.min = - M_PI;
            		dof.max = + M_PI;
            	}
            }

            tree.dofs.at(i)=dof;
            TRACE("generalized coordinat %s @ %i : min %f to %f", name, i, min, max);
        }


        mxDestroyArray(mxNames);
        mxDestroyArray(mxRanges);
    }


    void MatlabAdapter::printMap()
    {
        std::cout << std::right << std::setw(20) << "name";
        std::cout << std::right << std::setw(20) << "prename";
        std::cout << std::right << std::setw(20) << "postname";
        std::cout << std::right << std::setw(10) << "numDofs" << std::endl << std::endl;


        for(std::vector<BodyJointNode>::const_iterator it = tree.jointNodes.begin();
            it != tree.jointNodes.end(); it++)
        {
            std::string name = it->name;
            std::string prename = (it->parent) ? it->parent->name : "none";
            std::string postname = (it->children.size()) ? it->children[0]->name : "none";
            unsigned numDofs = it->indices.size();

            std::cout << std::right << std::setw(20) << name;
            std::cout << std::right << std::setw(20) << prename;
            std::cout << std::right << std::setw(20) << postname;
            std::cout << std::right << std::setw(10) << numDofs << std::endl;
        }
        std::cout << "================================================================================" << std::endl;
    }

    std::string& MatlabAdapter::getModelName(unsigned _index)
    {
        if(_index >= mModelNames.size())
        {
            for(unsigned i=0; i <= _index; i++)
            {
                std::string name = "Model_" + toString(i);
                mModelNames.push_back(name);
            }
        }
        return mModelNames.at(_index);
    }


}

