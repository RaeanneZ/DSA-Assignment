#pragma once

// Switch between data structures easily by uncommenting the preferred option

// #define USE_LIST
#define USE_LINKED_LIST
// #define USE_STACK
// #define USE_QUEUE
// #define USE_TREE
// #define USE_AVL_TREE
// #define USE_MAP

#ifdef USE_LIST
#include "List.h"
template <typename T>
using DataStructure = List<T>;
#endif

#ifdef USE_LINKED_LIST
#include "LinkedList.h"
template <typename T>
using DataStructure = LinkedList<T>;
#endif

#ifdef USE_STACK
#include "Stack.h"
template <typename T>
using DataStructure = Stack<T>;
#endif

#ifdef USE_QUEUE
#include "Queue.h"
template <typename T>
using DataStructure = Queue<T>;
#endif

#ifdef USE_TREE
#include "Tree.h"
template <typename T>
using DataStructure = Tree<T>;
#endif

#ifdef USE_AVL_TREE
#include "AVLTree.h"
template <typename T>
using DataStructure = AVLTree<T>;
#endif

#ifdef USE_MAP
#include "Map.h"
template <typename K, typename V>
using DataStructure = Map<K, V>;
#endif
