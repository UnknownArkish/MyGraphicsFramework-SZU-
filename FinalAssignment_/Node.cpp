#include "Node.h"


Node::Node()
{
}


Node::~Node()
{
}

Node * Node::Create()
{
	Node* pRet = new (std::nothrow)Node();
	if (pRet && pRet->Init()) {
		return pRet;
	}
	delete pRet;
	return nullptr;
}

void Node::ToUpdate(float deltaTime)
{
	this->Update(deltaTime);
	std::vector<Node*> childrens = GetAllChilder();
	for (Node* children : childrens) {
		children->ToUpdate(deltaTime);
	}
}

void Node::Update(float deltaTime)
{
}

bool Node::Init()
{
	if (!Ref::Init()) {
		return false;
	}

	m_Parent = nullptr;
	m_Childrens.clear();

	// 初始化是否可见（默认可见）
	m_Visiable = true;
	m_Anchor = vec3(0.0f, 0.0f, 0.0f);
	// 初始化几何变换信息
	m_Position = m_GlobalPosition = vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = m_GlobalRotation = vec3(0.0f, 0.0f, 0.0f);
	m_Scale = m_GlobalScale = vec3(1.0f, 1.0f, 1.0f);

	// 初始化模型矩阵
	m_ModelMatrix_Global = m_ModelMatrix_Local = mat4(1.0f);
	m_InstanceMatrix = mat4(1.0f);

	// 初始化坐标系
	m_LocalX = m_GlobalX = vec3(1.0f, 0.0f, 0.0f);
	m_LocalY = m_GlobalY = vec3(0.0f, 1.0f, 0.0f);
	m_LocalZ = m_GlobalZ = vec3(0.0f, 0.0f, 1.0f);

	return true;
}


void Node::SetParent(Node * node)
{
	if (this->GetParent() == node)	return;
	this->m_Parent = node;

	// @TODO：在这里更新自己的Global信息
	this->UpdateLocalPosition();
	this->UpdateLocalRotation();
	this->UpdateLocalScale();

	//this->UpdateGlobalPosition();
	//this->UpdateGlobalRotation();
	//this->UpdateGlobalScale();

	this->UpdateModelMatrix();
	this->UpdateCoordinate();

	if (node != nullptr)
		node->m_Childrens.push_back(this);
}

Node * Node::GetParent()
{
	return m_Parent;
}

void Node::AddChildren(Node * node)
{
	// 如果节点为空，则不添加
	if (node == nullptr)	return;
	// 若节点已经在当前节点中，直接返回
	if (node->GetParent() == this)	return;
	// 从node的父节点去除node（若有）
	if (node->GetParent() != nullptr) {
		node->GetParent()->RemoveChildren(node);
	}

	node->SetParent(this);
}

void Node::RemoveChildren(Node * node)
{
	// 如果节点为空，则不做处理
	if (node == nullptr)	return;

	std::vector<Node*>::iterator it = std::find(m_Childrens.begin(), m_Childrens.end(), node);
	if (m_Childrens.end() != it) {
		m_Childrens.erase(it);
		node->SetParent(nullptr);
	}
}

std::vector<Node*> Node::GetAllChilder()
{
	return m_Childrens;
}

void Node::SetAnchor(vec3 anchor)
{
	this->m_Anchor = anchor;
	// 更新世界坐标
	this->UpdateGlobalPosition();
	// 更新模型矩阵
	this->UpdateModelMatrix();
}

void Node::ToTranslate(vec3 translation)
{
	this->SetPosition(this->GetPosition() + translation);
}

void Node::ToRotate(vec3 rotation)
{
	this->SetRotation(this->GetRotation() + rotation);
}

void Node::ToScale(vec3 scale)
{
	this->SetScale(this->GetScale() + scale);

}

void Node::SetPosition(vec3 position)
{
	m_Position = position;
	this->UpdateGlobalPosition();
	this->UpdateModelMatrix();
}

void Node::SetRotation(vec3 rotation)
{
	m_Rotation = rotation;
	this->UpdateGlobalRotation();
	this->UpdateModelMatrix();
	// 只有旋转才会改变坐标系朝向
	this->UpdateCoordinate();
}

void Node::SetScale(vec3 scale)
{
	//vec3 originScale = m_Scale;
	m_Scale = scale;
	this->UpdateGlobalScale();
	this->UpdateModelMatrix();

	//std::vector<Node*> temp = m_Childrens;
	//for (Node* children : temp) {
	//	children->ToScale(scale);
	//}
}

void Node::SetInstanceMatrix(mat4 matrix)
{
	m_InstanceMatrix = matrix;
}

bool Node::Render()
{
	return m_Visiable;
}

void Node::Display()
{
	this->Render();									// 绘制自身
	// 遍历子节点，进行子节点的绘制
	for (Node* node : m_Childrens) {
		node->Display();
	}
}

void Node::UpdateLocalPosition()
{
	if (m_Parent) {
		m_Position = m_Position - m_Parent->GetGlobalPosition();
	}
}

void Node::UpdateLocalRotation()
{
	if (m_Parent) {
		m_Rotation = m_Rotation - m_Parent->GetGlobalRotation();
	}
}

void Node::UpdateLocalScale()
{
	if (m_Parent) {
		vec3 parentScale = m_Parent->GetGlobalScale();
		vec3 scale = vec3(m_Scale.x / parentScale.x, m_Scale.y / parentScale.y, m_Scale.z / parentScale.z);
		m_Scale = scale;
	}
}

