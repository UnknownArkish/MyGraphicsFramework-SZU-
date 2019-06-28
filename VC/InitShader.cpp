#include"include/Angel.h"

namespace Angel {

	// Create a NULL-terminated string by reading the provided file
	//������������ȡָ���ļ�����������ݣ�����һ��char*
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
	//���붥����ɫ����ƬԪ��ɫ���������������ӡ������Ϣ���˳�����
	//����һ��OpenGL���ʾprogram��GLuint������ֵ
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

		//����һ��OpenGL Program
		GLuint program = glCreateProgram();
    
		//��ʼ���붨����ɫ����ƬԪ��ɫ��
		for ( int i = 0; i < 2; ++i ) {
			Shader& s = shaders[i];

			//���ļ��ж�ȡ����
			s.source = readShaderSource( s.filename );
			if ( shaders[i].source == NULL ) {
				std::cerr << "Failed to read " << s.filename << std::endl;
				exit( EXIT_FAILURE );
			}

			GLuint shader = glCreateShader( s.type );	//����һ��ָ�����͵���ɫ��
			glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );	//������
			glCompileShader( shader );	//������ɫ��

			GLint  compiled;	//��ʱ���������
			glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );	//��ȡ������Ϣ
			if ( !compiled ) {	//������������ӡ������Ϣ���˳�����
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

			glAttachShader( program, shader );	//����ɫ���󶨵�Program
		}

		/* link  and error check */
		glLinkProgram(program);	//����Program

		GLint  linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );	//��ȡ������Ϣ
		if ( !linked ) {	//�����Ӵ���ͬ��
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
