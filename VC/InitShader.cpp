#include"include/Angel.h"

namespace Angel {

	// Create a NULL-terminated string by reading the provided file
	//帮助方法，读取指定文件里的所有内容，返回一个char*
	static char* readShaderSource(const char* shaderFile)
	{
		FILE *fp;
		fopen_s(&fp, shaderFile, "r");

		if (fp == NULL) { return NULL; }

		fseek(fp, 0L, SEEK_END);
		long size = ftell(fp);

		fseek(fp, 0L, SEEK_SET);
		char* buf = new char[size + 1];

		memset(buf, 0, size + 1);

		fread(buf, 1, size, fp);

		buf[size] = '\0';
		fclose(fp);

		return buf;
	}

	// Create a GLSL program object from vertex and fragment shader files
	//编译顶点着色器和片元着色器，若编译出错会打印错误信息并退出程序
	//返回一个OpenGL里表示program的GLuint类型数值
	GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
	{
		struct Shader {
			const char*  filename;
			GLenum       type;
			GLchar*      source;
		}  shaders[2] = {
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
		};

		//创建一个OpenGL Program
		GLuint program = glCreateProgram();
    
		//开始编译定点着色器和片元着色器
		for ( int i = 0; i < 2; ++i ) {
			Shader& s = shaders[i];

			//从文件中读取内容
			s.source = readShaderSource( s.filename );
			if ( shaders[i].source == NULL ) {
				std::cerr << "Failed to read " << s.filename << std::endl;
				exit( EXIT_FAILURE );
			}

			GLuint shader = glCreateShader( s.type );	//创建一个指定类型的着色器
			glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );	//绑定数据
			glCompileShader( shader );	//编译着色器

			GLint  compiled;	//临时保存编译结果
			glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );	//获取编译信息
			if ( !compiled ) {	//若编译错误则打印错误信息并退出程序
				std::cerr << s.filename << " failed to compile:" << std::endl;
				GLint  logSize;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
				char* logMsg = new char[logSize];
				glGetShaderInfoLog( shader, logSize, NULL, logMsg );
				std::cerr << logMsg << std::endl;
				delete [] logMsg;

				exit( EXIT_FAILURE );
			}
			delete [] s.source;

			glAttachShader( program, shader );	//将着色器绑定到Program
		}

		/* link  and error check */
		glLinkProgram(program);	//链接Program

		GLint  linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );	//获取链接信息
		if ( !linked ) {	//若链接错误同理
			std::cerr << "Shader program failed to link" << std::endl;
			GLint  logSize;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog( program, logSize, NULL, logMsg );
			std::cerr << logMsg << std::endl;
			delete [] logMsg;

			exit( EXIT_FAILURE );
		}

		/* use program object */
		glUseProgram(program);
		return program;
	}

}  // Close namespace Angel block
