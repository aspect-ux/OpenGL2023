#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#define ASSERT(x) if(!x) __debugbreak(); //underscore

//clear first,then invoke the operation you want to judge,finally assert to return any error code happened,and we can get where the error happened specifically both in file and path
#define GLCall(x) GLClearError();\
x; \
ASSERT(GLLogCall(#x,__FILE__,__LINE__)); 


static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function,const char* file,int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << ")"<<function<<file<<line<< std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1,VERTEX = 0,FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };

}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();// &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));//allocate on the stack
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compiled " <<
			(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow* window;

	/*Initialize the library*/
	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	/*
	float positions[] = {
		-0.5f,-0.5f, //bottom left
		0.5f,0.5f,   //top right
		0.5f,-0.5f,  //bottom right

		0.5f,0.5f,  //top right
		-0.5f,0.5f,  //top left
		-0.5f,-0.5f  //bottom left
	};*/

	float positions[] = {
		-0.5f,-0.5f, //bottom left
		0.5f,0.5f,   //top right
		0.5f,-0.5f,  //bottom right
		-0.5f,0.5f  //top left
		
	};

	unsigned int indices[] = { // This has to be unsigned
		0,1,2,
		0,1,3
	};
	


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW); //GL_STATIC_DRAW  data will not change or at all

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int IBO; //Indice buffer object
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	ShaderProgramSource source = ParseShader("Basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	GLCall(glUseProgram(shader));

	
	
	std::cout << source.VertexSource.length() << std::endl;
	std::cout<<"Vertex" << std::endl;
	std::cout << source.VertexSource<<std::endl;
	std::cout << source.FragmentSource << std::endl;
	 
	//GLCall(int location = glGetUniformLocation(shader, "u_Color"));//get uniform location to set value
	//std::cout << "location =" << location << std::endl;
	//ASSERT(location != -1);
	//glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
	
	/*Loop unitl the user close the window */
	while (!glfwWindowShouldClose(window))
	{
		/*render here*/
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawArrays(GL_ELEMENT_ARRAY_BUFFER,0,6);  draw arr

		//GLClearError();//if error's happening,block it
		
		GLCall(glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,nullptr));//draw by indices,6 indexs not vertex, remember to use glDrawElements

		//ASSERT(GLLogCall()); //assert

		/*SWAP FORNT AND BACK BUFFER*/
		glfwSwapBuffers(window);

		/*Poll for and process events*/
		glfwPollEvents();

	}

	//glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}

