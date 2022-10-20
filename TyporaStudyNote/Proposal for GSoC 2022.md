# Proposal for GSoC 2022

*P.S.  I have also submitted other proposal(s), and I would prefer this one if possible. :) Thanks!*

## **About Me**

#### **Basic**

- **姓名**: **龚娜** 
- **华中师范大学 软件工程**

#### **Information**

- **Email** ：[2036479155@qq.com](mailto:2036479155@qq.com)  
- **WeChat**：Ustinian200110
- **GitHub Account** :https://github.com/gongna-au
- **Website**：https://gongna-au.github.io/

#### Good At  

golang Backend development

#### **Education**  

Central China Normal University, WuHan, China  ,Software Engineering Major, expected graduation July 2024

#### **Related Experience** 

- [https://github.com/gongna-au/Summer2021-Projec](https://github.com/gongna-au/Summer2021-Project)
-  https://github.com/muxi-mini-project/2021-ZeroGravity-backend  
- https://github.com/gongna-au/FreshmanGuidanceProject-backend

## Project

#### Project Name

Casbin Dashboard

#### Project Description

https://github.com/casbin/SummerOfCode2022#casbin-dashboard

#### Outline

- **About manage models, adapters, enforcers,and handle different DBs**

  My initial thoughts, read the Casbin source code to understand what data the project needs to combine, use data visualization, add data blending tools, create abstract virtual database services, and determine where to host data sources.

- **About model editor**

  Learned from research，ozzo-validation is a Go package that provides configurable and extensible data validation capabilities. It has the following features。All these features can help us build a model editor with syntax and semantic validators to edit models

  - use normal programming constructs rather than error-prone struct tags to specify how data should be validated.
  - can validate data of different types, e.g., structs, strings, byte slices, slices, maps, arrays.
  - can validate custom data types as long as they implement the `Validatable` interface.
  - can validate data types that implement the `sql.Valuer` interface (e.g. `sql.NullString`).
  - customizable and well-formatted validation errors.
  - error code and message translation support.
  - provide a rich set of validation rules right out of box.
  - extremely easy to create and use custom validation rules

- **About  test their model and policy.**

  Read the source code and analyze it。In the face of huge tests, test cases, considering more logical judgments, more code length and complexity, we can use the GoConvey test framework, which can run examples with better management.

  Or use Gomock framework - mock interface.Based on its following characteristics:
  1. Based on the interface
  2. Can be well integrated with Golang's built-in testing package

- **About Authentication and authorization for the dashboard itself.** 

  Design an algorithm and implement it



## **Expected Timeline**

| *Prior May 4             | Familiarize yourself with the Casbin source code. Continue to dig deeper into the problem to be solved through the source code |
| ------------------------ | ------------------------------------------------------------ |
| ***May 4 - 30***         | **Analyze the source code and find the best solution. Discuss with the implementation of the Mentor algorithm. Choose the best framework to implement the corresponding function.** |
| ***June 1 - 30***        | **Implement each piece of functionality and test it. Write an evaluation document.** |
| ***July 1 - August 14*** | **Fix algorithm errors, and further improve the corresponding functions. If the result of the function implementation is not as expected, the algorithm should be improved.** |
| ***August 14 - 29***     | ***Write a summary essay on the entire project.If I have more time to use, please try more algorithms.*** |

## Extra Information

***Reason for Participation***

***I have always wanted to be a great developer since the first day I learnt programming. GSoC provides me a chance to make contributions to open source projects with mentorship from great developers all over the world. I believe it is really amazing. If I have the chance to participate in GSoC and work with Casbin, I will try my best to complete this project.***

***By now, I'm familiar with the contribution workflow and how to collaborate with other developers and project maintainers***

***I am looking forward to working on the project with  Casbin!!!***