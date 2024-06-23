# OpenGL2024

# INTRODUCTION

This is my OpenGL Learning Repo.

## 1. OpenGL Review

### 1.1 入门

* CMake: 工程文件生成工具，根据CMake脚本，用于生成适应不同IDE的工程文件。

* GLFW: 提供用于创建渲染物体最低限度的接口，如创建OpenGL上下文，窗口参数和用户输入。

* opengl32.lib: 只有GLFW生成glfw.lib还不够，我们需要opengl32.lib来链接到opengl的库。Windows平台Microsoft SDK自带。

* GLAD: OpenGL只是一个图形标准或规范，函数具体实现是由不同驱动开发商实现的，导致版本众多，所以大多数函数的位置在编译阶段无法确定，最终需要在运行时找到函数地址。进而出现需要开发者自己手动对调用的每个函数都要先找到地址，然后使用，十分繁琐，GLAD就是为了简化这一过程而出现的库。

* ==TODO: OpenGL绘制一个三角形的过程==

* ==TODO: GLSL着色器语言==

* 纹理：有1d,2d,3d纹理；环绕方式有四种REPEAT,MIRROR_REPEAT,CLAMP,BORDER；还有两种过滤方式NEAREAST, LINEAR,用于当纹理分辨率和物体大小不匹配(物体过大，纹理分辨率过小)，这个时候，有这两种采样策略，NEAREAST优先返回最近纹理像素中心坐标，这个像素会被选为样本颜色。LINEAR则是根据周围像素进行插值。

  总结前者类似于8-bit风格，有明显像素感；后者更接近真实的输出。

* 多级渐远纹理Mipmap：远处物体但是使用的是和近处一样的高分辨率图片，采样结果不正确；采用下采样后的纹理，后一张是前一张的1/2，通过插值形成中间效果。

* stb_image.h: 单头文件图像加载库。

* ==纹理单元：帮助使用多于1个的纹理==，纹理激活与绑定

* ==TODO: 数学基础，使用GLM变换，坐标系，摄像机等==

### 1.2 光照

* 基础光照模型(略)

* 材质+光照贴图(漫反射/镜面反射)，略

* 投光物(Light Caster)，类型如平行光，点光，聚光，手电筒；效果细节如衰减，平滑/软化边缘

  ==TODO: 光源实现与合并==

### 1.3 模型加载

* Assimp: 流行模型加载库，能够加载和导出不同模型类型。
* 网格与模型：网格是opengl能够理解的单个可绘制实体。模型则是包含多个网格，多个纹理的集合体。
* ==TODO: 不同类型模型文件的异同与使用==

### 1.4 高级

* 深度测试Depth Test,发生于像素处理阶段的片元着色器之后

  opengl中使用流程如下，深度缓冲值0-1，观察空间是线性的，屏幕空间是非线性的。

  ```cpp
  glEnable(GL_DEPTH_TEST);//开启深度测试
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//用于每个渲染迭代之前使用，防止上一帧的深度留存下来
  glDepthMask(GL_FALSE);//设置深度掩码来禁用深度写入，只丢弃片段，不写入缓冲
  glDepthFunc(GL_LESS);//设置通过测试的函数
  ```

* **深度冲突问题**

  两个物体并排无法确定深度优先级，并且物体在远处冲突更明显，因为非线性z远处精度会更小。

  解决方法

  * 物体之间不能太近
  * 近平面尽可能远，因为靠近近平面z值精度更高
  * 使用更高精度的深度缓冲，性能消耗高
  * 其它(主要是上面三个)

* 模板测试Stencil Test,立即发生在片元着色器之后，深度测试之前。

  ```
  启用模板缓冲的写入。
  渲染物体，更新模板缓冲的内容。
  禁用模板缓冲的写入。
  渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。
  ```

* 混合技术，Blend;实现透明度的技术

  ==opengl如何加载透明纹理，以及如何渲染半透明纹理==

  渲染次序：先渲染不透明物体，然后对透明物体排序，最后由远及近渲染透明物体(开启深度测试，关闭深度写入)。

* 面剔除技术，Face Culling

  顶点逆时针环绕为正面，反之为反面。

  ```cpp
  //默认关闭，开启如下，默认剔除背面
  glEnable(GL_CULL_FACE);
  //更改所剔除的面
  glCullFace(GL_FRONT);
  //默认正面逆时针环绕
  glFrontFace(GL_CCW);//GL_CCW就是逆时针，可以换成GL_CW将正面设为顺时针环绕
  ```

