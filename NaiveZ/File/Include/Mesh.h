#pragma once

#include <vector>
#include <map>

#include "../../Math/Include/Vector.h"
#include "../../Utils/Include/Constant.h"
#include "Face.h"

namespace NaiveZ3D
{
	class Model;

	class Mesh
	{
	public:
		void SetName(const std::string& name) { mName_ = name; }
		std::string GetName()const { return mName_; }

		void SetMtl(const std::string& mtl) { if(mMtlName_ == "")mMtlName_ = mtl; }
		std::string GetMtl()const { return mMtlName_; }

		void SetFaceBuffer(const std::vector<Face>& fb) { mFaceBuffer_ = fb; }
		void AddFace(const Face& f) { mFaceBuffer_.push_back(f); }
		const std::vector<Face>& GetFaceBuffer()const { return mFaceBuffer_; }
		size_t FaceBufferSize() const { return mFaceBuffer_.size(); }

		//�����ĸ������ǽ�Mesh�ڵ����ݱ任ΪOpengl�������������
		const std::vector<unsigned int>& GenIndiceBuffer(const Model&)const;
		const std::vector<Vector3>& GenVertexBuffer(const Model&)const;
		const std::vector<TextureCoord>& GenTexCoordBuffer(const Model&)const;
		const std::vector<Vector3>& GenNormalBuffer(const Model&)const;

	private:
		//����ʹ�����������һ��������ȫ�����ݣ�������
		void BuildDataUseTex(const Model& model)const;

	private:
		std::string mName_;
		std::string mMtlName_;
		std::vector<Face> mFaceBuffer_;

		mutable std::vector<Vector3> mVertexCache_;//����
		mutable std::vector<unsigned int> mIndiceCache_;//����
		mutable std::vector<TextureCoord> mTextureCoordCache_;//����
		mutable std::vector<Vector3> mNormalCache_;//����
	};
}