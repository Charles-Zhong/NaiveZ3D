#include <set>
#include <string>
using namespace std;

#include "Include\Mesh.h"
#include "Include\Model.h"

namespace
{
	struct record
	{
		int v, t, n;
		record() {}
		record(const record& r) :v(r.v), t(r.t), n(r.n) {}
		record& operator = (const record& r) { v = r.v; t = r.t; n = r.n; return *this; }
		string toString() { return to_string(v) + '/' + to_string(t) + '/' + to_string(n); }
	};
	bool operator == (const record& r1, const record& r2) { 
		return r1.v == r2.v && r1.t == r2.t && r1.n == r2.n; 
	}
	bool operator <(const record& r1, const record& r2) { 
		return 0; 
	}
}

namespace NaiveZ3D
{
	const std::vector<unsigned int>& Mesh::GenIndiceBuffer(const Model& model)const
	{
		if (!mIndiceCache_.empty())
		{
			return mIndiceCache_;
		}
		std::vector<unsigned int> indice;
		if (!model.UseTex())//��ʹ������
		{
			for (const auto& face : mFaceBuffer_)
			{
				const auto& ib = face.mVertexIndex_;
				if (ib.size() == 3)
				{
					//1��2��3
					indice.insert(indice.end(), ib.begin(), ib.end());
				}
				else if (ib.size() == 4)
				{
					//1��2��3
					indice.emplace_back(ib[0]);
					indice.emplace_back(ib[1]);
					indice.emplace_back(ib[2]);
					//1��3��4
					indice.emplace_back(ib[0]);
					indice.emplace_back(ib[2]);
					indice.emplace_back(ib[3]);
				}
			}
			mIndiceCache_ = move(indice);
		}
		else
		{
			BuildDataUseTex(model);
		}
		
		return mIndiceCache_;
	}
	const std::vector<Vector3>& Mesh::GenVertexBuffer(const Model& model)const
	{
		if (!model.UseTex())
		{
			return model.GetVertexBuffer();
		}

		if (!mVertexCache_.empty())
		{
			return mVertexCache_;
		}
		BuildDataUseTex(model);
		return mVertexCache_;
	}
	const std::vector<TextureCoord>& Mesh::GenTexCoordBuffer(const Model& model) const
	{
		if (!mTextureCoordCache_.empty())
		{
			return mTextureCoordCache_;
		}
		BuildDataUseTex(model);
		return mTextureCoordCache_;
	}
	void Mesh::BuildDataUseTex(const Model& model)const
	{
		//create indice
		std::vector<unsigned int> indice;
		for (const auto& face : mFaceBuffer_)
		{
			const auto& ib = face.mTextureIndex_;
			if (ib.size() == 3)
			{
				//1��2��3
				indice.insert(indice.end(), ib.begin(), ib.end());
			}
			else if (ib.size() == 4)
			{
				//1��2��3
				indice.emplace_back(ib[0]);
				indice.emplace_back(ib[1]);
				indice.emplace_back(ib[2]);
				//1��3��4
				indice.emplace_back(ib[0]);
				indice.emplace_back(ib[2]);
				indice.emplace_back(ib[3]);
			}
		}
		mIndiceCache_ = move(indice);

		//create vertex data
		std::vector<int> vi, ti, ni;
		record r, r1;
		set<string> added;
		std::vector<record> test;
		for (const auto& face : mFaceBuffer_)
		{
			const auto& vb = face.mVertexIndex_;
			const auto& tb = face.mTextureIndex_;
			const auto& nb = face.mNormalIndex_;
			
			//if (vb.size() == 3)
			//{
				int v, t, n;
				for (auto i = 0; i != vb.size(); ++i)
				{
					v = vb[i]; t = tb[i]; n = nb[i];
					r.v = v; r.t = t; r.n = n;
					test.push_back(r);
					auto rs = r.toString();
					if (added.count(rs) == 0)
					{
						added.insert(rs);
						vi.emplace_back(v);
						ti.emplace_back(t);
						ni.emplace_back(n);
					}
				}
			//}
			//else if (vb.size() == 4)
			//{

			//}
		}
		mVertexCache_.resize(vi.size());
		mTextureCoordCache_.resize(ti.size());
		mNormalCache_.resize(ni.size());
		const auto& vb = model.GetVertexBuffer();
		const auto& tb = model.GetTextureCoordBuffer();
		const auto& nb = model.GetNormalBuffer();
		for (auto i = 0; i != vi.size(); ++i)
		{
			mVertexCache_[i] = vb[vi[i]];
			mTextureCoordCache_[i] = tb[ti[i]];
			mNormalCache_[i] = nb[ni[i]];
		}
	}
}