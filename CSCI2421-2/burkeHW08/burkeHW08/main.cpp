//main.cpp
//Dalton Burke
//contains drivers and tests for HW8

#include<iostream>
#include"Node.h"
#include"BSTree.h"

int main()
{
  BSTree* Tree;
  Tree = new BSTree();

  std::cout << "Adding root of Tree, 300" << std::endl;
  Tree->addNode(300);

  std::cout << "Adding 100" << std::endl;
  Tree->addNode(100);

  std::cout << "Adding 200" << std::endl;
  Tree->addNode(200);

  std::cout << "Adding 400" << std::endl;
  Tree->addNode(400);
  std::cout << std::endl;

  std::cout << "Preorder Print:" << std::endl;
  Tree->printPreorder(Tree->Root());
  std::cout << std::endl << std::endl;

  std::cout << "Inorder Print:" << std::endl;
  Tree->printInorder(Tree->Root());
  std::cout << std::endl << std::endl;

  std::cout << "Postorder Print:" << std::endl;
  Tree->printPostorder(Tree->Root());
  std::cout << std::endl << std::endl;

  Tree->findNode(100, Tree->Root());
  Tree->findNode(200, Tree->Root());
  Tree->findNode(300, Tree->Root());
  Tree->findNode(400, Tree->Root());
  Tree->findNode(500, Tree->Root());
  Tree->findNode(600, Tree->Root());
  std::cout << std::endl;

  std::cout << "Min=" << Tree->min(Tree->Root())->Key() << std::endl;

  std::cout << "Max=" << Tree->max(Tree->Root())->Key() << std::endl << std::endl;

  std::cout << "Successor to 300=" << Tree->successor(300, Tree->Root())->Key() << std::endl;
  std::cout << "Predecessor to 300=" << Tree->predecessor(300, Tree->Root())->Key() << std::endl;

  std::cout << "Deleting 300..." << std::endl << std::endl;

  Tree->deleteNode(300);

  std::cout << "Preorder print:" << std::endl;

  Tree->printPreorder(Tree->Root());
  std::cout << std::endl << std::endl;

  std::cout << "Deleting entire tree pointer..." << std::endl;
  delete Tree;


  std::cout << "Goodbye!" << std::endl;
}
