#include "VertexLayout.hpp"

namespace UTE
{
	void VertexLayout::AddElementToLayout(EVertexDataType DataType, uint8_t Components)
	{
		VertexElement NewElement = VertexElement{ DataType, Components, GetVertexDataTypeSize(DataType) * Components, GetVertexStride()};
		mElementList.push_back(NewElement);

		RefreshVertexStride();
	}

	bool VertexLayout::SetElementAtIndex(uint32_t Index, EVertexDataType DataType, uint8_t Components)
	{
		//Check if specified index exists.
		if (!IsValidElement(Index))
		{
			return false;
		}

		uint32_t NewElementOffset = 0;
		GetOffsetAtIndex(Index, &NewElementOffset);

		uint32_t OldElementSize = mElementList[Index].Size;
		mElementList[Index] = VertexElement{ DataType, Components, GetVertexDataTypeSize(DataType) * Components, NewElementOffset };

		if (OldElementSize != mElementList[Index].Size)
		{
			RefreshElementOffsets();
			RefreshVertexStride();
		}

		return true;
	}

	bool VertexLayout::RemoveElementAtIndex(uint32_t Index)
	{
		//Check if specified index exists.
		if (!IsValidElement(Index))
		{
			return false;
		}

		mElementList.erase(mElementList.begin() + Index);

		RefreshElementOffsets();
		RefreshVertexStride();

		return true;
	}

	uint32_t VertexLayout::GetVertexStride() const
	{
		return mVertexStride;
	}

	bool VertexLayout::GetOffsetAtIndex(uint32_t Index, uint32_t* OutOffset) const
	{
		//Check if specified index exists.
		if (!IsValidElement(Index))
		{
			return false;
		}

		*OutOffset = mElementList[Index].Offset;
		return true;
	}

	uint32_t VertexLayout::GetNumElements() const
	{
		return static_cast<uint32_t>(mElementList.size());
	}

	const VertexElement& VertexLayout::GetElementAtIndex(uint32_t Index) const
	{
		return mElementList[Index];
	}

	bool VertexLayout::IsValidElement(uint32_t Index) const
	{
		return Index <= mElementList.size() - 1;
	}

	void VertexLayout::RefreshElementOffsets()
	{
		uint32_t CurrentOffset = 0;
		for (auto& CurrentElement : mElementList)
		{
			CurrentElement.Offset = CurrentOffset;
			CurrentOffset += CurrentElement.Size;
		}
	}

	void VertexLayout::RefreshVertexStride()
	{
		uint32_t CurrentSize = 0;
		for (auto& CurrentElement : mElementList)
		{
			CurrentSize += CurrentElement.Size;
		}

		mVertexStride = CurrentSize;
	}
}