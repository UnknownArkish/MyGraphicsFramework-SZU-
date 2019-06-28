# MyGraphicsFramework
此仓库是本人在课程《计算机图形学》（深圳大学）的大作业，是一个使用OpenGL编写的简单图形框架
- 完成时间: 2018-2019第一学期（大三上学期）

## 这是什么
这是一个利用OpenGL编写的简单的3D图形框架，它隐藏了底层OpenGL的内容，进而用以通过这个上游的框架，可以很轻松的搭建一个带有交互的简单场景

## 特点
- 用户不需要关心太多OpenGL的东西
- 采用了类似cocos2d-x的编程风格
- 数据和渲染分离

## 注意
- 由于本人对图形学不熟悉，因此引擎运行效率比较低
- 框架代码会有不合理的地方
- 没有实现垃圾回收机制，因此可能会有严重的内存泄露问题

## 如何使用
- 使用Visual Stdio 2017（或以上版本）打开FinalAssignment.sln，编译即可创建exe文件
- 注意：编译生成的exe文件运行的是下面的demo场景，资源需要被放置在exe的目录下
- 注意：依赖的OpenGL头文件和库放置在VC文件夹下，而且已经配置在解决方案中配置好了

## 示例Demo
### 加载并创建一个小草模型
1. 加载资源: `ResourcesSystem::GetInstance()->LoadModel("grass.fbx", "grass");`
2. 创建模型对象: `Model* grass = Model::Create( ResourcesSystem::GetInstance()->GetModelResources("grass") );`
3. 放置模型对象到场景中: `this-AddChild(grass);`
### 一个demo场景
- demo场景代码被放置在TestScene.c/h当中
- demo场景需要的资源放置在Resources文件夹下，需要和编译生成的exe文件放置在同一个目录下
![截图场景](https://github.com/UnknownArkish/MyGraphicsFramework-SZU-/blob/master/DemoScreenshot/demo1.png,"截图场景")
## 框架包含以下模块
### 基本模块ObjectSystem
- 基本的数据对象，例如不会进行渲染的Ref、Node、Scene，会进行渲染的Plane、Cube等
- 渲染器Renderer，渲染上述的数据对象
### 资源模块ResourcesSystem
- 存储、加载、获取资源（包括动画、模型文件、单张贴图、立方体贴图等）
- 模型文件的加载使用第三方库Assimp
- 暂时没有卸载资
### 摄像机模块CameraSystem
- 管理当前摄像机的模块，提供了一个可以全局性访问摄像机的方案
### 输入模块InputSystem
- 提供了一些现成的监听器，例如键盘监听器、鼠标监听器
- 管理注册到模块中的监听器，并在适当的时候响应他们
### 光照系统
- 提供了一些现成的光源，包括点光源、聚光灯、方向光
- 管理注册到模块中的光源，并负责着色器中对于光源的渲染
- 需要由渲染器主动向光照系统请求光照渲染
