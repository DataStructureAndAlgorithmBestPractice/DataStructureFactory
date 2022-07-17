# Binary Search Tree With Desired Pool

## Description

In computer science, a binary tree is a tree data structure in which each node has at most two children, which are referred to as the left child and the right child. A recursive definition using just set theory notions is that a (non-empty) binary tree is a tuple (L, S, R), where L and R are binary trees or the empty set and S is a singleton set containing the root. Some authors allow the binary tree to be the empty set as well.

The main **IDEA** to use this type of tree is the fact that in real industrial cases, sequential creation of tree elements is not efficient (since its a  system call). 
In other words, when a program is executed, it is always the job-schedualer task to establish a balance between IO-intensive and CPU-intensive processes. Meanwhile, there are critical system calls that require context switching so that time-sharing protocols would remain effective. In this project, we have examined how impactful **malloc** interupt signal really is on an insert-intensive system.
As depicted in [Figure-01](https://github.com/DataStructureAndAlgorithmBestPractice/B/blob/master/Results/plots/plot.png?raw=true), it could be observed that utilizing the pool mechanism which is ***Clustered Allocation*** produce faster responses.
More variations such as AVL, Red-Black, B-tree, and Splay is also on the way.

## Build & Installation

You can download latest compiled binary files from **[Releases](https://github.com/DataStructureAndAlgorithmBestPractice)**.

## Unique Features
### First Release (v1.0.0)
More Information will be found in [VersionGuide]().

## How does it work?
Source Code is Provided in src directory with proper Examples ()

## Credits
- All of the <a href="https://github.com/DataStructureAndAlgorithmBestPractice">contributors</a> 
- Masood Hamed Saghayan (<a href="https://github.com/M4si94">@M4si94</a>)
- Mohammad Hossein Zolfagharnasab (<a href="https://github.com/MsainZn">@MsainZn</a>)


## License
**FAT & SLIM**, and all its submodules and repos, unless a license is otherwise specified, are licensed under **MIT** LICENSE.
Dependencies are licensed by their own.


