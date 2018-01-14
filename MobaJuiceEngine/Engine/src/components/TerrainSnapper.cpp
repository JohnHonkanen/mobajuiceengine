#include "components\TerrainSnapper.h"
#include "components\Camera.h"
#include "core\GameEngine.h"
#include "physics\RaycastUtility.h"
#include "MobaJuiceCore.h"
namespace Engine {
	namespace Terrain {
		TerrainSnapper * TerrainSnapper::Create(GameObject * gameObject, TerrainGrid * grid)
		{
			TerrainSnapper * ts = new TerrainSnapper();
			ts->grid = grid;

			gameObject->AddComponent(ts);

			return ts;
		}

		void TerrainSnapper::Copy(GameObject * copyObject)
		{
			//Not a copyable component
			assert(0);
		}

		void TerrainSnapper::OnLoad()
		{
			
			
		}

		void TerrainSnapper::Start()
		{

		}

		void TerrainSnapper::Update()
		{
			InputManager im = GameEngine::manager.inputManager;
			if (!im.mouseVisible || heldObject == nullptr)
				return;

			vec3 colPoint = CalcRayTerrainCollisionPoint();
			vec3 snap = grid->GetSnapPoint(colPoint);
			snapPoint = snap;
			heldObject->transform->SetPosition(snap + vec3(5, 4.0f , 5));
			heldObject->transform->up = grid->GetNormal(snap) * 3.14f;
		}
		void TerrainSnapper::SetHeldObject(GameObject * gameObject)
		{
			heldObject = gameObject;
		}
		vec3 TerrainSnapper::GetMouseToWorldSnap()
		{
			return vec3();
		}
		vec3 TerrainSnapper::CalcRayTerrainCollisionPoint()
		{
			int mx, my;
			GameEngine::manager.inputManager.GetMousePos(mx, my);

			vec3 normCoords = RaycastUtility::ConvertPointToNormalizeCoords(mx, my, 1280, 720);
			vec3 rayDir = RaycastUtility::ConvertNormalizedCoordsToWorldCoords(
				normCoords, 
				Camera::mainCamera->GetProjectionMatrix(), 
				Camera::mainCamera->GetViewMatrix()
			);

			vec3 colPoint = BinarySearchFindPoint(
				Camera::mainCamera->transform->GetPosition(),
				rayDir,
				RAYDIST,
				0
				);

			return colPoint;
		}
		vec3 TerrainSnapper::BinarySearchFindPoint(vec3 position, vec3 ray, float rayDist, int recursionCount)
		{
			int count = recursionCount + 1;
			vec3 midPoint = position + ray * rayDist / 2.0f;

			if (recursionCount > RECURSION)
				return midPoint;

			float tHeight = grid->GetHeight(midPoint.x, midPoint.z);

			
			if (midPoint.y > tHeight) {
				//Ray is Above terrain
				midPoint = BinarySearchFindPoint(midPoint, ray, rayDist / 2, count);
			}
			else if (midPoint.y < tHeight) { 
				//Ray is below
				midPoint = BinarySearchFindPoint(position, ray, rayDist / 2, count);
			}

			return midPoint;

		}
	}
}