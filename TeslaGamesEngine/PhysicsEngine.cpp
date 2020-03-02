#include "PhysicsEngine.h"
#include <ctype.h>
#include <iostream>

#include "../include/PhysX/PxPhysicsAPI.h"


#include "../include/PhysX/vehicle/PxVehicleUtil.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleSceneQuery.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleFilterShader.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleTireFriction.h"
#include "../TeslaGamesEngine/snippetvehiclecommon/SnippetVehicleCreate.h"

#include "../TeslaGamesEngine/snippetcommon/SnippetPrint.h"
#include "../TeslaGamesEngine/snippetcommon/SnippetPVD.h"
#include "../TeslaGamesEngine/snippetutils/SnippetUtils.h"


using namespace physx;
using namespace snippetvehicle;



PhysicsEngine::PhysicsEngine() {
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	//set physics
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);


	//set scene
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	//cpu worker thread setup and add to sceneDesc
	PxU32 numWorkers = 1;
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = VehicleFilterShader;

	gScene = gPhysics->createScene(sceneDesc);
	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));

	player = new Vehicle(gPhysics, gCooking, gMaterial, gScene, gAllocator, 0, 5, 0);

	//create obstacle (needed for now)
	PxFilterData obstFilterData(snippetvehicle::COLLISION_FLAG_OBSTACLE, snippetvehicle::COLLISION_FLAG_OBSTACLE_AGAINST, 0, 0);
	PxShape* boxwall = gPhysics->createShape(PxBoxGeometry(1.0f, 2.0f, 1.0f), *gMaterial, false);
	wallActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0, 0, 0)));
	boxwall->setSimulationFilterData(obstFilterData);
	wallActor->setGlobalPose(PxTransform(PxVec3(0, 2, 5)));
	wallActor->attachShape(*boxwall);
	//gScene->addActor(*wallActor);

	//Create a plane to drive on (once we get track cooking working we can remove this, or have this as a safeguard just in case)
	PxFilterData groundPlaneSimFilterData(COLLISION_FLAG_GROUND, COLLISION_FLAG_GROUND_AGAINST, 0, 0);
	gGroundPlane = createDrivablePlane(groundPlaneSimFilterData, gMaterial, gPhysics);
	gScene->addActor(*gGroundPlane);

}

void PhysicsEngine::addEnemyVehicle(float x, float y, float z)
{
	//create vehicle object
	//add it to the list of vehicle
	Vehicle* v = new Vehicle(gPhysics, gCooking, gMaterial, gScene, gAllocator, x, y, z);
	enemyVehicles.push_back(v);
}

physx::PxVec3 PhysicsEngine::GetBoxPos()
{
	return wallActor->getGlobalPose().p;
}

void PhysicsEngine::stepPhysics()
{
	const PxF32 timestep = 1.0f / 60.0f;

	player->update(timestep, gScene);

	if (!enemyVehicles.empty()) {
		for (int i = 0; i < enemyVehicles.size(); i++) {
			enemyVehicles.at(i)->update(timestep, gScene);
		}
	}

	//Scene update.
	gScene->simulate(timestep);
	gScene->fetchResults(true);
}

int PhysicsEngine::getModeType()
{
	return modeType;
}

void PhysicsEngine::cleanupPhysics()
{
	player->cleanupPhysics(gAllocator);

	if (!enemyVehicles.empty()) {
		for (int i = 0; i < enemyVehicles.size(); i++) {
			enemyVehicles.at(i)->cleanupPhysics(gAllocator);
		}
	}


	box->release();
	PX_RELEASE(gGroundPlane);
	
	PX_RELEASE(gMaterial);
	PX_RELEASE(gCooking);
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	if (gPvd)
	{
		PxPvdTransport* transport = gPvd->getTransport();
		gPvd->release();	gPvd = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(gFoundation);

	printf("SnippetVehicle4W done.\n");
}

