#pragma once
#include <iostream>
#include <list>
using namespace std;

namespace CK
{
	class QuadTree
	{
	public:
		QuadTree() = default;
		QuadTree(const CK::Rectangle& InBound, int InLevel) : Bound(InBound), Level(InLevel) { }
		QuadTree(const CK::Rectangle& InBound, int InLevel, int InMaxLevel, size_t InNodeCapacity) : Bound(InBound), Level(InLevel), MaxLevel(InMaxLevel), NodeCapacity(InNodeCapacity) { }
		~QuadTree() { Clear(); }

	private:
		enum SubNames
		{
			NorthWest = 0,
			NorthEast = 1,
			SouthEast = 2,
			SouthWest = 3
		};

		struct TreeNode
		{
			TreeNode() = delete;
			TreeNode(const std::string& InNodeKey, const CK::Rectangle& InBound) : NodeKey(InNodeKey), NodeBound(InBound) { }

			CK::Rectangle NodeBound;
			std::string NodeKey;
		};

	public:
		bool Insert(const std::string& InKey, const CK::Rectangle& InBound);
		void Clear();
		void Query(const CK::Rectangle& InRectangleToQuery, std::vector<std::string>& InOutItems) const;
		bool HasItem() { return !IsLeaf; }

	private:
		void Split();
		bool Contains(const CK::Rectangle& InBox) const;
		QuadTree* FindSubTree(const CK::Rectangle& InBound);

	private:
		CK::Rectangle Bound;
		std::list<TreeNode> Nodes;

		bool IsLeaf = true;
		int Level = 1;
		int MaxLevel = 10;
		size_t NodeCapacity = 6;

		QuadTree* SubTrees[4] = { nullptr };
	};
}
