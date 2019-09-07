// 引入GLEW库 定义静态链接
#define GLEW_STATIC
#include <GLEW/glew.h>
// 引入GLFW库
#include <GLFW/glfw3.h>
// 引入SOIL库
#include <SOIL/SOIL.h>
// 引入GLM库
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include <stdio.h>
#include <iostream>

#include <vector>
#include <cstdlib>
// 包含着色器加载库
#include "shader.h"
// 包含相机控制辅助类
#include "camera.h"
// 包含纹理加载类
#include "texture.h"
// 加载模型的类
#include "model.h"
using namespace std;

// 键盘回调函数原型声明
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// 鼠标移动回调函数原型声明
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
// 鼠标滚轮回调函数原型声明
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// 场景中移动
void do_movement();

// 定义程序常量
const int WINDOW_WIDTH = 1600, WINDOW_HEIGHT = 800;
// 用于相机交互参数
GLfloat lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouseMove = true;
bool keyPressedStatus[1024]; // 按键情况记录
GLfloat deltaTime = 1.0f; // 当前帧和上一帧的时间差
GLfloat lastFrame = 0.0f; // 上一帧时间
Camera camera(glm::vec3(25.0f, -20.0f, 200.0f));

glm::vec3 plane_pos(0.0f, 0.0f, 0.0f);
glm::vec3 plane1_pos(0.0f, 0.0f, 0.0f);
glm::vec3 plane_angle(0.0f, 0.0f, 0.0f);
glm::vec3 plane_axis(0.0f, 0.0f, 0.0f);

GLfloat weizhi[5900];