void Node::UpdateGlobalPosition()
{
	vec4 position = Translate(-m_Anchor) * vec4(m_Position, 1.0f);
	if (m_Parent) {
		vec3 parentPosition = m_Parent->GetGlobalPosition();
		position = Translate(parentPosition) * position;
	}
	m_GlobalPosition = vec3(position.x, position.y, position.z);

	std::vector<Node*> temp = m_Childrens;
	for (Node* children : temp) {
		children->UpdateGlobalPosition();
	}
}

void Node::UpdateGlobalRotation()
{
	if (m_Parent) {
		//vec3 parentRotation = m_Parent->GetGlobalRotation();
		//vec4 rotation = RotateX(parentRotation.x) * RotateY(parentRotation.y) * RotateZ(parentRotation.z) * vec4(m_Rotation, 0.0f);
		m_GlobalRotation = m_Parent->GetGlobalRotation() + m_Rotation;
	}
	else {
		m_GlobalRotation = m_Rotation;
	}
	std::vector<Node*> temp = m_Childrens;
	for (Node* children : temp) {
		children->UpdateGlobalRotation();
	}
}

void Node::UpdateGlobalScale()
{
	if (m_Parent) {
		//vec3 parentScale = m_Parent->GetGlobalScale();
		//vec4 scale = Scale(parentScale) * vec4(m_Scale, 0.0f);
		//m_GlobalScale = vec3(scale.x, scale.y, scale.z);
		vec3 parentScale = m_Parent->GetGlobalScale();
		m_GlobalScale = vec3(m_Scale.x * parentScale.x, m_Scale.y * parentScale.y, m_Scale.z * parentScale.z);
	}
	else {
		m_GlobalScale = m_Scale;
	}
	std::vector<Node*> temp = m_Childrens;
	for (Node* children : temp) {
		children->UpdateGlobalScale();
	}
}


void Node::UpdateModelMatrix()
{
	m_ModelMatrix_Local =
		Translate(m_Position) *
		RotateX(m_Rotation.x)*RotateY(m_Rotation.y) * RotateZ(m_Rotation.z) *
		Scale(m_Scale) * Translate(-m_Anchor);

	mat4 parentModelMatrix = m_Parent == nullptr ? mat4(1.0) : m_Parent->GetGlobalMatrix();
	//mat4 parentModelMatrix = mat4(1.0f);
	//if (m_Parent) {
	//	vec3 parentRotation = m_Parent->GetGlobalRotation();
	//	parentModelMatrix = Translate(m_Parent->GetGlobalPosition()) * 
	//		RotateX(parentRotation.x) *RotateY(parentRotation.y) *RotateZ(parentRotation.z);
	//}
	m_ModelMatrix_Global = parentModelMatrix * m_ModelMatrix_Local;

	std::vector<Node*> temp = m_Childrens;
	for (Node* children : temp) {
		children->UpdateModelMatrix();
	}
}

void Node::UpdateCoordinate()
{
	this->UpdateLocalCoordinate();
	this->UpdateGlobalCoordinate();
}

void Node::UpdateLocalCoordinate()
{
	vec4 X = RotateX(m_Rotation.x) * RotateY(m_Rotation.y) * RotateZ(m_Rotation.z) * vec4(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 Y = RotateX(m_Rotation.x) * RotateY(m_Rotation.y) * RotateZ(m_Rotation.z) * vec4(0.0f, 1.0f, 0.0f, 0.0f);
	vec4 Z = RotateX(m_Rotation.x) * RotateY(m_Rotation.y) * RotateZ(m_Rotation.z) * vec4(0.0f, 0.0f, 1.0f, 0.0f);

	m_LocalX = normalize(vec3(X.x, X.y, X.z));
	m_LocalY = normalize(vec3(Y.x, Y.y, Y.z));
	m_LocalZ = normalize(vec3(Z.x, Z.y, Z.z));
	//m_LocalX = normalize(cross(vec3(0.0f, 1.0f, 0.0f), m_LocalZ));
	//m_LocalY = normalize(cross(m_LocalZ, m_LocalX));
}

void Node::UpdateGlobalCoordinate()
{
	if (m_Parent) {
		//vec3 parentRotation = m_Parent->GetRotation();
		vec4 X = RotateX(m_GlobalRotation.x) * RotateY(m_GlobalRotation.y) * RotateZ(m_GlobalRotation.z) * vec4(1.0f, 0.0f, 0.0f, 0.0f);
		vec4 Y = RotateX(m_GlobalRotation.x) * RotateY(m_GlobalRotation.y) * RotateZ(m_GlobalRotation.z) * vec4(0.0f, 1.0f, 0.0f, 0.0f);
		vec4 Z = RotateX(m_GlobalRotation.x) * RotateY(m_GlobalRotation.y) * RotateZ(m_GlobalRotation.z) * vec4(0.0f, 0.0f, 1.0f, 0.0f);

		m_GlobalX = normalize(vec3(X.x, X.y, X.z));
		m_GlobalY = normalize(vec3(Y.x, Y.y, Y.z));
		m_GlobalZ = normalize(vec3(Z.x, Z.y, Z.z));

		//vec4 Z = RotateX(parentRotation.x) * RotateY(parentRotation.y) * RotateZ(parentRotation.z) * vec4(m_LocalZ, 0.0f);
		//m_GlobalX = normalize(vec3(Z.x, Z.y, Z.z));
		//m_GlobalZ = normalize(cross(vec3(0.0f, 1.0f, 0.0f), m_GlobalX));
		//m_GlobalY = normalize(cross(m_GlobalZ, m_GlobalX));
	}
	else {
		m_GlobalX = m_LocalX;
		m_GlobalY = m_LocalY;
		m_GlobalZ = m_LocalZ;
	}
	std::vector<Node*> temp = m_Childrens;
	for (Node* children : temp) {
		children->UpdateGlobalCoordinate();
	}
}
