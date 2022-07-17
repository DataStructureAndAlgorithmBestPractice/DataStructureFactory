# Binary Search Tree With Desired Pool

## Description
The main **IDEA** to start the current project is the fact that in real industrial cases, sequential data allocation is significantly inefficient, since it requires a system call. 
In other words, when a program is executed, it is always the job-schedualer task to establish a balance between IO-intensive and CPU-intensive processes; any additional context switching would reduce the CPU performance. In this project, we have examined how impactful **malloc** interupt signal really is on an insert-intensive system.
As depicted in [Figure-01](https://github.com/DataStructureAndAlgorithmBestPractice/DataStructureFactory/BinarySearchTree/BenchMark/Results/plots/plot.png?raw=true), it could be observed that utilizing the pool mechanism which is ***Clustered Allocation*** produce faster responses.
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


