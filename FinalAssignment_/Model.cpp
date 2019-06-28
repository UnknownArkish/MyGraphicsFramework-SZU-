#include "Model.h"

#include"ResourcesSystem.h"

Model::Model()
{
}

bool Model::Init(std::string modelFilePath, std::string modelName, Material material)
{
	// 尝试从资源系统中根据modelName读取对应的模型
	// 若资源系统没有该资源才会真正读取
	ModelResource* model = ResourcesSystem::GetInstance()->LoadModel(modelFilePath.c_str(), modelName);
	return this->Init(model, material);
}

bool Model::Init(ModelResource*  modelResource, Material material)
{
	if (!Node::Init()) {
		return false;
	}

	m_ModelResource = modelResource;
	m_Material = material;
	// 从ModelResource中加载数据
	if (m_ModelResource) {
		aiScene* scene = m_ModelResource->ModelScene;
		this->AddChildren(this->ProcessNode(scene->mRootNode, m_ModelResource));
	}
	else {
		std::cout << "Model Error!" << std::endl;
	}


	return true;
}

Model::~Model()
{
}

Model * Model::Create(ModelResource*  modelResource, Material material)
{
	Model* pRet = new(std::nothrow)Model();
	if (pRet && pRet->Init(modelResource, material)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

Model * Model::Create(std::string modelFilePath, std::string modelName, Material material)
{
	Model* pRet = new(std::nothrow)Model();
	if (pRet && pRet->Init(modelFilePath, modelName, material)) {
		return pRet;
	}
	delete pRet;
	pRet = nullptr;
	return pRet;
}

ModelNode* Model::ProcessNode(aiNode * node, ModelResource* modelResource)
{
	ModelNode* modelNode = ModelNode::Create(modelResource);

	const aiScene* scene = modelResource->ModelScene;
	// 遍历当前节点的网格（Mesh）
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ModelMesh* _mesh = ProcessMesh(mesh, scene);
		_mesh->SetMaterial(m_Material);
		modelNode->AddChildren(_mesh);
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ModelNode* modelNode_ = ProcessNode(node->mChildren[i], modelResource);
		modelNode->AddChildren(modelNode_);
	}
	return modelNode;
}

ModelMesh * Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// 处理网格
	// 1.获取所有顶点数据信息
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) {
			vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// 2.获取网格上面片索引信息
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	// 3.获取材质
	std::vector<Texture*> textures;
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 漫反射贴图
		std::vector<Texture*> ambientMaps = LoadMaterialTexture(material, aiTextureType_AMBIENT, "texture_ambient");
		textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		// 漫反射贴图
		std::vector<Texture*> diffuseMaps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 镜面反射贴图
		std::vector<Texture*> specularMaps = LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 法向量贴图
		std::vector<Texture*> normalMaps = LoadMaterialTexture(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 高度贴图
		std::vector<Texture*> heightMaps = LoadMaterialTexture(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	ModelMesh* modelMesh = ModelMesh::Create(vertices, indices, textures);
	return modelMesh;
}

std::vector<Texture*> Model::LoadMaterialTexture(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);

		std::string picPath = m_ModelResource->Directory + '/' + std::string(str.C_Str());

		// ResourcesSystem的机制已经保证了若有重复的str名字的贴图
		// 则直接返回已有的贴图
		Texture* texture = ResourcesSystem::GetInstance()->LoadTexture(picPath.c_str(), typeName.c_str(), str.C_Str());
		if (texture != nullptr)
			textures.push_back(texture);
	}
	return textures;
}