int main(int argc, char** argv)
{
	//string sline,str;//每一行
	//string out;
	//string s1, s2, s3, s4;


	//while (getline(inf, sline))
	//{   
	//	int i = 0;
	//	istringstream sin(sline);
	//	while (sin >> str)
	//	{
	//		weizhi = str;
	//	}
	//		weizhi[i] = sline;
	//}
	//读取数据
	ifstream inf;
	inf.open("d://out.txt");
	
	GLfloat x, y, z;
	
	int i = 0;
	while (inf >> x >> y >> z)
	{
		weizhi[i] = x;
		weizhi[i + 1] = y;
		weizhi[i + 2] = z;
		i += 3;
	}

	int zong = i;
	i = 0;
	cout << zong << endl;
	for (i = 0;i<=zong;i++)
	{
		cout << GLfloat(weizhi[i]) << endl;
	}

	if (!glfwInit())	// 初始化glfw库
	{
		std::cout << "Error::GLFW could not initialize GLFW!" << std::endl;
		return -1;
	}

	// 开启OpenGL 3.3 core profile
	std::cout << "Start OpenGL core profile version 3.3" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
		"OPENGL-H6", NULL, NULL);
	if (!window)
	{
		std::cout << "Error::GLFW could not create winddow!" << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	// 创建的窗口的context指定为当前context
	glfwMakeContextCurrent(window);

	// 注册窗口键盘事件回调函数
	glfwSetKeyCallback(window, key_callback);
	// 注册鼠标事件回调函数
	glfwSetCursorPosCallback(window, mouse_move_callback);
	// 注册鼠标滚轮事件回调函数
	glfwSetScrollCallback(window, mouse_scroll_callback);
	// 鼠标捕获 停留在程序内
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 初始化GLEW 获取OpenGL函数
	glewExperimental = GL_TRUE; // 让glew获取所有拓展函数
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}

	// 设置视口参数
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Section1 加载模型数据 为了方便更换模型 我们从文件读取模型文件路径
	//第一个模型
	Model objModel1;
	std::ifstream modelPath("modelPath1.txt");
	if (!modelPath)
	{
		std::cerr << "Error::could not read model path file." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	std::string modelFilePath;
	std::getline(modelPath, modelFilePath);
	if (modelFilePath.empty())
	{
		std::cerr << "Error::model path empty." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	if (!objModel1.loadModel(modelFilePath))
	{
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	//第二个模型
	Model objModel2;
	std::ifstream modelPath2("modelPath2.txt");
	if (!modelPath)
	{
		std::cerr << "Error::could not read model path file." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	std::string modelFilePath2;
	std::getline(modelPath2, modelFilePath2);
	if (modelFilePath.empty())
	{
		std::cerr << "Error::model path empty." << std::endl;
		glfwTerminate();
		std::system("pause");
		return -1;
	}
	if (!objModel2.loadModel(modelFilePath2))
	{
		glfwTerminate();
		std::system("pause");
		return -1;
	}

	// 指定包围盒的顶点属性 位置
	GLfloat skyboxVertices[] = {
		// 背面
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, -1.0f, -1.0f,	// B
		1.0f, -1.0f, -1.0f,		// C
		1.0f, -1.0f, -1.0f,		// C
		1.0f, 1.0f, -1.0f,		// D
		-1.0f, 1.0f, -1.0f,		// A

		// 左侧面
		-1.0f, -1.0f, 1.0f,		// E
		-1.0f, -1.0f, -1.0f,	// B
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, 1.0f, -1.0f,		// A
		-1.0f, 1.0f, 1.0f,		// F
		-1.0f, -1.0f, 1.0f,		// E

		// 右侧面
		1.0f, -1.0f, -1.0f,		// C
		1.0f, -1.0f, 1.0f,		// G
		1.0f, 1.0f, 1.0f,		// H
		1.0f, 1.0f, 1.0f,		// H
		1.0f, 1.0f, -1.0f,		// D
		1.0f, -1.0f, -1.0f,		// C

		// 正面
		-1.0f, -1.0f, 1.0f,  // E
		-1.0f, 1.0f, 1.0f,  // F
		1.0f, 1.0f, 1.0f,  // H
		1.0f, 1.0f, 1.0f,  // H
		1.0f, -1.0f, 1.0f,  // G
		-1.0f, -1.0f, 1.0f,  // E

		// 顶面
		-1.0f, 1.0f, -1.0f,  // A
		1.0f, 1.0f, -1.0f,  // D
		1.0f, 1.0f, 1.0f,  // H
		1.0f, 1.0f, 1.0f,  // H
		-1.0f, 1.0f, 1.0f,  // F
		-1.0f, 1.0f, -1.0f,  // A

		// 底面
		-1.0f, -1.0f, -1.0f,  // B
		-1.0f, -1.0f, 1.0f,   // E
		1.0f, -1.0f, 1.0f,    // G
		1.0f, -1.0f, 1.0f,    // G
		1.0f, -1.0f, -1.0f,   // C
		-1.0f, -1.0f, -1.0f,  // B
	};


	// Section2 准备缓存对象
	GLuint cubeVAOId, cubeVBOId;
	glGenVertexArrays(1, &cubeVAOId);
	glGenBuffers(1, &cubeVBOId);
	glBindVertexArray(cubeVAOId);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBOId);

	// 顶点位置数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 顶点纹理数据
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	GLuint skyBoxVAOId, skyBoxVBOId;
	glGenVertexArrays(1, &skyBoxVAOId);
	glGenBuffers(1, &skyBoxVBOId);
	glBindVertexArray(skyBoxVAOId);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	// 顶点位置数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Section3 加载纹理

	std::vector<const char*> faces;
	faces.push_back("../../resources/skyboxes/sky/sky_rt.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_lf.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_up.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_dn.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_bk.jpg");
	faces.push_back("../../resources/skyboxes/sky/sky_ft.jpg");
	// 
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_rt.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_lf.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_up.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_dn.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_bk.tga");
	//faces.push_back("../../resources/skyboxes/urbansp/urbansp_ft.tga");
	GLuint skyBoxTextId = TextureHelper::loadCubeMapTexture(faces);

	// Section2 准备着色器程序
	Shader shadermodel1("model1.vertex", "model1.frag");
	Shader shadermodel2("model2.vertex", "model2.frag");

	Shader shader("scene.vertex", "scene.frag");
	Shader skyBoxShader("skybox.vertex", "skybox.frag");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	i = 2;
	// 开始渲染程序主循环
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents(); // 处理例如鼠标 键盘等事件
		do_movement(); // 根据用户操作情况 更新相机属性

		// 清除颜色缓冲区 重置为指定颜色
		glClearColor(0.18f, 0.04f, 0.14f, 1.0f);
		// 清除colorBuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 绘制model
		shadermodel1.use();
		//shadermodel2.use();
		//这一步有待考据用法   //这一步忽略




		//定义在左边的区域
		glViewport(0, 0, 800, 800);//注意，后面这两个参数是高度和宽度，而不是坐标

		// 绘制场景
		shader.use();
		glm::mat4 projection = glm::perspective(camera.mouse_zoom,
			(GLfloat)(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 100000.0f); // 投影矩阵
		glm::mat4 view = camera.getViewMatrix(); // 视变换矩阵
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // 适当调整位置
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型


		// 然后绘制包围盒  使包围盒原点位于观察者位置并使用缩放
		glDepthFunc(GL_LEQUAL); // 深度测试条件 小于等于
		skyBoxShader.use();
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "view"),
			1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(skyBoxVAOId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextId); // 注意绑定到CUBE_MAP
		glUniform1i(glGetUniformLocation(skyBoxShader.programId, "skybox"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);//顶点数组绘图



		// 这里填写场景绘制代码
		model = glm::translate(glm::mat4(), camera.position);
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view_mat = glm::translate(glm::mat4(), -camera.position);

		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // 适当调整城市的位置
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型2
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));
		objModel2.draw(shader); // 绘制物体2

		plane_pos.x = weizhi[i];
		plane_pos.y = weizhi[i + 1];
		plane_pos.z = weizhi[i + 2];
		if (i == zong - 1){ i = 0; }
		else { i += 3; }

	//	model = glm::translate(glm::mat4(), glm::vec3(plane_pos.x - weizhi[i - 3], plane_pos.y - weizhi[i - 2], plane_pos.z - weizhi[i - 1])); // 飞机移动

		model = glm::translate(glm::mat4(), glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z)); // 飞机移动
		

		//    model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f + plane_pos.y, 0.0f + plane_pos.z)); // 飞机移动备份

		//model = glm::rotate(model, plane_pos.y/100, glm::vec3(0.0f, 1.0f, 0.0f)); // 旋转

	//	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型1

		//view = glm::lookAt(glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z), glm::vec3(plane_pos.x+0., plane_pos.y, plane_pos.z), glm::vec3(0,0,1));

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		objModel1.draw(shader); // 绘制物体1


		
		//camera.position = plane_pos;   //摄像机与飞机同步
		// camera.yawAngle = plane_angle.x;

		glEnable(GL_BLEND);

		glBindVertexArray(0);
		glUseProgram(0);




		//定义在右边的区域
		glViewport(800, 0, 800, 800);//注意，后面这两个参数是高度和宽度，而不是坐标
		// 绘制场景
		shader.use();
		glm::mat4 projection1 = glm::perspective(camera.mouse_zoom,
			(GLfloat)(WINDOW_WIDTH) / WINDOW_HEIGHT, 1.0f, 10000.0f); // 投影矩阵
		glm::mat4 view1 = camera.getViewMatrix(); // 视变换矩阵
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "projection1"),
			1, GL_FALSE, glm::value_ptr(projection1));
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view1"),
			1, GL_FALSE, glm::value_ptr(view1));
		glm::mat4 model1;
		//model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, 0.0f)); // 适当调整位置
		//model1 = glm::scale(model1, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型


		// 然后绘制包围盒  使包围盒原点位于观察者位置并使用缩放
		glDepthFunc(GL_LEQUAL); // 深度测试条件 小于等于
		skyBoxShader.use();
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "projection1"),
			1, GL_FALSE, glm::value_ptr(projection1));
		glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "view1"),
			1, GL_FALSE, glm::value_ptr(view1));

		glBindVertexArray(skyBoxVAOId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextId); // 注意绑定到CUBE_MAP
		glUniform1i(glGetUniformLocation(skyBoxShader.programId, "skybox"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);//顶点数组绘图



		// 这里填写场景绘制代码
		//model1 = glm::translate(glm::mat4(), camera.position);
		//model1 = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		//glUniformMatrix4fv(glGetUniformLocation(skyBoxShader.programId, "model1"),
		//	1, GL_FALSE, glm::value_ptr(model1));

		//glm::mat4 view1_mat = glm::translate(glm::mat4(), -camera.position);


		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); // 适当调整城市的位置
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型2
		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));
		objModel2.draw(shader); // 绘制物体2



		shader.use();
		model = glm::translate(glm::mat4(), glm::vec3(plane1_pos.x, plane1_pos.y, plane1_pos.z)); // 飞机移动

		//model = glm::rotate(model, plane1_pos.y/100, glm::vec3(0.0f, 1.0f, 0.0f)); // 旋转

		//model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // 适当缩小模型1

		//view = glm::lookAt(glm::vec3(plane_pos.x, plane_pos.y, plane_pos.z), glm::vec3(plane_pos.x+0., plane_pos.y, plane_pos.z), glm::vec3(0,0,1));

		glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"),
			1, GL_FALSE, glm::value_ptr(model));

		plane1_pos.z += 0.5;
		plane1_pos.y += 0.3;
		cout << plane1_pos.z << " " << plane1_pos.y << "xxxxxx" 
			<< plane_pos.x << " " << plane_pos.y << " " << plane_pos.z << endl;
		//camera.position = plane_pos;   //摄像机与飞机同步
		// camera.yawAngle = plane_angle.x;
		objModel1.draw(shader); // 绘制物体1


		//glEnable(GL_BLEND);

		//	glBindVertexArray(0);
		//	glUseProgram(0);
		
		glfwSwapBuffers(window); // 交换缓存
		
	}


	//定义在右上角的区域
	//glViewport(400, 400, 400, 400);//注意，后面这两个参数是高度和宽度，而不是坐标

	//定义在左下角的区域
	//glViewport(0, 0, 400, 400);//注意，后面这两个参数是高度和宽度，而不是坐标

	//定义在左上角的区域
	//glViewport(0, 400, 400, 400);//注意，后面这两个参数是高度和宽度，而不是坐标	

	//定义在右下角的区域
	//glViewport(400, 0, 400, 400);//注意，后面这两个参数是高度和宽度，而不是坐标

	// 释放资源
	glfwTerminate();
	inf.close();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keyPressedStatus[key] = true;
		else if (action == GLFW_RELEASE)
			keyPressedStatus[key] = false;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE); // 关闭窗口
	}
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouseMove) // 首次鼠标移动
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseMove = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.handleMouseMove(xoffset, yoffset);
}
// 由相机辅助类处理鼠标滚轮控制
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.handleMouseScroll(yoffset);
}
// 由相机辅助类处理键盘控制
void do_movement()
{

	if (keyPressedStatus[GLFW_KEY_W])
		camera.handleKeyPress(FORWARD, deltaTime);
	if (keyPressedStatus[GLFW_KEY_S])
		camera.handleKeyPress(BACKWARD, deltaTime);
	if (keyPressedStatus[GLFW_KEY_A])
		camera.handleKeyPress(LEFT, deltaTime);
	if (keyPressedStatus[GLFW_KEY_D])
		camera.handleKeyPress(RIGHT, deltaTime);
}