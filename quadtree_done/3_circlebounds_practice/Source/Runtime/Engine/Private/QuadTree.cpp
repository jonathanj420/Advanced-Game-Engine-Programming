#include "Precompiled.h"

// 핵심 로직 
bool QuadTree::Insert(const std::string& InKey, const Rectangle& InBound)
{
	if (!Bound.Intersect(InBound)) {
		return false;
	}

	// 마지막 Depth까지 도달하면 자료구조에 추가하고 종료 { return true; }
	if (Level >= MaxLevel) {
		Nodes.emplace_back(InKey, InBound);
		return true;
	}

	// 자식 노드를 만들어야 하는 경우 4개의 자식 노드를 새롭게 생성 => Split()
	if (SubTrees[SubNames::NorthWest] == nullptr) {
		Split();
	}
	// Split된 상태에서 FindSubTree 함수의 결과에 따라 처리를 다르게 진행
	// 1. 겹쳐 있으면 자신의 자료구조에 넣고 끝내기 ( return true; )
	QuadTree* newNode = FindSubTree(InBound);
	if (newNode == nullptr) {
		Nodes.emplace_back(InKey, InBound);
		return true;
	}
	else {
		newNode->Insert(InKey,InBound);
	}
	// 2. 안겹쳐져 있으면 자식으로 내려보내기 ( childNode->Insert ( 재귀 호출 ) )
}

void CK::QuadTree::Clear()
{
}

void CK::QuadTree::Query(const CK::Rectangle& InRectangleToQuery, std::vector<std::string>& InOutItems) const
{
	//Automatically abort if the range does not intersect this quad
	if (!Bound.Intersect(InRectangleToQuery)) {
		return;
	}

	// Check objects at this quad level
	for (const TreeNode& node : Nodes) {

		InOutItems.emplace_back(node.NodeKey);
	}

	// Terminate here, if there are no children
	if (SubTrees[SubNames::NorthWest] == nullptr) {
		return;
	}

	// Otherwise, add the points from the children

	for (QuadTree* subTree : SubTrees)
	{
		subTree->Query(InRectangleToQuery, InOutItems);

	}

}

void QuadTree::Split()
{
	Vector2 center;
	Vector2 extent;

	Bound.GetCenterAndExtent(center, extent);


	// SW, SE, NW, SE 네 개의 영역으로 쪼개고 이들의 바운딩 볼륨을 계산해서 넣기
	SubTrees[SubNames::NorthWest] = new QuadTree(CK::Rectangle(Vector2(center.X-extent.X,center.Y),Vector2(center.X,center.Y+extent.Y)),Level+1,MaxLevel,NodeCapacity);

	SubTrees[SubNames::NorthEast] = new QuadTree(CK::Rectangle(center,center+extent),Level+1,MaxLevel,NodeCapacity);

	SubTrees[SubNames::SouthEast] = new QuadTree(CK::Rectangle(Vector2(center.X,center.Y - extent.Y), Vector2(center.X + extent.X ,center.Y)), Level + 1, MaxLevel, NodeCapacity);

	SubTrees[SubNames::SouthWest] = new QuadTree(CK::Rectangle(center - extent, center), Level + 1, MaxLevel, NodeCapacity);

}

bool CK::QuadTree::Contains(const CK::Rectangle& InBox) const
{
	if (Bound.IsInside(InBox) == true) {

		return true;

	}
	else {

		return false;

	}
}

QuadTree* QuadTree::FindSubTree(const Rectangle& InBound)
{
	// 네 개의 자식 노드를 돌면서 주어진 영역을 완전 포함하는 자식 트리가 있는지 조사.
	for (QuadTree* subTree : SubTrees)
	{
		assert(subTree != nullptr);
		if (subTree->Contains(InBound))
		{
			return subTree;
		}
	}

	// 없으면 겹친다고 판단하고 null 반환
	return nullptr;
}