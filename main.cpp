/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Smart_Delay.cpp
 * Author: rlcancian
 * 
 * Created on 3 de Setembro de 2019, 18:34
 */

#include "Smart_Delay.h"

// you have to included need libs

// GEnSyS Simulator
#include "../../../../kernel/simulator/Simulator.h"

// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Delay.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Process.h"

Smart_Delay::Smart_Delay() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int Smart_Delay::main(int argc, char** argv) {
	Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(Util::TraceLevel::L4_warning);
	this->setDefaultTraceHandlers(genesys->getTracer());
	this->insertFakePluginsByHand(genesys);

	// create model
	Model* model = genesys->getModels()->newModel();
	PluginManager* plugins = genesys->getPlugins();
	
    Create* create = plugins->newInstance<Create>(model);
	create->setEntityTypeName("Garrafa");
	create->setTimeBetweenCreationsExpression("EXPO(1)");
	create->setTimeUnit(Util::TimeUnit::second);
	create->setEntitiesPerCreation(4);
	
	Resource* embaladora = plugins->newInstance<Resource>(model, "Embaladora");
	embaladora->setCapacity(30);

    Process* process = plugins->newInstance<Process>(model);
	process->getSeizeRequests()->insert(new SeizableItem(embaladora));
	process->setQueueableItem(new QueueableItem(plugins->newInstance<Queue>(model)));
    process->setDelayTimeUnit(Util::TimeUnit::second);
	process->setDelayExpression("NORM(5,1)");

    Dispose* dispose = plugins->newInstance<Dispose>(model);

    create->getConnections()->insert(process);
	process->getConnections()->insert(dispose);

    model->getSimulation()->setReplicationLengthTimeUnit(Util::TimeUnit::hour);
    model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->getSimulation()->setReplicationLength(24);
	model->getSimulation()->setNumberOfReplications(100);
    model->getSimulation()->setWarmUpPeriod(2);

	model->save("./models/ModelTest.gen");
	model->getSimulation()->start();
	genesys->~Simulator();
	return 0;
};