* 帧缓冲技术，Framebuffer: 颜色，深度，模板缓冲结合起来就是帧缓冲。使用帧缓冲可以获得额外的RT(渲染目标)

  帧缓冲要求：

  ```
  附加至少一个缓冲（颜色、深度或模板缓冲）。
  至少有一个颜色附件(Attachment)。
  所有的附件都必须是完整的（保留了内存）。
  每个缓冲都应该有相同的样本数(sample)。
  ```

  **纹理附件**，通过创建纹理附件，可以把帧缓冲的渲染指令渲染到纹理RTT，以便结果后续反复使用，例如后处理操作。

  **渲染缓冲对象附件：** 渲染缓冲是和纹理图像都是真正的缓冲，也都可以作为帧缓冲的附件。是在纹理之后引入的。相比较之下，存储格式是opengl原始渲染格式，为离屏渲染到帧缓冲优化过，一般情况下只写，并且复制和交换缓冲的操作很快。

  一般来说，RBO常用于深度、模板缓冲附件，因为我们一般无需采样深度、模板缓冲，只关心测试本身，只写不读。

  使用方法，id,gen,bind,storage创建对象，glFramebufferRenderbuffer附加缓冲对象到帧缓冲。

* RTT技术，渲染到纹理技术。==TODO:实操将Framebuffer绘制到纹理==

* 后处理技术，反相，灰度，核处理等。

* 立方体贴图Cubemap, 1) 天空盒 2) Environment Mapping环境映射

* ==高级数据==

  ```cpp
  glBufferData //填充缓冲对象的内存
  glBufferSubData //填充缓冲对象的特定区域，可以设置偏移值起始点，在此之前调用glBufferData保证预留足够空间
      
  glMapBuffer //返回当前缓冲指针，然后可以通过memcpy直接复制到内存，最后需要glUnmapBuffer(GL_ARRAY_BUFFER);解除映射
   
  // 分批顶点属性
  glVertexAttribPointer //指定数组缓冲布局
  // 由于获取顶点属性都是一个坐标数组，一个法线数组,一个纹理坐标数组，设置布局的时候采用交错布局会很麻烦，这里通过glBufferSubData分批设置(另一种可行但不太好的方法是将三个数组合并，然后glBufferData)
  
  // 复制缓冲操作
  glCopyBufferSubData
  ```

* GLSL进阶，内建变量如gl_Position(顶点着色器输出)

  以及接口块interface block

  ```glsl
  //in out关键字修饰
  out VS_OUT
  {
      vec2 TexCoords;
  } vs_out;
  ```

  **Uniform缓冲对象**，类似于全局变量，多个着色器中相同的全局uniform对象，不用反复设置值。

  ```glsl
  //定义uniform块
  //layout (std140)表示对当前uniform块使用特定内存布局
  layout (std140) uniform Matrices
  {
      mat4 projection;
      mat4 view;
  };
      
  layout (std140) uniform ExampleBlock
  {
                       // 基准对齐量       // 对齐偏移量
      float value;     // 4               // 0 
      vec3 vector;     // 16              // 16  (必须是16的倍数，所以 4->16)
      mat4 matrix;     // 16              // 32  (列 0)
                       // 16              // 48  (列 1)
                       // 16              // 64  (列 2)
                       // 16              // 80  (列 3)
      float values[3]; // 16              // 96  (values[0])
                       // 16              // 112 (values[1])
                       // 16              // 128 (values[2])
      bool boolean;    // 4               // 144
      int integer;     // 4               // 148
  }; 
  //除了std140布局，还有shared布局和packed布局
  //std140可以手动计算出每个变量的偏移值，一个变量的对齐字节偏移量必须等于基准对齐量的倍数
  //这样保证了opengl内存布局和声明这个uniform块的程序的布局保持一致
  ```

  c++端使用ubo

  ```cpp
  unsigned int uboExampleBlock;
  glGenBuffers(1, &uboExampleBlock);
  glBindBuffer(GL_UNIFORM_BUFFER, uboExampleBlock);
  glBufferData(GL_UNIFORM_BUFFER, 152, NULL, GL_STATIC_DRAW); // 分配152字节的内存
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  ```

* 几何着色器Geometry Shader

  几何着色器能够将一组顶点生成不同的图元，也能生成更多顶点。

  ==TODO: to be extended==

* **实例化**Instancing: 大量绘制同一模型时，会很容易导致绘制发生瓶颈。opengl绘制顶点需要做很多准备工作，cpu需要告诉gpu绘制哪些顶点，从哪里读取顶点数据等。频繁发生CPU To GPU BUS(总线)上的操作很容易影响性能，所以实例化解决了这样的问题，一次性将数据由CPU发给GPU，以求实现**一次渲染多个物体**

  gl_InstanceID内建变量则是具体实例id

  ==见小行星实例化案例==

* 最后是抗锯齿，Jagged Edges为锯齿边；OpenGL中的MSAA,离屏MSAA,以及自定义抗锯齿。

## 2. Game Demos

### 2D Game

### 3D Game



