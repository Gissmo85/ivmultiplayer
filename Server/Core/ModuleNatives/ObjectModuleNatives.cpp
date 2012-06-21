//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: ObjectNatives.cpp
// Project: Server.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "ModuleNatives.h"
#include "Scripting/CScriptingManager.h"
#include "../CObjectManager.h"
#include "../CNetworkManager.h"

extern CObjectManager * g_pObjectManager;
extern CNetworkManager * g_pNetworkManager;

// Object functions
namespace Modules
{
	// createObject(modelhash, x, y, z, rx, ry, rz)
	EntityId CObjectModuleNatives::Create(int modelhash, CVector3 vecPosition, CVector3 vecRotation)
	{
		return g_pObjectManager->Create(modelhash, vecPosition, vecRotation);
	}

	// deleteObject(objectid)
	bool CObjectModuleNatives::Delete(EntityId objectId)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			g_pObjectManager->Delete(objectId);
			return true;
		}

		return false;
	}

	// getObjectModel(objectid)
	int CObjectModuleNatives::GetModel(EntityId objectId)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			return g_pObjectManager->GetModel(objectId);
		}

		return -1;
	}

	// setObjectCoordinates(objectid, x, y, z)
	bool CObjectModuleNatives::SetCoordinates(EntityId objectId, CVector3 vecPosition)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			return g_pObjectManager->SetPosition(objectId, vecPosition);
		}

		return false;
	}

	// getObjectCoordinates(objectid)
	CVector3 CObjectModuleNatives::GetCoordinates(EntityId objectId)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			CVector3 vecPosition;

			if(g_pObjectManager->GetPosition(objectId, vecPosition))
			{
				return vecPosition;
			}
		}

		return CVector3();
	}


	// setObjectRotation(objectid, x, y, z)
	bool CObjectModuleNatives::SetRotation(EntityId objectId, CVector3 vecRotation)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			return g_pObjectManager->SetRotation(objectId, vecRotation);
		}

		return false;
	}

	// getObjectRotation(objectid)
	CVector3 CObjectModuleNatives::GetRotation(EntityId objectId)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			CVector3 vecRotation;

			if(g_pObjectManager->GetRotation(objectId, vecRotation))
			{
				return vecRotation;
			}
		}

		return CVector3();
	}

	void CObjectModuleNatives::CreateExplosion(CVector3 vecPos, float fDensity)
	{
		g_pObjectManager->CreateExplosion(vecPos, fDensity);
	}

	EntityId CObjectModuleNatives::CreateFire(CVector3 vecPos, float fDensity)
	{
		return g_pObjectManager->CreateFire(vecPos,fDensity);
	}

	void CObjectModuleNatives::DeleteFire(EntityId fireId)
	{
		g_pObjectManager->DeleteFire(fireId);
	}

	bool CObjectModuleNatives::AttachPed(EntityId objectId, EntityId playerId, CVector3 vecPos, CVector3 vecRot)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			g_pObjectManager->AttachToPlayer(objectId,playerId,vecPos,vecRot);
			return true;
		}
		return false;
	}

	bool CObjectModuleNatives::AttachVehicle(EntityId objectId, EntityId vehicleId, CVector3 vecPos, CVector3 vecRot)
	{
		if(g_pObjectManager->DoesExist(objectId))
		{
			g_pObjectManager->AttachToVehicle(objectId,vehicleId,vecPos,vecRot);
			return true;
		}
		return false;
	}
}