#include "Precompiled.h"

// �ٽ� ���� 
bool QuadTree::Insert(const std::string& InKey, const Rectangle& InBound)
{
	if (!Bound.Intersect(InBound)) {
		return false;
	}

	// ������ Depth���� �����ϸ� �ڷᱸ���� �߰��ϰ� ���� { return true; }
	if (Level >= MaxLevel) {
		Nodes.emplace_back(InKey, InBound);
		return true;
	}

	// �ڽ� ��带 ������ �ϴ� ��� 4���� �ڽ� ��带 ���Ӱ� ���� => Split()
	if (SubTrees[SubNames::NorthWest] == nullptr) {
		Split();
	}
	// Split�� ���¿��� FindSubTree �Լ��� ����� ���� ó���� �ٸ��� ����
	// 1. ���� ������ �ڽ��� �ڷᱸ���� �ְ� ������ ( return true; )
	QuadTree* newNode = FindSubTree(InBound);
	if (newNode == nullptr) {
		Nodes.emplace_back(InKey, InBound);
		return true;
	}
	else {
		newNode->Insert(InKey,InBound);
	}
	// 2. �Ȱ����� ������ �ڽ����� ���������� ( childNode->Insert ( ��� ȣ�� ) )
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


	// SW, SE, NW, SE �� ���� �������� �ɰ��� �̵��� �ٿ�� ������ ����ؼ� �ֱ�
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
	// �� ���� �ڽ� ��带 ���鼭 �־��� ������ ���� �����ϴ� �ڽ� Ʈ���� �ִ��� ����.
	for (QuadTree* subTree : SubTrees)
	{
		assert(subTree != nullptr);
		if (subTree->Contains(InBound))
		{
			return subTree;
		}
	}

	// ������ ��ģ�ٰ� �Ǵ��ϰ� null ��ȯ
	return nullptr;
}