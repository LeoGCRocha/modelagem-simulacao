#include "Water.h"
// Geneysys Simulator
#include "../../../../kernel/simulator/Simulator.h"
// Model Components
#include "../../../../plugins/components/Create.h"
#include "../../../../plugins/components/Delay.h"
#include "../../../../plugins/components/Dispose.h"
#include "../../../../plugins/components/Seize.h"
#include "../../../../plugins/components/Release.h"
// Model data definitions
#include "../../../../kernel/simulator/ModelDataManager.h"
#include "../../../../plugins/data/Set.h"

// int Smart_AssignWriteSeizes::main(int argc, char** argv) {

Water::Water() {
}

int Water::main(int argc, char** argv) {
    Simulator* genesys = new Simulator();
	genesys->getTracer()->setTraceLevel(Util::TraceLevel::L4_warning);
	this->setDefaultTraceHandlers(genesys->getTracer());
	this->insertFakePluginsByHand(genesys);
    // create model
    Model* model = genesys->getModels()->newModel();
	PluginManager* plugins = genesys->getPlugins();
    // create
	Create* create1 = plugins->newInstance<Create>(model);
    create1->setEntityTypeName("Entity 1");
    create1->setTimeBetweenCreationsExpression("EXPO(1)");
    create1->setTimeUnit(Util::TimeUnit::second);
    create1->setEntitiesPerCreation(4);
    // SeizeDelayRelease
    Resource* machine1 = plugins->newInstance<Resource>(model); // water bootle
    machine1->setCapacity(30);
    Queue* queueSeize1 = plugins->newInstance<Queue>(model);
    queueSeize1->setOrderRule(Queue::OrderRule::FIFO);
    Seize* seize1 = plugins->newInstance<Seize>(model);
    seize1->getSeizeRequests()->insert(new SeizableItem(machine1));
    seize1->setQueueableItem(new QueueableItem(model, "Seize_1.Queue"));
    Delay* delay1 = plugins->newInstance<Delay>(model);
    delay1->setDelayExpression("norm(5, 1)");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    Release* release1 = plugins->newInstance<Release>(model);
    release1->getReleaseRequests()->insert(new SeizableItem(machine1));
    Dispose* dispose1 = plugins->newInstance<Dispose>(model);
    create1->getConnections()->insert(seize1);
    seize1->getConnections()->insert(release1);
    release1->getConnections()->insert(delay1);
    delay1->getConnections()->insert(dispose1);

    
    model->getSimulation()->setReplicationLengthTimeUnit(Util::TimeUnit::hour);
    model->getSimulation()->setReplicationReportBaseTimeUnit(Util::TimeUnit::hour);
    model->getSimulation()->setReplicationLength(24);
	model->getSimulation()->setNumberOfReplications(100);
    model->getSimulation()->setWarmUpPeriod(2);

	model->save("./models/ModelTest.gen");
	model->getSimulation()->start();
	genesys->~Simulator();
    
    return 0;
}   
