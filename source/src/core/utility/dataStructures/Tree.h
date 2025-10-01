#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory> 


template <typename Tkey> class Tree {
public:

	class TreeNode : public std::enable_shared_from_this<TreeNode> {
	public:

		std::shared_ptr<TreeNode> getPtr()
		{
			return this->shared_from_this();
		}

		Tkey key;
		std::shared_ptr<TreeNode> parent;
		std::vector<std::shared_ptr<TreeNode>> children;

		TreeNode(Tkey key, std::shared_ptr<TreeNode> parent = nullptr) {
			this->key = key;
			this->setParent(parent);

		}

		~TreeNode() {
			children.clear();
		}
		void setParent(std::shared_ptr<TreeNode> parent = nullptr) {
			if (parent) {
				this->parent = parent;

			}
		}

		std::shared_ptr<TreeNode> addChild(Tkey childElement) {
			auto childNode = std::make_shared<TreeNode>(childElement, getPtr());
			children.push_back(childNode);
			return childNode;
		}

		Tkey getParentKey() {
				return parent->key;
		}
	};
	// Not using unique_ptr because we are inheriting from enable_shared_from_this
	std::shared_ptr<TreeNode> root = nullptr; 

	Tree() = default;

	Tree(Tkey rootElement) {
		this->root = std::make_shared<TreeNode>(rootElement);
	};

	Tkey getRootValue() {
		return root->key;
	}


};

#endif 