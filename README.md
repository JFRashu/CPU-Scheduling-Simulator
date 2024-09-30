# CPU Scheduling Algorithm Simulator

## Project Overview
This project implements and compares various CPU scheduling algorithms, including a novel algorithm designed to address starvation in preemptive priority scheduling. The project was developed as part of the Operating System (Sessional) course (CSE-336) at Chittagong University of Engineering & Technology.

## Table of Contents
- [Objectives](#objectives)
- [Implemented Algorithms](#implemented-algorithms)
- [Novel Algorithm](#novel-algorithm)
- [Features](#features)
- [Team Members and Contributions](#team-members-and-contributions)
- [Conclusion](#conclusion)
- [Acknowledgments](#acknowledgments)

## Objectives
1. Develop a new CPU scheduling algorithm to improve average waiting time, turnaround time, and CPU utilization
2. Implement the new algorithm and existing algorithms
3. Compare the performance of the novel algorithm with existing algorithms
4. Analyze the results to determine the effectiveness of the new algorithm

## Implemented Algorithms
1. First Come First Serve (FCFS)
2. Non-Preemptive Shortest Job First (SJF)
3. Preemptive Shortest Job First (SRTF)
4. Non-Preemptive Priority Scheduling
5. Preemptive Priority Scheduling
6. Round Robin
7. Novel Algorithm (Our Proposed Algorithm)

## Novel Algorithm
Our proposed algorithm addresses the issue of starvation in preemptive priority scheduling. Key features include:
- Highest priority selection
- Redundancy tracking
- Dynamic priority adjustment
- Preemptive execution with dynamic time quantum

This project showcases our team's ability to work collaboratively, leveraging individual strengths to create a comprehensive CPU scheduling simulation tool, including an innovative new algorithm.

## Features
- Implementation of 7 different CPU scheduling algorithms
- Comparative analysis of all implemented algorithms
- Dynamic time quantum calculation for the novel algorithm
- Gantt chart visualization for each algorithm

## Team Members and Contributions

This project implements various CPU scheduling algorithms, including a novel algorithm designed by our team.

- Shougata Paul: Implemented First-Come-First-Serve (FCFS) and Shortest Job First (SJF) algorithms.
- Abid Al Hossain : Implemented Shortest Remaining Time First (SRTF) algorithm.
- Arupa Barua: Implemented Priority Scheduling algorithm.
- Md. Tasnimur Rahman : Implemented Round Robin algorithm.
- Jannatul Farzana Rashumoni: Implemented Preemptive Priority Scheduling algorithm.

Novel Algorithm:
- Implementation and Debugging: Jointly by  Md. Tasnimur Rahman and Jannatul Farzana Rashumoni
- Concept and Design: All team members

The novel algorithm was a collective effort, with the core idea being developed by all team members through collaborative discussions and brainstorming sessions.

All team members contributed to the testing phase, rigorously checking the entire program against numerous test cases to ensure robustness and accuracy.

## Conclusion
Our novel CPU scheduling algorithm successfully addresses the long-standing issue of starvation in preemptive priority scheduling, offering a balanced and efficient approach to process management. While it provides significant benefits in fairness and efficiency, it also has some limitations in terms of complexity and overhead.


## Acknowledgments
We would like to thank our course instructors:
- MD. Shafiul Alam Forhad, Assistant Professor, CSE, CUET
- Hasan Murad, Assistant Professor, CSE, CUET

