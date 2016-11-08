#pragma once

#include <string>
#include <map>
#include <memory>

#include "../../../Math/Include/Vector.h"
#include "Texture.h"

namespace NaiveZ3D
{
	using TexturePtr = std::unique_ptr<Texture>;

	struct MtlData
	{
		MtlData()
		{
			Clear();
		}
		void Clear()
		{
			useNs_ = false;
			useKa_ = false;
			useKd_ = false;
			useKs_ = false;
			useKe_ = false;
			useNi_ = false;
			used_ = false;
			useillum_ = false;
			newmtl_ = "";
			map_Kd_ = "";
			map_Bump_ = "";
			map_Ke_ = "";
			map_Ks_ = "";
			refl_ = "";
			KdTexPtr_.reset();
			BumpTexPtr_.reset();
			KeTexPtr_.reset();
			KsTexPtr_.reset();
			reflTexPtr_.reset();
		}
		std::string newmtl_;
		float Ns_;	//����ָ��exponent
		Vector3 Ka_;//��������
		Vector3 Kd_;//������
		Vector3 Ks_;//������
		Vector3 Ke_;
		float Ni_;	//����ֵ,����0.001��10֮�����ȡֵ����ȡֵΪ1.0������ͨ�������ʱ�򲻷���������
		float d_;	//����ָ��,ȡֵ��ΧΪ0.0~1.0��ȡֵΪ1.0��ʾ��ȫ��͸����ȡֵΪ0.0ʱ��ʾ��ȫ͸��
		int illum_;	//���ʵĹ���ģ��,illum����ɽ�0~10��Χ�ڵ����ֲ�����������������Ĺ���ģ��������ʾ
					//0 Color on and Ambient off
					//1 Color on and Ambient on
					//2 Highlight on
					//3 Reflection on and Ray trace on
					//4 Transparency: Glass on Reflection : Ray trace on
					//5 Reflection : Fresnel on and Ray trace on
					//6 Transparency : Refraction on Reflection : Fresnel off and Ray trace on
					//7 Transparency : Refraction on Reflection : Fresnel on and Ray trace on
					//8 Reflection on and Ray trace off
					//9 Transparency : Glass on Reflection : Ray trace off
					//10 Casts shadows onto invisible surfaces
		std::string map_Kd_;
		TexturePtr	KdTexPtr_;
		std::string map_Bump_;
		TexturePtr  BumpTexPtr_;
		std::string map_Ke_;
		TexturePtr	KeTexPtr_;
		std::string map_Ks_;
		TexturePtr	KsTexPtr_;
		std::string refl_;
		TexturePtr	reflTexPtr_;

		bool useNs_;
		bool useKa_;
		bool useKd_;
		bool useKs_;
		bool useKe_;
		bool useNi_;
		bool used_;
		bool useillum_;
	};

	class MTL{};

	class Material : public MTL
	{
	public:
		Material(){}
		Material(const std::string& name);

		void AddMtlData(MtlData&& data);

		std::string GetName()const { return mName_; }

	private:
		std::string mName_;//mtl name
		std::map<std::string, MtlData> mMtlDataMap_;
	};
}