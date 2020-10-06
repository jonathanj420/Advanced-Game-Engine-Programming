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
	if (SubTrees[SubNames::TopLeft] == nullptr) {
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
}

void QuadTree::Split()
{
	Vector2 center;
	Vector2 extent;

	Bound.GetCenterAndExtent(center, extent);


	// SW, SE, NW, SE �� ���� �������� �ɰ��� �̵��� �ٿ�� ������ ����ؼ� �ֱ�
	SubTrees[SubNames::TopLeft] = new QuadTree(CK::Rectangle(Vector2(center.X-extent.X,center.Y),Vector2(center.X,center.Y+extent.Y)),Level+1,MaxLevel,NodeCapacity);

	SubTrees[SubNames::TopRight] = new QuadTree(CK::Rectangle(center,center+extent),Level+1,MaxLevel,NodeCapacity);

	SubTrees[SubNames::BottomRight] = new QuadTree(CK::Rectangle(Vector2(center.X,center.Y - extent.Y), Vector2(center.X + extent.X ,center.Y)), Level + 1, MaxLevel, NodeCapacity);

	SubTrees[SubNames::BottomLeft] = new QuadTree(CK::Rectangle(center - extent, center), Level + 1, MaxLevel, NodeCapacity);

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